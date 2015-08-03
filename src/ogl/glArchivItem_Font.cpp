// $Id: glArchivItem_Font.cpp 9357 2014-04-25 15:35:25Z FloSoft $
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

///////////////////////////////////////////////////////////////////////////////
// Header
#include "defines.h"
#include "glArchivItem_Font.h"
#include "Settings.h"
#include "ExtensionList.h"
#include "drivers/VideoDriverWrapper.h"
#include "glArchivItem_Bitmap.h"
#include "Loader.h"
#include "Log.h"
#include "glAllocator.h"

#include "../libsiedler2/src/types.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

std::string glArchivItem_Font::Unicode_to_Utf8(uint32_t c) const
{
    std::string text;
    if(c > 0x7F) // unicode?
    {
        if(c >= 0x80 && c <= 0x7FF) // 2 byte utf-8
        {
            uint32_t cH = ((c & 0x0000FF00) >> 8);
            uint32_t cL =  (c & 0x000000FF);

            uint8_t c0 = 0xC0 | ((cL & 0xC0) >> 6) | ((cH & 0x07) << 2); // untere 2 bits und obere 3 bits
            uint8_t c1 = 0x80 |  (cL & 0x3F); // untere 6 bits

            text.push_back(c0);
            text.push_back(c1);
        }
        else if(c >= 0x800 && c <= 0xFFFF) // 3 byte utf-8
        {
            uint32_t cH = ((c & 0x0000FF00) >> 8);
            uint32_t cL =  (c & 0x000000FF);

            uint8_t c0 = 0xE0 | ((cH & 0xF0) >> 4); // obere 4 bits
            uint8_t c1 = 0x80 | ((cL & 0xC0) >> 6) | ((cH & 0x0F) << 2); // untere 2 bits und obere 4 bits
            uint8_t c2 = 0x80 |  (cL & 0x3F); // untere 6 bits

            text.push_back(c0);
            text.push_back(c1);
            text.push_back(c2);
        }
        else if(c >= 0x10000 && c <= 0x1FFFFF) // 4 byte utf-8
        {
            //uint32_t cH1 = ((c & 0xFF000000) >> 24);
            uint32_t cH  = ((c & 0x00FF0000) >> 16);
            uint32_t cL1 = ((c & 0x0000FF00) >> 8);
            uint32_t cL2 =  (c & 0x000000FF);

            uint8_t c0 = 0xF0 | ((cH & 0x3C) >> 2); // obere 4 bits xxHHHHhh -> xxxxHHHH
            uint8_t c1 = 0x80 | ((cL1 & 0xF0) >> 4) | ((cH & 0x03) << 4); // untere1 4 bits und obere 2 bits LLLLllll xxhhhhHH -> xxHHLLLL
            uint8_t c2 = 0x80 | ((cL2 & 0xC0) >> 6) | ((cL1 & 0x0F) << 2); // untere2 2 bits und untere1 4 bits
            uint8_t c3 = 0x80 |  (cL2 & 0x3F); // untere2 6 bits

            text.push_back(c0);
            text.push_back(c1);
            text.push_back(c2);
            text.push_back(c3);
        }
    }
    else
        text.push_back(c & 0xFF);

    return text;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  @brief wandelt ein UTF-8 Zeichen nach Unicode um
 *
 *  @author FloSoft
 */
uint32_t glArchivItem_Font::Utf8_to_Unicode(const std::string& text, uint32_t& i) const
{
    uint32_t c = (text[i] & 0xFF);
    // qx: fix für namen in der Kartenübersicht
    if(c == 0xF6 || c == 0xDF)return c; // if we accidentally try to convert an already unicode text including ö (0xF6) this will catch it (todo: find a better way to do this that includes other cases)
    if( (c & 0x80) == 0x80) // 1Xxxxxxx
    {

        if( (c & 0xC0) == 0x80) // 10xxxxxx
        {
// Disabled this message since it is repeated for ages and does not really help :-)
//          if(!CharExist(c)) // some hardcoded non utf-8 characters may be here ...
//              LOG.lprintf("woops, corrupt utf-8 stream: %02x / %d\n", c, c);
        }
        else if( (c & 0xE0) == 0xC0) // 110xxxxx
        {
            // 2 byte sequence 110xxxxx 10xxxxxx
            uint32_t c2 = (text[++i] & 0xFF);
            c =  ((c & 0x1F ) << 6) | (c2 & 0x3F);
        }
        else if( (c & 0xF0) == 0xE0) // 1110xxxx
        {
            // 3 byte sequence 1110xxxx 10xxxxxx 10xxxxxx
            uint32_t c2 = (text[++i] & 0xFF);
            uint32_t c3 = (text[++i] & 0xFF);

            c =  ((c & 0x0F) << 12) | ((c2 & 0x3F) << 6) | (c3 & 0x3F);
        }
        else if( (c & 0xF8) == 0xF0) // 11110xxx
        {
            // 4 byte sequence 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
            uint32_t c2 = (text[++i] & 0xFF);
            uint32_t c3 = (text[++i] & 0xFF);
            uint32_t c4 = (text[++i] & 0xFF);
            c =  ((c & 0x0F) << 18) | ((c2 & 0x3F) << 12) | ((c3 & 0x3F) << 6) | (c4 & 0x3F);
        }
        else
        {
            if(!CharExist(c)) // some hardcoded non utf-8 characters may be here ...
                LOG.lprintf("unknown utf-8 sequence: %02x / %d\n", c, c);
        }
    }
    return c;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  @brief fügt ein einzelnes Zeichen zur Zeichenliste hinzu
 *
 *  @author Marcus
 */
inline void glArchivItem_Font::DrawChar(const std::string& text,
                                        uint32_t& i,
                                        GL_T2F_V3F_Struct* tmp,
                                        int16_t& cx,
                                        int16_t& cy,
                                        float tw,
                                        float th,
                                        uint32_t& idx)
{
    uint32_t c = Utf8_to_Unicode(text, i);
    char_info ci = CharInfo(c);

    if(CharExist(ci))
    {

        float tx1 = (float)(ci.x) / tw;
        float tx2 = (float)(ci.x + ci.width) / tw;
        float ty1 = (float)(ci.y) / th;
        float ty2 = (float)(ci.y + dy) / th;

        tmp[idx].tx = tx1;
        tmp[idx].ty = ty1;

        tmp[idx].x = cx;
        tmp[idx].y = cy;
        tmp[idx].z = 0.0f;

        idx++;

        tmp[idx].tx = tx1;
        tmp[idx].ty = ty2;

        tmp[idx].x = cx;
        tmp[idx].y = (GLfloat)(cy + dy);
        tmp[idx].z = 0.0f;

        idx++;

        tmp[idx].tx = tx2;
        tmp[idx].ty = ty2;

        tmp[idx].x = (GLfloat)(cx + ci.width);
        tmp[idx].y = (GLfloat)(cy + dy);
        tmp[idx].z = 0.0f;

        idx++;

        tmp[idx].tx = tx2;
        tmp[idx].ty = ty1;

        tmp[idx].x = (GLfloat)(cx + ci.width);
        tmp[idx].y = cy;
        tmp[idx].z = 0.0f;

        idx++;

        cx += ci.width;
    }
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  @brief
 *
 *  @author FloSoft
 */
void glArchivItem_Font::Draw(int16_t x,
                             int16_t y,
                             const std::wstring& wtext,
                             uint32_t format,
                             uint32_t color,
                             uint16_t length,
                             uint16_t max,
                             const std::wstring& wend,
                             uint16_t end_length)
{
    // etwas dämlich, aber einfach ;)
    // da wir hier erstmal in utf8 konvertieren, und dann im anderen Draw wieder zurück ...

    std::string text;
    for(uint32_t i = 0; i < wtext.length(); ++i)
        text += Unicode_to_Utf8(wtext[i]);

    std::string end;
    for(uint32_t i = 0; i < wend.length(); ++i)
        end += Unicode_to_Utf8(wend[i]);

    Draw(x, y, text, format, color, length, max, end, end_length);
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  Zeichnet einen Text.
 *
 *  @param[in] x      X-Koordinate
 *  @param[in] y      Y-Koordinate
 *  @param[in] text   Der Text
 *  @param[in] format Format des Textes (verodern)
 *                      @p glArchivItem_Font::DF_LEFT    - Text links ( standard )
 *                      @p glArchivItem_Font::DF_CENTER  - Text mittig
 *                      @p glArchivItem_Font::DF_RIGHT   - Text rechts
 *                      @p glArchivItem_Font::DF_TOP     - Text oben ( standard )
 *                      @p glArchivItem_Font::DF_VCENTER - Text vertikal zentriert
 *                      @p glArchivItem_Font::DF_BOTTOM  - Text unten
 *  @param[in] color  Farbe des Textes
 *  @param[in] length Länge des Textes
 *  @param[in] max    maximale Länge
 *
 *  @author OLiver
 */
void glArchivItem_Font::Draw(int16_t x,
                             int16_t y,
                             const std::string& text,
                             uint32_t format,
                             uint32_t color,
                             uint16_t length,
                             uint16_t max,
                             const std::string& end,
                             uint16_t end_length)
{
    if(!_font)
        initFont();

    // Breite bestimmen
    if(length == 0)
        length = (uint16_t)text.length();
    if(end_length == 0)
        end_length = (uint16_t)end.length();

    bool enable_end;

    uint16_t text_max = 0;
    uint16_t text_width = getWidth(text, length, max, &text_max);

    // text_max ist die maximale Indexzahl, nicht mehr die Breite in Pixel!
    if(end.length() && text_max < length)
    {
        uint16_t end_max = 0;
        uint16_t end_width = getWidth(end, end_length, max, &end_max);

        // Bei Überlauf oder kleiner 0 - nix zeichnen ;)
        if( text_width - end_width > text_width || text_width - end_width <= 0 )
            return;

        text_width -= end_width;

        // Wieviele Buchstaben gehen in den "Rest" (ohne "end")
        text_max = 0;
        getWidth(text, length, text_width, &text_max);

        enable_end = true;
    }
    else
        enable_end = false;

    if(text_max == 0)
        return;

    if( (format & 3) == DF_RIGHT)
        x -= text_width;
    if( (format & 12) == DF_BOTTOM)
        y -= dy;
    if( (format & 12) == DF_VCENTER)
        y -= dy / 2;

    int16_t cx = x, cy = y;
    if( (format & 3) == DF_CENTER)
    {
        uint16_t line_width = text_width;
        for(uint16_t j = 0; j < text_max; ++j)
        {
            if(text[j] == '\n')
            {
                line_width = getWidth(text, j);
                break;
            }
        }
        cx = x - line_width / 2;
    }

    GL_T2F_V3F_Struct* tmp = new GL_T2F_V3F_Struct[(text_max + (enable_end ? end_length : 0)) * 4];
    float tw = _font->GetTexWidth();
    float th = _font->GetTexHeight();
    uint32_t idx = 0;

    glColor4ub(GetRed(color), GetGreen(color), GetBlue(color), GetAlpha(color));

    for(uint32_t i = 0; i < text_max; ++i)
    {
        if(text[i] == '\n')
        {
            cy += dy;
            if( (format & 3) == DF_CENTER)
            {
                uint16_t line_width = 0;
                for(uint16_t j = i + 1; j < text_max; ++j)
                {
                    if(text[j] == '\n')
                    {
                        line_width = getWidth(&text[i + 1], j - i - 1);
                        break;
                    }
                }
                if(line_width == 0)
                    line_width = getWidth(&text[i + 1], text_max - i - 1);
                cx = x - line_width / 2;
            }
            else
                cx = x;
        }
        else
            DrawChar(text, i, tmp, cx, cy, tw, th, idx);
    }

    if(enable_end)
    {
        for(uint32_t i = 0; i < end_length; ++i)
        {
            if(end[i] == '\n')
            {
                cy += dy;
                cx = x;
            }
            else
                DrawChar(end, i, tmp, cx, cy, tw, th, idx);
        }
    }

    if (SETTINGS.video.vbo)
    {
        // unbind VBO
        glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
    }

    glInterleavedArrays(GL_T2F_V3F, 0, tmp);
    VIDEODRIVER.BindTexture(((format & DF_NO_OUTLINE) == DF_NO_OUTLINE) ? _font->GetTexture() : _font_outline->GetTexture());
    glDrawArrays(GL_QUADS, 0, idx);

    delete[] tmp;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  liefert die Länge einer Zeichenkette.
 *
 *  @param[in]     text   Der Text
 *  @param[in]     length Textlänge
 *  @param[in,out] max    In:  maximale Breite des Textes in Pixeln
 *                        Out: maximale Breite in Buchstaben der in "max"-Pixel reinpasst.
 *
 *  @return Breite des Textes in Pixeln
 *
 *  @author OLiver
 */
uint16_t glArchivItem_Font::getWidth(const std::wstring& text, uint32_t length, uint32_t max_width, uint16_t* max) const
{
    if(length == 0)
        length = unsigned(text.length());

    uint16_t w = 0, wm = 0;
    for(uint32_t i = 0; i < length; ++i)
    {
        uint16_t cw = CharWidth(text[i]);

        if(text[i] == '\n')
        {
            if(w > wm) // Längste Zeile
                wm = w;
            w = 0;
        }

        // haben wir das maximum erreicht?
        if(unsigned((wm > 0 ? wm : w) + cw) > max_width)
        {
            *max = i;
            if(wm == 0)
                wm = w;
            return wm;
        }
        w += cw;
    }

    if((wm == 0) || (wm < w)) // Letzte Zeile kann auch die längste sein und hat kein \n am Ende
        wm = w;

    if(max)
        *max = length;

    return wm;
}

uint16_t glArchivItem_Font::getWidth(const std::string& text, uint32_t length, uint32_t max_width, uint16_t* max) const
{
    if(length == 0)
        length = unsigned(text.length());

    uint16_t w = 0, wm = 0;
    for(uint32_t i = 0; i < length; ++i)
    {
        uint16_t cw = CharWidth(Utf8_to_Unicode(text, i));

        if(text[i] == '\n')
        {
            if(w > wm) // Längste Zeile
                wm = w;
            w = 0;
        }

        // haben wir das maximum erreicht?
        if(unsigned((wm > 0 ? wm : w) + cw) > max_width)
        {
            *max = i;
            if(wm == 0)
                wm = w;
            return wm;
        }
        w += cw;
    }

    if((wm == 0) || (wm < w)) // Letzte Zeile kann auch die längste sein und hat kein \n am Ende
        wm = w;

    if(max)
        *max = length;

    return wm;
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  @brief
 *
 *  @author OLiver
 */
void glArchivItem_Font::WrapInfo::CreateSingleStrings(const std::string& origin_text, std::string* dest_strings)
{
    // Kopie des ursprünglichen Strings erstellen
    std::string copy(origin_text);

    for(uint32_t i = 0; i < positions.size(); ++i)
    {
        // Gibts noch weitere Teile danach?
        char temp = 0;
        if(i + 1 < positions.size())
        {
            // dann muss statt des Leerzeichens o.ä. ein Nullzeichen gesetzt werden, damit nur der Teilstring aufgenommen
            // wird und nicht noch alles was danach kommt

            // das Zeichen merken, was da vorher war
            temp = origin_text[positions.at(i + 1)];
            // Zeichen 0 setzen
            copy[positions.at(i + 1)] = 0;
        }

        if(i < origin_text.length()) //in case of empty string dont try to read char 1 ...
            dest_strings[i] = &copy[positions.at(i)];

        // wieder ggf. zurücksetzen, siehe oben
        if(i + 1 < positions.size())
            copy[positions.at(i + 1)] = temp;
    }
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  Gibt Infos, über die Unterbrechungspunkte in einem Text
 *
 *  @param[in]     text            Text, der auf Zeilen verteilt werden soll
 *  @param[in]     primary_width   Maximale Breite der ersten Zeile
 *  @param[in]     secondary_width Maximale Breite der weiteren Zeilen
 *  @param[in,out] wi              Pointer auf die Anfänge der einzelnen Zeilen
 *
 *
 *  @author OLiver
 */
void glArchivItem_Font::GetWrapInfo(const std::string& text,
                                    const uint16_t primary_width, const uint16_t secondary_width,
                                    WrapInfo& wi)
{
    if(!_font)
        initFont();

    // Breite der aktuellen Zeile
    uint16_t line_width = 0;
    // Breite des aktuellen Wortes
    uint16_t word_width = 0;
    // Beginn des aktuellen Wortes
    uint32_t word_start = 0;

    // Logischerweise fangen wir in der ersten Zeile an
    wi.positions.clear();
    wi.positions.push_back(0);

    // Länge des Strings
    uint32_t length = (uint32_t)text.length();

    for(uint32_t i = 0; i <= length; ++i)
    {
        // Leerzeichen, Umbruch oder ende?
        if(text[i] == '\n' || text[i] == ' ' || i == length)
        {
            // Passt das letzte Wort mit auf die Zeile? (bzw bei newline immer neue zeile anfangen)
            if(word_width + line_width <= ( (wi.positions.size() == 1) ? primary_width : secondary_width))
            {
                // Länge des Leerzeichens mit draufaddieren
                line_width += word_width;
                line_width += CharWidth(' ');

                // neues Wort fängt dann nach dem Leerzeichen an (falls wir nicht schon am Ende vom Text sind)
                if(i < length - 1)
                {
                    word_width = 0;
                    word_start = i + 1;
                }
            }
            else
            {
                // Ansonsten neue Zeile anfangen

                // Passt das Wort wenigsens komplett überhaupt in die nächste Zeile?
                if(word_width <= secondary_width)
                {
                    // neue Zeile anfangen mit diesem Wort
                    wi.positions.push_back(word_start);
                    // In der Zeile ist schon das Wort und das jetzige Leerzeichen mit drin
                    line_width = word_width + CharWidth(' ');
                    // Neues Wort beginnen (falls wir nicht schon am Ende vom Text sind)
                    if(i < length - 1)
                    {
                        word_start = i + 1;
                        word_width = 0;
                    }
                }
                else
                {
                    // ansonsten muss das Wort zwangsläufig auf mehrere Zeilen verteilt werden
                    for(size_t z = 0; text[word_start + z] != ' ' && text[word_start + z]; ++z)
                    {
                        uint32_t zz = word_start + z;
                        uint16_t letter_width = CharWidth(Utf8_to_Unicode(text, zz));
                        z = zz - word_start;

                        // passt der neue Buchstabe noch mit drauf?
                        if(line_width + letter_width <= ( (wi.positions.size() == 1) ? primary_width : secondary_width))
                            line_width += letter_width;
                        else
                        {
                            // wenn nicht, muss hier ein Umbruch erfolgen

                            // neue Zeile anfangen mit diesem Buchstaben
                            wi.positions.push_back(word_start + z);
                            line_width = letter_width;
                        }
                    }

                    // Leerzeichen nicht vergessen
                    line_width += CharWidth(' ');

                    // Neues Wort beginnen (falls wir nicht schon am Ende vom Text sind)
                    if(i < length - 1)
                    {
                        word_start = i + 1;
                        word_width = 0;
                    }
                }
            }
            // Bei Newline immer neue Zeile anfangen, aber erst jetzt
            // und nicht schon oben in diesem if-Zweig
            if(text[i] == '\n' && i < length - 1)
            {
                word_start = i + 1;
                word_width = 0;
                line_width = 0;
                wi.positions.push_back(word_start);
            }
        }
        else
        {
            // Anderes Zeichen --> einfach dessen Breite mit addieren
            uint32_t c = Utf8_to_Unicode(text, i);
            if( CharExist(c) )
                word_width += CharWidth(c);
        }
    }

    // Ignore trailing newline
    if(wi.positions[wi.positions.size() - 1] == length - 1)
        wi.positions.pop_back();
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  @brief
 *
 *  @author FloSoft
 */
void glArchivItem_Font::initFont()
{
    _font_outline = dynamic_cast<glArchivItem_Bitmap*>(glAllocator(libsiedler2::BOBTYPE_BITMAP_RLE, 0, NULL));
    _font = dynamic_cast<glArchivItem_Bitmap*>(glAllocator(libsiedler2::BOBTYPE_BITMAP_RLE, 0, NULL));

    //memset(_charwidths, 0, sizeof(_charwidths));

    // first, we have to find how much chars we really have, but we can also skip first 32
    uint32_t chars = 32;
    for(uint32_t i = 32; i < getCount(); ++i)
    {
        if(get(i))
            ++chars;
    }

    chars_per_line = (uint32_t)std::sqrt((double)chars);

    int32_t w = (dx + 2) * chars_per_line + 2;
    int32_t h = (dy + 2) * chars_per_line + 2;
    uint32_t buffersize = w * h * 4; // RGBA Puffer für alle Buchstaben
    uint8_t* buffer = new uint8_t[buffersize];
    memset(buffer, 0, buffersize);

    int32_t x = 1;
    int32_t y = 1;
    chars = 0;
    for(uint32_t i = 32; i < getCount(); ++i)
    {
        if( (chars % chars_per_line) == 0 && i != 32 )
        {
            y += dy + 2;
            x = 1;
        }

        const libsiedler2::baseArchivItem_Bitmap_Player* c = dynamic_cast<const libsiedler2::baseArchivItem_Bitmap_Player*>(get(i));
        if(c)
        {
            // Spezialpalette (blaue Spielerfarben sind Grau) verwenden,
            // damit man per OpenGL einfärben kann!
            c->print(buffer, w, h, libsiedler2::FORMAT_RGBA, LOADER.GetPaletteN("colors"), 128, x, y, 0, 0, 0, 0, true);

            char_info ci;
            ci.x = x;
            ci.y = y;
            ci.width = (c->getWidth() > dx + 2 ? dx + 2 : c->getWidth());

            utf8_mapping[i] = ci;
            x += dx + 2;
            ++chars;
        }
    }

    // Spezialpalette (blaue Spielerfarben sind Grau) verwenden,
    // damit man per OpenGL einfärben kann!
    _font->create(w, h, buffer, w, h, libsiedler2::FORMAT_RGBA, LOADER.GetPaletteN("colors"));

    x = 1;
    y = 1;
    chars = 0;
    for(uint32_t i = 32; i < getCount(); ++i)
    {
        if( (chars % chars_per_line) == 0 && i != 32 )
        {
            y += dy + 2;
            x = 1;
        }

        const libsiedler2::baseArchivItem_Bitmap_Player* c = dynamic_cast<const libsiedler2::baseArchivItem_Bitmap_Player*>(get(i));
        if(c)
        {
            // Spezialpalette (blaue Spielerfarben sind Grau) verwenden,
            // damit man per OpenGL einfärben kann!
            c->print(buffer, w, h, libsiedler2::FORMAT_RGBA, LOADER.GetPaletteN("colors"), 128, x, y);

            x += dx + 2;
            ++chars;
        }
    }

    _font_outline->create(w, h, buffer, w, h, libsiedler2::FORMAT_RGBA, LOADER.GetPaletteN("colors"));

    delete[] buffer;

    /*ArchivInfo items;
    items.pushC(_font);
    libsiedler2::loader::WriteBMP((std::string("font") + std::string(getName()) + std::string(".bmp")).c_str(), LOADER.GetPaletteN("colors"), &items);*/
}
