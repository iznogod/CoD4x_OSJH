///////////////////////////////////////////////////////////////////////////////
// traps.h - definitions for all the functions "imported" from server code.
//      If function was added once - it must exist all the time.
//      You can change inner code. Do not delete functions - old plugins may rely on these.
#pragma once

#include "syscall.hpp"
#include <cstdio>
#include <cstdarg>
#include <compiletime/ctcrc32.hpp>
#include <phandler/macro.hpp>

BEGIN_EXTERN_C
#include <core/sys_net_types.h>
END_EXTERN_C

/**
 * \brief Print message to a console window.
 * \param[in] Format_ - Format of message similar to `printf` function.
 * */
inline void trap_Com_Printf(const char* const Format_, ...)
{
    char msg[1024];
    va_list ap;
    va_start(ap, Format_);

    vsnprintf(msg, sizeof(msg), Format_, ap);
    va_end(ap);

    constexpr unsigned int hash = CRC32("Com_Printf");
    TSysCall* pSysCall = getPSysCall();
    (*pSysCall)(hash, msg);
}

/**
 * \brief Shutdown server and print message to a console window.
 * \param[in] Error_ - Format of error message to be printed.
 * */
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

/**
 * \brief Print message as error to console window.
 * \param[in] Fmt_ - Format of message to be printed.
 * */
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

/**
 * \brief Print message to console window in developer mode only.
 * \Format_ - Format of message to be printed.
 * \note Does nothing if "developer 0" mode set.
 * */
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

/**
 * \brief Print message as warning to console window.
 * \param[in] Fmt_ - Format of message to be printed.
 * */
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

/**
 * \brief Execute string as console command.
 * \param[in] Text_ - A command to execute.
 * \note Command must be "\n" terminated.
 * */
inline void trap_Cbuf_AddText(const char* const Text_)
{
    constexpr unsigned int hash = CRC32("Cbuf_AddText");
    syscall(hash, Text_);
}

/**
 * \brief Set config string for both server and clients.
 * \param[in] Index_ - Index of config string.
 * \param[in] Value_ - Null-terminated value of config string.
 * */
inline void trap_SV_SetConfigString(const int Index_, const char* const Value_)
{
    constexpr unsigned int hash = CRC32("SV_SetConfigString");
    syscall(hash, Index_, Value_);
}

/**
 * \brief Retrieve value of config string.
 * \param[in] Index_ - Index of config string.
 * \param[out] Buffer_ - Storage for config string value.
 * \param[in] BufferSize_ - Size of passed buffer in bytes.
 * */
inline void trap_SV_GetConfigString(const int Index_, char* const Buffer_, const int BufferSize_)
{
    constexpr unsigned int hash = CRC32("SV_GetConfigString");
    syscall(hash, Index_, Buffer_, BufferSize_);
}

/**
 * \brief Retrieve value of player stat.
 * \param[in] ClientNum_ - Client number.
 * \param[in] Index_ - Index of player stat.
 * \return Integer value of player stat.
 * */
inline int trap_SV_GetStat(const int ClientNum_, const unsigned int Index_)
{
    int ret = 0;
    constexpr unsigned int hash = CRC32("SV_GetStat");
    syscall(hash, ClientNum_, Index_, &ret);
    return ret;
}

/**
 * \brief Set value of player stat.
 * \param[in] ClientNum_ - Client number.
 * \param[in] Index_ - Index of player stat.
 * \param[in] Value_ - New value of stat.
 * */
inline void trap_SV_SetStat(const int ClientNum_, const unsigned int Index_, const int Value_)
{
    constexpr unsigned int hash = CRC32("SV_SetStat");
    syscall(hash, ClientNum_, Index_, Value_);
}

/**
 * \brief Remove player ban by IP.
 * \param[in] Client_ - Client's \a netadr_t structure.
 * */
inline void trap_RemoveBanByIP(const netadr_t* const Client_)
{
    constexpr unsigned int hash = CRC32("RemoveBanByIP");
    syscall(hash, Client_);
}

/**
 * \brief Add player ban by IP.
 * \param[in] Client_ - Client's \a netadr_t structure.
 * \param[in] Message_ - Description of ban.
 * \param[in] Expire_ - Duration of ban.
 * */
inline void trap_AddBanByIP(const netadr_t* const Client_, const char* Message_, const int Expire_)
{
    constexpr unsigned int hash = CRC32("AddBanByIP");
    syscall(hash, Client_, Message_, Expire_);
}

/**
 * \brief Allocate RAM.
 * \param[in] Size_ - Desired size of memory block.
 * \return Address of allocated memory or \a nullptr in case of failure.
 * */
inline void* trap_MemAlloc(const unsigned int Size_)
{
    void* result = nullptr;
    constexpr unsigned int hash = CRC32("MemAlloc");
    syscall(hash, Size_, &result);
    return result;
}

/**
 * \brief Free RAM.
 * \param[in] Address_ - Address of previously allocated block of memory.
 * */
inline void trap_MemFree(const void* const Address_)
{
    constexpr unsigned int hash = CRC32("MemFree");
    syscall(hash, Address_);
}