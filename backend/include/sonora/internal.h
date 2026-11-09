#ifndef SONORA_BACKEND_INTERNAL_H
#define SONORA_BACKEND_INTERNAL_H

#include <sonora/sonora.h>

struct SonoraContext {
    Format* format;
    OutDevice* outDevice;
    SonoraEngine* engine;
};

typedef struct SonoraEngine {
    SONORARESULT(*open)(SonoraContext* ctx);
    SONORARESULT(*close)(SonoraContext* ctx);
    SONORARESULT(*play)(SonoraContext* ctx);
} SonoraEngine;

extern const SonoraEngine sonora_winmm;

#endif // SONORA_BACKEND_INTERNAL_H

