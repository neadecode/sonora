#include "pch.h"
#include "sonora.h"

namespace {
	std::vector<PCWSTR> device_arr; //vector<const wchar_t*>
	struct OnFreeDll {
		~OnFreeDll() {
			free_contents(device_arr);
			device_arr.clear();
		}
	};
	OnFreeDll on_free_dll;
};

void free_contents(std::vector<const wchar_t*>& v) {
	for (auto ptr : v) 
		{ if (ptr != nullptr) free((void*)(ptr)); }
}

AUDIODLL_API int getAudioDeviceNames(PCWSTR* out_csarr)
{
	WAVEOUTCAPS woc;
	ULONG iNumDevs, i;
	iNumDevs = waveOutGetNumDevs();

	if (out_csarr == nullptr) {
		free_contents(device_arr);
		device_arr.assign(static_cast<size_t>(iNumDevs), nullptr);

		for (i = 0; i < iNumDevs; ++i) {
			if (waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR) {
				device_arr[i] = _wcsdup(woc.szPname); // Heap duplicate;
			}
		}
		return static_cast<int>(iNumDevs);
	}

	for (i = 0; i < iNumDevs; ++i) out_csarr[i] = device_arr[i];
	return static_cast<int>(iNumDevs);
}
