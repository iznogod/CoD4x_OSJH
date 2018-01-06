#pragma once
#include <cod4x_plugin.hpp>

class CPluginAllTests
    : public CBasePluginImpl
{
public:

    /**
     * \brief Get unique instance of a plugin.
     * \return Pointer to a plugin interface.
     * */
    static IBasePluginImpl* GetInstance();

    // Events overrides.

    void OnInfoRequest(SPluginInfo_t* pPluginInfo_) override final;
    EPluginLoadingResult OnPluginLoad() override final;
    void OnPluginUnload() override final;
};
