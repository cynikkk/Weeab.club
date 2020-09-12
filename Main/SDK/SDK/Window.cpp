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

#include "../../../Menu/GUI/GUI.h"
#include "../../../Menu/Interface/Interfaces.h"

void CWindow::SetPosition(int x, int y)
{
	m_x = x; m_y = y;
}
void CWindow::SetSize(int w, int h)
{
	m_iWidth = w;
	m_iHeight = h;
}
void CWindow::SetTitle(std::string title)
{
	Title = title;
}
void CWindow::RegisterTab(CTab* Tab)
{
	if (Tabs.size() == 0)
	{
		SelectedTab = Tab;
	}
	Tab->parent = this;
	Tabs.push_back(Tab);
}
RECT CWindow::GetClientArea()
{
	RECT client;
	client.left = m_x + 8;
	client.top = m_y + 1 + 27;
	client.right = m_iWidth - 4 - 12;
	client.bottom = m_iHeight - 2 - 8 - 26;
	return client;
}
RECT CWindow::GetTabArea()
{
	RECT client;
	client.left = m_x + 8;
	client.top = m_y + 1 + 27;
	client.right = m_iWidth - 4 - 12;
	client.bottom = 29;
	return client;
}
void CWindow::Open()
{
	m_bIsOpen = true;
}
void CWindow::Close()
{
	m_bIsOpen = false;
}
void CWindow::Toggle()
{
		m_bIsOpen = !m_bIsOpen;
		static ConVar * cvar = Interfaces::CVar->FindVar("cl_mouseenable");
		if (m_bIsOpen)
		{
			cvar->SetValue(0);
		}
		else
		{
			cvar->SetValue(1);
		}
}
CControl* CWindow::GetFocus()
{
	return FocusedControl;
}

/*
	Tabs
*/
void CTab::SetTitle(std::string name)
{
	Title = name;
}
void CTab::RegisterControl(CControl* control)
{
	control->parent = parent;
	Controls.push_back(control);
}