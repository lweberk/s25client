// $Id: Minimap.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef MINIMAP_H_
#define MINIMAP_H_

struct MapNode;
class GameWorldViewer;

#include "Loader.h"
#include "ogl/glArchivItem_Bitmap_Direct.h"
#include "gameTypes/MapTypes.h"
#include "Point.h"
#include <vector>

class glArchivItem_Map;

class Minimap
{
        ///// Breite und Höhe (Pixel) der Bounding Box, in die die Map zentriert wird
        //uint16_t width,height;
        ///// Breite und Höhe (Pixel) der angezeigten Map
        //uint16_t width_show, height_show;
    protected:
        /// Breite und Höhe der Map (in Knoten)
        uint16_t map_width, map_height;

        /// Textur für die Map
        glArchivItem_Bitmap_Direct map;

        //struct PlayerColor
        //{
        //  PlayerColor() { color = 0; }
        //  uint32_t color;
        //} players_color[MAX_PLAYERS];

    protected:

        /// Zusätzliche Dinge, die die einzelnen Maps vor dem Zeichenvorgang zu tun haben
        virtual void BeforeDrawing();
        /// Variiert die übergebene Farbe zufällig in der Helligkeit
        uint32_t VaryBrightness(const uint32_t color, const int32_t range) const;

    public:

        Minimap() { };
        Minimap(const uint16_t map_width, const uint16_t map_height);
        virtual ~Minimap() {}

        void SetMap(glArchivItem_Map* s2map);

        /// Zeichnet die Minimap zentriert in die entsprechende Bounding-Box
        /// (x und y bezieht sich auf obere linke Ecke der Bounding Box)
        void Draw(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);

        /// Gibt Größe der Map zurück
        uint16_t GetMapWidth() const { return map_width; }
        uint16_t GetMapHeight() const { return map_height; }

    protected:

        /// Erstellt die Textur
        void CreateMapTexture(const void* param);

        /// Berechnet einen bestimmten Punkt neu
        void RecalcNode(const void* param, const MapPoint pt);
        /// Berechnet die Farbe eines Pixels
        virtual uint32_t CalcPixelColor(const void* param, const MapPoint pt, const uint32_t t) = 0;
};

class PreviewMinimap : public Minimap
{
    public:
        PreviewMinimap(glArchivItem_Map* s2map);

    protected:

        /// Berechnet die Farbe für einen bestimmten Pixel der Minimap (t = Terrain1 oder 2)
        uint32_t CalcPixelColor(const void* param, const MapPoint pt, const uint32_t t);
};

class IngameMinimap : public Minimap
{
        /// Referenz auf den GameWorldViewer
        const GameWorldViewer& gwv;
        /// Speichert die einzelnen Veränderungen eines jeden Mappunktes, damit nicht unnötigerweise
        /// in einem GF mehrmals der Mappunkt verändert wird
        std::vector<bool> nodes_updated;
        /// Liste mit allen Punkten, die geändert werden müssen
        std::vector<MapPoint> nodesToUpdate;


        /// Für jeden einzelnen Knoten speichern, welches Objekt hier dominiert, also wessen Pixel angezeigt wird
        enum DrawnObject
        {
            DO_INVALID = 0,
            DO_INVISIBLE, /// im im vollständigem Dunklen
            DO_TERRAIN, /// Nur Terrain oder Baum und Granit ohne irgendwas
            DO_PLAYER, /// Nur Terrain oder Baum und Granit mit Spielerterritorium dazu
            DO_BUILDING, /// Gebäude
            DO_ROAD /// Straße
        };

        std::vector<DrawnObject> dos;

        /// Einzelne Dinge anzeigen oder nicht anzeigen
        bool territory; /// Länder der Spieler
        bool houses; /// Häuser
        bool roads; /// Straßen

    public:
        IngameMinimap(const GameWorldViewer& gwv);


        /// Merkt, vor dass ein bestimmter Punkt aktualisiert werden soll
        void UpdateNode(const MapPoint pt);

        /// Updatet die gesamte Minimap
        void UpdateAll();
        uint32_t GetMMIdx(const MapPoint pt)
        { return static_cast<uint32_t>(pt.y) * static_cast<uint32_t>(map_width) + static_cast<uint32_t>(pt.x); }


        /// Die einzelnen Dinge umschalten
        void ToggleTerritory();
        void ToggleHouses();
        void ToggleRoads();

    protected:

        /// Berechnet die Farbe für einen bestimmten Pixel der Minimap (t = Terrain1 oder 2)
        uint32_t CalcPixelColor(const void* param, const MapPoint pt, const uint32_t t);
        /// Berechnet für einen bestimmten Punkt und ein Dreieck die normale Terrainfarbe
        uint32_t CalcTerrainColor(const MapPoint pt, const uint32_t t);
        /// Prüft ob an einer Stelle eine Straße gezeichnet werden muss
        bool IsRoad(const MapPoint pt, const Visibility visibility);
        /// Berechnet Spielerfarbe mit in eine gegebene Farbe mit ein (player muss mit +1 gegeben sein!)
        uint32_t CombineWithPlayerColor(const uint32_t color, const uint8_t player) const;
        /// Zusätzliche Dinge, die die einzelnen Maps vor dem Zeichenvorgang zu tun haben
        /// in dem Falle: Karte aktualisieren
        void BeforeDrawing();
        /// Alle Punkte Updaten, bei denen das DrawnObject gleich dem übergebenen drawn_object ist
        void UpdateAll(const DrawnObject drawn_object);
};



#endif

