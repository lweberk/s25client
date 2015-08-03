// $Id: ctrlTable.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CTRLTABLE_H_INCLUDED
#define CTRLTABLE_H_INCLUDED

#pragma once

#include "ctrlScrollBar.h"
#include <vector>
#include <cstdarg>

class ctrlTable : public Window
{
    public:
        ctrlTable(Window* parent, uint32_t id, uint16_t x, uint16_t y, uint16_t width,  uint16_t height, TextureColor tc, glArchivItem_Font* font, uint16_t column_count, va_list liste);
        virtual ~ctrlTable(void);

        /// löscht alle Items.
        void DeleteAllItems(void);
        /// setzt die Auswahl.
        void SetSelection(uint16_t selection, bool left = true);
        /// fügt eine Zeile hinzu.
        void AddRow(uint32_t alwaysnull, ...);
        /// liefert den Wert eines Feldes.
        const std::string& GetItemText(uint16_t row, uint16_t column) const;
        /// sortiert die Zeilen.
        void SortRows(uint16_t column, bool* direction = NULL);
        uint16_t GetSortColumn() { return sort_column; }
        bool GetSortDirection() { return sort_direction; }
        uint16_t GetRowCount() { return static_cast<uint16_t>(rows.size()); }
        uint16_t GetColumnCount() { return static_cast<uint16_t>(columns.size()); }
        uint16_t GetSelection(bool left = true) { return (left ? row_l_selection : row_r_selection); }

        virtual bool Msg_LeftDown(const MouseCoords& mc);
        virtual bool Msg_RightDown(const MouseCoords& mc);
        virtual bool Msg_LeftUp(const MouseCoords& mc);
        virtual bool Msg_WheelUp(const MouseCoords& mc);
        virtual bool Msg_WheelDown(const MouseCoords& mc);
        virtual bool Msg_MouseMove(const MouseCoords& mc);
        virtual void Msg_ButtonClick(const uint32_t ctrl_id);
        virtual void Msg_ScrollShow(const uint32_t ctrl_id, const bool visible);
        virtual bool Msg_KeyDown(const KeyEvent& ke);

        enum SortType
        {
            SRT_STRING,
            SRT_MAPSIZE,
            SRT_NUMBER,
            SRT_DATE,
            SRT_DEFAULT
        };

    protected:

        virtual bool Draw_(void);

        /// Größe ändern
        void Resize_(uint16_t width, uint16_t height);
        /// Setzt die Breite und Position der Buttons ohne Scrolleiste
        void ResetButtonWidths();

    private:
        TextureColor tc;
        glArchivItem_Font* font;

        uint16_t header_height;
        uint16_t line_count;

        struct COLUMN
        {
            /// Breite der Spalten in Promille von der Tabellenlänge
            uint16_t width;
            std::string title;
            SortType sortType;
        };
        std::vector<COLUMN> columns;

        uint16_t row_l_selection;
        uint16_t row_r_selection;

        uint16_t sort_column;
        bool sort_direction;

        struct ROW
        {
            std::vector<std::string> columns;
        };
        std::vector<ROW> rows;

        int32_t Compare(const std::string& a, const std::string& b, SortType sortType);
};

#endif // !CTRLTABLE_H_INCLUDED
