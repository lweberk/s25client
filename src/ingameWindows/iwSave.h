// $Id: iwSave.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef iwSAVE_H_INCLUDED
#define iwSAVE_H_INCLUDED

#pragma once

#include "IngameWindow.h"
#include "iwDirectIPCreate.h"

/// Fenster fürs Speichern UND(!) Laden von Spielständen
class iwSaveLoad : public IngameWindow
{
    public:
        /// Konstruktor von @p iwSave.
        iwSaveLoad(const uint16_t add_height, const std::string& window_title);

    protected:
        /// Aktualisiert die Tabelle
        void RefreshTable();

    private:
        /// Speichert bzw. läd die angegebene Datei
        virtual void SaveLoad() = 0;

        void Msg_EditEnter(const uint32_t ctrl_id);
        void Msg_ButtonClick(const uint32_t ctrl_id);
        void Msg_TableSelectItem(const uint32_t ctrl_id, const uint16_t selection);

        /// Callbackfunktion zum Eintragen eines Spielstandes in die Tabelle
        static void FillSaveTable(const std::string& filename, void* param);
};

class iwSave: public iwSaveLoad
{
    public:
        iwSave();

    private:
        // Speichert Datei
        void SaveLoad();

        void Msg_ComboSelectItem(const uint32_t ctrl_id, const uint16_t selection);
};


class iwLoad: public iwSaveLoad
{
        /// Informationen zum Erstellen des Servers
        const CreateServerInfo csi;
    public:
        iwLoad(const CreateServerInfo& csi);

    private:
        /// Handle double click on the table
        void Msg_TableChooseItem(const uint32_t ctrl_id, const uint16_t selection);

        // Läd Datei
        void SaveLoad();
};

#endif // !iwSAVE_H_INCLUDED
