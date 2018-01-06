#pragma once
///////////////////////////////////////////////////////////////////////////////
// Main plugin file to be included in plugin's source code.
// Purpose: declare/define version dependent plugin functions wrappers and declare plugin event handlers.

// Do not change order: at least EventDispatcher depends on BasePluginImpl.
#include "syscall.hpp"
#include "BasePluginImpl.hpp"
#include "traps.h"
#include "EventDispatcher.hpp"

/**
 * \brief Plugin entry point. The only function gets exported in plugin.
 * \param[in] Dispatcher_ - A function pointer to a server's system call dispatcher used to dispatch \a trap_* calls.
 * \return Function pointer to a plugin's event dispatcher used to response to various plugin hander events.
 * */
DECL_IN_DLL inline TSysCall pluginEntry(const TSysCall Dispatcher_)
{
    TSysCall* pSysCall = getPSysCall();
    *pSysCall = Dispatcher_;
    return EventDispatcher;
}
