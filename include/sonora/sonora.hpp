#ifndef SONORA_HPP
#define SONORA_HPP

#include "sonora.h"

#include <vector>
#include <string>
#include <optional>
#include <variant>

#define SONORA_BEGIN namespace sonora {
#define SONORA_END }

//TODO: get device list and devices with AnyDevice 
//TOOD: inDevice (I HAVE NO IDEA HOW DOES THAT WORK MAN)

using Device = std::variant<OutDevice*>;

SONORA_BEGIN
OutDevice* newOutDevice(); //WAVE_MAPPER
OutDevice* newOutDevice(uint32_t index);
std::vector<std::wstring>   getOutDeviceNameList();
std::optional<std::wstring> getOutDeviceNameById(uint32_t index);

bool openOutDevice(Format *format, OutDevice *outDevice);
bool closeDevice(Device device);
bool closeFormat(Format* format);

Format* newFormat(); //44.1Hz, Stereo, 16bits
Format* newFormat(uint32_t format); //DEFINED BY MACRO
Format* newFormat(
    uint16_t formatTag,
	uint16_t channels, 
	uint32_t sampleRate, 
	uint16_t bitsPerSample
);

bool playSound(Format* format, OutDevice* device, const char* path);
SONORA_END

#endif