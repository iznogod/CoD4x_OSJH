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
#include <core/scr_vm_types.h>
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

/**
 * \brief Get count of arguments passed to a console command.
 * \return Count of args as unsigned integer.
 * */
inline unsigned int trap_Cmd_Argc()
{
    unsigned int argc = 0;
    constexpr unsigned int hash = CRC32("Cmd_Argc");
    syscall(hash, &argc);
    return argc;
}

/**
 * \brief Get argument of console command.
 * \param[in] ArgNum_ - number of an argument, started from 0.
 * \
 * */
inline const char* trap_Cmd_Argv(const unsigned int ArgNum_)
{
    const char* argv = "";
    constexpr unsigned int hash = CRC32("Cmd_Argv");
    syscall(hash, ArgNum_, &argv);
    return argv;
}

/**
 * \brief Retrieve all passed arguments to a console command and save it to buffer.
 * \param[out] pBuffer_ - A storage for arguments.
 * \param[in] Size_ - Size of storage in bytes.
 * */
inline void trap_Cmd_Args(char* pBuffer_, const unsigned int Size_)
{
    constexpr unsigned int hash = CRC32("Cmd_Args");
    syscall(hash, pBuffer_, Size_);
}

/**
 * \brief Add new console command.
 * \param[in] CmdName_ - Name of console command.
 * \param[in] Function_ - Callback to be invoked when command issued.
 * \param[in] Power_ - Required minimum power of player to be able to invoke command.
 * \note This is not real \a Cmd_AddCommand. It adds cmd to plugin's storage and executes Function_ from there.
 * */
inline void trap_Cmd_AddCommand(const char* const CmdName_, xfunction_t Function_)
{
    constexpr unsigned int hash = CRC32("Cmd_AddCommand");
    syscall(hash, CmdName_, Function_);
}

/**
 * \brief Remove previously added console command.
 * \param[in] CmdName_ - Name of console command.
 * */
inline void trap_Cmd_RemoveCommand(const char* const CmdName_)
{
    constexpr unsigned int hash = CRC32("Cmd_RemoveCommand");
    syscall(hash, CmdName_);
}

/**
 * \brief Get value of CVar as string.
 * \param[in] CvarName_ - Name of CVar.
 * \param[out] Buffer_ - A storage for CVar string value.
 * \param[in] Size_ - Size of passed buffer.
 * */
inline void trap_Cvar_Get(const char* const CvarName_, char* const Buffer_, unsigned int Size_)
{
    constexpr unsigned int hash = CRC32("Cvar_Get_String");
    syscall(hash, CvarName_, Buffer_, Size_);
}

/**
 * \brief Get value of CVar as integer value.
 * \param[in] CvarName_ - Name of CVar.
 * \param[out] Value_ - A storage for CVar integer value.
 * */
inline void trap_Cvar_Get(const char* const CvarName_, int& Value_)
{
    constexpr unsigned int hash = CRC32("Cvar_Get_Int");
    syscall(hash, CvarName_, &Value_);
}

/**
 * \brief Get value of CVar as qboolean value.
 * \param[in] CvarName_ - Name of CVar.
 * \param[out] Value_ - A storage for CVar qboolean value.
 * */
inline void trap_Cvar_Get(const char* const CvarName_, qboolean& Value_)
{
    constexpr unsigned int hash = CRC32("Cvar_Get_Bool");
    syscall(hash, CvarName_, &Value_);
}

/**
 * \brief Get value of CVar as float value.
 * \param[in] CvarName_ - Name of CVar.
 * \param[out] Value_ - A storage for CVar float value.
 * */
inline void trap_Cvar_Get(const char* const CvarName_, float& Value_)
{
    constexpr unsigned int hash = CRC32("Cvar_Get_Float");
    syscall(hash, CvarName_, &Value_);
}

/**
 * \brief Set value of CVar as string.
 * \param[in] CvarName_ - Name of CVar.
 * \param[in] Value_ - Null-terminated string.
 * */
inline void trap_Cvar_Set(const char* const CvarName_, const char* const Value_)
{
    constexpr unsigned int hash = CRC32("Cvar_Set_String");
    syscall(hash, CvarName_, Value_);
}

/**
 * \brief Set value of CVar as integer value.
 * \param[in] CvarName_ - Name of CVar.
 * \param[in] Value_ - integer value.
 * */
inline void trap_Cvar_Set(const char* const CvarName_, const int Value_)
{
    constexpr unsigned int hash = CRC32("Cvar_Set_Int");
    syscall(hash, CvarName_, Value_);
}

/**
 * \brief Set value of CVar as qboolean value.
 * \param[in] CvarName_ - Name of CVar.
 * \param[in] Value_ - qboolean value.
 * */
inline void trap_Cvar_Set(const char* const CvarName_, const qboolean Value_)
{
    constexpr unsigned int hash = CRC32("Cvar_Set_Bool");
    syscall(hash, CvarName_, Value_);
}

/**
 * \brief Set value of CVar as float value.
 * \param[in] CvarName_ - Name of CVar.
 * \param[in] Value_ - float value.
 * */
inline void trap_Cvar_Set(const char* const CvarName_, const float Value_)
{
    constexpr unsigned int hash = CRC32("Cvar_Set_Float");
    syscall(hash, CvarName_, &Value_); // Yep, passing like pointer to a float.
}
