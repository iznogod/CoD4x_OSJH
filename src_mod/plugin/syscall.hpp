#pragma once
#include "shared.h"

// Static function to declare syscall storage variable.
inline TSysCall* getPSysCall()
{
    static TSysCall g_sysCall;
    return &g_sysCall;
}

// Wrapper for a function call.
#define syscall (*(getPSysCall()))
