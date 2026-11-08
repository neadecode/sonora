#include "../../include/sonora/sonora.h"
#include "win_utils.h"

Format* newFormat(uint16_t formatTag, uint16_t channels, uint32_t sampleRate, uint16_t bitsPerSample) {
    Format* format = malloc(sizeof(Format));
    if (!format) return NULL;

    uint16_t blockAlign = (uint16_t)(channels * bitsPerSample / 8);
    
    format->formatTag = formatTag;
    format->channels = channels;
    format->sampleRate = sampleRate; //Frequency
    format->blockAlign = blockAlign;
    format->avgBytesPerSec = (uint32_t)(blockAlign) * sampleRate;
    format->bitsPerSample = bitsPerSample;
    format->cbSize = 0;

    return format;
}

SONORARESULT closeFormat(Format* format) {
    if (!format) return SONORA_INVALID_PARAMETER; 
    free(format);
    return SONORA_SUCCESS;
}

const wchar_t* getOutDeviceNameByIdx(uint64_t index) {
    uint32_t numDevs = waveOutGetNumDevs();
    if (numDevs == 0 || index >= numDevs) return NULL;

    WAVEOUTCAPS woc;
    if (waveOutGetDevCapsW((UINT)index, (LPWAVEOUTCAPSW)&woc, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR) {
        return _wcsdup((const wchar_t*)woc.szPname); // Seguro de retornar al heap
    }
    return NULL;
}

const wchar_t** getOutDeviceNameList(uint64_t* numberOfDevices) {
    if (!numberOfDevices) return NULL;

    *numberOfDevices = waveOutGetNumDevs();
    if (*numberOfDevices == 0) return NULL;

    const wchar_t** arr = malloc((size_t)(*numberOfDevices) * sizeof(wchar_t*));
    if (!arr) return NULL;

    WAVEOUTCAPS woc;
    for (uint64_t idx = 0; idx < *numberOfDevices; ++idx) {
        if (waveOutGetDevCapsW((UINT)idx, (LPWAVEOUTCAPSW)&woc, sizeof(WAVEOUTCAPS)) == MMSYSERR_NOERROR) {
            arr[idx] = _wcsdup((const wchar_t*)woc.szPname); 
        } else { 
            arr[idx] = NULL; 
        }
    }
    return arr;
}


SONORARESULT freeOutDeviceNameList(const wchar_t** list, uint64_t numberOfDevices) {
    if (!list) return SONORA_INVALID_PARAMETER;

    for (uint64_t idx = 0; idx < numberOfDevices; ++idx) {
        if (list[idx] != NULL) {
            free((void*)list[idx]);
        }
    } 
    free((void*)list);
    return SONORA_SUCCESS;
}

OutDevice* newOutDeviceIdx(uint32_t index) {
    uint32_t numDevs = waveOutGetNumDevs();
    if (numDevs == 0 || index >= numDevs) return NULL;
    
    OutDevice* out = malloc(sizeof(OutDevice));
    if (!out) return NULL;

    out->handle = NULL; // Initialize to NULL until opened
    out->id = index;
    out->isOpen = false;

    return out;
}

SONORARESULT openOutDevice(Format* format, OutDevice* outDevice) {
    if (format == NULL || outDevice == NULL) {
        return SONORA_INVALID_PARAMETER;
    }

    MMRESULT result = waveOutOpen(
        (HWAVEOUT*)&outDevice->handle,
        (UINT)outDevice->id,
        (LPCWAVEFORMATEX)format,
        0,
        0,
        CALLBACK_NULL);

    
    if (result == MMSYSERR_NOERROR) {
        outDevice->isOpen = true;
        return SONORA_SUCCESS;
    }
    
    return SONORA_UNKNOWN_ERROR;
}

SONORARESULT closeOutDevice(OutDevice* outDevice) {
    if (!outDevice) return SONORA_INVALID_PARAMETER; 

    if (outDevice->isOpen && outDevice->handle) {
        HWAVEOUT hwo = (HWAVEOUT)outDevice->handle;
        MMRESULT result = waveOutClose(hwo);
        
        if (result != MMSYSERR_NOERROR) {
            return SONORA_DEVICE_BUSY;
        }
        
        outDevice->isOpen = false;
        outDevice->handle = NULL;
    }

    free(outDevice);
    return SONORA_SUCCESS;
}