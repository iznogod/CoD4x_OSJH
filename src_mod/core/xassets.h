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



#ifndef __XASSETS_H__
#define __XASSETS_H__

#include "q_shared.h"
#include "dobj.h"
#include "xassets_types.h"

void R_Init();
void __cdecl DB_SetInitializing(qboolean State_);
qboolean __cdecl DB_FileExists(const char* filename, int mode);
qboolean __cdecl DB_ModFileExists();
__cdecl unsigned int DB_GetXAssetTypeSize(int Type_);
void XAssets_PatchLimits(void);
void Material_DirtyTechniqueSetOverrides();
void DB_LoadXAssets_Hook(XZoneInfo*, unsigned int assetscount);
void DB_BuildOverallocatedXAssetList(char* configstring, int len);
void DB_SyncXAssets();
void DB_AddUserMapDir(const char *dir);
void DB_ReferencedFastFiles(char* g_zoneSumList, char* g_zoneNameList, int maxsize);

#endif

