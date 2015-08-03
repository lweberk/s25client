// $Id: TerritoryRegion.h 9357 2014-04-25 15:35:25Z FloSoft $
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

#ifndef TERRITORY_REGION_H_
#define TERRITORY_REGION_H_

#include <vector>

#include "GameWorld.h"

/// TerritoryRegion ist ein Rechteck aus der Karte quasi "ausgeschnitten", die für die Berechnung bei Militärgebäuden-
/// aktionen (Neubau, Übernahme, Abriss) benötigt wird von RecalcTerritory

class noBaseBuilding;
class GameWorldBase;

class TerritoryRegion
{
        /// Lage des Ausschnittes in der Karte
        const int32_t x1, y1, x2, y2;
        /// Größe der Karte (wird aus x1,y1...) berechnet
        const uint16_t width, height;

        /// Beschreibung eines Knotenpunktes
        struct TRNode
        {
            /// Spieler-index (+1, da 0 = besitzlos!)
            uint8_t owner;
            /// Entfernung vom Militärgebäude
            uint8_t radius;

            TRNode(): owner(0), radius(0){}
        };

        std::vector<TRNode> nodes;
        GameWorldBase* const gwb;

    private:
        /// Check whether the point x, y is part of the polygon
        static bool IsPointInPolygon(GameWorldBase* gwb, std::vector< MapPoint > &polygon, const MapPoint pt);

        /// Testet einen Punkt, ob der neue Spieler ihn übernehmen kann und übernimmt ihn ggf.
        void TestNode(MapPoint pt, const uint8_t player, const uint8_t radius, const bool check_barriers);

        /// Unterfunktionen von AdjustBorders, vergleicht 2 Punkte, ob sie von unterschiedlichen Spielern sind und setzt
        /// Punkt ggf. zu gar keinem Spieler, 2. Funktion wird für Punkte im 2er Abstand verwendet, da es dort ein bisschen anders läuft!
        void AdjustNodes(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2);
        void AdjustNodes2(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2);

    public:


        TerritoryRegion(const int32_t x1, const int32_t y1, const int32_t x2, const int32_t y2, GameWorldBase* const gwb);
        ~TerritoryRegion();

        static bool IsPointValid(GameWorldBase* gwb, std::vector< MapPoint > &polygon, const MapPoint pt);

        /// Berechnet ein Militärgebäude mit ein
        void CalcTerritoryOfBuilding(const noBaseBuilding* const building);

        // Liefert den Besitzer eines Punktes (mit absoluten Koordinaten, werden automatisch in relative umgerechnet!)
        uint8_t GetOwner(const int32_t x, const int32_t y)
        { return nodes[(y - y1) * (x2 - x1) + (x - x1)].owner; }
        /// Liefert Radius mit dem der Punkt besetzt wurde
        uint8_t GetRadius(const int32_t x, const int32_t y) const
        { return nodes[(y - y1) * (x2 - x1) + (x - x1)].radius; }

        // Korrigiert die Grenzen (schneidet vom aktuellen Territorium immer noch die äußeren Punkte ab für die Grenzpfähle)
        void AdjustBorders();


};

#endif


