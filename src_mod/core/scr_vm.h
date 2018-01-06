/*
===========================================================================
    Copyright (C) 2010-2013  Ninja and TheKelm

    This file is part of CoD4X18-Server source code.

    CoD4X18-Server source code is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    CoD4X18-Server source code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>
===========================================================================
*/



#ifndef __SCR_VM_H__
#define __SCR_VM_H__

#define SCRSTRUCT_ADDR 0x895bf08
#define STRINGINDEX_ADDR 0x836fe20
#define stringIndex (*((stringIndex_t*)(STRINGINDEX_ADDR)))
#define scrVarGlob (((VariableValueInternal*)( 0x8a64e80 )))
#define scrVarGlob_high (((VariableValueInternal*)( 0x8a64e80 + 16 * 32770 )))
#define scrVarPub (*((scrVarPub_t*)( 0x8be4e80 )))
#define scrVmPub (*((scrVmPub_t*)( 0x8c06320 )))
#define g_script_error_level *(int*)(0x8c0631c)
#define g_threadStartingTime *(int*)(0x8c0a678)

#include "q_math.h"
#include "entity.h"
#include "player.h"
#include "g_hud.h"
#include "filesystem.h"
#include "g_sv_shared.h"
#include "scr_vm_types.h"

extern int script_CallBacks_new[8];

void __cdecl Scr_InitVariables(void);			//VM
void __cdecl Scr_Init(void);			//VM_Init
void __cdecl Scr_Settings(int, int, int);
void __cdecl Scr_AddEntity(gentity_t* ent);
void __cdecl Scr_Cleanup(void);
void __cdecl GScr_Shutdown(void);
int __cdecl Scr_AllocArray();
int __cdecl AllocObject();
int __cdecl Scr_GetNumParam( void );
int __cdecl Scr_GetInt( unsigned int );
float __cdecl Scr_GetFloat( unsigned int );
char* __cdecl Scr_GetString( unsigned int );
gentity_t* __cdecl Scr_GetEntity( unsigned int );
short __cdecl Scr_GetConstString( unsigned int );
unsigned int __cdecl Scr_GetType( unsigned int );
unsigned int __cdecl Scr_GetPointerType( unsigned int );
void __cdecl Scr_GetVector( unsigned int, float* );
unsigned int __cdecl Scr_GetObject( unsigned int );

int Scr_GetFunc(unsigned int paramnum);
extern char* (__cdecl *Scr_GetLocalizedString)(unsigned int arg);

/* Scr_Error
 *
 * Throws script runtime error with 'string' description.
 * Asterisk points to function name.
 */
void __cdecl Scr_Error( const char *string);
void __cdecl Scr_SetLoading( qboolean );

/* Scr_ParamError
 *
 * Throws script runtime error with 'string' description.
 * Asterisk points to 'paramNum' function parameter.
 */
void __cdecl Scr_ParamError( int paramNum, const char *string);

/* Scr_ObjectError
 *
 * Throws script runtime error with 'string' description.
 * Asterisk points to function caller.
 */
void __cdecl Scr_ObjectError( const char *string);

void __cdecl Scr_AddInt(int value);
void __cdecl Scr_AddFloat(float);
void __cdecl Scr_AddBool(qboolean);
void __cdecl Scr_AddString(const char *string);
void __cdecl Scr_AddConstString(int strindex);
void __cdecl Scr_AddUndefined(void);
void __cdecl Scr_AddVector( vec3_t vec );
void __cdecl Scr_AddArray( void );
void __cdecl Scr_MakeArray( void );
void __cdecl Scr_AddArrayKey( int strIdx );
void __cdecl Scr_Notify( gentity_t*, unsigned short, unsigned int);
void __cdecl Scr_NotifyNum( int, unsigned int, unsigned int, unsigned int);
/*Not working :(  */
void __cdecl Scr_PrintPrevCodePos( int printDest, const char* pos, qboolean unk2 );
int __cdecl Scr_GetFunctionHandle( const char* scriptName, const char* labelName);
short __cdecl Scr_ExecEntThread( gentity_t* ent, int callbackHook, unsigned int numArgs);
short __cdecl Scr_ExecThread( int callbackHook, unsigned int numArgs);
void __cdecl Scr_FreeThread( short threadId);
unsigned int __cdecl Scr_CreateCanonicalFilename( const char* name );
//Unknown real returntype
unsigned int __cdecl FindVariable( unsigned int, unsigned int );
unsigned int __cdecl FindObject( unsigned int );
unsigned int __cdecl GetNewVariable( unsigned int, unsigned int );
void * __cdecl TempMalloc( int );
void __cdecl ScriptParse( sval_u* , byte);
unsigned int __cdecl GetObjectA( unsigned int );
unsigned int __cdecl GetObject( unsigned int );
unsigned int __cdecl GetVariable( unsigned int, unsigned int );
void __cdecl ScriptCompile( sval_u, unsigned int, unsigned int, PrecacheEntry*, int);
void* __cdecl Scr_AddSourceBuffer( const char*, const char*, const char*, byte );
void __cdecl Scr_InitAllocNode( void );
void __cdecl Scr_BeginLoadScripts( void );
void __cdecl Scr_SetClassMap( unsigned int );
#define Scr_AddClassField ((void (__cdecl *)(unsigned int classnum, const char* name, unsigned short int offset))0x081535BA)
void __cdecl Scr_SetGenericField( void*, fieldtype_t, int );
void __cdecl Scr_GetGenericField( void*, fieldtype_t, int );
void __cdecl Scr_SetString(unsigned short *strindexptr, unsigned const stringindex);
int __cdecl Scr_AllocString(const char* string);
void Scr_InitSystem();
int GetArraySize(int);
void RemoveRefToValue(scriptVarType_t type, union VariableUnion val);

void __cdecl GScr_AddFieldsForHudElems( void );
void __cdecl GScr_AddFieldsForRadiant( void );
void __cdecl Scr_AddHudElem( game_hudelem_t* );
void __cdecl Scr_FreeHudElem( game_hudelem_t* );
void __cdecl Scr_EndLoadScripts( void );
void __cdecl Scr_ConstructMessageString( int, int, const char*, char*, unsigned int );

qboolean Scr_PlayerSay(gentity_t*, int mode, const char* text);
qboolean Scr_ScriptCommand(int clientnum, const char* cmd, const char* args);

void GScr_LoadGameTypeScript(void);
unsigned int Scr_LoadScript(const char* scriptname, PrecacheEntry *precache, int iarg_02);
qboolean Scr_ExecuteMasterResponse(char* s);
void Scr_AddStockFunctions();
void Scr_AddStockMethods();
void Scr_ScriptPreCompile( void *scr_buffer_handle, char *filepath );

qboolean Scr_AddFunction( const char *cmd_name, xfunction_t function, qboolean developer);
qboolean Scr_RemoveFunction( const char *cmd_name );
void Scr_ClearFunctions( void );
__cdecl void* Scr_GetFunction( const char** v_functionName, qboolean* v_developer );
qboolean Scr_AddMethod( const char *cmd_name, xfunction_t function, qboolean developer);
qboolean Scr_RemoveMethod( const char *cmd_name );
void Scr_ClearMethods( void );
__cdecl void* Scr_GetMethod( const char** v_functionName, qboolean* v_developer );
qboolean Scr_IsSyscallDefined( const char *name );
void __regparm3 VM_Notify(int, int, VariableValue* val);
int __cdecl FindEntityId(int, int);

#define MAX_SCRIPT_FILEHANDLES 10

typedef enum{
    SCR_FH_FILE,
    SCR_FH_PARALIST,
    SCR_FH_INDEXPARALIST
}scr_fileHandleType_t;


typedef struct{
    FILE* fh;
    scr_fileHandleType_t type;
    char filename[MAX_QPATH];
    int baseOffset;
    int fileSize;
}scr_fileHandle_t;

qboolean Scr_FS_CloseFile( scr_fileHandle_t* f );
int Scr_FS_ReadLine( void *buffer, int len, fileHandle_t f );
qboolean Scr_FS_AlreadyOpened(char* qpath);
qboolean Scr_FS_FOpenFile( const char *filename, fsMode_t mode, scr_fileHandle_t* f );
fileHandle_t Scr_OpenScriptFile( char* qpath, scr_fileHandleType_t ft, fsMode_t mode);
qboolean Scr_CloseScriptFile( fileHandle_t fh);
int Scr_FS_Read( void *buffer, int len, fileHandle_t f );
int Scr_FS_Write( const void *buffer, int len, fileHandle_t h );
int Scr_FS_Seek( fileHandle_t f, long offset, int origin );
qboolean Scr_FileExists( const char* filename );

void GScr_MakeCvarServerInfo(void);
void GScr_SetCvar();
void GScr_GetCvarFloat();
void GScr_GetCvarInt();
void GScr_GetCvar();
void GScr_AddScriptCommand();
void RuntimeError(char *a3, int arg4, char *message, char *a4);
void ClientScr_GetName(gclient_t* gcl);
const char* Scr_GetPlayername(gentity_t* gent);


// Safe function to get gentity for num passed by script call "ent function()"
gentity_t* VM_GetGEntityForNum(scr_entref_t num);
gclient_t* VM_GetGClientForEntity(gentity_t* ent);
gclient_t* VM_GetGClientForEntityNumber(scr_entref_t num);
client_t* VM_GetClientForEntityNumber(scr_entref_t num); // Mainly for pressed buttons detection.

// Returns pointer to new 'fields_1' array. To be used in patching purposes.
ent_field_t* __internalGet_fields_1();

#endif
