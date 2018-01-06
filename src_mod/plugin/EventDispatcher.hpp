#pragma once
#include "IBasePluginImpl.hpp"
#include <compiletime/ctcrc32.hpp>

#define VARG(num, type) ((type)(((int*)&EventHash_)[1 + num]))

/**
 * \brief   This function needs to be declared in plugin code.
 *          It returns pointer to a unique per plugin instance.
 * */
IBasePluginImpl* GetPlugin();

/**
 * \brief Per plugin event dispatcher.
 * \param[in] EventHash_ - CRC32 of event name.
 * 
 * */
inline void EventDispatcher(const unsigned int EventHash_, ...)
{
    switch(EventHash_)
    {
        case CRC32("OnInfoRequest"):
        {
            SPluginInfo_t* pPluginInfo = VARG(0, SPluginInfo_t*);
            GetPlugin()->OnInfoRequest(pPluginInfo);
            break;
        }

        case CRC32("OnPluginLoad"):
        {
            EPluginLoadingResult* pResult = VARG(0, EPluginLoadingResult*);
            *pResult = GetPlugin()->OnPluginLoad();
            break;
        }

        case CRC32("OnPluginUnload"):
        {
            GetPlugin()->OnPluginUnload();
            break;
        }
    }
}