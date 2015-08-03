// $Id: glArchivItem_Bitmap.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef GLARCHIVITEM_BITMAP_INCLUDED
#define GLARCHIVITEM_BITMAP_INCLUDED

#pragma once

#include "../libutil/src/colors.h"
#include "../libsiedler2/src/ArchivItem_Bitmap.h"

#ifdef _WIN32
typedef uint64_t int64_t uint64_t;
#endif

/// Basisklasse für GL-Bitmapitems.
class glArchivItem_Bitmap : public virtual libsiedler2::baseArchivItem_Bitmap
{
    public:
        /// Konstruktor von @p glArchivItem_Bitmap.
        glArchivItem_Bitmap(void);
        /// Kopiekonstruktor von @p glArchivItem_Bitmap.
        glArchivItem_Bitmap(const glArchivItem_Bitmap* item);

        /// Destruktor von @p glArchivItem_Bitmap.
        virtual ~glArchivItem_Bitmap(void);

        /// Erzeugt und zeichnet die Textur.
        virtual void Draw(int16_t dst_x, int16_t dst_y, int16_t dst_w = 0, int16_t dst_h = 0, int16_t src_x = 0, int16_t src_y = 0, int16_t src_w = 0, int16_t src_h = 0, const uint32_t color = COLOR_WHITE, const uint32_t unused = COLOR_WHITE);

        /// liefert das GL-Textur-Handle.
        uint32_t GetTexture();
        /// Löscht die GL-Textur (z.B fürs Neuerstellen)
        virtual void DeleteTexture();
        /// Setzt den Texturfilter auf einen bestimmten Wert.
        virtual void setFilter(uint32_t filter);

        uint16_t GetTexWidth() {return(tex_width);}
        uint16_t GetTexHeight() {return(tex_width);}

    protected:
        /// Erzeugt die Textur.
        virtual void GenerateTexture();

    protected:
        uint32_t texture; ///< Das GL-Textur-Handle
        uint32_t filter;  ///< Der aktuell gewählte Texturfilter
};

#endif // !GLARCHIVITEM_BITMAP_INCLUDED
