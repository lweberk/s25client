// $Id: noBuildingSite.h 9357 2014-04-25 15:35:25Z FloSoft $
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

#ifndef NO_BUILDINGSITE_H_
#define NO_BUILDINGSITE_H_

#include "noBaseBuilding.h"
#include <list>

// Enumforwarddeklaration bei VC nutzen
#ifdef _MSC_VER
enum BuildingType;
#else
#include "gameData/GameConsts.h"
#endif

class nofBuilder;
class nofPlaner;

/// repräsentiert eine Baustelle
class noBuildingSite : public noBaseBuilding
{
        friend class nofBuilder;

        /// Typ/Status der Baustelle
        enum State
        {
            STATE_PLANING = 0, // Baustelle muss erst noch planiert werden
            STATE_BUILDING
        } state;
        /// Planierer
        nofPlaner* planer;
        /// Bauarbeiter, der an dieser Baustelle arbeitet
        nofBuilder* builder;
        /// Bretter und Steine, die hier liegen
        uint8_t boards, stones;
        /// Bretter und Steine, die schon verbaut wurden
        uint8_t used_boards, used_stones;
        /// Gibt den Baufortschritt an, wie hoch das Gebäude schon gebaut ist, gemessen in 8 Stufen für jede verbaute Ware
        uint8_t build_progress;
        /// Bestellte Bretter und Steine, d.h. Steine/Bretter, die noch "bestellt" wurden, aber noch nicht da sind
        std::list<Ware*> ordered_boards, ordered_stones;

    public:
        uint8_t getUsedBoards() const { return used_boards; }
        uint8_t getUsedStones() const { return used_stones; }
        uint8_t getBoards() const { return boards; }
        uint8_t getStones() const { return stones; }

        noBuildingSite(const BuildingType type, const MapPoint pt, const uint8_t player);
        /// Konstruktor für Hafenbaustellen vom Schiff aus
        noBuildingSite(const MapPoint pt, const uint8_t player);
        noBuildingSite(SerializedGameData* sgd, const uint32_t obj_id);

        ~noBuildingSite();

        /// Aufräummethoden
    protected:  void Destroy_noBuildingSite();
    public:     void Destroy() { Destroy_noBuildingSite(); }

        /// Serialisierungsfunktionen
    protected:  void Serialize_noBuildingSite(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_noBuildingSite(sgd); }

        GO_Type GetGOT() const { return GOT_BUILDINGSITE; }

        void Draw(int32_t x, int32_t y);

        /// Erzeugt von ihnen selbst ein FOW Objekt als visuelle "Erinnerung" für den Fog of War
        FOWObject* CreateFOWObject() const;

        void AddWare(Ware* ware);
        void GotWorker(Job job, noFigure* worker);

        /// Fordert Baumaterial an
        void OrderConstructionMaterial();
        /// Wird aufgerufen, wenn der Bauarbeiter kündigt
        void Abrogate();
        /// Eine bestellte Ware konnte doch nicht kommen
        void WareLost(Ware* ware);
        /// Gibt den Bau-Fortschritt zurück
        uint8_t GetBuildProgress(bool percent = true) const;

        uint32_t CalcDistributionPoints(noRoadNode* start, const GoodType type);

        /// Wird aufgerufen, wenn eine neue Ware zum dem Gebäude geliefert wird (nicht wenn sie bestellt wurde vom Gebäude!)
        void TakeWare(Ware* ware);
        /// Gibt zurück, ob die Baustelle fertiggestellt ist
        bool IsBuildingComplete();

        /// Aufgerufen, wenn Planierung beendet wurde
        void PlaningFinished();
        /// Gibt zurück, ob eine bestimmte Baustellen eine Baustelle ist, die vom Schiff aus errichtet wurde
        bool IsHarborBuildingSiteFromSea() const;


};


#endif
