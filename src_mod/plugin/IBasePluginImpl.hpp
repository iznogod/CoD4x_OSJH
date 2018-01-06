#pragma once
#include "shared.h"
/**
 * \brief   Base plugin implementation interface. 
 *          This interface is used by EventDispatcher in each plugin code.
 *          It declares all the events available to use in plugin.
 *          Do not forget to add implementation in \a CBasePluginImpl
 * */
class IBasePluginImpl
{
public:
    virtual ~IBasePluginImpl() {};

    /**
     * \brief Server requested plugin information.
     * \param[out] pPluginInfo_ - struct contains all the plugin information.
     * */
    virtual void OnInfoRequest(SPluginInfo_t* pPluginInfo_) = 0;

    /**
     * \brief Server attempted to load this plugin.
     * \return \a PLR_OK if everything is OK, \a PLR_FAILED if something went wrong.
     * \note Make all the global-time memory allocations here.
     * */
    virtual EPluginLoadingResult OnPluginLoad() = 0;

    /**
     * \brief Server initiated plugin unloading.
     * \note Free all used resources here - this plugin is not going to be used anymore.
     * */
    virtual void OnPluginUnload() = 0;
};

/* to be used later.
DECL_IN_DLL void OnInit();
DECL_IN_DLL void OnUnload();
DECL_IN_DLL void OnPlayerDisconnect();
DECL_IN_DLL void OnPlayerConnect();
DECL_IN_DLL void OnExitLevel();
DECL_IN_DLL void OnMessageSent();
DECL_IN_DLL void PerFrame();
DECL_IN_DLL void PerSecond();
DECL_IN_DLL void PerTenSeconds();
DECL_IN_DLL void OnClientAuthorized();
DECL_IN_DLL void OnClientSpawned();
DECL_IN_DLL void OnClientEnteredWorld();
DECL_IN_DLL void OnTCPPacketReceived();
DECL_IN_DLL void OnUDPEvent();
DECL_IN_DLL void OnUDPSent();
DECL_IN_DLL void OnSpawnServer();
DECL_IN_DLL void BeforeFastRestart();
DECL_IN_DLL void AfterFastRestart();
DECL_IN_DLL void OnClientUserInfoChanged();
DECL_IN_DLL void OnClientMove();
DECL_IN_DLL void OnReservedSlotRequested();
DECL_IN_DLL void OnFilesystemStartup();
DECL_IN_DLL void OnPlayerGotAuthInfo();
DECL_IN_DLL void OnBanAdded();
DECL_IN_DLL void OnGetBanStatus();
DECL_IN_DLL void OnBanRemoved();
DECL_IN_DLL void OnModuleLoaded();
DECL_IN_DLL void OnScreenshotArrived();
DECL_IN_DLL void OnTerminate();
DECL_IN_DLL void Script_OnGametypeLoaded();
DECL_IN_DLL void Script_OnLevelLoaded();
DECL_IN_DLL void Script_OnGametypeStarted();
DECL_IN_DLL void Script_OnPlayerConnected();
DECL_IN_DLL void Script_OnPlayerDisconnected();
DECL_IN_DLL void Script_OnPlayerDamage();
DECL_IN_DLL void Script_OnPlayerKilled();
DECL_IN_DLL void Script_OnPlayerLastStand();
*/
