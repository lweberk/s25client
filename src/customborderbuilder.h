// $Id: customborderbuilder.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef CUSTOMBORDERBUILDER_H_INCLUDED
#define CUSTOMBORDERBUILDER_H_INCLUDED

#pragma once

class glArchivItem_Bitmap_RLE;
namespace libsiedler2{
    class ArchivItem_Palette;
    class ArchivInfo;
}

class CustomBorderBuilder
{
    public:
        CustomBorderBuilder(const libsiedler2::ArchivItem_Palette* const palette);
        ~CustomBorderBuilder();
        int32_t loadEdges(const libsiedler2::ArchivInfo* archiveInfo);
        int32_t buildBorder(const uint32_t width, const uint32_t height, libsiedler2::ArchivInfo* borderInfo);
        const libsiedler2::ArchivItem_Palette* palette;

    private:
        class BdrBitmap
        {
            public:
                BdrBitmap(const uint32_t width, const uint32_t height);
                ~BdrBitmap();
                BdrBitmap* get(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) const;
                inline uint8_t get(const uint32_t x, const uint32_t y) const;
                void put(const uint32_t x, const uint32_t y, BdrBitmap* pic, bool picGetted = false); // mit true wird das übergebene BdrBitmap wieder zerstört. Das ist genau dann sinnvoll, wenn es mit BdrBitmap::get() erstellt wurde, da der Zeiger ja außeralb von BdrBitmap::put() nicht mehr verfügbar ist.
                inline void put(const uint32_t x, const uint32_t y, const uint8_t c);
                uint32_t w;
                uint32_t h;

            private:
                inline const uint32_t getpos(const uint32_t x, const uint32_t y) const;
                uint8_t* value;
        };

        void BitmapRLE2BdrBitmap(const glArchivItem_Bitmap_RLE* bitmapRLE, BdrBitmap* bdrBitmap);
        void BdrBitmap2BitmapRLE2(BdrBitmap* bdrBitmap, glArchivItem_Bitmap_RLE* bitmapRLE);

        void FindEdgeDistribution(uint32_t toFill, uint16_t lengths[3], uint8_t (counts)[3]);
        void WriteEdgeDistribution(const uint32_t x,
                                   const uint32_t y,
                                   const uint32_t toFill,
                                   const bool direction, // false = waagerecht, true = senkrecht
                                   const uint16_t edgeLengths[3],
                                   uint8_t edgeCounts[3], // wird verändert, nicht weiterbenutzen
                                   BdrBitmap* edges[],
                                   const uint8_t numFillers,
                                   BdrBitmap* fillers[],
                                   BdrBitmap* outBorder);

        bool edgesLoaded;
        static const uint8_t numCorners = 9;
        BdrBitmap* corners[numCorners];
        BdrBitmap* edgesTop[3]; // edges sind die "großen" Stücke, die jeweils zwischen zwei Auflösungen dazukommen.
        BdrBitmap* edgesBottom[3];
        BdrBitmap* edgesLeft[3];
        BdrBitmap* edgesRight[3];
        static const uint8_t numFillersTop = 4; // fillers sind zusammengesuchte "kleine" Stücke, die aneinandergereiht werden können
        BdrBitmap* fillersTop[numFillersTop];
        static const uint8_t numFillersBottom = 5;
        BdrBitmap* fillersBottom[numFillersBottom];
        static const uint8_t numFillersLeft = 5;
        BdrBitmap* fillersLeft[numFillersLeft];
        static const uint8_t numFillersRight = 6;
        BdrBitmap* fillersRight[numFillersRight];
};

#endif // CUSTOMBORDER_H_INCLUDED
