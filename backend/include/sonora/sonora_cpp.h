#ifndef SONORA_CPP_H
#define SONORA_CPP_H

#include "sonora.h"

#include <vector>
#include <string>
#include <optional>
#include <variant>

#define SONORA_BEGIN namespace sonora {
#define SONORA_END }

using Device = std::variant<OutDevice*>;

SONORA_BEGIN

Format* newFormat(
    uint16_t formatTag,
    uint16_t channels, 
    uint32_t sampleRate, 
    uint16_t bitsPerSample
);
Format* newFormat(uint32_t formatMacro);
bool closeFormat(Format* format);

OutDevice* newOutDevice(uint32_t index);
OutDevice* newOutDevice(); // WAVE_MAPPER
std::vector<std::wstring> getOutDeviceNameList();
std::optional<std::wstring> getOutDeviceNameById(uint32_t index);

bool openOutDevice(Format *format, OutDevice *outDevice);
bool closeDevice(Device device);


SONORA_END

#endif // SONORA_CPP_H