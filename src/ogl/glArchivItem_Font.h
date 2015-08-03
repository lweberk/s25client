// $Id: glArchivItem_Font.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef GLARCHIVITEM_FONT_H_INCLUDED
#define GLARCHIVITEM_FONT_H_INCLUDED

#pragma once

#include "../libsiedler2/src/ArchivItem_Font.h"
#include "oglIncludes.h"
#include "colors.h"
#include <map>
#include <vector>
#include <string>

class glArchivItem_Bitmap;

/// Klasse für GL-Fontfiles.
class glArchivItem_Font : public libsiedler2::ArchivItem_Font
{
    public:
        /// Konstruktor von @p glArchivItem_Font.
        glArchivItem_Font(void) : ArchivItem_Font(), _font(NULL), chars_per_line(16) {}
        /// Kopierkonstruktor von @p glArchivItem_Font.
        glArchivItem_Font(const glArchivItem_Font* item) : ArchivItem_Font(item), _font(NULL) {}

        /// Zeichnet einen Text.
        void Draw(int16_t x, int16_t y, const std::wstring& wtext, uint32_t format, uint32_t color = COLOR_WHITE, uint16_t length = 0, uint16_t max = 0xFFFF, const std::wstring& wend = L"...", uint16_t end_length = 0);
        void Draw(int16_t x, int16_t y, const std::string& text, uint32_t format, uint32_t color = COLOR_WHITE, uint16_t length = 0, uint16_t max = 0xFFFF, const std::string& end = "...", uint16_t end_length = 0);

        /// liefert die Länge einer Zeichenkette.
        uint16_t getWidth(const std::wstring& text, uint32_t length = 0, uint32_t max_width = 0xffffffff, uint16_t* max = NULL) const;
        uint16_t getWidth(const std::string& text, uint32_t length = 0, uint32_t max_width = 0xffffffff, uint16_t* max = NULL) const;
        /// liefert die Höhe des Textes ( entspricht @p getDy()+1 )
        inline uint16_t getHeight() const { return dy + 1; }

        /// Gibt Infos, über die Unterbrechungspunkte in einem Text
        class WrapInfo
        {
            public:
                /// Erzeugt ein Arrays aus eigenständigen Strings aus den Unterbrechungsinfos.
                void CreateSingleStrings(const std::string& origin_text, std::string* dest_strings);

            public:
                /// Array von Positionen, wo der Text umbrochen werden soll (jeweils der Anfang vom String)
                std::vector<uint32_t> positions;
        };

        /// Gibt Infos, über die Unterbrechungspunkte in einem Text, versucht Wörter nicht zu trennen, tut dies aber, falls
        /// es unumgänglich ist (Wort länger als die Zeile)
        void GetWrapInfo(const std::string& text, const uint16_t primary_width, const uint16_t secondary_width, WrapInfo& wi);

        enum
        {
            DF_LEFT   = 0,
            DF_RIGHT  = 1,
            DF_CENTER = 2
        };

        enum
        {
            DF_TOP     = 0,
            DF_BOTTOM  = 4,
            DF_VCENTER = 8
        };

        enum
        {
            DF_NO_OUTLINE = 16
        };

        struct char_info
        {
            char_info() : x(0), y(0), width(0), reserved(0xFFFF) {}
            uint16_t x;
            uint16_t y;
            uint16_t width;
            uint16_t reserved; // so we have 8 byte's
        };

        /// prüft ob ein Buchstabe existiert.
        inline bool CharExist(uint32_t c) const { return (CharWidth(c) > 0); }
        inline bool CharExist(char_info ci) const { return (ci.width > 0); }

        /// liefert die Breite eines Zeichens
        inline uint32_t CharWidth(uint32_t c) const { return CharInfo(c).width; }
        inline uint32_t CharWidth(char_info ci) const { return ci.width; }

        std::string Unicode_to_Utf8(uint32_t c) const;
        uint32_t Utf8_to_Unicode(const std::string& text, uint32_t& i) const;

    private:
        void initFont();

        struct GL_T2F_V3F_Struct
        {
            GLfloat tx, ty;
            GLfloat x, y, z;
        };

        void DrawChar(const std::string& text, uint32_t& i, GL_T2F_V3F_Struct* tmp, int16_t& cx, int16_t& cy, float tw, float th, uint32_t& idx);

        /// liefert das Char-Info eines Zeichens
        inline const char_info& CharInfo(uint32_t c) const
        {
            static char_info ci;

            std::map<uint32_t, char_info>::const_iterator it = utf8_mapping.find(c);
            if(it != utf8_mapping.end())
                return it->second;

            ci.width = 0;

            return ci;
        }

        glArchivItem_Bitmap* _font_outline;
        glArchivItem_Bitmap* _font;

        uint32_t chars_per_line;
        std::map<uint32_t, char_info> utf8_mapping;
};

#endif // !GLARCHIVITEM_FONT_H_INCLUDED
