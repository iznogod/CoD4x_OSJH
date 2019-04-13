// OSJH main file since working with plugins is not desired for this project

/**************************************************************************
 * Includes                                                               *
 **************************************************************************/
 
#include <stdlib.h>
#include <stdbool.h>
 
#include "osjh_main.h"

#include "scr_vm.h"
#include "xassets/weapondef.h"
#include "bg_public.h"

/**************************************************************************
 * Extern functions without available prototype                           *
 **************************************************************************/

extern int GScr_LoadScriptAndLabel(const char *scriptName, const char *labelName, qboolean mandatory);
 
/**************************************************************************
 * Defines                                                                *
 **************************************************************************/
 
#define TMP_MAXCLIENTS  64 // TODO: Dynamic calculation based on max clients
 
/**************************************************************************
 * Global variables                                                       *
 **************************************************************************/
 
static bool *osjh_playerElevationPermissions = NULL;
static uint32_t osjh_callbacks[OSJH_CB_COUNT];

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

/**************************************************************************
 * Regular functions                                                      *
 **************************************************************************/

void osjh_init(void)
{
    osjh_playerElevationPermissions = malloc(TMP_MAXCLIENTS * sizeof(bool));
    
    // Init callbacks
    osjh_callbacks[OSJH_CB_PLAYERCOMMAND]   = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_PlayerCommand", 0);
    osjh_callbacks[OSJH_CB_RPGFIRED]        = GScr_LoadScriptAndLabel("maps/mp/gametypes/_callbacksetup", "CodeCallback_RPGFired",      0);
}

void osjh_deinit(void)
{
    free(osjh_playerElevationPermissions);
}

int osjh_getCallback(osjh_callback_t callbackType)
{
    return osjh_callbacks[callbackType];
}

void osjh_addMethodsAndFunctions(void)
{
    Scr_AddFunction("getcvar",      GScr_GetCvar,       0);
    Scr_AddFunction("getcvarint",   GScr_GetCvarInt,    0);
    Scr_AddFunction("getcvarfloat", GScr_GetCvarFloat,  0);
    Scr_AddFunction("setcvar",      GScr_SetCvar,       0);
    
    Scr_AddMethod("clientcommand",  PlayerCmd_ClientCommand, 0);
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