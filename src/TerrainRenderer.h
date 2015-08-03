// $Id: TerrainRenderer.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef TERRAIN_RENDERER_H_
#define TERRAIN_RENDERER_H_

#include <cstdint>

#include "gameTypes/MapTypes.h"

class GameWorldViewer;
class GameWorldView;

struct MapTile
{
    int32_t x;
    int32_t y;
    uint32_t count;
    int32_t xo;
    int32_t yo;
};

struct BorderTile
{
    int32_t offset;
    uint32_t count;
    int32_t xo;
    int32_t yo;
};

struct PreparedRoad
{
    uint8_t type;
    float xpos, ypos;
    float xpos2, ypos2;
    float color1, color2;
    uint8_t dir;

    PreparedRoad(uint8_t type, float xpos, float ypos, float xpos2, float ypos2, float color1, float color2, uint8_t dir) : type(type), xpos(xpos), ypos(ypos), xpos2(xpos2), ypos2(ypos2), color1(color1), color2(color2), dir(dir) {}

    bool operator<(const PreparedRoad b) const {return(type < b.type);}
};


/// Klasse, die für das grafische Anzeigen (Rendern) des Terrains zuständig ist
class TerrainRenderer
{
        struct Point
        {
            float x;
            float y;
        };

        struct ColorPoint
        {
            Point pos;
            float color;
        };

        struct Vertex
        {
            ColorPoint pos; // Position vom jeweiligen Punkt
            uint8_t terrain[2]; // Terrain der Dreiecke
            ColorPoint border[2]; // Mittelpunkt für Ränder
        };

        struct Color
        {
            float r;
            float g;
            float b;
        };

        struct Triangle
        {
            Point pos[3];
        };

        struct ColorTriangle
        {
            Color colors[3];
        };

        struct Borders
        {
            uint8_t left_right[2];
            uint8_t right_left[2];
            uint8_t top_down[2];
            uint32_t left_right_offset[2];
            uint32_t right_left_offset[2];
            uint32_t top_down_offset[2];
        };

        /// Breite und Höhe der Karte
        uint16_t width, height;

        Vertex* vertices;

        Triangle* gl_vertices;
        Triangle* gl_texcoords;
        ColorTriangle* gl_colors;

        uint32_t vbo_vertices;
        uint32_t vbo_texcoords;
        uint32_t vbo_colors;

        Borders* borders;
        uint32_t border_count;

    private:

        uint32_t GetTRIdx(const MapPoint pt)
        { return static_cast<uint32_t>(pt.y) * static_cast<uint32_t>(width) + static_cast<uint32_t>(pt.x); }

        /// liefert den Vertex an der Stelle X, Y.
        Vertex& GetVertex(const MapPoint pt) { return vertices[GetTRIdx(pt)]; }

        /// erzeugt die Terrain-Vertices.
        void GenerateVertices(const GameWorldViewer* gwb);
        /// erzeugt Vertex (update, wenn die Daten ggf. im Vertexbuffer ersetzt werden sollen, bei Veränderung)
        void UpdateVertexPos(const MapPoint pt, const GameWorldViewer* gwv);
        void UpdateVertexColor(const MapPoint pt, const GameWorldViewer* gwv);
        void UpdateVertexTerrain(const MapPoint pt, const GameWorldViewer* gwv);
        /// erzeugt Rand-Vertex
        void UpdateBorderVertex(const MapPoint pt, const GameWorldViewer* gwv);

        /// Erzeugt fertiges Dreieick für OpenGL
        void UpdateTrianglePos(const MapPoint pt, const GameWorldViewer* gwv, const bool update);
        void UpdateTriangleColor(const MapPoint pt, const GameWorldViewer* gwv, const bool update);
        void UpdateTriangleTerrain(const MapPoint pt, const GameWorldViewer* gwv, const bool update);
        /// Erzeugt die Dreiecke für die Ränder
        void UpdateBorderTrianglePos(const MapPoint pt, const GameWorldViewer* gwv, const bool update);
        void UpdateBorderTriangleColor(const MapPoint pt, const GameWorldViewer* gwv, const bool update);
        void UpdateBorderTriangleTerrain(const MapPoint pt, const GameWorldViewer* gwv, const bool update);

        /// liefert den Vertex-Farbwert an der Stelle X,Y
        float GetColor(const MapPoint pt) { return GetVertex(pt).pos.color; }
        /// liefert den X-Rand-Vertex an der Stelle X,Y
        float GetBX(const MapPoint pt, uint8_t triangle) { return GetVertex(pt).border[triangle].pos.x; }
        /// liefert den Y-Rand-Vertex an der Stelle X,Y
        float GetBY(const MapPoint pt, uint8_t triangle) { return GetVertex(pt).border[triangle].pos.y; }
        /// Liefert BX,BY um einen Punkt herum, beachtet auch Kartenränder (entspricht GetTerrainX)
        float GetBXAround(int32_t x, int32_t y, const uint8_t triangle, const uint8_t dir);
        float GetBYAround(int32_t x, int32_t y, const uint8_t triangle, const uint8_t dir);
        /// liefert den Rand-Vertex-Farbwert an der Stelle X,Y
        float GetBColor(const MapPoint pt, uint8_t triangle) { return GetVertex(pt).border[triangle].color; }

        /// Zeichnet die Wege
        void PrepareWays(GameWorldView* gwv);
        void PrepareWaysPoint(GameWorldView* gwv, MapPoint t, int32_t xo, int32_t yo);

        void DrawWays(GameWorldView* gwv);


    public:

        TerrainRenderer();
        ~TerrainRenderer();

        /// erzeugt die OpenGL-Vertices.
        void GenerateOpenGL(const GameWorldViewer* gwv);


        /// zeichnet den Kartenausschnitt.
        void Draw(GameWorldView* gwv, uint32_t* water);

        /// Konvertiert "falsche Koordinaten", also im Minusbereich oder zu groß wegen Zeichnen, in "richtige Koordinaten"
        /// mit 0 <= x_out < width und 0 <= y_out < height
        MapPoint ConvertCoords(int32_t x, int32_t y, int32_t* xo = 0, int32_t* yo = 0) const;
        /// liefert den X-Vertex an der Stelle X,Y
        float GetTerrainX(const MapPoint pt) { return GetVertex(pt).pos.pos.x; }
        /// liefert den Y-Vertex an der Stelle X,Y
        float GetTerrainY(const MapPoint pt) { return GetVertex(pt).pos.pos.y; }
        /// liefert X-Vertex drumherum, korrigiert Koordinaten nicht
        float GetTerrainXAround(int32_t x,  int32_t y, const uint32_t dir);
        float GetTerrainYAround(int32_t x,  int32_t y, const uint32_t dir);

        /// Höhe eines Punktes wurde (durch Planierer) verändert --> updaten
        void AltitudeChanged(const MapPoint pt, const GameWorldViewer* gwv);
        /// Sichtbarkeit eines Punktes verändert
        void VisibilityChanged(const MapPoint pt, const GameWorldViewer* gwv);

        /// Berechnet Schattierungen der gesamten Map neu
        void UpdateAllColors(const GameWorldViewer* gwv);

};


#endif
