#include "../../include/sonora/sonora.h"
#include "win_utils.h"

const wchar_t* *getOutDeviceNameList(uint64_t* numberOfDevices) {
	WAVEOUTCAPS woc;
	*numberOfDevices = waveOutGetNumDevs();
	if (!numberOfDevices || *numberOfDevices == 0) return NULL;

	const wchar_t* *arr = malloc((size_t)(*numberOfDevices) * sizeof(wchar_t*));
	if (!arr) return NULL;

	for (uint64_t idx = 0; idx < *numberOfDevices; ++idx) {
		if (waveOutGetDevCapsw((uint64_t)(idx), &woc, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR) {
			//This is done becaause on every call, names might change
			const wchar_t* str = _wcsdup(woc.szPname); //ptr to a str duplicate on the heap
			arr[idx] = str; 
		}
		else { arr[idx] = NULL; }
	}
	return arr;
}

void freeOutDeviceNameList(const wchar_t* *list, uint64_t numberOfDevices) {
	if (!list) return;

	for (uint64_t idx = 0; idx < numberOfDevices; ++idx) {
		free((void*)list[idx]);
	}
	free((void*)list);
}

const wchar_t* getOutDeviceNameByIdx(uint64_t index) {
	uint32_t numDevs = waveOutGetNumDevs();
	const uint32_t sane_i = (index >= numDevs) ? (numDevs - 1) : index;

	WAVEOUTCAPS woc;
	if (waveOutGetDevCapsW((uint32_t)(index), &woc, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR) {
		return woc.szPname;
	}
	return nullptr;
}