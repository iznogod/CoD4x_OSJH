#ifndef __OSJH_MAIN_H
#define __OSJH_MAIN_H

// Enums
typedef enum {
    OSJH_CB_PLAYERCOMMAND,
    OSJH_CB_RPGFIRED,
    OSJH_CB_COUNT, // Always keep this as last entry
} osjh_callback_t;

// Prototypes
void osjh_addMethodsAndFunctions(void);
int osjh_getCallback(osjh_callback_t callbackType);

#endif