#ifndef S_DEVICEMACROS_H
#define S_DEVICEMACROS_H

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

#endif