#include "../Audio DLL/sonora.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <string>
#include <chrono>

int main(void) {	
	Format* format = sonora::newFormat();
	OutDevice* device = sonora::newOutDevice(0);

	auto name = sonora::getOutDeviceNameById(device->id);
	printf("%ws \n", name->c_str());
	printf("%u Hz, %u channels, %u bits\n",
		format->sampleRate, format->channels, format->bitsPerSample);

	sonora::openOutDevice(format, device);

	auto t1 = std::chrono::steady_clock::now();
	sonora::playSound(format, device, "sonora.wav");
	auto t2 = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(t2 - t1);

	printf("%lld seconds", duration.count());

	sonora::closeDevice(device);
	sonora::closeFormat(format);
}