#ifndef SONORA_H
#define SONORA_H

#include <stdint.h> // for integer types
#include <sonora/macro.h>

#ifdef SONORA_EXPORT
	#define SONORA_API __declspec(dllexport)
#else
	#define SONORA_API __declspec(dllimport)
#endif

#define _OUT_
#define _IN_

typedef struct Format Format;
typedef struct OutDevice OutDevice;
typedef struct SonoraContext SonoraContext;

#if defined(__cplusplus)
extern "C" {
#endif

SONORA_API SONORARESULT    openAudioContext(SonoraContext* ctx, Format* fmt, OutDevice* out, unsigned int engineMacro);
SONORA_API SONORARESULT    closeAudioContext(SonoraContext* ctx);

SONORA_API Format*         newFormat(uint16_t formatTag, uint16_t channels, uint32_t sampleRate, uint16_t bitsPerSample);
SONORA_API OutDevice*      newOutDeviceIdx(uint32_t index);
SONORA_API const wchar_t** getOutDeviceNameList(_OUT_ uint32_t* numberOfDevices);
SONORA_API SONORARESULT    getOutDeviceNameByIdx(uint64_t index, _OUT_ char* buff);
SONORA_API SONORARESULT    freeOutDeviceNameList(const wchar_t** list, uint64_t numberOfDevices);

SONORA_API SONORARESULT    playSound(SonoraContext* ctx, const char* path);
SONORA_API SONORARESULT    getErrorText(SONORARESULT error, char* buffer, size_t size);

#if defined(__cplusplus)
}
#endif
#endif // SONORA_H