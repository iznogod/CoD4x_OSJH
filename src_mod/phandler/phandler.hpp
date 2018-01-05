///////////////////////////////////////////////////////////////////////////////
// phandler.h/cpp - Plugin handler C++ -> C bridge.
//      Allows you to call plugin handler C++ code from C code.
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "macro.hpp"

BEGIN_EXTERN_C
__cdecl void PHandler_Init();
__cdecl void PHandler_Shutdown();
END_EXTERN_C
