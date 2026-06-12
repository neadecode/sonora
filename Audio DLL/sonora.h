#ifndef SONORA_H
#define SONORA_H

#include <stdint.h> //for uint64_t
#include "s_deviceinfo.h"

#if defined(__cplusplus)
	#include <vector>
	#include <string>
	#include <optional>
#endif

// For now, we'll just support either of these.
// TODO: Remember to resample the incoming audio signal to process it.
// We do this as we are thinking of scaling this to a DAW. 

#define SONORA_WAVE_PCM			0x0001
#define SONORA_WAVE_IEEE_FLOAT  0x0003

// Monolithic format.
typedef struct EngineFormat {
	uint16_t	formatTag;
	uint16_t	channels;
	uint32_t	samplesPerSec;
	/// If wFormatTag = WAVE_FORMAT_PCM, then wBitsPerSample 
	/// should be set to either 8 or 16. 
	/// If wFormatTag = WAVE_FORMAT_IEEE_FLOAT, 
	/// wBitsPerSample should be set to 32.
	uint16_t	bitsPerSample;
	/// If wFormatTag = WAVE_FORMAT_PCM or wFormatTag = WAVE_FORMAT_IEEE_FLOAT, 
	/// set nBlockAlign to (Channels*BitsPerSample)/8, which is the size of a 
	/// single audio frame. 
	uint16_t    blockAlign;
	/// Specifies the required average data transfer rate in bytes per second. 
	/// This value is useful for estimating buffer size.
	uint32_t	avgBytesPerSec;
} EngineFormat;

// Structure containing device handle
#if defined(_WIN32)
	typedef void* Handle; //HWAVEOUT in Windows
#endif

typedef struct OutDevice {
	Handle handle;
	bool isOpen;
	uint32_t id;
} OutDevice;

typedef struct Buffer {

} Buffer;

#if defined(__cplusplus)
extern "C" {
#endif
	const wchar_t **getOutDeviceNameList(uint64_t* outNumDevs);
	const wchar_t  *getOutDeviceNameByIdx(uint64_t i);
#if defined(__cplusplus)
} // extern "C"

namespace sonora {
	auto getOutDeviceNameList()	      -> std::vector<std::wstring>;
	auto getOutDeviceNameById(uint32_t index) -> std::optional<std::wstring>;
	auto newOutDevice()               -> OutDevice*; // DEFAULT WAVE MAPPER
	auto newOutDevice(uint32_t index) -> OutDevice*;
	bool initDevice(OutDevice *outDevice);
}
#endif // defined(__cplusplus)


#endif // !SONORA_H
