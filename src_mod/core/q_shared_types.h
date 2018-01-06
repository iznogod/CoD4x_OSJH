#ifndef __Q_SHARED_TYPES_H__
#define __Q_SHARED_TYPES_H__

// Standalone types from "q_shared.h" file.

#include "q_math_types.h"

typedef unsigned int long DWORD;
typedef unsigned short WORD;

typedef unsigned char byte;
typedef enum {
    qfalse = 0,
    qtrue
} qboolean;

typedef int fileHandle_t;

typedef struct
{
    int parents;
    qboolean last;
    void *stack[48];
    char *buffer;
    int bufposition;
    char *encoding;
    size_t buffersize;
} xml_t;

typedef union {
    int i;
    byte rgba[4];
} ucolor_t;

// parameters to the main Error routine
typedef enum {
    ERR_UNKNOWN = 0,
    ERR_FATAL,            // exit the entire game with a popup window
    ERR_DROP,             // print to console and disconnect from game
    ERR_SERVERDISCONNECT, // don't kill server
    ERR_DISCONNECT,       // client disconnected from the server
    ERR_SCRIPT            // script error occured
} errorParm_t;

// plane_t structure
// !!! if this is changed, it must be changed in asm code too !!!
typedef struct cplane_s
{ //Nothing validated
    vec3_t normal;
    float dist;
    byte type;     // for fast side tests: 0,1,2 = axial, 3 = nonaxial
    byte signbits; // signx + (signy<<1) + (signz<<2), used as lookup during collision
    byte pad[2];
} cplane_t;

typedef enum {
    OBJST_EMPTY = 0x0,
    OBJST_ACTIVE = 0x1,
    OBJST_INVISIBLE = 0x2,
    OBJST_DONE = 0x3,
    OBJST_CURRENT = 0x4,
    OBJST_FAILED = 0x5,
    OBJST_NUMSTATES = 0x6,
} objectiveState_t;

typedef struct objective_s
{
    objectiveState_t state;
    float origin[3];
    int entNum;
    int teamNum;
    int icon;
} objective_t;

typedef enum {
    PLAYER_OFFHAND_SECONDARY_SMOKE = 0x0,
    PLAYER_OFFHAND_SECONDARY_FLASH = 0x1,
    PLAYER_OFFHAND_SECONDARIES_TOTAL = 0x2,
} OffhandSecondaryClass_t;

typedef enum {
    PLAYERVIEWLOCK_NONE = 0x0,
    PLAYERVIEWLOCK_FULL = 0x1,
    PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
    PLAYERVIEWLOCKCOUNT = 0x3,
} ViewLockTypes_t;

typedef enum {
    ACTIONSLOTTYPE_DONOTHING = 0x0,
    ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
    ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
    ACTIONSLOTTYPE_NIGHTVISION = 0x3,
    ACTIONSLOTTYPECOUNT = 0x4,
} ActionSlotType_t;

typedef struct
{
    unsigned int index;
} ActionSlotParam_SpecifyWeapon_t;

typedef struct
{
    ActionSlotParam_SpecifyWeapon_t specifyWeapon;
} ActionSlotParam_t;

#define MAX_HUDELEMENTS 31

typedef enum {
    HE_TYPE_FREE = 0x0,
    HE_TYPE_TEXT = 0x1,
    HE_TYPE_VALUE = 0x2,
    HE_TYPE_PLAYERNAME = 0x3,
    HE_TYPE_MAPNAME = 0x4,
    HE_TYPE_GAMETYPE = 0x5,
    HE_TYPE_MATERIAL = 0x6,
    HE_TYPE_TIMER_DOWN = 0x7,
    HE_TYPE_TIMER_UP = 0x8,
    HE_TYPE_TENTHS_TIMER_DOWN = 0x9,
    HE_TYPE_TENTHS_TIMER_UP = 0xA,
    HE_TYPE_CLOCK_DOWN = 0xB,
    HE_TYPE_CLOCK_UP = 0xC,
    HE_TYPE_WAYPOINT = 0xD,
    HE_TYPE_COUNT = 0xE,
} he_type_t;

/* 6853 */
typedef struct
{
    char r;
    char g;
    char b;
    char a;
} hudelem_colorsplit_t;

/* 6854 */
typedef union {
    hudelem_colorsplit_t split;
    int rgba;
} hudelem_color_t;

typedef struct hudelem_s
{
    he_type_t type;
    float x;
    float y;
    float z;
    int targetEntNum;
    float fontScale;
    int font;
    int alignOrg;
    int alignScreen;
    hudelem_color_t color;
    hudelem_color_t fromColor; //0x28
    int fadeStartTime;         //0x2c
    int fadeTime;
    int label;
    int width;
    int height; //0x3C
    int materialIndex;
    int offscreenMaterialIdx; //0x44
    int fromWidth;
    int fromHeight;
    int scaleStartTime;
    int scaleTime;
    float fromX;
    float fromY;
    int fromAlignOrg;
    int fromAlignScreen;
    int moveStartTime;
    int moveTime;
    int time;
    int duration;
    float value;
    int text;
    float sort;
    hudelem_color_t glowColor; //0x84
    int fxBirthTime;
    int fxLetterTime;
    int fxDecayStartTime;
    int fxDecayDuration;
    int soundID;
    int flags;
} hudelem_t;

typedef struct hudElemState_s
{
    hudelem_t current[MAX_HUDELEMENTS];
    hudelem_t archival[MAX_HUDELEMENTS];
} hudElemState_t;

// mode parm for FS_FOpenFile
typedef enum {
    FS_READ,
    FS_WRITE,
    FS_APPEND,
    FS_APPEND_SYNC
} fsMode_t;

typedef enum {
    FS_SEEK_CUR,
    FS_SEEK_END,
    FS_SEEK_SET
} fsOrigin_t;

#endif