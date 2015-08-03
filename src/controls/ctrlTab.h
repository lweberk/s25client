// $Id: ctrlTab.h 9357 2014-04-25 15:35:25Z FloSoft $
//
// Copyright (c) 2005 - 2011 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Return To The Roots is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Return To The Roots. If not, see <http://www.gnu.org/licenses/>.
#ifndef CTRLTAB_H_INCLUDED
#define CTRLTAB_H_INCLUDED

#pragma once

#include "Window.h"

#define MAX_TAB_COUNT 20

class ctrlGroup;

class ctrlTab : public Window
{
    public:
        /// Konstruktor von @p ctrlTab.
        ctrlTab(Window* parent, uint32_t id, uint16_t x, uint16_t y, uint16_t width);

        /// fügt eine Tab hinzu.
        ctrlGroup* AddTab(glArchivItem_Bitmap* image, std::string tooltip, const uint32_t id);
        /// löscht alle Tabs.
        void DeleteAllTabs(void);
        /// aktiviert eine bestimmte Tabseite.
        void SetSelection(uint16_t nr, bool notify = false);
        /// Gibt ID des aktuell gewählten Tabs zurück
        uint32_t GetCurrentTab(void) const { return tabs[tab_selection]; }
        /// Gibt Tab-Group zurück, über die die Steuerelemente der Tab angesprochen werden können
        ctrlGroup* GetGroup(const uint32_t tab_id);
        /// Gibt aktuell ausgewählte Tab-Gruppe zürck
        ctrlGroup* GetCurrentGroup() { return GetGroup(GetCurrentTab()); }

        virtual void Msg_Group_ButtonClick(const uint32_t group_id, const uint32_t ctrl_id);
        virtual void Msg_Group_EditEnter(const uint32_t group_id, const uint32_t ctrl_id);
        virtual void Msg_Group_EditChange(const uint32_t group_id, const uint32_t ctrl_id);
        virtual void Msg_Group_TabChange(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t tab_id);
        virtual void Msg_Group_ListSelectItem(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_ComboSelectItem(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_CheckboxChange(const uint32_t group_id, const uint32_t ctrl_id, const bool checked);
        virtual void Msg_Group_ProgressChange(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t position);
        virtual void Msg_Group_ScrollShow(const uint32_t group_id, const uint32_t ctrl_id, const bool visible);
        virtual void Msg_Group_OptionGroupChange(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_Timer(const uint32_t group_id, const uint32_t ctrl_id);
        virtual void Msg_Group_TableSelectItem(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_TableRightButton(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_TableLeftButton(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_ButtonClick(const uint32_t ctrl_id);
        virtual bool Msg_LeftDown(const MouseCoords& mc);
        virtual bool Msg_LeftUp(const MouseCoords& mc);
        virtual bool Msg_WheelUp(const MouseCoords& mc);
        virtual bool Msg_WheelDown(const MouseCoords& mc);
        virtual bool Msg_MouseMove(const MouseCoords& mc);

    protected:
        virtual bool Draw_(void);

    private:
        uint16_t tab_count;
        uint16_t tab_selection;

        uint32_t tabs[MAX_TAB_COUNT];
};

#endif // !CTRLTAB_H_INCLUDED
