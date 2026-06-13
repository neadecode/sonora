# Sonora

Lightweight C++17 static library for Windows audio playback, wrapping WinMM.

## Requirements

- Windows
- C++17 or later
- Visual Studio 2019+

## Usage

```cpp
#include <sonora/sonora.h>

int main() {
    Format* format = sonora::newFormat(); // 44.1kHz, Stereo, 16-bit

    OutDevice* device = sonora::newOutDevice(0);
    sonora::openOutDevice(format, device);

    sonora::playSound(format, device, "audio.wav");

    sonora::closeDevice(device);
    sonora::closeFormat(format);
}
```

## API

### Format

```cpp
Format* sonora::newFormat();                                                              // 44.1kHz, Stereo, 16-bit
Format* sonora::newFormat(uint32_t format);                                               // SONORA_WAVE_PCM_* constant
Format* sonora::newFormat(uint16_t formatTag, uint16_t channels, uint32_t sampleRate, uint16_t bitsPerSample);
bool    sonora::closeFormat(Format* format);
```

### Devices

```cpp
OutDevice*  sonora::newOutDevice();              // WAVE_MAPPER (default device)
OutDevice*  sonora::newOutDevice(uint32_t id);   // specific device by ID
bool        sonora::openOutDevice(Format* format, OutDevice* device);
bool        sonora::closeDevice(DevicePtr device);
```

### Playback

```cpp
bool sonora::playSound(Format* format, OutDevice* device, const char* path);
```

### Device Enumeration

```cpp
std::vector<std::wstring>    sonora::getOutDeviceNameList();
std::optional<std::wstring>  sonora::getOutDeviceNameById(uint32_t id);
```

### Supported Formats

| Constant                  | Sample Rate | Channels | Bit Depth |
|---------------------------|-------------|----------|-----------|
| `SONORA_WAVE_PCM_1M08`    | 11.025 kHz  | Mono     | 8-bit     |
| `SONORA_WAVE_PCM_1S08`    | 11.025 kHz  | Stereo   | 8-bit     |
| `SONORA_WAVE_PCM_1M16`    | 11.025 kHz  | Mono     | 16-bit    |
| `SONORA_WAVE_PCM_1S16`    | 11.025 kHz  | Stereo   | 16-bit    |
| `SONORA_WAVE_PCM_2M08`    | 22.05 kHz   | Mono     | 8-bit     |
| `SONORA_WAVE_PCM_2S08`    | 22.05 kHz   | Stereo   | 8-bit     |
| `SONORA_WAVE_PCM_2M16`    | 22.05 kHz   | Mono     | 16-bit    |
| `SONORA_WAVE_PCM_2S16`    | 22.05 kHz   | Stereo   | 16-bit    |
| `SONORA_WAVE_PCM_4M08`    | 44.1 kHz    | Mono     | 8-bit     |
| `SONORA_WAVE_PCM_4S08`    | 44.1 kHz    | Stereo   | 8-bit     |
| `SONORA_WAVE_PCM_4M16`    | 44.1 kHz    | Mono     | 16-bit    |
| `SONORA_WAVE_PCM_4S16`    | 44.1 kHz    | Stereo   | 16-bit    |
| `SONORA_WAVE_PCM_48M08`   | 48 kHz      | Mono     | 8-bit     |
| `SONORA_WAVE_PCM_48S08`   | 48 kHz      | Stereo   | 8-bit     |
| `SONORA_WAVE_PCM_48M16`   | 48 kHz      | Mono     | 16-bit    |
| `SONORA_WAVE_PCM_48S16`   | 48 kHz      | Stereo   | 16-bit    |
| `SONORA_WAVE_PCM_96M08`   | 96 kHz      | Mono     | 8-bit     |
| `SONORA_WAVE_PCM_96S08`   | 96 kHz      | Stereo   | 8-bit     |
| `SONORA_WAVE_PCM_96M16`   | 96 kHz      | Mono     | 16-bit    |
| `SONORA_WAVE_PCM_96S16`   | 96 kHz      | Stereo   | 16-bit    |

## Roadmap

- [ ] Streaming (double buffering)
- [ ] Input devices (recording)
- [ ] WASAPI backend
- [ ] ASIO backend
- [ ] Format conversion / resampling

## License

MIT
