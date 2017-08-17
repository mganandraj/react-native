#include <dlfcn.h>
#include <android/log.h>

#include "mssystrace.h"

namespace ms {

// initializeTracing must be called before using these.. 
// Not checking for initialization to avoid any perf hit due to that.
void *(*ATrace_beginSection) (const char* sectionName) = nullptr;
void *(*ATrace_endSection) (void) = nullptr;
bool *(*ATrace_isEnabled) (void) = nullptr;

typedef void *(*fp_ATrace_beginSection) (const char* sectionName);
typedef void *(*fp_ATrace_endSection) (void);
typedef bool *(*fp_ATrace_isEnabled) (void);

void initializeTracing()
{

LOGE("initializeTracing called.");

// Native Trace API is supported in API level 23
void *lib = dlopen("libandroid.so", RTLD_NOW | RTLD_LOCAL);
if (lib != nullptr) {
    //LOGI("Run with Trace Native API.");
    // Retrieve function pointers from shared object.
    ATrace_beginSection =
            reinterpret_cast<fp_ATrace_beginSection >(
                    dlsym(lib, "ATrace_beginSection"));
    ATrace_endSection =
            reinterpret_cast<fp_ATrace_endSection >(
                    dlsym(lib, "ATrace_endSection"));
    ATrace_isEnabled =
            reinterpret_cast<fp_ATrace_isEnabled >(
                    dlsym(lib, "ATrace_isEnabled"));
} else {
    __android_log_print(ANDROID_LOG_ERROR, "AMG", "Unable to open libandroid.so.");
    *((int*)0) = 0;
}

if(!ATrace_beginSection)
{
    __android_log_print(ANDROID_LOG_ERROR, "AMG", "ATrace_beginSection not found.");
    *((int*)0) = 0;
}

LOGE("initializeTracing ended.");

}

}