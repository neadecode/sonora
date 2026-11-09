#ifndef SONORA_WIN_WINMM_H
#define SONORA_WIN_WINMM_H

#include <sonora/sonora.h>
#include <sonora/internal.h>

struct Format {
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
};

struct OutDevice {
	void* handle;
	bool isOpen;
	uint32_t id;
};

const SonoraEngine sonora_winmm = {
    .open = open_winmm,
    .close = close_winmm
};

#endif // SONORA_WIN_WINMM_H

