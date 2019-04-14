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


 
/**************************************************************************
 * Global variables                                                       *
 **************************************************************************/
 
static bool *osjh_playerElevationPermissions = NULL;
static int osjh_callbacks[OSJH_CB_COUNT];
static int previousbuttons[MAX_CLIENTS] = {0};

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

/**************************************************************************
 * Regular functions                                                      *
 **************************************************************************/

void osjh_init(void)
{
    printf("\na\n");
    osjh_playerElevationPermissions = (bool *)malloc(MAX_CLIENTS * sizeof(bool));
    printf("\nb\n");
    // Init callbacks
    osjh_callbacks[OSJH_CB_PLAYERCOMMAND]       = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_PlayerCommand",     qfalse);
    printf("\nc\n");
    osjh_callbacks[OSJH_CB_RPGFIRED]            = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_RPGFired",          qfalse);
    printf("\nd\n");
    osjh_callbacks[OSJH_CB_USERINFOCHANGED]     = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_UserInfoChanged",   qfalse);
    printf("\ne\n");
    osjh_callbacks[OSJH_CB_MELEEBUTTONPRESSED]  = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_MeleeButton",       qfalse);
    printf("\nf\n");
    osjh_callbacks[OSJH_CB_USEBUTTONPRESSED]    = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_UseButton",         qfalse);
    printf("\ng\n");
    osjh_callbacks[OSJH_CB_ATTACKBUTTONPRESSED] = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_AttackButton",      qfalse);
    printf("\nh\n");
}

void osjh_deinit(void)
{
    free(osjh_playerElevationPermissions);
}

void osjh_onFrame(void)
{
    mysql_handle_result_callbacks();
}

int osjh_getCallback(osjh_callback_t callbackType)
{
    return osjh_callbacks[callbackType];
}

void gsc_voidmethod(int id)
{
	stackPushInt(0);
}

void osjh_addMethodsAndFunctions(void)
{
    Scr_AddFunction("getcvar",      GScr_GetCvar,       qfalse);
    Scr_AddFunction("getcvarint",   GScr_GetCvarInt,    qfalse);
    Scr_AddFunction("getcvarfloat", GScr_GetCvarFloat,  qfalse);
    Scr_AddFunction("setcvar",      GScr_SetCvar,       qfalse);
    
    Scr_AddFunction("mysqla_create_query",          gsc_mysqla_create_level_query, qfalse);
    Scr_AddFunction("mysqla_initializer",           gsc_mysqla_initializer,        qfalse);
    Scr_AddFunction("mysql_real_connect",           gsc_mysqls_real_connect,       qfalse);
    Scr_AddFunction("mysql_query",                  gsc_mysqls_query,              qfalse);
    Scr_AddFunction("mysql_real_escape_string",     gsc_mysqls_real_escape_string, qfalse);
    
	Scr_AddFunction("printf",           Gsc_Utils_Printf,          qfalse);
	Scr_AddFunction("vectorscale",      Gsc_Utils_VectorScale,     qfalse);
	Scr_AddFunction("createrandomint",  Gsc_Utils_CreateRandomInt, qfalse);
    
    Scr_AddMethod("clientcommand",  PlayerCmd_ClientCommand, qfalse);
    Scr_AddMethod("allowelevate",   PlayerCmd_allowElevate,  qfalse);
    Scr_AddMethod("setclientcvar",  PlayerCmd_SetClientDvar, qfalse);
    
	Scr_AddMethod("jumpclearstateextended",         (xmethod_t)Gsc_Player_JumpClearStateExtended,  qfalse);
	Scr_AddMethod("getgroundentity",                (xmethod_t)Gsc_Player_GetGroundEntity,         qfalse);
	Scr_AddMethod("saveposition_initclient",        (xmethod_t)gsc_saveposition_initclient,        qfalse);
	Scr_AddMethod("saveposition_save",              (xmethod_t)gsc_saveposition_save,              qfalse);
	Scr_AddMethod("saveposition_selectsave",        (xmethod_t)gsc_saveposition_selectsave,        qfalse);
	Scr_AddMethod("saveposition_getangles",         (xmethod_t)gsc_saveposition_getangles,         qfalse);
	Scr_AddMethod("saveposition_getorigin",         (xmethod_t)gsc_saveposition_getorigin,         qfalse);
	Scr_AddMethod("saveposition_getgroundentity",   (xmethod_t)gsc_saveposition_getgroundentity,   qfalse);
    Scr_AddMethod("mysqla_create_query",            (xmethod_t)gsc_mysqla_create_entity_query,     qfalse);
    Scr_AddMethod("mysqla_ondisconnect",            (xmethod_t)gsc_mysqla_ondisconnect,            qfalse);
    Scr_AddMethod("leftbuttonpressed", PlayerCmd_MoveLeftButtonPressed, qfalse);
    Scr_AddMethod("rightbuttonpressed", PlayerCmd_MoveRightButtonPressed, qfalse);
    //TODO: add funcs below this line
    Scr_AddMethod("isthinking", (xmethod_t)gsc_voidmethod, qfalse);
    Scr_AddMethod("getjumpslowdowntimer", (xmethod_t)gsc_voidmethod, qfalse);
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

int Ext_AllowPlayerToEle(struct pmove_t *pmove)
{
    return (osjh_playerElevationPermissions[pmove->ps->clientNum]);
}