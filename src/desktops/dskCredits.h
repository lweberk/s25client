// $Id: dskCredits.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef dskCREDITS_H_INCLUDED
#define dskCREDITS_H_INCLUDED

#pragma once

#include "Desktop.h"

#include <list>

/// Klasse des Credits Desktops.
class dskCredits : public Desktop
{
    public:
        /// Konstruktor von @p dskCredits.
        dskCredits();
        ~dskCredits();

    private:
        bool Msg_KeyDown(const KeyEvent& ke);
        void Msg_PaintAfter();
        void Msg_ButtonClick(const uint32_t ctrl_id);

        bool Close(void);

        struct CreditsEntry
        {
            std::string title;
            std::string lastLine;
            int32_t picId;
            struct Line
            {
                Line(std::string l, uint32_t c = 0) : line(l), column(c) { }
                std::string line;
                uint32_t column;
            };
            std::list<Line> lines;
        };

        std::list<CreditsEntry> entries;
        std::list<dskCredits::CreditsEntry>::iterator it;

        struct Bob
        {
            uint32_t id;
            bool hasWare;
            bool isFat;
            uint32_t direction;
            uint8_t speed;
            uint32_t animationStep;
            int16_t x;
            int16_t y;
            uint32_t color;
        };

        std::list<Bob> bobs;

        uint32_t startTime;
        uint32_t bobTime;
        uint32_t bobSpawnTime;
};

#endif // !dskCREDITS_H_INCLUDED
