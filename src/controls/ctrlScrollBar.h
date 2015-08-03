// $Id: ctrlScrollBar.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CTRLSCROLLBAR_H_INCLUDED
#define CTRLSCROLLBAR_H_INCLUDED

#pragma once

#include "Window.h"

class ctrlScrollBar : public Window
{
    public:
        ctrlScrollBar(Window* parent, uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t button_height, TextureColor tc, uint16_t pagesize);
        void SetPos(uint16_t scroll_pos);
        void SetRange(uint16_t scroll_range);
        void SetPageSize(uint16_t pagesize);

        uint16_t GetPageSize() const { return pagesize; }
        uint16_t GetPos() const { return scroll_pos; }

        virtual bool Msg_LeftUp(const MouseCoords& mc);
        virtual bool Msg_LeftDown(const MouseCoords& mc);
        virtual bool Msg_MouseMove(const MouseCoords& mc);
        virtual void Msg_ButtonClick(const uint32_t ctrl_id);

    protected:
        virtual bool Draw_(void);

        void Resize_(uint16_t width, uint16_t height);

    private:
        void CalculatePosition() { scroll_pos = (scrollbar_pos * scroll_range / scroll_height); }
        void CalculateScrollBar(uint16_t height = 0);

    private:
        uint16_t button_height;
        TextureColor tc;
        uint16_t pagesize;

        bool move;
        uint16_t scroll_range;
        uint16_t scroll_pos;
        uint16_t scroll_height;
        uint16_t scrollbar_height;
        uint16_t scrollbar_pos;

        int32_t last_y;
};

#endif // !CTRLSCROLLBAR_H_INCLUDED
