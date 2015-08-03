// $Id: ctrlGroup.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CTRLGROUP_H_INCLUDED
#define CTRLGROUP_H_INCLUDED

#pragma once

#include "Window.h"

class ctrlGroup : public Window
{
    public:
        ctrlGroup(Window* parent, uint32_t id, bool scale = false);

        void Msg_ScreenResize(const ScreenResizeEvent& sr);

        virtual void Msg_ButtonClick(const uint32_t ctrl_id);
        virtual void Msg_EditEnter(const uint32_t ctrl_id);
        virtual void Msg_EditChange(const uint32_t ctrl_id);
        virtual void Msg_TabChange(const uint32_t ctrl_id, const uint16_t tab_id);
        virtual void Msg_ListSelectItem(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_ComboSelectItem(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_CheckboxChange(const uint32_t ctrl_id, const bool checked);
        virtual void Msg_ProgressChange(const uint32_t ctrl_id, const uint16_t position);
        virtual void Msg_ScrollShow(const uint32_t ctrl_id, const bool visible);
        virtual void Msg_OptionGroupChange(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Timer(const uint32_t ctrl_id);
        virtual void Msg_TableSelectItem(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_TableRightButton(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_TableLeftButton(const uint32_t ctrl_id, const uint16_t selection);

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

        virtual bool Msg_LeftDown(const MouseCoords& mc);
        virtual bool Msg_RightDown(const MouseCoords& mc);
        virtual bool Msg_LeftUp(const MouseCoords& mc);
        virtual bool Msg_RightUp(const MouseCoords& mc);
        virtual bool Msg_WheelUp(const MouseCoords& mc);
        virtual bool Msg_WheelDown(const MouseCoords& mc);
        virtual bool Msg_MouseMove(const MouseCoords& mc);
        virtual bool Msg_KeyDown(const KeyEvent& ke);

    protected:
        virtual bool Draw_(void);
};

#endif // !CTRLGROUP_H_INCLUDED
