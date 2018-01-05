///////////////////////////////////////////////////////////////////////////////
// traps.h - definitions for all the functions "imported" from server code.
//      If function was added once - it must exist all the time.
//      You can change inner code. Do not delete functions - old plugins may rely on these.
#pragma once

#include "../core/server.h"
#include "base.h"
#include <cstdio>
#include <cstdarg>
#include <compiletime/ctcrc32.hpp>

inline void trap_Com_Printf(const char* const Format_, ...)
{
    char msg[1024];
    va_list ap;
    va_start(ap, Format_);

    vsnprintf(msg, sizeof(msg), Format_, ap);
    va_end(ap);

    constexpr unsigned int hash = CRC32("Com_Printf");
    syscall(hash, msg);
}

inline void trap_Com_Error(const char* const Error_, ... )
{
    char msg[1024];
    va_list ap;
    va_start(ap, Error_);

    vsnprintf(msg, sizeof(msg), Error_, ap);
    va_end(ap);

    constexpr unsigned int hash = CRC32("Com_Error");
    syscall(hash, msg);
}

inline void trap_Com_PrintError(const char* const Fmt_, ... )
{
    char msg[1024];
    va_list ap;
    va_start(ap, Fmt_);

    vsnprintf(msg, sizeof(msg), Fmt_, ap);
    va_end(ap);

    constexpr unsigned int hash = CRC32("Com_PrintError");
    syscall(hash, msg);
}

inline void trap_Com_DPrintf(const char* const Format_, ...)
{
    char msg[1024];
    va_list ap;
    va_start(ap, Format_);

    vsnprintf(msg, sizeof(msg), Format_, ap);
    va_end(ap);

    constexpr unsigned int hash = CRC32("Com_DPrintf");
    syscall(hash, msg);
}

inline void trap_Com_PrintWarning(const char* const Fmt_, ... )
{
    char msg[1024];
    va_list ap;
    va_start(ap, Fmt_);

    vsnprintf(msg, sizeof(msg), Fmt_, ap);
    va_end(ap);

    constexpr unsigned int hash = CRC32("Com_PrintWarning");
    syscall(hash, msg);
}

inline void trap_Cbuf_AddText(const char* const Text_)
{
    constexpr unsigned int hash = CRC32("Cbuf_AddText");
    syscall(hash, Text_);
}

inline void trap_SV_SetConfigString(const int Index_, const char* const Value_)
{
    constexpr unsigned int hash = CRC32("SV_SetConfigString");
    syscall(hash, Index_, Value_);
}

inline void trap_SV_GetConfigString(const int Index_, char* const Buffer_, const int BufferSize_)
{
    constexpr unsigned int hash = CRC32("SV_GetConfigString");
    syscall(hash, Index_, Buffer_, BufferSize_);
}

inline int trap_SV_GetStat(const int ClientNum_, const unsigned int Index_)
{
    int ret = 0;
    constexpr unsigned int hash = CRC32("SV_GetStat");
    syscall(hash, ClientNum_, Index_, &ret);
    return ret;
}

inline void trap_SV_SetStat(const int ClientNum_, const unsigned int Index_, const int Value_)
{
    constexpr unsigned int hash = CRC32("SV_SetStat");
    syscall(hash, ClientNum_, Index_, Value_);
}

inline void trap_RemoveBanByIP(const netadr_t* const Client_)
{
    constexpr unsigned int hash = CRC32("RemoveBanByIP");
    syscall(hash, Client_);
}

inline void trap_AddBanByIP(const netadr_t* const Client_, const char* Message_, const int Expire_)
{
    constexpr unsigned int hash = CRC32("AddBanByIP");
    syscall(hash, Client_, Message_, Expire_);
}