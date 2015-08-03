﻿// $Id: noRoadNode.h 9357 2014-04-25 15:35:25Z FloSoft $
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

#ifndef NO_ROADNODE_H_
#define NO_ROADNODE_H_

#include "noCoordBase.h"
#include "RoadSegment.h"

class noFigure;
class Ware;
// Enumforwarddeklaration bei VC nutzen
#ifdef _MSC_VER
enum Job;
#else
#include "gameData/GameConsts.h"
#endif

// Basisklasse für Gebäude und Flagge (alles, was als "Straßenknoten" dient
class noRoadNode : public noCoordBase
{
    protected:

        uint8_t player;

    public:

        RoadSegment* routes[6];

// For Pathfinding
        mutable uint32_t coord_id;
        // cost from start
        mutable uint32_t cost;
        // distance to target
        mutable uint32_t distance;
        // estimated total distance (cost + distance)
        mutable uint32_t estimate;

        mutable uint32_t last_visit;

        mutable const noRoadNode* prev;
        mutable uint32_t dir;
    public:

        noRoadNode(const NodalObjectType nop, const MapPoint pt, const uint8_t player);
        noRoadNode(SerializedGameData* sgd, const uint32_t obj_id);

        virtual ~noRoadNode();
        /// Aufräummethoden
    protected:  void Destroy_noRoadNode();
    public:     void Destroy() { Destroy_noRoadNode(); }

        /// Serialisierungsfunktionen
    protected:  void Serialize_noRoadNode(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_noRoadNode(sgd); }

        inline noRoadNode* GetNeighbour(const uint8_t dir) const {if(!routes[dir]) return 0; return((routes[dir]->GetF1() == this) ? routes[dir]->GetF2() : routes[dir]->GetF1());}

        void DestroyRoad(const uint8_t dir);
        void UpgradeRoad(const uint8_t dir);
        /// Vernichtet Alle Straße um diesen Knoten
        void DestroyAllRoads();

        uint8_t GetPlayer() const { return player; }

        /// Legt eine Ware am Objekt ab (an allen Straßenknoten (Gebäude, Baustellen und Flaggen) kann man Waren ablegen
        virtual void AddWare(Ware* ware) = 0;

        /// Nur für Flagge, Gebäude können 0 zurückgeben, gibt Wegstrafpunkte für das Pathfinden für Waren, die in eine bestimmte Richtung noch transportiert werden müssen
        virtual uint16_t GetPunishmentPoints(const uint8_t dir) const { return 0; }

};

#endif
