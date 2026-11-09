#include <sonora/sonora.h>
#include <sonora/internal.h>

// Agnostic function definitions.

SONORARESULT openAudioContext(SonoraContext* ctx, Format* fmt, OutDevice* out, unsigned int engine) {
    if (fmt == NULL || out == NULL || ctx == NULL) { return SONORA_INVALID_PARAMETER; }

    ctx->format = fmt;
    ctx->outDevice = out;

    switch (engine) {
    case SONORA_BACKEND_WINMM:
        ctx->engine = &sonora_winmm;
        break;    
    default:
        break;
    }


    SONORARESULT r = ctx->engine->open(ctx);
    if (r != SONORA_SUCCESS) {
        return r;
    }
    return SONORA_SUCCESS;
}

SONORARESULT closeAudioContext(SonoraContext* ctx) {
    if (!ctx) return SONORA_INVALID_PARAMETER; 

    SONORARESULT result = SONORA_SUCCESS;
    if (ctx->engine && ctx->engine->close) {
        result = ctx->engine->close(ctx); 
    }
    // THIS FREES THE CONTEXT RESOURCE.
    // FOR ME: DO NOT FREE THE RESOURCE FROM THE .close() ON THE ENGINE-DEPENDENT DEFINITION.
    return result;
}

SONORARESULT freeOutDeviceNameList(const wchar_t** list, uint64_t numberOfDevices) {
    if (!list) return SONORA_INVALID_PARAMETER;
    if (!numberOfDevices) return SONORA_INVALID_PARAMETER;

    for (uint64_t idx = 0; idx < numberOfDevices; ++idx) {
        if (list[idx] != NULL) {
            free(list[idx]);
        }
    } 
    free(list);
    return SONORA_SUCCESS;
}

SONORARESULT getErrorText(SONORARESULT error, char* buffer, size_t size) {}
