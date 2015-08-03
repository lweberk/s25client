// $Id: ctrlMultiline.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CTRL_MULTILINE_H_INCLUDED
#define CTRL_MULTILINE_H_INCLUDED

#include "ctrlRectangle.h"
#include <vector>

class ctrlMultiline : public Window
{
    public:

        /// Breite der Scrollbar
        static const uint16_t SCROLLBAR_WIDTH = 20;

    public:
        ctrlMultiline(Window* parent, uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, glArchivItem_Font* font, uint32_t format = 0);

        //void AddText(const std::string& text, uint32_t color);
        void AddString(const std::string& str, uint32_t color, bool scroll = true);
        uint32_t GetLineCount() { return unsigned(lines.size()); }
        /// Gibt den index-ten Eintrag zurück
        const std::string& GetLine(const uint32_t index) const { return lines[index].str; }
        void SetLine(const uint32_t index, const std::string& str, uint32_t color);

        /// Schaltet Box ein und aus
        void EnableBox(const bool enable) { draw_box = enable; }

        virtual bool Msg_LeftDown(const MouseCoords& mc);
        virtual bool Msg_LeftUp(const MouseCoords& mc);
        virtual bool Msg_WheelUp(const MouseCoords& mc);
        virtual bool Msg_WheelDown(const MouseCoords& mc);
        virtual bool Msg_MouseMove(const MouseCoords& mc);

    protected:
        virtual bool Draw_(void);

        void Resize_(uint16_t width, uint16_t height);

    private:

        TextureColor tc;
        glArchivItem_Font* font;
        uint32_t format;


        struct Line
        {
            std::string str;
            uint32_t color;
        };
        /// Die ganzen Strings
        std::vector<Line> lines;
        /// Anzahl der Zeilen, die in das Control passen
        uint32_t lines_in_control;

        /// Soll die Box gezeichnet werden?
        bool draw_box;
};

#endif /// !CTRLMULTILINE_H_INCLUDED
