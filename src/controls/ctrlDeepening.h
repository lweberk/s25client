// $Id: ctrlDeepening.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CTRLDEEPENING_H_INCLUDED
#define CTRLDEEPENING_H_INCLUDED

#pragma once

#include "ctrlText.h"
#include "ctrlRectangle.h"

class ctrlDeepening : public ctrlText
{
    public:
        ctrlDeepening(Window* parent, uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, const std::string& text, glArchivItem_Font* font, uint32_t color);

    protected:
        virtual bool Draw_(void);
        /// Abgeleitete Klassen müssen erweiterten Inhalt zeichnen
        virtual void DrawContent() const {}

    private:
        TextureColor tc;
};

/// Colored Deepening
class ctrlColorDeepening : public ctrlDeepening, public ColorControlInterface
{
    public:
        ctrlColorDeepening(Window* parent, uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, uint32_t fillColor);

        /// Setzt die Farbe des Controls
        virtual void SetColor(const uint32_t fill_color);

    protected:
        void DrawContent() const;

    protected:
        uint16_t width, height;
        uint32_t fillColor;
};

#endif // !CTRLDEEPENING_H_INCLUDED

