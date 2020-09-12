/*
Copyright 2018 weeab.club

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once
#include "../../../Main/Hooks/Hooks.h"

class VarMapEntry_t {
public:
	unsigned short type;
	unsigned short m_bNeedsToInterpolate; // Set to false when this var doesn't
										  // need Interpolate() called on it anymore.
	void *data;
	void *watcher;
};

struct VarMapping_t {
	VarMapping_t() {
		m_nInterpolatedEntries = 0;
	}

	VarMapEntry_t* m_Entries;
	int m_nInterpolatedEntries;
	float m_lastInterpolationTime;
};

class CLagcompensation {
	VarMapping_t* GetVarMap(void* pBaseEntity) {
		return reinterpret_cast<VarMapping_t*>((DWORD)pBaseEntity + 0x24); //0x4C );
	}

public:
	void disable_interpolation(IClientEntity* m_entity) {
		VarMapping_t* map = GetVarMap(m_entity);
		if (!map) return;
		for (int i = 0; i < map->m_nInterpolatedEntries; i++) {
			VarMapEntry_t *e = &map->m_Entries[i];
			e->m_bNeedsToInterpolate = false;
		}
	}
};
extern CLagcompensation lagcompensation;