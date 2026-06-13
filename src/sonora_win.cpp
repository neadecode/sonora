#include "pch.h"

#include "../include/sonora/sonora.h"
#include "s_win_utils.h"

bool prepareBlock(OutDevice* device, LPSTR block, DWORD size);
LPSTR loadAudioBlock(const char* filename, DWORD* blockSize);

//------------------------------------
//------ C DEFINITIONS ---------------
//------------------------------------

//TODO: FREE NAME LIST
//TODO: C IMPLEMENTATIONS
//TODO: MAN DO WE NEED SOME SORT OF ERROR MESSAGES??
const wchar_t** getOutDeviceNameList(uint32_t* outNumDevs) {
	WAVEOUTCAPS woc;  //Get the capabilites of the audio devices
	*outNumDevs = winmm.OutGetNumDevs();

	//We malloc for the amount of pointers to const char* in the current device.
	const wchar_t** arr = (const wchar_t**)malloc(
		static_cast<size_t>(*outNumDevs) * sizeof(wchar_t*));
	if (!arr) return nullptr;

	//For every device specified by its index, 
	//we override the information we retrieved to waveOutCaps
	for (size_t idx{}; idx < *outNumDevs; ++idx) {
		if (winmm.OutGetDevCapsW(static_cast<UINT_PTR>(idx), &woc, sizeof(WAVEOUTCAPS))
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
	UINT numDevs = winmm.OutGetNumDevs();
	const UINT sane_i = (index >= numDevs) ? (numDevs - 1) : index;

	WAVEOUTCAPS woc;
	if (winmm.OutGetDevCapsW(static_cast<UINT_PTR>(index), &woc, sizeof(WAVEOUTCAPS))
		
		== MMSYSERR_NOERROR) {
		return woc.szPname;
	}
	return nullptr;
}

//------------------------------------
//------ C++ DEFINITIONS -------------
//------------------------------------

namespace sonora {
	Format* newFormat(uint16_t formatTag, uint16_t channels, uint32_t sampleRate, uint16_t bitsPerSample) 
	{
		uint16_t blockAlign = static_cast<uint16_t>(channels * bitsPerSample / 8);
		return new Format{formatTag,
			channels,
			sampleRate,
			static_cast<uint32_t>(blockAlign) * sampleRate,
			blockAlign,
			bitsPerSample,
			0 //cbSize = 0
		};
	}

	Format* newFormat(uint32_t format) {
		//Format cannot be higher than SONORA_FORMAT_96S16 98kHz Stereo 16bits
		format = std::clamp(format, static_cast<uint32_t>(0x00000001), static_cast<uint32_t>(0x00080000));
		switch (format) {
		case SONORA_WAVE_PCM_1M08:  return newFormat(_1M08);
		case SONORA_WAVE_PCM_1S08:  return newFormat(_1S08);
		case SONORA_WAVE_PCM_1M16:  return newFormat(_1M16);
		case SONORA_WAVE_PCM_1S16:  return newFormat(_1S16);
		case SONORA_WAVE_PCM_2M08:  return newFormat(_2M08);
		case SONORA_WAVE_PCM_2S08:  return newFormat(_2S08);
		case SONORA_WAVE_PCM_2M16:  return newFormat(_2M16);
		case SONORA_WAVE_PCM_2S16:  return newFormat(_2S16);
		case SONORA_WAVE_PCM_4M08:  return newFormat(_4M08);
		case SONORA_WAVE_PCM_4S08:  return newFormat(_4S08);
		case SONORA_WAVE_PCM_4M16:  return newFormat(_4M16);
		case SONORA_WAVE_PCM_4S16:  return newFormat(_4S16);
		case SONORA_WAVE_PCM_48M08: return newFormat(_48M08);
		case SONORA_WAVE_PCM_48S08: return newFormat(_48S08);
		case SONORA_WAVE_PCM_48M16: return newFormat(_48M16);
		case SONORA_WAVE_PCM_48S16: return newFormat(_48S16);
		case SONORA_WAVE_PCM_96M08: return newFormat(_96M08);
		case SONORA_WAVE_PCM_96S08: return newFormat(_96S08);
		case SONORA_WAVE_PCM_96M16: return newFormat(_96M16);
		case SONORA_WAVE_PCM_96S16: return newFormat(_96S16);
		default: return nullptr;
		}
	}
	
	Format* newFormat() { return newFormat(SONORA_WAVE_PCM_4S16); }

	std::vector<std::wstring> getOutDeviceNameList() {
		if (!checkWinApi()) return {};

		const UINT numDevs = winmm.OutGetNumDevs();
		if (numDevs == 0) return {};

		std::vector<std::wstring> names;
		names.reserve(static_cast<size_t>(numDevs));

		for (UINT i{}; i < numDevs; ++i) {
			WAVEOUTCAPS woc;
			if (winmm.OutGetDevCapsW(static_cast<UINT_PTR>(i), &woc, sizeof(WAVEOUTCAPS))
				== MMSYSERR_NOERROR) 
			names.emplace_back(woc.szPname);
		}
		return names;
	} 

	std::optional<std::wstring> getOutDeviceNameById(uint32_t index) {
		if (!checkWinApi()) return std::nullopt;

		if (index == WAVE_MAPPER) return std::wstring(L"Default Device");

		const UINT numDevs = winmm.OutGetNumDevs();
		if (numDevs == 0) return std::nullopt;

		const UINT sane_i = std::clamp(index, 0U, numDevs);

		WAVEOUTCAPS woc;
		if (winmm.OutGetDevCapsW(static_cast<UINT_PTR>(sane_i), &woc, sizeof(WAVEOUTCAPS))
			== MMSYSERR_NOERROR) {
			return std::wstring(woc.szPname);
		}
		return std::nullopt;
	}

	OutDevice *newOutDevice() {
		return new OutDevice{ Handle{}, false, WAVE_MAPPER };
	}

	OutDevice *newOutDevice(uint32_t index) {
		if (!checkWinApi()) return nullptr;

		const UINT numDevs = winmm.OutGetNumDevs();
		if (numDevs == 0) return nullptr;

		const UINT sane_i = std::clamp(index, 0U, numDevs - 1);

		return new OutDevice{Handle{}, false, sane_i};
	}
	
	bool openOutDevice(Format* format, OutDevice* outDevice) {
		if (!checkWinApi()) return false;
		if (format == nullptr || outDevice == nullptr) return false;
		
		HWAVEOUT hwo = nullptr;
		MMRESULT result = winmm.OutOpen(&hwo, outDevice->id, (LPCWAVEFORMATEX)format, 0, 0, CALLBACK_NULL);

		if (result == MMSYSERR_NOERROR) {
			outDevice->handle = static_cast<void*>(hwo);
			outDevice->isOpen = true;
			return true;
		}
		return false;
	}

	bool closeDevice(DevicePtr device) {
		return std::visit([](auto* d) -> bool {
			if (d == nullptr) return false;
			using T = std::decay_t<decltype(d)>;

			if constexpr (std::is_same_v<T, OutDevice*>)
			{ winmm.OutClose(static_cast<HWAVEOUT>(d->handle)); };
			delete d;
			return true;
			},
			device);
	}
	bool closeFormat(Format* format) {
		if (format == nullptr) return false;
		delete format;
		return true;
	}

	bool playSound(Format* format, OutDevice* device, char const* path)
	{
		LPSTR block;
		DWORD blockSize;	

		if ((block = loadAudioBlock(path, &blockSize)) == NULL) {
			fprintf(stderr, "Unable to load file\n");
			ExitProcess(1);
		}
		prepareBlock(device, block, blockSize);
	}
}

bool prepareBlock(OutDevice* device, LPSTR block, DWORD size) {
	WAVEHDR header{ block, size };
	winmm.OutPrepareHeader((HWAVEOUT)device->handle, &header, sizeof(WAVEHDR));
	winmm.OutWrite((HWAVEOUT)device->handle, &header, sizeof(WAVEHDR));
	while (winmm.OutUnprepareHeader((HWAVEOUT)device->handle, &header, sizeof(WAVEHDR)) == WAVERR_STILLPLAYING) {
		Sleep(100);
	}
	return true;
}

LPSTR loadAudioBlock(const char* filename, DWORD* blockSize)
{
	std::ifstream file(filename, std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();

	file.seekg(0, std::ios::beg);
	char* block = new char[size];

	if (size > 0) file.read(block, size);
	file.close();

	*blockSize = size;
	return (LPSTR)block;
}