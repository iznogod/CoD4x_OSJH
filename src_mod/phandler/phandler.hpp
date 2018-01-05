///////////////////////////////////////////////////////////////////////////////
// phandler.h/cpp - Plugin handler C++ -> C bridge.
//      Allows you to call plugin handler C++ code from C code.
///////////////////////////////////////////////////////////////////////////////
#pragma once
#include "macro.hpp"

BEGIN_C_INCLUDE
__cdecl void PHandler_Init();
__cdecl void PHandler_Shutdown();
END_C_INCLUDE
