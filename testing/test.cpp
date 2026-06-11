#include "../Audio DLL/sonora.h"
#include <iostream>

int main(void) {
	auto a = sonora::getOutDeviceNameList();
	auto b = sonora::getOutDeviceNameByIdx(2);

	for (auto& s : a) std::wcout << s << "\n";
	std::wcout << *b;
}