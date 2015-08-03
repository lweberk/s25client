// $Id: FOWObjects.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef FOWOBJECT_H_INCLUDED
#define FOWOBJECT_H_INCLUDED

#include "gameData/GameConsts.h"
#include "gameTypes/MapTypes.h"

class SerializedGameData;

/// Typen für die FOW Objekte
enum FOW_Type
{
    FOW_NOTHING,
    FOW_BUILDING,
    FOW_BUILDINGSITE,
    FOW_FLAG,
    FOW_TREE,
    FOW_GRANITE
};

/// Helligkeit der Objekte beim Zeichnen
const uint32_t FOW_DRAW_COLOR_BRIGHTNESS = 0x80;
/// Farbe für das Zeichnen
const uint32_t FOW_DRAW_COLOR = 0xFF808080;

/// Berechnet die dunklere Spielerfarbe zum Zeichnen
uint32_t CalcPlayerFOWDrawColor(const uint32_t color);

/// Visuelles Objekt im Nebel, nur zur sichtbaren "Erinnerung",
/// was ein bestimmter Spieler gesehen hat
class FOWObject
{
    public:

        virtual ~FOWObject();
        /// An x,y zeichnen.
        virtual void Draw(int32_t x, int32_t y) const = 0;
        /// Serialisierungsfunktion.
        virtual void Serialize(SerializedGameData* sgd) const = 0;
        /// Gibt Typ zurück
        virtual FOW_Type GetType() const = 0;
};

/// Platzhalter-Objekt, falls dort kein Objekt existiert
class fowNothing : public FOWObject
{
    public:

        fowNothing();
        fowNothing(SerializedGameData* sgd);
        void Serialize(SerializedGameData* sgd) const;
        void Draw(int32_t x, int32_t y) const;
        FOW_Type GetType() const { return FOW_NOTHING; }
} const nothing;



/// Gebäude im Nebel
class fowBuilding : public FOWObject
{
    private:
        /// Typ des Gebäudes
        const BuildingType type;
        /// Volk des Gebäudes (muss extra gespeichert werden, da ja auch z.B. fremde Gebäude erobert werden können)
        const Nation nation;
    public:

        fowBuilding(const BuildingType type, const Nation nation);
        fowBuilding(SerializedGameData* sgd);
        void Serialize(SerializedGameData* sgd) const;
        void Draw(int32_t x, int32_t y) const;
        FOW_Type GetType() const { return FOW_BUILDING; }
};

/// Baustelle
class fowBuildingSite : public FOWObject
{
    private:
        /// Wird planiert?
        const bool planing;
        /// Typ des Gebäudes
        const BuildingType type;
        /// Volk des Gebäudes (muss extra gespeichert werden, da ja auch z.B. fremde Gebäude erobert werden können)
        const Nation nation;
        /// Gibt den Baufortschritt an, wie hoch das Gebäude schon gebaut ist, gemessen in 8 Stufen für jede verbaute Ware
        const uint8_t build_progress;
    public:

        fowBuildingSite(const bool planing, const BuildingType type, const Nation nation, const uint8_t build_progress);
        fowBuildingSite(SerializedGameData* sgd);
        void Serialize(SerializedGameData* sgd) const;
        void Draw(int32_t x, int32_t y) const;
        FOW_Type GetType() const { return FOW_BUILDINGSITE; }
};


/// Flagge
class fowFlag : public FOWObject
{
    private:
        /// Besitzer
        const uint8_t player;
        /// Flaggenart
        const FlagType flag_type;

    public:

        fowFlag(const uint8_t player, const FlagType flag_type);
        fowFlag(SerializedGameData* sgd);
        void Serialize(SerializedGameData* sgd) const;
        void Draw(int32_t x, int32_t y) const;
        FOW_Type GetType() const { return FOW_FLAG; }
};

/// Baum
class fowTree : public FOWObject
{
    private:

        /// Typ des Baumes (also welche Baumart)
        const uint8_t type;
        /// Größe des Baumes (0-2, 3 = aufgewachsen!)
        const uint8_t size;

    public:

        fowTree(const uint8_t type, const uint8_t size);
        fowTree(SerializedGameData* sgd);
        void Serialize(SerializedGameData* sgd) const;
        void Draw(int32_t x, int32_t y) const;
        FOW_Type GetType() const { return FOW_TREE; }
};

/// Granitblock
class fowGranite : public FOWObject
{
    private:

        const GraniteType type; /// Welcher Typ ( gibt 2 )
        const uint8_t state; /// Status, 0 - 5, von sehr wenig bis sehr viel

    public:

        fowGranite(const GraniteType type, const uint8_t state);
        fowGranite(SerializedGameData* sgd);
        void Serialize(SerializedGameData* sgd) const;
        void Draw(int32_t x, int32_t y) const;
        FOW_Type GetType() const { return FOW_GRANITE; }
};




#endif // !FOWOBJECT_H_INCLUDED
