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

#include <deque>
#include <algorithm>

#include "../../../Main/Hooks/Hooks.h"
#include "../../Hacks.h"
#include "../Visuals/ESP/ESP.h"
#include "../../../Main/Entities/Entities.h"
#include "../../../Main/SDK/SDK.h"
#include "../../../Main/SDK/SDK/Singleton.h"


struct LagRecord
{
	LagRecord()
	{
		
	}

	

	void SaveRecord(IClientEntity *player);
	float_t m_flSimulationTime;
	int32_t m_nFlags;
	int32_t m_iPriority;
//	std::vector<LagRecord> m_PlayerTrack[64]; 
	
};



class CMBacktracking : public Singleton<CMBacktracking>
{
public:
	std::deque<LagRecord> m_LagRecord[64]; // All records
	std::pair<LagRecord, LagRecord> m_RestoreLagRecord[64]; // Used to restore/change
	std::deque<LagRecord> backtrack_records; // Needed to select records based on menu option.
	LagRecord current_record[64]; // Used for various other actions where we need data of the current lag compensated player

	inline void ClearHistory()
	{
		for (int i = 0; i < 64; i++)
			m_LagRecord[i].clear();
	}
	int lastincomingsequencenumber;

	void AnimationFix(IClientEntity * player);

	float GetLerpTime();

	bool IsTickValid(int tick);

	bool IsPlayerValid(IClientEntity * player);

	int GetPriorityLevel(IClientEntity * player, LagRecord * lag_record);

	void FrameUpdatePostEntityThink();

	bool StartLagCompensation(IClientEntity * player);

//	void tickoverride(IClientEntity * player, QAngle angles, float simtime);

	void RemoveBadRecords(int Idx, std::deque<LagRecord>& records);

	bool FindViableRecord(IClientEntity *player, LagRecord* record);
	void FinishLagCompensation(IClientEntity *player);

	
	std::vector<LagRecord> m_PlayerTrack[64]; //master record
	template<class T, class U>
	T clamp(T in, U low, U high);
};

class createmove_backtrack
{
public:

	void tickoverride(IClientEntity * player, QAngle angles, float simtime);
	void SaveRecord(IClientEntity * player);
	void anim_fix(IClientEntity * player);
	std::vector<LagRecord> m_PlayerTrack[64]; //master record

	float_t m_flSimulationTime;
	int32_t m_nFlags;
};
//extern createmove_backtrack* cmbacktrack;