// $Id: GameReplay.h 9517 2014-11-30 09:21:25Z marcus $
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
#ifndef GAMEREPLAY_H_INCLUDED
#define GAMEREPLAY_H_INCLUDED

#pragma once

#include "BinaryFile.h"
#include "GameSavedFile.h"
#include "GameProtocol.h"
#include "gameTypes/MapTypes.h"
#include "Point.h"

class Savegame;

/// Klasse für geladene bzw. zu speichernde Replays
class Replay : public SavedFile
{
    public:
        /// Replay-Command-Art
        enum ReplayCommand
        {
            RC_REPLAYEND = 0,
            RC_CHAT,
            RC_GAME

        };

    public:
        Replay();
        ~Replay();

        /// Räumt auf, schließt datei
        void StopRecording();

        /// Replaydatei gültig?
        bool IsValid() const { return file.IsValid(); }

        /// Beginnt die Save-Datei und schreibt den Header
        bool WriteHeader(const std::string& filename);
        /// Lädt den Header
        bool LoadHeader(const std::string& filename, const bool load_extended_header);

        /// Fügt ein Chat-Kommando hinzu (schreibt)
        void AddChatCommand(const uint32_t gf, const uint8_t player, const uint8_t dest, const std::string& str);
        /// Fügt ein Spiel-Kommando hinzu (schreibt)
        void AddGameCommand(const uint32_t gf, const uint16_t length, const uint8_t* const data);
        /// Fügt Pathfinding-Result hinzu
        void AddPathfindingResult(const uint8_t data, const uint32_t* const length, const MapPoint * const next_harbor);

        /// Liest RC-Type aus, liefert false, wenn das Replay zu Ende ist
        bool ReadGF(uint32_t* gf);
        /// RC-Type aus, liefert false
        ReplayCommand ReadRCType();
        /// Liest ein Chat-Command aus
        void ReadChatCommand(uint8_t* player, uint8_t*   dest, std::string& str);
        void ReadGameCommand(uint16_t* length, uint8_t** data);
        bool ReadPathfindingResult(uint8_t* data, uint32_t* length, MapPoint * next_harbor);

        /// Aktualisiert den End-GF, schreibt ihn in die Replaydatei (nur beim Spielen bzw. Schreiben verwenden!)
        void UpdateLastGF(const uint32_t last_gf);

        const std::string& GetFileName() const { return filename; }
        BinaryFile* GetFile() { return &file; }

    public:
        /// NWF-Länge
        uint16_t nwf_length;
        /// Zufallsgeneratorinitialisierung
        uint32_t random_init;
        /// Bestimmt, ob Pathfinding-Ergebnisse in diesem Replay gespeichert sind
        bool pathfinding_results;

        /// Gespeichertes Spiel, Zufallskarte, normale Karte...?
        MapType map_type;
        /// Gepackte Map - Daten (für alte Karte)
        uint32_t map_length, map_zip_length;
        uint8_t* map_data;
        /// Savegame (für gespeichertes Spiel)
        Savegame* savegame;

        /// End-GF
        uint32_t last_gf;
        /// Position des End-GF in der Datei
        uint32_t last_gf_file_pos;
        /// Position des GFs fürs nächste Command -> muss gleich hinter
        /// bestehendes beschrieben werden
        uint32_t gf_file_pos;

    private:
        /// Replayformat-Version und Signaturen
        static const uint16_t REPLAY_VERSION;
        static const char REPLAY_SIGNATURE[6];

        /// Dateihandle
        BinaryFile file;
        /// File handle for pathfinding results
        BinaryFile pf_file;
        /// File path +  name
        std::string filename;
};

#endif //!GAMEREPLAY_H_INCLUDED
