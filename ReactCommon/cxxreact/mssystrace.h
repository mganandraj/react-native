#pragma once

#include <android/log.h>

#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

namespace ms {
    extern void *(*ATrace_beginSection) (const char* sectionName);
    extern void *(*ATrace_endSection) (void);
    extern bool *(*ATrace_isEnabled) (void);

    void initializeTracing();
}