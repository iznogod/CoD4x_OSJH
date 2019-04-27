#ifndef __OSJH_MAIN_H
#define __OSJH_MAIN_H

// Enums
typedef enum {
    OSJH_CB_PLAYERCOMMAND,
    OSJH_CB_RPGFIRED,
    OSJH_CB_USERINFOCHANGED,
    OSJH_CB_MELEEBUTTONPRESSED,
    OSJH_CB_USEBUTTONPRESSED,
    OSJH_CB_ATTACKBUTTONPRESSED,
    OSJH_CB_STARTJUMP,
    OSJH_CB_MOVEFORWARD,
    OSJH_CB_MOVERIGHT,
    OSJH_CB_MOVEBACKWARD,
    OSJH_CB_MOVELEFT,
    OSJH_CB_SPECTATORCLIENTCHANGED,
    OSJH_CB_WENTFREESPEC,
    OSJH_CB_COUNT, // Always keep this as last entry
} osjh_callback_t;

#ifdef __cplusplus
extern "C" {
#endif

#include "scr_vm.h"
#include "bg_public.h"

// Prototypes
void osjh_addMethodsAndFunctions(void);
int osjh_getCallback(osjh_callback_t callbackType);
void osjh_init(void);
void osjh_onFrame(void);
void osjh_onStartJump(struct pmove_t *pm);
void osjh_onClientMoveCommand(client_t *client, usercmd_t *ucmd);
void Ext_RPGFiredCallback(gentity_t *player, gentity_t *rpg);
void Ext_SpectatorClientChanged(gentity_t *player, int beingSpectatedClientNum);
void Ext_WentFreeSpec(gentity_t *player);
int Ext_AllowPlayerToEle(struct pmove_t *pmove);

#ifdef __cplusplus
}
#endif

#endif