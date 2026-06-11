#include "pch.h"
#include "sonora.h"

//Attach the winmm dynamic library to the executable.
static FARPROC GetProc(const char* funcName) {
	static HMODULE hWinmm = LoadLibrary(L"winmm.dll");
	if (!hWinmm) return nullptr;
	return GetProcAddress(hWinmm, funcName);
}
//UINT waveOutGetNumDevs(void);
auto GetNumDevs = (UINT(WINAPI*)())GetProc("waveOutGetNumDevs");
//MMRESULT waveOutGetDevCapsWW(_In_ UINT_PTR uDeviceID, _Out_ LPWAVEOUTCAPSW pwoc, _In_ UINT cbwoc);
auto GetDevCapsW = (MMRESULT(WINAPI*)(UINT_PTR, WAVEOUTCAPS*, UINT))GetProc("waveOutGetDevCapsW");


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
	*outNumDevs = GetNumDevs();

	//We malloc for the amount of pointers to const char* in the current device.
	const wchar_t** arr = (const wchar_t**)malloc(
		static_cast<size_t>(*outNumDevs) * sizeof(wchar_t*));
	if (!arr) return nullptr;

	//For every device specified by its index, 
	//we override the information we retrieved to waveOutCaps
	for (size_t idx{}; idx < *outNumDevs; ++idx) {
		if (GetDevCapsW(static_cast<UINT_PTR>(idx), &woc, sizeof(WAVEOUTCAPS))
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
	UINT numDevs = GetNumDevs();
	const UINT sane_i = (index >= numDevs) ? (numDevs - 1) : index;

	WAVEOUTCAPS woc;
	if (GetDevCapsW(static_cast<UINT_PTR>(index), &woc, sizeof(WAVEOUTCAPS))
		== MMSYSERR_NOERROR) {
		return woc.szPname;
	}
	return nullptr;
}

//------------------------------------
//------ C++ DEFINITIONS -------------
//------------------------------------
namespace sonora {
	std::vector<std::wstring> getOutDeviceNameList()
	{
		const UINT numDevs = GetNumDevs();
		if (numDevs == 0) return {}; //Early return if no audio devices.

		std::vector<std::wstring> names;
		names.reserve(static_cast<size_t>(numDevs));

		for (UINT i{}; i < numDevs; ++i) {
			WAVEOUTCAPS woc;
			if (GetDevCapsW(static_cast<UINT_PTR>(i), &woc, sizeof(WAVEOUTCAPS))
				== MMSYSERR_NOERROR) 
				names.emplace_back(woc.szPname);
		}
		return names;
	} 
	std::optional<std::wstring> getOutDeviceNameByIdx(uint32_t index) {
		const UINT numDevs = GetNumDevs();
		if (numDevs == 0) return std::nullopt;

		const UINT sane_i = (index >= numDevs) ? (numDevs - 1) : index;

		WAVEOUTCAPS woc;
		if (GetDevCapsW(static_cast<UINT_PTR>(sane_i), &woc, sizeof(WAVEOUTCAPS))
			== MMSYSERR_NOERROR) {
			return std::wstring(woc.szPname);
		}
		return std::nullopt;
	}

	OutDevice& newOutDevice() {
		auto it = outs.find(WAVE_MAPPER);
		if (it != outs.end()) {
			return it->second;
		}
		//std::pair
		auto result = outs.emplace(WAVE_MAPPER, OutDevice{});
		return result.first->second; 
	}

	OutDevice& newOutDevice(uint32_t index) {
		auto it = outs.find(index);
		if (it != outs.end()) {
			return it->second;
		}

		const UINT numDevs = GetNumDevs();
		uint32_t sane_i = (index >= GetNumDevs()) ? (GetNumDevs() - 1) : index;

		//std::pair
		auto result = outs.emplace(index, OutDevice{});
		return result.first->second;
	}
}