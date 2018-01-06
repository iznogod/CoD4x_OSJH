#pragma once
#include <string>
#include <list>
#include <map>
#include <vector>
#include "macro.hpp"

BEGIN_EXTERN_C
#include <core/sys_main.h>
#include <plugin/shared.h>
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
    bool IsInitialized() const;
    
    /////////////////////////////////////
    // Sets current plugin enabled state.
    void SetInitialized(bool bInitialized_);

    /////////////////////
    // Fire plugin event.
    template <class... PTypes>
    bool Event(const unsigned int EventHashCode_, PTypes... Params)
    {
        if (!m_pEventDispatcher)
            return false;
        
        m_pEventDispatcher(EventHashCode_, Params...);
        return true;
    }

    /////////////////////////////////////////////
    // Add address to memory allocations storage.
    void SaveMemoryAddress(void* const Address_, const unsigned int Size_);

    //////////////////////////////////////////////////
    // Remove address from memory allocations storage.
    void DeleteMemoryAddress(void* const Address_);

    //////////////////////////////////////////
    // Add name of console command to storage.
    void SaveConsoleCommand(const char* const CmdName_);

    /////////////////////////////////////////
    // Returns true if console command exist.
    bool IsConsoleCommandExist(const char* const CmdName_);

    ///////////////////////////////////////////////
    // Remove name of console command from storage.
    void DeleteConsoleCommand(const char* const CmdName_);

private:

    void freeAllocatedMemory();
    void removeCustomConsoleCommands();

    libHandle_t m_LibHandle;                        // Handle of a plugin library.
    TSysCall m_pEventDispatcher;                    // Plugin event dispatcher returned by "pluginEntry".
    std::map<void*, unsigned int> m_mapMemAllocs;   // Memory allocations <address, size of block>.
    std::vector<std::string> m_vConsoleCommands;    // Custom console commands names.

    ////////////////////////////////////////////////////////////////////
    // If set to true, plugin successfully loaded and initialized.
    // Must not be set to "true" inside this class. (depends on dll info, returned by event)
    // When unloading, if set to "true" - must fire "OnTerminate" first.
    bool m_Initialized;
};

} // end namespace phandler
