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
class CMoveData {
public:
	bool m_bFirstRunOfFunctions : 1;
	bool m_bGameCodeMovedPlayer : 1;
	bool m_bNoAirControl : 1;

	unsigned long m_nPlayerHandle;
	int m_nImpulseCommand;
	QAngle m_vecViewAngles;
	QAngle m_vecAbsViewAngles;
	int m_nButtons;
	int m_nOldButtons;
	float m_flForwardMove;
	float m_flSideMove;
	float m_flUpMove;

	float m_flMaxSpeed;
	float m_flClientMaxSpeed;

	Vector m_vecVelocity;
	Vector m_vecOldVelocity;
	float somefloat;
	QAngle m_vecAngles;
	QAngle m_vecOldAngles;

	float m_outStepHeight;
	Vector m_outWishVel;
	Vector m_outJumpVel;

	Vector m_vecConstraintCenter;
	float m_flConstraintRadius;
	float m_flConstraintWidth;
	float m_flConstraintSpeedFactor;
	bool m_bConstraintPastRadius;

	void SetAbsOrigin(const Vector& vec);
	const Vector& GetOrigin() const;

private:
	Vector m_vecAbsOrigin;
};

class CPredictionSystem {
public:
	void EnginePrediction(CUserCmd* pCmd);

private:
	int iTickBaseBackup;
	int iFlagsBackup;
	int iButtonsBackup;
	int* m_pPredictionRandomSeed;
	int* m_pSetPredictionPlayer;
};
