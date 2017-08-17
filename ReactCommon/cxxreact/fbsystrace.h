#pragma once

#include <stdint.h>
#include <string.h>
#include <string>

// No-OP for now being.
#define FBSYSTRACE_UNLIKELY(x) x
#define FBSYSTRACE_LIKELY(x) x

#define FBSYSTRACE_MAX_MESSAGE_LENGTH 1024
#define FBSYSTRACE_MAX_SECTION_NAME_LENGTH 1024

#define TRACE_TAG_REACT_CXX_BRIDGE 0
#define TRACE_TAG_REACT_APPS 0

// We assume that this is always called for begin_section
void fbsystrace_trace_raw(const char* buffer, size_t length);
void fbsystrace_trace_raw(const char* buffer);

void fbsystrace_end_section(uint64_t tag);

bool fbsystrace_is_tracing(uint64_t tag);

void fbsystrace_end_async_flow(uint64_t tag, const char* name, int callId);

// Currently, not supporting the async methods as android's ASystrace* APIs currently does 
// officially support only calling from the same stackframe.. Calling across may work but
// it may result in non deterministic behaviour as the end calls would try matching the last begin ..

namespace fbsystrace {

    struct FbSystraceSection{
        
        // We assume that arguements are null terminated .. 

        FbSystraceSection(uint64_t tag, const char* v);
        FbSystraceSection(uint64_t tag, const char* v1, const char* v2);
        FbSystraceSection(uint64_t tag, const char* v1, const char* v2, const char* v3);
        FbSystraceSection(uint64_t tag, const char* v1, const char* v2, std::string v3);
        FbSystraceSection(uint64_t tag, const char* v1, const char* v2, std::string v3, const char* v4, std::string v5);
        ~FbSystraceSection();
    };

    struct FbSystraceAsyncFlow{
        static void begin(uint64_t tag, const char* name, int cookie);
        static void end(uint64_t tag, const char* name, int cookie);
    };
}