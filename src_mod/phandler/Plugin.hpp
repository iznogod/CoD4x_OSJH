#pragma once
#include <string>
#include <list>
#include <map>
#include <vector>
#include "events.h"
#include "macro.hpp"

BEGIN_EXTERN_C
#include <core/sys_main.h>
END_EXTERN_C

namespace phandler
{
///////////////////////////////////////////////
// A class that represents one loadable plugin.
class CPlugin
{
    NO_COPY_CLASS(CPlugin);

public:
    CPlugin();
    ~CPlugin();

    // ... but can be moved.
    CPlugin(CPlugin&& From_);

    ////////////////////////////////////////////////
    // Loads plugin from file specified by LibPath_.
    bool LoadFromFile(const std::string& LibPath_);

    /////////////////////////////////////////
    // Unloads and frees all the plugin data.
    void Unload();

    //////////////////////
    // Prints plugin info.
    void PrintPluginInfo(); // TODO: when all done, add different storages data.

    //////////////////////////////////////////
    // Returns true if current plugin initialized.
    bool IsInitialized() const { return m_Initialized; }
    
    /////////////////////////////////////
    // Sets current plugin enabled state.
    void SetInitialized(bool State_) { m_Initialized = State_; }

    ///////////////////////////////////////////////////////////////////////////
    // Returns string representation of an event number.
    const char* const GetEventName(const EPluginEvent EventIdx_) const;

    /////////////////////
    // Fire plugin event.
    template <class... PTypes>
    bool Event(EPluginEvent Event_, PTypes... Params)
    {
        int idx = static_cast<int>(Event_);
        if (!m_Events[idx])
            return false;

        (reinterpret_cast<void(__cdecl *)(PTypes...)>(m_Events[idx]))(Params...);
        return true;
    }

private:

    void (*m_Events[PEV_Count]);
    libHandle_t m_LibHandle;

    ////////////////////////////////////////////////////////////////////
    // If set to true, plugin successfully loaded and initialized.
    // Must not be set to "true" inside this class.
    // When unloading, if set to "true" - must fire "OnTerminate" first.
    bool m_Initialized;
};

} // end namespace phandler
