#ifndef S_DEVICEINFO_H
#define S_DEVICEINFO_H

#include <stdint.h>
// For now, we'll just support either of these.
// TODO: Remember to resample the incoming audio signal to process it.
// We do this as we are thinking of scaling this to a DAW. 
#define SONORA_WAVE_PCM			0x0001
#define SONORA_WAVE_IEEE_FLOAT  0x0003

#define SONORA_WAVE_PCM_1M08       0x00000001       /* 11.025 kHz, Mono,   8-bit  */
#define SONORA_WAVE_PCM_1S08       0x00000002       /* 11.025 kHz, Stereo, 8-bit  */
#define SONORA_WAVE_PCM_1M16       0x00000004       /* 11.025 kHz, Mono,   16-bit */
#define SONORA_WAVE_PCM_1S16       0x00000008       /* 11.025 kHz, Stereo, 16-bit */
#define SONORA_WAVE_PCM_2M08       0x00000010       /* 22.05  kHz, Mono,   8-bit  */
#define SONORA_WAVE_PCM_2S08       0x00000020       /* 22.05  kHz, Stereo, 8-bit  */
#define SONORA_WAVE_PCM_2M16       0x00000040       /* 22.05  kHz, Mono,   16-bit */
#define SONORA_WAVE_PCM_2S16       0x00000080       /* 22.05  kHz, Stereo, 16-bit */
#define SONORA_WAVE_PCM_4M08       0x00000100       /* 44.1   kHz, Mono,   8-bit  */
#define SONORA_WAVE_PCM_4S08       0x00000200       /* 44.1   kHz, Stereo, 8-bit  */
#define SONORA_WAVE_PCM_4M16       0x00000400       /* 44.1   kHz, Mono,   16-bit */
#define SONORA_WAVE_PCM_4S16       0x00000800       /* 44.1   kHz, Stereo, 16-bit */
#define SONORA_WAVE_PCM_44M08      0x00000100       /* 44.1   kHz, Mono,   8-bit  */
#define SONORA_WAVE_PCM_44S08      0x00000200       /* 44.1   kHz, Stereo, 8-bit  */
#define SONORA_WAVE_PCM_44M16      0x00000400       /* 44.1   kHz, Mono,   16-bit */
#define SONORA_WAVE_PCM_44S16      0x00000800       /* 44.1   kHz, Stereo, 16-bit */
#define SONORA_WAVE_PCM_48M08      0x00001000       /* 48     kHz, Mono,   8-bit  */
#define SONORA_WAVE_PCM_48S08      0x00002000       /* 48     kHz, Stereo, 8-bit  */
#define SONORA_WAVE_PCM_48M16      0x00004000       /* 48     kHz, Mono,   16-bit */
#define SONORA_WAVE_PCM_48S16      0x00008000       /* 48     kHz, Stereo, 16-bit */
#define SONORA_WAVE_PCM_96M08      0x00010000       /* 96     kHz, Mono,   8-bit  */
#define SONORA_WAVE_PCM_96S08      0x00020000       /* 96     kHz, Stereo, 8-bit  */
#define SONORA_WAVE_PCM_96M16      0x00040000       /* 96     kHz, Mono,   16-bit */
#define SONORA_WAVE_PCM_96S16      0x00080000       /* 96     kHz, Stereo, 16-bit */

#define _1M08  SONORA_WAVE_PCM, 1, 11025,  8
#define _1S08  SONORA_WAVE_PCM, 2, 11025,  8
#define _1M16  SONORA_WAVE_PCM, 1, 11025, 16
#define _1S16  SONORA_WAVE_PCM, 2, 11025, 16

#define _2M08  SONORA_WAVE_PCM, 1, 22050,  8
#define _2S08  SONORA_WAVE_PCM, 2, 22050,  8
#define _2M16  SONORA_WAVE_PCM, 1, 22050, 16
#define _2S16  SONORA_WAVE_PCM, 2, 22050, 16

#define _4M08  SONORA_WAVE_PCM, 1, 44100,  8
#define _4S08  SONORA_WAVE_PCM, 2, 44100,  8
#define _4M16  SONORA_WAVE_PCM, 1, 44100, 16
#define _4S16  SONORA_WAVE_PCM, 2, 44100, 16

#define _44M08 SONORA_WAVE_PCM, 1, 44100,  8
#define _44S08 SONORA_WAVE_PCM, 2, 44100,  8
#define _44M16 SONORA_WAVE_PCM, 1, 44100, 16
#define _44S16 SONORA_WAVE_PCM, 2, 44100, 16

#define _48M08 SONORA_WAVE_PCM, 1, 48000,  8
#define _48S08 SONORA_WAVE_PCM, 2, 48000,  8
#define _48M16 SONORA_WAVE_PCM, 1, 48000, 16
#define _48S16 SONORA_WAVE_PCM, 2, 48000, 16

#define _96M08 SONORA_WAVE_PCM, 1, 96000,  8
#define _96S08 SONORA_WAVE_PCM, 2, 96000,  8
#define _96M16 SONORA_WAVE_PCM, 1, 96000, 16
#define _96S16 SONORA_WAVE_PCM, 2, 96000, 16

#endif