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

#include "../SDK.h"
#include "singleton.hpp"
#include "../../MathFunctions/MathFunctions.h"


struct ImpactInfo {

	float x, y, z;
	long long time;
};

struct HitmarkerInfo {

	ImpactInfo pImpact;
	int pAlpha;
	int pDamage;
};

class Hitmarker : IGameEventListener2 {

public:
	void Initialize();
	void Paint();

private:
	void FireGameEvent(IGameEvent* pEvent) override;
	int GetEventDebugID(void) override;
	void PlayerHurt(IGameEvent* pEvent);
	void BulletImpact(IGameEvent* pEvent);
	std::vector<ImpactInfo> pImpacts;
	std::vector<HitmarkerInfo> pHitmarkers;
};

extern Hitmarker* pHitmarker;