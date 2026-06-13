#include "../Audio DLL/sonora.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <string>

int main(void) {	
	Format* format = sonora::newFormat();
	OutDevice* device = sonora::newOutDevice(0);

	auto name = sonora::getOutDeviceNameById(device->id);
	printf("%ws \n", name->c_str());
	printf("%u Hz, %u channels, %u bits\n",
		format->sampleRate, format->channels, format->bitsPerSample);

	if (!sonora::openOutDevice(format, device)) printf("failed to open audio device");
	sonora::playSound(format, device, "sonora.wav");

	sonora::closeDevice(device); sonora::closeEngine(format);
}