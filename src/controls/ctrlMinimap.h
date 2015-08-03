// $Id: ctrlMinimap.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CTRL_MINIMAP_H_
#define CTRL_MINIMAP_H_

#include "ctrlRectangle.h"
#include "gameTypes/MapTypes.h"

class Minimap;

/// Übersichtskarte (MapPreview)
class ctrlMinimap : public Window
{
    protected:
        /// Größe der Anzeige der Minimap
        uint16_t width_show, height_show;
        /// Abstand der Minimap vom Rand des Controls
        uint16_t padding_x, padding_y;
    public:

        ctrlMinimap( Window* parent,
                     const uint32_t id,
                     const uint16_t x,
                     const uint16_t y,
                     const uint16_t width,
                     const uint16_t height,
                     const uint16_t padding_x,
                     const uint16_t padding_y,
                     const uint16_t map_width,
                     const uint16_t map_height);

        /// Gibt width_show und height_show zurück
        uint16_t GetWidthShow() const { return width_show; }
        uint16_t GetHeightShow() const { return height_show; }

        /// Gibt die entsprechenden Kanten relativ zur oberen linken Ecke der Bounding-Box
        inline uint16_t GetLeft() const { return padding_x + (width - width_show - 2 * padding_x) / 2; }
        inline uint16_t GetTop() const { return padding_y + (height - height_show - 2 * padding_y) / 2; }
        inline uint16_t GetRight() const { return GetLeft() + width_show + padding_x; }
        inline uint16_t GetBottom() const { return GetTop() + height_show + padding_y; }

        /// Größe ändern
        virtual void Resize_(uint16_t width, uint16_t heigth);
        void SetDisplaySize(const uint16_t width, const uint16_t height,
                            const uint16_t map_width, const uint16_t map_height);

        /// Liefert für einen gegebenen Map-Punkt die Pixel-Koordinaten relativ zur Bounding-Box
        inline uint16_t CalcMapCoordX(const uint16_t x) const
        { return GetLeft() + width_show * x / map_width; }
        inline uint16_t CalcMapCoordY(const uint16_t y) const
        { return GetTop() + height_show * y / map_height; }

        /// Verkleinert Minimap soweit es geht (entfernt Bounding-Box) in Y-Richtung und gibt neue Höhe zurück
        void RemoveBoundingBox(const uint16_t width_min, const uint16_t height_min);

    protected:

        /// Zeichnet die Minimap an sich
        void DrawMap(Minimap& map);

        ///// Berechnet X-Koordinaten der rechten Seiten
        //uint16_t GetLeft() const { return x+minimap.GetLeft(); }
        ///// Berechnet Y-Koordinate der unteren Kante
        //uint16_t GetBottom() const { return y+minimap.GetBottom(); }

    protected:

        uint16_t map_width;
        uint16_t map_height;
};


#endif // !MapPreview_H_

