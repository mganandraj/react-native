#include "fbsystrace.h"
#include "mssystrace.h"


// We assume that this is always called for begin_section
void fbsystrace_trace_raw(const char* buffer, size_t length)
{
    LOGE("fbsystrace_trace_raw 2 called. %p, %d", (void*)buffer, length);

    if (buffer != nullptr)
    {
        if(length > 0 )
        {
            // TODO :: We must avoid this copying.
            // std::string str(buffer, length);
            // ms::ATrace_beginSection(str.c_str());
            ms::ATrace_beginSection(buffer);
        }
        else
        {
            ms::ATrace_beginSection(buffer);
        }
    }
    else
    {
        LOGE("fbsystrace_trace_raw 2 -- null buffer.");
    }

    LOGE("fbsystrace_trace_raw 2 ended.");
}

void fbsystrace_trace_raw(const char* buffer)
{
    LOGE("fbsystrace_trace_raw called.");
    fbsystrace_trace_raw(buffer, -1);
}

void fbsystrace_end_section(uint64_t /*tag*/)
{
    LOGE("fbsystrace_end_section called.");
    ms::ATrace_endSection();
}

bool fbsystrace_is_tracing(uint64_t /*tag*/)
{
    LOGE("fbsystrace_is_tracing called.");
    return ms::ATrace_isEnabled();
}

void fbsystrace_end_async_flow(uint64_t tag, const char* name, int callId)
{
    LOGE("fbsystrace_end_async_flow called.");
    // No-OP
}

namespace fbsystrace {

    FbSystraceSection::FbSystraceSection(uint64_t tag, const char* v)
    {
        LOGE("FbSystraceSection::FbSystraceSection 1 called. : %s", v);
        fbsystrace_trace_raw(v);
    }

    FbSystraceSection::FbSystraceSection(uint64_t tag, const char* v1, const char* v2)
    {
        LOGE("FbSystraceSection::FbSystraceSection 2 called. : %s : %s", v1, v2);
        char bigString[FBSYSTRACE_MAX_MESSAGE_LENGTH];
        bigString[0] = '\0';
        strcat(bigString,v1);
        strcat(bigString,"#");
        strcat(bigString,v2);
        fbsystrace_trace_raw(bigString);
    }

    FbSystraceSection::FbSystraceSection(uint64_t tag, const char* v1, const char* v2, const char* v3)
    {
        LOGE("FbSystraceSection::FbSystraceSection 3 called. : %s : %s : %s", v1, v2, v3);
        char bigString[FBSYSTRACE_MAX_MESSAGE_LENGTH];
        bigString[0] = '\0';
        strcat(bigString,v1);
        strcat(bigString,"#");
        strcat(bigString,v2);
        strcat(bigString,"#");
        strcat(bigString,v3);
        fbsystrace_trace_raw(bigString);
    }

    FbSystraceSection::FbSystraceSection(uint64_t tag, const char* v1, const char* v2, std::string v3)
    {
        LOGE("FbSystraceSection::FbSystraceSection 4b called.. : %s : %s : %s ", v1, v2, v3.c_str());
        char bigString[FBSYSTRACE_MAX_MESSAGE_LENGTH];
        bigString[0] = '\0';
        strcat(bigString,v1);
        strcat(bigString,"#");
        strcat(bigString,v2);
        strcat(bigString,"#");
        strcat(bigString,v3.c_str());
        fbsystrace_trace_raw(bigString);
    }

    FbSystraceSection::FbSystraceSection(uint64_t tag, const char* v1, const char* v2, std::string v3, const char* v4, std::string v5)
    {
        LOGE("FbSystraceSection::FbSystraceSection 5 called. : %s : %s : %s : %s : %s", v1, v2, v3.c_str(), v4, v5.c_str());
        char bigString[FBSYSTRACE_MAX_MESSAGE_LENGTH];
        bigString[0] = '\0';
        strcat(bigString,v1);
        strcat(bigString,"#");
        strcat(bigString,v2);
        strcat(bigString,"#");
        strcat(bigString,v3.c_str());
        strcat(bigString,"#");
        strcat(bigString,v4);
        strcat(bigString,"#");
        strcat(bigString,v5.c_str());
        fbsystrace_trace_raw(bigString);
    }

    FbSystraceSection::~FbSystraceSection()
    {
        LOGE("FbSystraceSection::~FbSystraceSection called.");
        ms::ATrace_endSection();
    }

    /*static */void FbSystraceAsyncFlow::begin(uint64_t tag, const char* name, int cookie)
    {
        LOGE("FbSystraceAsyncFlow::begin called.");
        // No-OP for now.
    }

    /*static */void FbSystraceAsyncFlow::end(uint64_t tag, const char* name, int cookie)
    {
        LOGE("FbSystraceAsyncFlow::end called.");
        // No-OP for now.
    }
}