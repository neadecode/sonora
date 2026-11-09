#include <sonora/sonora.h>
#include <sonora/internal.h>
#include "winmm.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmeapi.h>
#ifdef _WIN32
    #include <mmsystem.h>
#endif
#include <mmreg.h>

SONORARESULT open_winmm(SonoraContext* ctx) {
    if (!ctx || !ctx->outDevice || !ctx->format) return SONORA_INVALID_PARAMETER;
    
    MMRESULT result = waveOutOpen(
        (LPHWAVEOUT)ctx->outDevice->handle,
        (UINT)ctx->outDevice->id,
        (LPCWAVEFORMATEX)ctx->format,
        0,
        0,
        CALLBACK_NULL
    );
    
    if (result == MMSYSERR_NOERROR) {
        ctx->outDevice->isOpen = true;
        return SONORA_SUCCESS;
    }
    
    return SONORA_UNKNOWN_ERROR;

}

SONORARESULT close_winmm(SonoraContext* ctx) {
    if (!ctx || !ctx->outDevice || !ctx->format) return SONORA_INVALID_PARAMETER;
    free(ctx->format);

    if (ctx->outDevice && ctx->outDevice->handle) {
        HWAVEOUT hwo = (HWAVEOUT)ctx->outDevice->handle;
        MMRESULT result = waveOutClose(hwo);
        
        if (result != MMSYSERR_NOERROR) {
            return SONORA_DEVICE_BUSY;
        }
        ctx->outDevice->isOpen = false;
        ctx->outDevice->handle = NULL;
    }
    free(ctx->outDevice);
    free(ctx);
    return SONORA_SUCCESS;
}

Format* format_winmm(SonoraContex)


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

SONORARESULT closeAudioContext(SonoraContext* ctx) {
    if (!ctx || !ctx->outDevice || !ctx->format) return SONORA_INVALID_PARAMETER; 
    free(ctx->format);

    if (ctx->outDevice && ctx->outDevice->handle) {
        HWAVEOUT hwo = (HWAVEOUT)ctx->outDevice->handle;
        MMRESULT result = waveOutClose(hwo);
        
        if (result != MMSYSERR_NOERROR) {
            return SONORA_DEVICE_BUSY;
        }
        ctx->outDevice->isOpen = false;
        ctx->outDevice->handle = NULL;
    }

    free(ctx->outDevice);
    return SONORA_SUCCESS;
}

SONORARESULT getOutDeviceNameByIdx(uint64_t index, char* buff) {
    UINT numDevs = waveOutGetNumDevs();
    if (!numDevs) return SONORA_INTERNAL_ERROR;
    if (index >= numDevs) return SONORA_INVALID_PARAMETER;

    WAVEOUTCAPSA woc;
    MMRESULT r = waveOutGetDevCapsA((UINT)index, (LPWAVEOUTCAPSA)&woc, sizeof(WAVEOUTCAPSA));

    if (r == MMSYSERR_NOERROR) {
        strcpy(buff, (const char*)woc.szPname);
        return SONORA_SUCCESS;
    }
    return SONORA_UNKNOWN_ERROR;
}

const wchar_t** getOutDeviceNameList(uint32_t* numberOfDevices) {
    UINT numDevs = waveOutGetNumDevs();
    if (!numDevs) return NULL;

    *numberOfDevices = (uint32_t)numDevs;
    if (!numberOfDevices) return NULL;
 
    const wchar_t** arr = malloc((size_t)(*numberOfDevices) * sizeof(wchar_t*)); 
    if (!arr) return NULL;

    WAVEOUTCAPSW woc;
    for (uint32_t idx = 0; idx < *numberOfDevices; ++idx) {
        MMRESULT r = waveOutGetDevCapsW((UINT)idx, (LPWAVEOUTCAPSW)&woc, sizeof(WAVEOUTCAPSW));
        if (r == MMSYSERR_NOERROR) {
            arr[idx] = _wcsdup((const wchar_t*)woc.szPname);
        }
        else return NULL;
    }
    return arr;
}


OutDevice* newOutDeviceIdx(uint32_t index) {
    uint32_t numDevs = waveOutGetNumDevs();
    if (numDevs == 0 || index >= numDevs) return NULL;
    
    OutDevice* out = malloc(sizeof(OutDevice));
    if (!out) return NULL;

    out->handle = NULL;
    out->id = index;
    out->isOpen = false;

    return out;
}

SONORARESULT playSound(SonoraContext* ctx, char const* path) {
    FILE* file = fopen(path, "rb");
    if (!file) { return 1; }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file); 
    
    char* block = malloc(size); 
    if (!block) {
        fclose(file);
        return 1;
    }

    size_t bytesRead = fread(block, 1, size, file);
    fclose(file);

    WAVEHDR header = { 0 };
    header.lpData = block;
    header.dwBufferLength = (DWORD)bytesRead;

    MMRESULT resOpen = waveOutPrepareHeader((HWAVEOUT)ctx->outDevice->handle, &header, sizeof(WAVEHDR));
    if (resOpen != MMSYSERR_NOERROR) {
        free(block);
        return 1;
    }

    MMRESULT resWrite = waveOutWrite((HWAVEOUT)ctx->outDevice->handle, &header, sizeof(WAVEHDR));
    if (resWrite != MMSYSERR_NOERROR) {
        waveOutUnprepareHeader((HWAVEOUT)ctx->outDevice->handle, &header, sizeof(WAVEHDR));
        free(block);
        return 1;
    }

    while (waveOutUnprepareHeader((HWAVEOUT)ctx->outDevice->handle, &header, sizeof(WAVEHDR))
        == WAVERR_STILLPLAYING) {
        Sleep(50);  
    }

    free(block);
    return 0;
}

