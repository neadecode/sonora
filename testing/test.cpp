#include "../Audio DLL/sonora.h"
#include <iostream>

int main(void) {
	OutDevice* device = sonora::newOutDevice(0);
	if (sonora::initDevice(device)) {
		printf("Initialized correctly!\n");
		printf("%d\n", device->id);
		printf("%ws\n", sonora::getOutDeviceNameById(device->id)->c_str());
	}

	sonora::closeDevice(device);
	sonora::closeEngine(engine);
}