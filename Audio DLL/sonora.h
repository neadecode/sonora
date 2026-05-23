#pragma once

#include <vector>

#ifdef AUDIODLL_EXPORTS
	#define AUDIODLL_API extern "C" __declspec(dllexport)
#else
	#define AUDIODLL_API extern "C" __declspec(dllimport)
#endif

AUDIODLL_API int getAudioDeviceNames(PCWSTR* out_csarr);
void free_contents(std::vector<const wchar_t*>& v);
