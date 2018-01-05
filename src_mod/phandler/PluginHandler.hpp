#pragma once
#include <map>
#include <string>
#include "events.h"
#include "Plugin.hpp"

namespace phandler
{
////////////////////////
// CoD4X plugin handler.
class CPluginHandler 
{
    NO_COPY_CLASS(CPluginHandler);

public:

    CPluginHandler();
    ~CPluginHandler();

    ////////////////////////////////
    // Plugin handler management. //
    ////////////////////////////////

    //////////////////////////////
    // Initializes plugin handler.
    void Init();

    ///////////////////////////////////////////////////////////////////////////
    // Shut plugin handler down and free all resources.
    void Shutdown();

    ////////////////////////
    // Plugin management. //
    ////////////////////////

    ///////////////////////////////////
    // Loads plugin by its LibName_.
    void LoadPlugin(const char *LibName_);

    ///////////////////////////////////
    // Unload plugin by name LibName_.
    void UnloadPlugin(const char *LibName_);

    ///////////////////////////////////////////////
    // Prints info about plugin with name LibName_.
    void PrintPluginInfo(const char *LibName_);

    //////////////////////////////////////////
    // Prints all plugins summary information.
    void PrintPluginsSummary();

    /////////////////////
    // Fire plugin event.
    template <class... TParms>
    void Event(EPluginEvent Event_, TParms... Params)
    {
        /*if (Event_ < PEV_Start || Event_ >= PEV_Count)
        {
            Com_PrintError("Unknown plugin event");
            return;
        }

        for (auto &plugin : m_Plugins)
        {
            m_CurrentPlugin = &plugin.second;
            m_CurrentPlugin->Event(Event_, Params...);
        }
        m_CurrentPlugin = nullptr;*/
    }

  private:
    ////////////////////////////////////////////////////////////////
    // Returns true if plugin with name LibName_ has known checksum.
    bool isLegacyPlugin(const std::string &LibPath_) const;

    ////////////////////////////
    // Returns plugin file path.
    std::string getPluginFilePath(const std::string& strPluginName_) const;

    bool m_Initialized;
    std::map<std::string, CPlugin> m_Plugins;
    CPlugin *m_CurrentPlugin;
};
} // end of namespace phandler

phandler::CPluginHandler* GetPluginHandler();
