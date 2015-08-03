﻿// $Id: ctrlList.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CTRLLIST_H_INCLUDED
#define CTRLLIST_H_INCLUDED

#pragma once

#include "Window.h"
#include <string>
#include <vector>

class ctrlList : public Window
{
    public:
        /// Konstruktor von @p ctrlList.
        ctrlList(Window* parent, uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, glArchivItem_Font* font);
        /// Destruktor von @p ctrlList.
        virtual ~ctrlList(void);

        /// Größe verändern
        void Resize_(uint16_t width, uint16_t height);

        /// Neuen String zur Listbox hinzufügen.
        void AddString(const std::string& text);
        /// Verändert einen String
        void SetString(const std::string& text, const uint32_t id);
        /// Listbox leeren.
        void DeleteAllItems(void);
        /// liefert den Wert einer Zeile.
        const std::string& GetItemText(uint16_t line) const;
        /// liefert den Wert der aktuell gewählten Zeile.
        const std::string& GetSelItemText(void) const { return GetItemText(selection); };
        /// Vertauscht zwei Zeilen.
        void Swap(uint16_t first, uint16_t second);
        /// Löscht ein Element
        void Remove(const uint16_t index);

        uint16_t GetLineCount(void) const { return static_cast<uint16_t>(lines.size()); }
        uint16_t GetSelection(void) const { return static_cast<uint16_t>(selection); };
        void SetSelection(uint16_t selection)
        {
            if(selection != this->selection && selection < lines.size())
            {
                this->selection = selection;
                if(parent)
                    parent->Msg_ListSelectItem(id, selection);
            }
        }

        virtual bool Msg_MouseMove(const MouseCoords& mc);
        virtual bool Msg_LeftDown(const MouseCoords& mc);
        virtual bool Msg_RightDown(const MouseCoords& mc);
        virtual bool Msg_LeftUp(const MouseCoords& mc);
        virtual bool Msg_WheelUp(const MouseCoords& mc);
        virtual bool Msg_WheelDown(const MouseCoords& mc);
    protected:
        /// Zeichenmethode.
        virtual bool Draw_(void);

    private:
        TextureColor tc;
        glArchivItem_Font* font;

        std::vector<std::string> lines;

        uint16_t selection;
        uint16_t mouseover;
        uint32_t pagesize;

};

#endif // CTRLLIST_H_INCLUDED
