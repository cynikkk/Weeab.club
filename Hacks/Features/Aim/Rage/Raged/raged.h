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
#pragma once

#ifndef _CPREDICTION_H_
#define _CPREDICTION_H_
#include "../../../../../Main/SDK/SDK.h"
#include <vector>

class cPrediction
{
private:
	typedef struct matrixentry_s
	{
		std::vector < Vector > vecOrigins;	
		Vector	vOrigin;				
		DWORD	dwTime;					
		DWORD	dwFraction;
		int simulation;
		int oldsimulation;
		int simulationdifference;
	}matrixentry_t;
public:
	void ReportMove(Vector  vOrigin, int iIndex);
	void Reset(void);							
	bool bGetCurOrigin(Vector& vOrigin, int iIndex);
	bool bGetOrigin(Vector& vOrigin, int iIndex, DWORD dwTime);
	void UpdatePlayerPos();
protected:
	matrixentry_t m_Matrix[128];
};
extern cPrediction DataManager;
#endif