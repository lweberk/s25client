// $Id: CatapultStone.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CATAPULT_STONE_H_
#define CATAPULT_STONE_H_

#include "GameObject.h"
#include "EventManager.h"
#include "gameTypes/MapTypes.h"

class nobMilitary;
class GameWorldView;
class GameWorldViewer;


/// Klasse für einen fliegenden Katapultstein
class CatapultStone : public GameObject
{
    private:

        /// (Map-)Koordinaten des Hauses, in dem er einschlagen soll
        const MapPoint dest_building;
        /// Aufschlagspunkt des Steines (Map-Koordinaten!)
        const MapPoint dest_map;
        /// Koordinaten der Startposition des Steins
        const int32_t start_x, start_y;
        /// Koordinaten der Zielposition des Steins
        const int32_t dest_x, dest_y;
        /// Explodiert der Stein schon? (false = fliegt)
        bool explode;
        /// Flieg-/Explodier-Event
        EventManager::Event* event;

    public:

        CatapultStone(const MapPoint dest_building, const MapPoint dest_map,
                      const int32_t start_x, const int32_t start_y, const int32_t dest_x, const int32_t dest_y, const uint32_t fly_duration);

        CatapultStone(SerializedGameData* sgd, const uint32_t obj_id);

        ~CatapultStone() {}

        /// Zerstören
        void Destroy();

        /// Serialisierungsfunktionen
    protected:  void Serialize_CatapultStone(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_CatapultStone(sgd); }

        // Zeichnet den fliegenden Stein
        void Draw(const GameWorldView& gwv, const int32_t xoffset, const int32_t yoffset);

        /// Event-Handler
        void HandleEvent(const uint32_t id);

        GO_Type GetGOT() const { return GOT_CATAPULTSTONE; }
};

#endif // !CATAPULT_STONE_H_
