#include "../Audio DLL/sonora.h"
#include <iostream>

int main(void) {
	auto a = sonora::getOutDeviceNameList();
	const int n = 2;
	auto b = sonora::getOutDeviceNameByIdx(n);

	auto device = sonora::newOutDevice();


	for (auto& s : a) std::wcout << s << "\n";
	std::wcout << "INDEX " << n  << ": " << *b;
	getchar();
}