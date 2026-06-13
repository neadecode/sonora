#ifndef SONORA_H
#define SONORA_H

#include <stdint.h> //for uint64_t
#include "s_deviceinfo.h"

#if defined(__cplusplus)
	#include <vector>
	#include <string>
	#include <optional>
	#include <variant>
#endif

//TODO: C COMPATIBILITY

// Monolithic format.
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

// Structure containing device handle
#if defined(_WIN32)
	typedef void* Handle; //HWAVEOUT in Windows
#endif

typedef struct OutDevice {
	Handle handle;
	bool isOpen;
	uint32_t id;
} OutDevice;


#if defined(__cplusplus)
extern "C" {
#endif
	const wchar_t **getOutDeviceNameList(uint64_t* outNumDevs);
	const wchar_t  *getOutDeviceNameByIdx(uint64_t i);
#if defined(__cplusplus)
} // extern "C"

//TODO: open and close out and in devices with AnyDevice
//TODO: get device list and devices with AnyDevice 
//TOOD: in Device (I HAVE NO IDEA HOW DOES THAT WORK MAN)
//TODO: fromFile(FILE) FILE C type

namespace sonora {
	using DevicePtr = std::variant<OutDevice*>;

	void       __test();

	//No need for engine or device (Defaults devices)
	auto       getOutDeviceNameList()               -> std::vector<std::wstring>;
	auto       getOutDeviceNameById(uint32_t index) -> std::optional<std::wstring>;

	bool	   openOutDevice(Format *engine, OutDevice *outDevice);
	bool	   closeDevice(DevicePtr device);
	bool       closeEngine(Format* engine);
	bool	   playSound(Format* engine, DevicePtr device, const char* path);

	Format*    newFormat(); //44.1Hz, Stereo, 16bits
	Format*    newFormat(uint32_t format);
	Format*    newFormat(uint16_t formatTag, uint16_t channels, uint32_t sampleRate, uint16_t bitsPerSample);

	OutDevice* newOutDevice(); //WAVE_MAPPER
	OutDevice* newOutDevice(uint32_t index);

}	
#endif // defined(__cplusplus)

#endif // !SONORA_H


