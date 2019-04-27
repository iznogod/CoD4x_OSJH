// OSJH main file since working with plugins is not desired for this project

/**************************************************************************
 * Includes                                                               *
 **************************************************************************/
 
#include <stdlib.h>
#include <stdbool.h>
 
#include "osjh_main.hpp"

#include "extra/gsc_custom_mysql.hpp"
#include "extra/gsc_custom_utils.hpp"
#include "extra/gsc_saveposition.hpp"
#include "extra/gsc_custom_player.hpp"
#include "extra/gsc_settings.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include "scr_vm.h"
#include "scr_vm_functions.h"
#include "xassets/weapondef.h"
#include "bg_public.h"

#ifdef __cplusplus
}
#endif

/**************************************************************************
 * Extern functions without available prototype                           *
 **************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

extern int GScr_LoadScriptAndLabel(const char *scriptName, const char *labelName, qboolean mandatory);

#ifdef __cplusplus
}
#endif

/**************************************************************************
 * Defines                                                                *
 **************************************************************************/
 
typedef struct {
    char forward;
    char right;
} playermovement_t;
 
/**************************************************************************
 * Defines                                                                *
 **************************************************************************/


 
/**************************************************************************
 * Global variables                                                       *
 **************************************************************************/
 
static bool osjh_playerElevationPermissions[MAX_CLIENTS] = {0};
static bool osjh_playerWASDCallbackEnabled[MAX_CLIENTS] = {0};
static int osjh_callbacks[OSJH_CB_COUNT] = {0};
static int previousbuttons[MAX_CLIENTS] = {0};
static playermovement_t playermovement[MAX_CLIENTS] = {{0}};

/**************************************************************************
 * Static functions                                                       *
 **************************************************************************/

static void PlayerCmd_ClientCommand(scr_entref_t arg)
{
    if(arg.classnum)
    {
        Scr_ObjectError("Not an entity");
        return;
    }
    
    int entityNum = arg.entnum;
    gentity_t *gentity = &g_entities[entityNum];
    
    if (!gentity->client)
    {
        Scr_ObjectError(va("Entity: %i is not a player", entityNum));
    }
    
    if(Scr_GetNumParam())
    {
        Scr_Error("Usage: self ClientCommand()\n");
    }
    
    ClientCommand(entityNum);
}

static void PlayerCmd_allowElevate(scr_entref_t arg)
{
    if(arg.classnum)
    {
        Scr_ObjectError("Not an entity");
    }
    else
    {
        int entityNum = arg.entnum;
        bool canElevate = Scr_GetInt(0);
        osjh_playerElevationPermissions[entityNum] = canElevate;
    }
}

static void PlayerCmd_EnableWASDCallback(scr_entref_t arg)
{
    if(arg.classnum)
    {
        Scr_ObjectError("Not an entity");
    }
    else
    {
        osjh_playerWASDCallbackEnabled[arg.entnum] = true;
    }
}

static void PlayerCmd_DisableWASDCallback(scr_entref_t arg)
{
    if(arg.classnum)
    {
        Scr_ObjectError("Not an entity");
    }
    else
    {
        osjh_playerWASDCallbackEnabled[arg.entnum] = false;
    }
}

/**************************************************************************
 * Regular functions                                                      *
 **************************************************************************/

void osjh_init(void)
{
    // Init callbacks
    osjh_callbacks[OSJH_CB_PLAYERCOMMAND]       = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_PlayerCommand",     qfalse);
    osjh_callbacks[OSJH_CB_RPGFIRED]            = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_RPGFired",          qfalse);
    osjh_callbacks[OSJH_CB_SPECTATORCLIENTCHANGED] = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_SpectatorClientChanged", qfalse);
    osjh_callbacks[OSJH_CB_WENTFREESPEC]        = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_WentFreeSpec",      qfalse);
    osjh_callbacks[OSJH_CB_USERINFOCHANGED]     = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_UserInfoChanged",   qfalse);
    osjh_callbacks[OSJH_CB_MELEEBUTTONPRESSED]  = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_MeleeButton",       qfalse);
    osjh_callbacks[OSJH_CB_USEBUTTONPRESSED]    = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_UseButton",         qfalse);
    osjh_callbacks[OSJH_CB_ATTACKBUTTONPRESSED] = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_AttackButton",      qfalse);
    osjh_callbacks[OSJH_CB_STARTJUMP]           = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_StartJump",         qfalse);
    osjh_callbacks[OSJH_CB_MOVEFORWARD]         = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_MoveForward",       qfalse);
    osjh_callbacks[OSJH_CB_MOVERIGHT]           = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_MoveRight",         qfalse);
    osjh_callbacks[OSJH_CB_MOVEBACKWARD]        = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_MoveBackward",      qfalse);
    osjh_callbacks[OSJH_CB_MOVELEFT]            = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_MoveLeft",          qfalse);
}

static void osjh_onDisconnect(int id)
{
    gsc_mysqla_ondisconnect(id);
    
    // Can call other onDisconnect methods from here
}

void osjh_onFrame(void)
{
    mysql_handle_result_callbacks();
}

void osjh_onStartJump(struct pmove_t *pm)
{
    if(osjh_callbacks[OSJH_CB_STARTJUMP])
    {
        int ret = Scr_ExecEntThread(&g_entities[pm->ps->clientNum], osjh_callbacks[OSJH_CB_STARTJUMP], 0);
        Scr_FreeThread(ret);
    }
}

void osjh_onClientMoveCommand(client_t *client, usercmd_t *ucmd)
{
    int clientNum = client - svs.clients;//client->gentity->client->ps.clientNum;
	if(ucmd->buttons & KEY_MASK_MELEE && !(previousbuttons[clientNum] & KEY_MASK_MELEE))
	{
		if(osjh_callbacks[OSJH_CB_MELEEBUTTONPRESSED])
		{
			short ret = Scr_ExecEntThread(client->gentity, osjh_callbacks[OSJH_CB_MELEEBUTTONPRESSED], 0);
			Scr_FreeThread(ret);
		}
	}

	if(ucmd->buttons & KEY_MASK_USE && !(previousbuttons[clientNum] & KEY_MASK_USE))
	{
		if(osjh_callbacks[OSJH_CB_USEBUTTONPRESSED])
		{
			short ret = Scr_ExecEntThread(client->gentity, osjh_callbacks[OSJH_CB_USEBUTTONPRESSED], 0);
			Scr_FreeThread(ret);
		}
	}

	if(ucmd->buttons & KEY_MASK_FIRE && !(previousbuttons[clientNum] & KEY_MASK_FIRE))
	{
		if(osjh_callbacks[OSJH_CB_ATTACKBUTTONPRESSED])
		{
			short ret = Scr_ExecEntThread(client->gentity, osjh_callbacks[OSJH_CB_ATTACKBUTTONPRESSED], 0);
			Scr_FreeThread(ret);
		}
	}
    
    if(ucmd->rightmove != playermovement[clientNum].right)
    {
        if(ucmd->rightmove == 127) // Pressed D
        {
            if(osjh_callbacks[OSJH_CB_MOVERIGHT])
            {
                short ret = Scr_ExecEntThread(&g_entities[clientNum], osjh_callbacks[OSJH_CB_MOVERIGHT], 0);
                Scr_FreeThread(ret);
            }
        }
        else if(ucmd->rightmove == -127) // Pressed A
        {
            if(osjh_callbacks[OSJH_CB_MOVELEFT])
            {
                short ret = Scr_ExecEntThread(&g_entities[clientNum], osjh_callbacks[OSJH_CB_MOVELEFT], 0);
                Scr_FreeThread(ret);
            }
        }
        else
        {
            // Released a key, we don't care
        }
        
        playermovement[clientNum].right = ucmd->rightmove;
    }
    
    if(ucmd->forwardmove != playermovement[clientNum].forward)
    {
        if(ucmd->forwardmove == 127) // Pressed W
        {
            if(osjh_callbacks[OSJH_CB_MOVEFORWARD])
            {
                short ret = Scr_ExecEntThread(&g_entities[clientNum], osjh_callbacks[OSJH_CB_MOVEFORWARD], 0);
                Scr_FreeThread(ret);
            }
        }
        else if(ucmd->forwardmove == -127) // Pressed S
        {
            if(osjh_callbacks[OSJH_CB_MOVEBACKWARD])
            {
                short ret = Scr_ExecEntThread(&g_entities[clientNum], osjh_callbacks[OSJH_CB_MOVEBACKWARD], 0);
                Scr_FreeThread(ret);
            }
        }
        else
        {
            // Released a key, we don't care
        }
        
        playermovement[clientNum].forward = ucmd->forwardmove;
    }

	previousbuttons[clientNum] = ucmd->buttons;
}

int osjh_getCallback(osjh_callback_t callbackType)
{
    return osjh_callbacks[callbackType];
}

void gsc_voidmethod(int id)
{
	stackPushInt(0);
}

static void Gsc_StopFollowingMe(int id)
{
    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        gentity_t *player = SV_GentityNum(i);
        if(player != NULL && player->client != NULL)
        {
            if(player->client->lastFollowedClient == id)
                player->client->lastFollowedClient = -1;
        }
    }
}

static void Gsc_GetFollowersAndMe(int id)
{
    int alsoMe;
    stackGetParamInt(0, &alsoMe);
    
    stackPushArray();

    for(int i = 0; i < MAX_CLIENTS; i++)
    {
        gentity_t *player = SV_GentityNum(i);
        
        if(!player)
            continue;
        
        if(!player->client)
            continue;
        
        if(player->client->spectatorClient != id)
            continue;
        
        // Now we can treat it as a client
        client_t *client = &svs.clients[i];
        
        if(!client)
            continue;
        
        if(client->state != CS_ACTIVE)
            continue;
        
        // We don't have to check if this is the calling player, because it doesn't have itself as the spectatorClient
        
        stackPushEntity(player);
        stackPushArrayLast();
    }
    
    if(alsoMe)
    {
        gentity_t *me = SV_GentityNum(id);
        stackPushEntity(me);
        stackPushArrayLast();
    }
}

void osjh_addMethodsAndFunctions(void)
{
    /** Functions */
    Scr_AddFunction("getcvar",                      GScr_GetCvar,                   qfalse);
    Scr_AddFunction("getcvarint",                   GScr_GetCvarInt,                qfalse);
    Scr_AddFunction("getcvarfloat",                 GScr_GetCvarFloat,              qfalse);
    Scr_AddFunction("setcvar",                      GScr_SetCvar,                   qfalse);
    
    Scr_AddFunction("mysqla_create_query",          gsc_mysqla_create_level_query,  qfalse);
    Scr_AddFunction("mysqla_initializer",           gsc_mysqla_initializer,         qfalse);
    Scr_AddFunction("mysql_real_connect",           gsc_mysqls_real_connect,        qfalse);
    Scr_AddFunction("mysql_query",                  gsc_mysqls_query,               qfalse);
    Scr_AddFunction("mysql_real_escape_string",     gsc_mysqls_real_escape_string,  qfalse);
    
	Scr_AddFunction("printf",                       Gsc_Utils_Printf,               qfalse);
	Scr_AddFunction("vectorscale",                  Gsc_Utils_VectorScale,          qfalse);
	Scr_AddFunction("createrandomint",              Gsc_Utils_CreateRandomInt,      qfalse);
    
    Scr_AddFunction("setting_createnew",            Gsc_CreateNewSetting,           qfalse);
    Scr_AddFunction("setting_deleteall",            Gsc_DeleteAllSettings,          qfalse);
    
    /** Methods */
    Scr_AddMethod("clientcommand",                  PlayerCmd_ClientCommand,        qfalse);
    Scr_AddMethod("allowelevate",                   PlayerCmd_allowElevate,         qfalse);
    Scr_AddMethod("setclientcvar",                  PlayerCmd_SetClientDvar,        qfalse);
    Scr_AddMethod("enablewasdcallback",             PlayerCmd_EnableWASDCallback,   qfalse);
    Scr_AddMethod("disablewasdcallback",            PlayerCmd_DisableWASDCallback,  qfalse);
    
	Scr_AddMethod("jumpclearstateextended",         (xmethod_t)Gsc_Player_JumpClearStateExtended,  qfalse);
	Scr_AddMethod("getgroundentity",                (xmethod_t)Gsc_Player_GetGroundEntity,         qfalse);
	Scr_AddMethod("saveposition_initclient",        (xmethod_t)gsc_saveposition_initclient,        qfalse);
	Scr_AddMethod("saveposition_save",              (xmethod_t)gsc_saveposition_save,              qfalse);
	Scr_AddMethod("saveposition_selectsave",        (xmethod_t)gsc_saveposition_selectsave,        qfalse);
	Scr_AddMethod("saveposition_getangles",         (xmethod_t)gsc_saveposition_getangles,         qfalse);
	Scr_AddMethod("saveposition_getorigin",         (xmethod_t)gsc_saveposition_getorigin,         qfalse);
	Scr_AddMethod("saveposition_getgroundentity",   (xmethod_t)gsc_saveposition_getgroundentity,   qfalse);
    Scr_AddMethod("saveposition_getnadejumps",      (xmethod_t)gsc_saveposition_getnadejumps,      qfalse);
    Scr_AddMethod("saveposition_getrpgjumps",       (xmethod_t)gsc_saveposition_getrpgjumps,       qfalse);
    Scr_AddMethod("saveposition_getdoublerpgs",     (xmethod_t)gsc_saveposition_getdoublerpg,      qfalse);
    Scr_AddMethod("saveposition_getcheckpointid",   (xmethod_t)gsc_saveposition_getcheckpointid,   qfalse);
    Scr_AddMethod("mysqla_create_query",            (xmethod_t)gsc_mysqla_create_entity_query,     qfalse);
    
    Scr_AddMethod("player_ondisconnect",            (xmethod_t)osjh_onDisconnect,                  qfalse);
    
    Scr_AddMethod("leftbuttonpressed",              PlayerCmd_MoveLeftButtonPressed,               qfalse);
    Scr_AddMethod("rightbuttonpressed",             PlayerCmd_MoveRightButtonPressed,              qfalse);
    
    Scr_AddMethod("setting_set",                    (xmethod_t)Gsc_SetSetting,                     qfalse);
    Scr_AddMethod("setting_get",                    (xmethod_t)Gsc_GetSetting,                     qfalse);
    Scr_AddMethod("setting_clear",                  (xmethod_t)Gsc_ClearSettings,                  qfalse);
    
    Scr_AddMethod("stopfollowingme",                (xmethod_t)Gsc_StopFollowingMe,                qfalse);
    Scr_AddMethod("getspectatorlist",               (xmethod_t)Gsc_GetFollowersAndMe,              qfalse);
    
    //TODO: add funcs below this line
    Scr_AddMethod("isthinking",                     (xmethod_t)gsc_voidmethod,                     qfalse);
    Scr_AddMethod("getjumpslowdowntimer",           (xmethod_t)gsc_voidmethod,                     qfalse);
}

/**************************************************************************
 * Functions that are called from ASM (mostly callbacks or checks)        *
 **************************************************************************/
 
void Ext_RPGFiredCallback(gentity_t *player, gentity_t *rpg)
{
    int callback = osjh_callbacks[OSJH_CB_RPGFIRED];
    if(callback)
    {
        Scr_AddString(BG_GetWeaponDef(rpg->s.weapon)->szInternalName);
        Scr_AddEntity(rpg);
        int threadId = Scr_ExecEntThread(player, callback, 2);
        Scr_FreeThread(threadId);
    }
}

void Ext_SpectatorClientChanged(gentity_t *player, int beingSpectatedClientNum)
{
    int callback = osjh_callbacks[OSJH_CB_SPECTATORCLIENTCHANGED];
    if(callback)
    {
        gentity_t *ent = SV_GentityNum(beingSpectatedClientNum);
        Scr_AddEntity(ent);
        int threadId = Scr_ExecEntThread(player, callback, 1);
        Scr_FreeThread(threadId);
    }
}

void Ext_WentFreeSpec(gentity_t *player)
{
    int callback = osjh_callbacks[OSJH_CB_WENTFREESPEC];
    if(callback)
    {
        int threadId = Scr_ExecEntThread(player, callback, 0);
        Scr_FreeThread(threadId);
    }
}

int Ext_AllowPlayerToEle(struct pmove_t *pmove)
{
    return (osjh_playerElevationPermissions[pmove->ps->clientNum]);
}