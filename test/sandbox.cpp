#include <sonora/sonora.h>
#include <iostream>

int main(void) {
    Format* format = newFormat(SONORA_WAVE_PCM, 2, 441000, 24);

    uint64_t devices;
    const wchar_t** list = getOutDeviceNameList(&devices);

    for (uint64_t i{}; i < devices; ++i) {
        std::wcout <<  list[i] << "\n";
    }

}