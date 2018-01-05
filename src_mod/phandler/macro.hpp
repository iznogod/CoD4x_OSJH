#pragma once

#define BEGIN_C_INCLUDE extern "C" {
#define END_C_INCLUDE }

#ifndef FUNCTION_NAME
#ifdef WIN32   //WINDOWS
#define FUNCTION_NAME (__FUNCTION__)
#else          //*NIX
#define FUNCTION_NAME (__func__)
#endif
#endif

#define THREAD_UNSAFE_RET(retVal) \
do { \
    if (Sys_IsMainThread() == qfalse) \
    { \
        Com_PrintError("Attempting to execute non thread safe function '%s'\n", FUNCTION_NAME); \
        return retVal; \
    } \
} while(0)

#define THREAD_UNSAFE() THREAD_UNSAFE_RET(;)

#define DURING_EVENT_ONLY_RET(retVal) \
    do { \
        if (!m_CurrentPlugin) \
        { \
            Com_PrintError("Attempt to call function '%s' outside of plugin event\n", FUNCTION_NAME); \
            return retVal; \
        } \
    } while(0)

#define DURING_EVENT_ONLY() DURING_EVENT_ONLY_RET(;)

#define NO_COPY_CLASS(className) \
    public: \
    className(const className&) = delete; \
    void operator=(const className&) = delete
