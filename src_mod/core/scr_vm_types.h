#ifndef __SCR_VM_TYPES_H__
#define __SCR_VM_TYPES_H__

#include "q_shared_types.h"
#include "player.h"

typedef struct
{
    short emptystring;
    short active;
    short j_spine4;
    short j_helmet;
    short j_head;
    short all;
    short allies;
    short axis;
    short bad_path;
    short begin_firing;
    short cancel_location;
    short confirm_location;
    short crouch;
    short current;
    short damage;
    short dead;
    short death;
    short detonate;
    short direct;
    short dlight;
    short done;
    short empty;
    short end_firing;
    short entity;
    short explode;
    short failed;
    short fraction;
    short free;
    short goal;
    short goal_changed;
    short goal_yaw;
    short grenade;
    short grenade_danger;
    short grenade_fire;
    short grenade_pullback;
    short info_notnull;
    short invisible;
    short key1;
    short key2;
    short killanimscript;
    short left;
    short light;
    short movedone;
    short noclass;
    short none;
    short normal;
    short player;
    short position;
    short projectile_impact;
    short prone;
    short right;
    short reload;
    short reload_start;
    short rocket;
    short rotatedone;
    short script_brushmodel;
    short script_model;
    short script_origin;
    short snd_enveffectsprio_level;
    short snd_enveffectsprio_shellshock;
    short snd_channelvolprio_holdbreath;
    short snd_channelvolprio_pain;
    short snd_channelvolprio_shellshock;
    short stand;
    short suppression;
    short suppression_end;
    short surfacetype;
    short tag_aim;
    short tag_aim_animated;
    short tag_brass;
    short tag_butt;
    short tag_clip;
    short tag_flash;
    short tag_flash_11;
    short tag_flash_2;
    short tag_flash_22;
    short tag_flash_3;
    short tag_fx;
    short tag_inhand;
    short tag_knife_attach;
    short tag_knife_fx;
    short tag_laser;
    short tag_origin;
    short tag_weapon;
    short tag_player;
    short tag_camera;
    short tag_weapon_right;
    short tag_gasmask;
    short tag_gasmask2;
    short tag_sync;
    short target_script_trigger;
    short tempEntity;
    short top;
    short touch;
    short trigger;
    short trigger_use;
    short trigger_use_touch;
    short trigger_damage;
    short trigger_lookat;
    short truck_cam;
    short weapon_change;
    short weapon_fired;
    short worldspawn;
    short flashbang;
    short flash;
    short smoke;
    short night_vision_on;
    short night_vision_off;
    short MOD_UNKNOWN;
    short MOD_PISTOL_BULLET;
    short MOD_RIFLE_BULLET;
    short MOD_GRENADE;
    short MOD_GRENADE_SPLASH;
    short MOD_PROJECTILE;
    short MOD_PROJECTILE_SPLASH;
    short MOD_MELEE;
    short MOD_HEAD_SHOT;
    short MOD_CRUSH;
    short MOD_TELEFRAG;
    short MOD_FALLING;
    short MOD_SUICIDE;
    short MOD_TRIGGER_HURT;
    short MOD_EXPLOSIVE;
    short MOD_IMPACT;
    short script_vehicle;
    short script_vehicle_collision;
    short script_vehicle_collmap;
    short script_vehicle_corpse;
    short turret_fire;
    short turret_on_target;
    short turret_not_on_target;
    short turret_on_vistarget;
    short turret_no_vis;
    short turret_rotate_stopped;
    short turret_deactivate;
    short turretstatechange;
    short turretownerchange;
    short reached_end_node;
    short reached_wait_node;
    short reached_wait_speed;
    short near_goal;
    short veh_collision;
    short veh_predictedcollision;
    short auto_change;
    short back_low;
    short back_mid;
    short back_up;
    short begin;
    short call_vote;
    short freelook;
    short head;
    short intermission;
    short j_head_dup;
    short manual_change;
    short menuresponse;
    short neck;
    short pelvis;
    short pistol;
    short plane_waypoint;
    short playing;
    short spectator;
    short vote;
    short sprint_begin;
    short sprint_end;
    short tag_driver;
    short tag_passenger;
    short tag_gunner;
    short tag_wheel_front_left;
    short tag_wheel_front_right;
    short tag_wheel_back_left;
    short tag_wheel_back_right;
    short tag_wheel_middle_left;
    short tag_wheel_middle_right;
    short script_vehicle_collision_dup;
    short script_vehicle_collmap_dup;
    short script_vehicle_corpse_dup;
    short tag_detach;
    short tag_popout;
    short tag_body;
    short tag_turret;
    short tag_turret_base;
    short tag_barrel;
    short tag_engine_left;
    short tag_engine_right;
    short front_left;
    short front_right;
    short back_left;
    short back_right;
    short tag_gunner_pov;
} stringIndex_t;

typedef void (*xfunction_t)();

typedef struct scr_function_s
{
    struct scr_function_s *next;
    char *name;
    xfunction_t function;
    qboolean developer;
} scr_function_t;

typedef byte PrecacheEntry[8192];
typedef unsigned int sval_u;

#ifndef SCR_ENTREF_DEFINED
#define SCR_ENTREF_DEFINED
typedef int scr_entref_t;
#endif
/**************** Additional *************************/

typedef enum
{
    SCR_CB_SAY,
    SCR_CB_SCRIPTCOMMAND
} script_CallBacks_new_t;

typedef enum fieldtype_e
{
    F_INT = 0x0,
    F_FLOAT = 0x1,
    F_LSTRING = 0x2,
    F_STRING = 0x3,
    F_VECTOR = 0x4,
    F_ENTITY = 0x5,
    F_VECTORHACK = 0x6,
    F_OBJECT = 0x7,
    F_UNKNOWN = 0x8,
	F_MODEL = 0x9
} fieldtype_t;

typedef struct client_fields_s
{
    const char *name;
    int ofs;
    fieldtype_t type;
    void (__cdecl *setter)(gclient_t *, struct client_fields_s *);
    void (__cdecl *getter)(gclient_t *);
}client_fields_t;

typedef struct ent_field_s
{
  const char *name;
  int ofs;
  fieldtype_t type;
  void (__cdecl *callback)(gentity_t *, int);
} ent_field_t;

typedef enum
{
    SCR_UNK,
    SCR_POINTER,
    SCR_STRING,
    SCR_ISTRING, //(Localized String)
    SCR_VECTOR,
    SCR_FLOAT,
    SCR_INT
}scriptVarType_t;

typedef struct
{
    unsigned short type;
    unsigned short size;
}scrTypeSize_t;

struct VariableStackBuffer
{
  const char *pos;
  uint16_t size;
  uint16_t bufLen;
  uint16_t localId;
  char time;
  char buf[1];
};

/* 7500 */
union VariableUnion
{
  int intValue;
  float floatValue;
  unsigned int stringValue;
  const float *vectorValue;
  const char *codePosValue;
  unsigned int pointerValue;
  struct VariableStackBuffer *stackValue;
  unsigned int entityOffset;
};

#pragma pack(push, 1)
/* 7512 */
union ObjectInfo_u
{
  uint16_t size;
  uint16_t entnum;
  uint16_t nextEntId;
  uint16_t self;
};


/* 7513 */
struct ObjectInfo
{
  uint16_t refCount;
  union ObjectInfo_u u;
};

/* 7514 */
union VariableValueInternal_u
{
  uint16_t next;
  union VariableUnion u;
  struct ObjectInfo o;
};

/* 7515 */
union VariableValueInternal_w
{
  unsigned int status;
  unsigned int type;
  unsigned int name;
  unsigned int classnum;
  unsigned int notifyName;
  unsigned int waitTime;
  unsigned int parentLocalId;
};

/* 7516 */
union VariableValueInternal_v
{
  uint16_t next;
  uint16_t index;
};


typedef struct
{
  union VariableUnion u;
  int type;
}VariableValue;

/* 7510 */
union Variable_u
{
  uint16_t prev;
  uint16_t prevSibling;
};

/* 7511 */
struct Variable
{
  uint16_t id;
  union Variable_u u;
};

/* 7517 */
typedef struct 
{
  struct Variable hash;
  union VariableValueInternal_u u;
  union VariableValueInternal_w w;
  union VariableValueInternal_v v;
  uint16_t nextSibling;
}VariableValueInternal;


typedef struct
{
  const char *fieldBuffer;
  uint16_t canonicalStrCount;
  byte developer;
  byte developer_script;
  byte evaluate;
  byte pad[3];
  const char *error_message;
  int error_index;
  unsigned int time;
  unsigned int timeArrayId;
  unsigned int pauseArrayId;
  unsigned int levelId;
  unsigned int gameId;
  unsigned int animId;
  unsigned int freeEntList;
  unsigned int tempVariable;
  byte bInited;
  byte pad2;
  uint16_t savecount;
  unsigned int checksum;
  unsigned int entId;
  unsigned int entFieldName;
  struct HunkUser *programHunkUser;
  const char *programBuffer;
  const char *endScriptBuffer;
  uint16_t saveIdMap[24574];
  uint16_t saveIdMapRev[24574];
}scrVarPub_t;


struct function_stack_t
{
  const char *pos;
  unsigned int localId;
  unsigned int localVarCount;
  VariableValue *top;
  VariableValue *startTop;
};


struct function_frame_t
{
  struct function_stack_t fs;
  int topType;
};

typedef struct
{
  unsigned int *localVars;
  VariableValue *maxstack;
  int function_count;
  struct function_frame_t *function_frame;
  VariableValue *top;
  byte debugCode;
  byte abort_on_error;
  byte terminal_error;
  byte pad;
  unsigned int inparamcount;
  unsigned int outparamcount;
  struct function_frame_t function_frame_start[32];
  VariableValue stack[2048];
}scrVmPub_t;

#pragma pack(pop)

typedef enum
{
    SCR_FH_FILE,
    SCR_FH_PARALIST,
    SCR_FH_INDEXPARALIST
} scr_fileHandleType_t;


typedef struct
{
    FILE* fh;
    scr_fileHandleType_t type;
    char filename[MAX_QPATH];
    int baseOffset;
    int fileSize;
} scr_fileHandle_t;

#endif
