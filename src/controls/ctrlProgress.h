// $Id: ctrlProgress.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CTRLPROGRESS_H_INCLUDED
#define CTRLPROGRESS_H_INCLUDED

#pragma once

#include "Window.h"

class ctrlProgress : public Window
{
    public:
        ctrlProgress(Window* parent,
                     const uint32_t id,
                     const uint16_t x,
                     const uint16_t y,
                     const uint16_t width,
                     const uint16_t height,
                     const TextureColor tc,
                     uint16_t button_minus,
                     uint16_t button_plus,
                     const uint16_t maximum,
                     const uint16_t x_padding,
                     const uint16_t y_padding,
                     const uint32_t force_color,
                     const std::string& tooltip,
                     const std::string& button_minus_tooltip = NULL,
                     const std::string& button_plus_tooltip = NULL,
                     uint16_t* const write_val = NULL);

        void SetPosition(uint16_t position);
        const uint16_t& GetPosition(void) const { return position; }

        virtual void Msg_ButtonClick(const uint32_t ctrl_id);
        virtual bool Msg_LeftDown(const MouseCoords& mc);
        virtual bool Msg_LeftUp(const MouseCoords& mc);
        virtual bool Msg_WheelUp(const MouseCoords& mc);
        virtual bool Msg_WheelDown(const MouseCoords& mc);
        virtual bool Msg_MouseMove(const MouseCoords& mc);

    protected:
        virtual bool Draw_(void);

    private:
        TextureColor tc;

        uint16_t position;
        uint16_t minimum;
        uint16_t maximum;

        // Abstand vom Button zur Leiste (Leiste wird entsprechend verkleinert!)
        uint16_t x_padding, y_padding;

        /// Falls der Balken immer eine bestimmte Farben haben soll, ansonsten 0 setzen!
        uint32_t force_color;

        /// Optionaler Pointer auf eine Variable,
};

#endif // !CTRLPROGRESS_H_INCLUDED
