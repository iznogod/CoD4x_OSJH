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
    OSJH_CB_COUNT, // Always keep this as last entry
} osjh_callback_t;

#ifdef __cplusplus
extern "C" {
#endif

#include "scr_vm.h"

// Prototypes
void osjh_addMethodsAndFunctions(void);
int osjh_getCallback(osjh_callback_t callbackType);
void osjh_init(void);
void osjh_onFrame(void);
void Ext_RPGFiredCallback(gentity_t *player, gentity_t *rpg);
int Ext_AllowPlayerToEle(struct pmove_t *pmove);

#ifdef __cplusplus
}
#endif

#endif