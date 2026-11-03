#ifndef SONORA_H
#define SONORA_H

#define SONORA_DEFAULT_DEVICE 0

#include <stdint.h> //for integer types
#include "device_macros.h"

typedef struct Format {
	uint16_t	formatTag;
	uint16_t	channels;
	uint32_t	sampleRate;
	/// Specifies the required average data transfer rate in bytes per second. 
	/// This value is useful for estimating buffer size. BLOCK_ALIGN * SAMPLE_RATE;
	uint32_t	avgBytesPerSec;
	/// If wFormatTag = WAVE_FORMAT_PCM or wFormatTag = WAVE_FORMAT_IEEE_FLOAT, 
	/// set nBlockAlign to (Channels*BitsPerSample)/8, which is the size of a 
	/// single audio frame. 
	uint16_t    blockAlign;
	/// If wFormatTag = WAVE_FORMAT_PCM, then wBitsPerSample 
	/// should be set to either 8 or 16. 
	/// If wFormatTag = WAVE_FORMAT_IEEE_FLOAT, 
	/// wBitsPerSample should be set to 32.
	uint16_t	bitsPerSample;
	uint16_t    cbSize; //extra information (after cbSize)
} Format;

typedef void* Handle;

typedef struct OutDevice {
	Handle handle;
	bool isOpen;
	uint32_t id;
} OutDevice;

#if defined(__cplusplus)
extern "C" {
#endif

const wchar_t** getOutDeviceNameList(uint64_t* numberOfDevices);
const wchar_t*  getOutDeviceNameByIdx(uint64_t index);
void freeOutDeviceNameList(const wchar_t* *list, uint64_t numberOfDevices);

#if defined(__cplusplus)
}
#endif
#endif // !SONORA_H