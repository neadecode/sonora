#include "pch.h"
#include "sonora.h"

//Attach the winmm dynamic library to the executable.
static FARPROC GetProc(const char* funcName) {
	static HMODULE hWinmm = LoadLibrary(L"winmm.dll");
	if (!hWinmm) return nullptr;
	return GetProcAddress(hWinmm, funcName);
}
//UINT waveOutGetNumDevs(void);
auto OutGetNumDevs = (UINT(WINAPI*)())GetProc("waveOutGetNumDevs");
//MMRESULT waveOutGetDevCapsWW(_In_ UINT_PTR uDeviceID, _Out_ LPWAVEOUTCAPSW pwoc, _In_ UINT cbwoc);
auto OutGetDevCapsW = (MMRESULT(WINAPI*)(UINT_PTR, WAVEOUTCAPS*, UINT))GetProc("waveOutGetDevCapsW");
//MMRESULT waveOutOpen(_Out_opt_ LPHWAVEOUT phwo, _In_ UINT uDeviceID, _In_ LPCWAVEFORMATEX pwfx, _In_opt_ DWORD_PTR dwCallback, _In_opt_ DWORD_PTR dwInstance, _In_ DWORD fdwOpen);
auto OutOpen = (MMRESULT(WINAPI*)(LPHWAVEOUT, UINT, LPCWAVEFORMATEX, DWORD_PTR, DWORD_PTR, DWORD))GetProc("waveOutOpen");

//Monolithic format. TODO: RESAMPLE INCOMING WAVESTREAMS
static constexpr uint32_t SAMPLE_RATE = 44100;
static constexpr uint16_t CHANNELS = 2;
static constexpr uint16_t BIT_DEPTH = 16;
static constexpr uint16_t BLOCK_ALIGN = (CHANNELS * BIT_DEPTH) / 8;
static constexpr uint32_t AVG_BYTES_PER_SEC = BLOCK_ALIGN * SAMPLE_RATE;
	
//TODO: Think if it is modifyible or not
static EngineFormat engine{
	SONORA_WAVE_PCM,
	CHANNELS,
	SAMPLE_RATE,
	BIT_DEPTH,
	BLOCK_ALIGN,
	AVG_BYTES_PER_SEC
};
static WAVEFORMATEX wfx{
	engine.formatTag,
	engine.channels,
	engine.samplesPerSec,
	engine.avgBytesPerSec,
	engine.blockAlign,
	engine.bitsPerSample,
	0
};
//[DEVICE ID, DEVICE]
static std::unordered_map<UINT, OutDevice> outs;

//------------------------------------
//------ C DEFINITIONS ---------------
//------------------------------------

//TODO: VOID FREE NAME LIST
const wchar_t** getOutDeviceNameList(uint32_t* outNumDevs) {
	WAVEOUTCAPS woc;  //Get the capabilites of the audio devices
	*outNumDevs = OutGetNumDevs();

	//We malloc for the amount of pointers to const char* in the current device.
	const wchar_t** arr = (const wchar_t**)malloc(
		static_cast<size_t>(*outNumDevs) * sizeof(wchar_t*));
	if (!arr) return nullptr;

	//For every device specified by its index, 
	//we override the information we retrieved to waveOutCaps
	for (size_t idx{}; idx < *outNumDevs; ++idx) {
		if (OutGetDevCapsW(static_cast<UINT_PTR>(idx), &woc, sizeof(WAVEOUTCAPS))
			== MMSYSERR_NOERROR) {
			const wchar_t* str = _wcsdup(woc.szPname);
			arr[idx] = str; // Heap duplicate of wstring
		}
		else {
			arr[idx] = nullptr;
		}
	}
	return arr;
}
const wchar_t* getOutDeviceNameByIdx(uint32_t index) {
	UINT numDevs = OutGetNumDevs();
	const UINT sane_i = (index >= numDevs) ? (numDevs - 1) : index;

	WAVEOUTCAPS woc;
	if (OutGetDevCapsW(static_cast<UINT_PTR>(index), &woc, sizeof(WAVEOUTCAPS))
		== MMSYSERR_NOERROR) {
		return woc.szPname;
	}
	return nullptr;
}

//------------------------------------
//------ C++ DEFINITIONS -------------
//------------------------------------
namespace sonora {
	std::vector<std::wstring> getOutDeviceNameList() {
		if (!OutGetNumDevs) return {};

		const UINT numDevs = OutGetNumDevs();
		if (numDevs == 0) return {}; //Early return if no audio devices.

		std::vector<std::wstring> names;
		names.reserve(static_cast<size_t>(numDevs));

		for (UINT i{}; i < numDevs; ++i) {
			WAVEOUTCAPS woc;
			if (OutGetDevCapsW(static_cast<UINT_PTR>(i), &woc, sizeof(WAVEOUTCAPS))
				== MMSYSERR_NOERROR) 
				names.emplace_back(woc.szPname);
		}
		return names;
	} 
	std::optional<std::wstring> getOutDeviceNameById(uint32_t index) {
		if (!OutGetNumDevs) return std::nullopt;

		const UINT numDevs = OutGetNumDevs();
		if (numDevs == 0) return std::nullopt;
		const UINT sane_i = (index >= numDevs) ? (numDevs - 1) : index;

		WAVEOUTCAPS woc;
		if (OutGetDevCapsW(static_cast<UINT_PTR>(sane_i), &woc, sizeof(WAVEOUTCAPS))
			== MMSYSERR_NOERROR) {
			return std::wstring(woc.szPname);
		}
		return std::nullopt;
	}

	OutDevice *newOutDevice() {
		auto it = outs.find(WAVE_MAPPER);
		if (it != outs.end()) { return &it->second; }
		//std::pair
		auto result = outs.emplace(WAVE_MAPPER, OutDevice{});
		result.first->second.id = static_cast<UINT>(WAVE_MAPPER);
		return &result.first->second; 
	}

	OutDevice *newOutDevice(uint32_t index) {
		if (!OutGetNumDevs) return nullptr;  
		const UINT numDevs = OutGetNumDevs();
		if (numDevs == 0) return nullptr;

		auto it = outs.find(index);
		if (it != outs.end()) return &it->second;

		const UINT sane_i = (index >= numDevs) ? (numDevs - 1) : index;
		auto result = outs.emplace(sane_i, OutDevice{});
		result.first->second.id = sane_i;
		return &result.first->second;
	}

	bool initDevice(OutDevice *outDevice) { 
		if (!OutOpen) return false;
		if (outDevice->isOpen) return false;

		HWAVEOUT hTemp = nullptr;
		MMRESULT result = OutOpen(&hTemp, outDevice->id, &wfx, 0, 0, CALLBACK_NULL);

		if (result == MMSYSERR_NOERROR) {
			outDevice->handle = static_cast<void*>(hTemp);
			outDevice->isOpen = true;
			return true;
		}

		return false;
	}
}