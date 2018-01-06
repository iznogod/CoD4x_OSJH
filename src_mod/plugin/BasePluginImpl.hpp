#pragma once
#include "IBasePluginImpl.hpp"
#include <cstring>
/**
 * \brief   Implementation of basic plugin.
 *          It contains all the default responses on each known event.
 * */
class CBasePluginImpl 
    : public IBasePluginImpl
{
    NO_COPY_CLASS(CBasePluginImpl);

public:
    virtual inline void OnInfoRequest(SPluginInfo_t* pPluginInfo_) override
    {
        strcpy(pPluginInfo_->fullName, "Base plugin");
        strcpy(pPluginInfo_->shortDescription, "Base plugin short description");
        strcpy(pPluginInfo_->longDescription, "Base plugin long description");
    };

    virtual inline EPluginLoadingResult OnPluginLoad() override { return PLR_FAILED; };
    virtual inline void OnPluginUnload() override {};
};
