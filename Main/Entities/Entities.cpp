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

#include "Entities.h"
#include "../Offsets/Offsets.h"
#include "../../Menu/Interface/Interfaces.h"
#include "../Hooks/Hooks.h"

float intervalPerTick;
#define TICK_INTERVAL			(  )
#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / intervalPerTick ) )



C_BaseCombatWeapon* IClientEntity::GetWeapon2()
{
	static int iOffset = GET_NETVAR("DT_BaseCombatCharacter", "m_hActiveWeapon");
	ULONG pWeepEhandle = *(PULONG)((DWORD)this + iOffset);
	return (C_BaseCombatWeapon*)(Interfaces::EntList->GetClientEntityFromHandle((HANDLE)pWeepEhandle));
}

inline Vector ExtrapolateTick(Vector p0, Vector v0)
{
	return p0 + (v0 * intervalPerTick);
}
Vector IClientEntity::GetPredicted(Vector p0)
{
	return ExtrapolateTick(p0, this->GetVelocity());
}
void IClientEntity::CopyPoseParameters(float* dest)
{
	float* flPose = (float*)((DWORD)this + 0x2764);
	memcpy(dest, flPose, sizeof(float) * 24);
}

void IClientEntity::CopyAnimLayers(CAnimationLayer* dest)
{
	int count = 15;
	for (int i = 0; i < count; i++)
	{
		dest[i] = GetAnimOverlayX(i);
	}
}
Vector IClientEntity::GetBonePosAIZ(int i)
{
	matrix3x4 boneMatrix[128];
	if (this->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, Interfaces::Engine->GetLastTimeStamp()))
	{
		return Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]);
	}
	return Vector(0, 0, 0);
}