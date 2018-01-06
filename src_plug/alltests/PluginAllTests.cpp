#include "PluginAllTests.hpp"
#include <cstring>

IBasePluginImpl* CPluginAllTests::GetInstance()
{
    static CPluginAllTests g_pluginInstance;
    return &g_pluginInstance;
}

void CPluginAllTests::OnInfoRequest(SPluginInfo_t* pPluginInfo_)
{
    strcpy(pPluginInfo_->fullName, "alltests");
    strcpy(pPluginInfo_->shortDescription, "Test of all plugin functionality");
    strcpy(pPluginInfo_->longDescription, "This plugin contains all the test functionality you can use to reference or watch how it's working");
}

EPluginLoadingResult CPluginAllTests::OnPluginLoad()
{
    trap_Com_Printf("[alltests]: Hello, %s world!\n", "formatted");
    trap_Com_PrintError("[alltests]: Com_PrintError(): Test Com_PrintError %d\n", 1);
    //trap_Cbuf_AddText("developer 2\n");
    trap_Com_DPrintf("[alltests]: Com_DPrintf(): Com_DPrintf %s !\n", "test");
    trap_Com_PrintWarning("[alltests]: Com_PrintWarning(): Com_PrintWarning %s !\n", "test");
    trap_SV_SetConfigString(1000, "defaultweapon");// :D
    char buffer[8192] = {'\0'};
    trap_SV_GetConfigString(1000, buffer, sizeof(buffer));
    trap_Com_Printf("[alltests]: SV_GetConfigString(): CS len is %d CS is: %s\n", strlen(buffer), buffer);
    trap_SV_SetStat(0, 0, 800);
    int ret = trap_SV_GetStat(0, 0);
    trap_Com_Printf("[alltests]: SV_GetStat(): %d \n", ret);
    //trap_RemoveBanByIP(&remote);
    //trap_AddBanByIP(&request->remote, "Invalid login attempt. You have to wait 20 seconds", 20);
    //trap_Com_Error("[alltests]: Com_Error(): Test Com_Error %d\n", 2);
    void* pMem = trap_MemAlloc(16);
    trap_Com_Printf("[alltests]: MemAlloc(): 16 bytes for 0x%X", pMem);
    trap_MemFree(pMem);
    
    return PLR_OK;
}

void CPluginAllTests::OnPluginUnload()
{
     trap_Com_Printf("[alltests]: Goodbye, cruel world!\n");
}