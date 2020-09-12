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

#include "EnginePrediction.h"
#include "../../Main/NetVars/NetVars.h"
#include "../../Main/Xor/XorStr.hpp"
#include "../../Main/MathFunctions/MathFunctions.h"
#include "../../Hacks/Hacks.h"
BYTE bMoveData[200];

void start_prediction(CUserCmd* pCmd)
{
	auto m_local = hackManager.pLocal();
	if (Interfaces::MoveHelper && m_local->IsAlive())
	{
		float curtime = Interfaces::Globals->curtime;
		float frametime = Interfaces::Globals->frametime;
		int iFlags = m_local->GetFlags();
		Interfaces::Globals->curtime = (float)m_local->GetTickBase() * Interfaces::Globals->interval_per_tick;
		Interfaces::Globals->frametime = Interfaces::Globals->interval_per_tick;
		Interfaces::MoveHelper->SetHost(m_local);
		Interfaces::Prediction1->SetupMove(m_local, pCmd, nullptr, bMoveData);
		Interfaces::GameMovement->ProcessMovement(m_local, bMoveData);
		Interfaces::Prediction1->FinishMove(m_local, pCmd, bMoveData);
		Interfaces::MoveHelper->SetHost(0);
		Interfaces::Globals->curtime = curtime;
		Interfaces::Globals->frametime = frametime;
		*m_local->GetPointerFlags() = iFlags;
	}
}