// $Id: customborderbuilder.cpp 9357 2014-04-25 15:35:25Z FloSoft $
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

/*
Border-Builder 09.09.2008
by Stefan Kriwanek
contact@stefankriwanek.de

erstellt mit libsiedler2 rev 3935

Die Methode loadEdges() der Klasse lädt die zum Erstellen eines Rahmens nötigen Bitmaps in den Speicher.
Übergeben wird
archiveInfo:    Zeiger auf ein geladenes ArchivInfo der RESOURCE.DAT/IDX

Die Methode buildBorder() erstellt einen Rahmen zu gegebener Größe.
Übergeben werden:
width, height:  die gewünschte Größe
borderInfo:     Zeiger auf ein initialisiertes, leeres ArchivInfo

In borderInfo werden vier Bilder als glArchivItem_Bitmap_RLE an Index 0 bis 3 geschrieben, das sind die Rahmen oben, unten, links und rechts, wobei die Ecken zu oben/unten gehören. Sie müssen also an den Stellen
oben:   0        0
unten:  0        height-12
links:  0        12
rechts: widht-12 12
zu sehen sein.

Vor dem Aufruf von buildBorder() muss der interne, öffentliche Zeiger *palette auf ein ArchivItem_Palette* gesetzt werden.
*/

#include "defines.h"
#include "customborderbuilder.h"
#include "ogl/glArchivItem_Bitmap_RLE.h"
#include "../libsiedler2/src/ArchivItem_Palette.h"
#include "../libsiedler2/src/ArchivInfo.h"

using namespace libsiedler2;

/*--- CustomBorderBuilder-Klasse *********************************************/

CustomBorderBuilder::CustomBorderBuilder(const ArchivItem_Palette* const palette) : palette(palette)
{
    edgesLoaded = false;
}
CustomBorderBuilder::~CustomBorderBuilder()
{
    if (edgesLoaded)
    {
        // temporäre Bitmaps löschen
        for(uint8_t i = 0; i < numCorners; i++)
            delete corners[i];
        for(uint8_t i = 0; i < 3; i++)
        {
            delete edgesTop[i];
            delete edgesBottom[i];
            delete edgesLeft[i];
            delete edgesRight[i];
        }
        for(uint8_t i = 0; i < numFillersTop; i++)
            delete fillersTop[i];
        for(uint8_t i = 0; i < numFillersBottom; i++)
            delete fillersBottom[i];
        for(uint8_t i = 0; i < numFillersLeft; i++)
            delete fillersLeft[i];
        for(uint8_t i = 0; i < numFillersRight; i++)
            delete fillersRight[i];
    }
}

int32_t CustomBorderBuilder::loadEdges(const ArchivInfo* archiveInfo)
{
    // simples Fehlerabfangen
    if (archiveInfo->getCount() != 57)
        return 1; // nicht RESOURCE.DAT übergeben

    // Musterstücke einladen
    /* Evtl. könnte man hier nur den größten Rahmen laden und alle Teile aus diesem rauskopieren, um das Ganze etwas schneller zu machen.
       Allerdings sind die einander entsprechenden Stücke teilweise nicht in jeder Auflösung tatsächlich gleich, sodass man das für jedes vorher prüfen müsste.*/
    BdrBitmap* tempBMP;
    tempBMP = new BdrBitmap(1280, 1024);
    //palette = dynamic_cast<glArchivItem_Bitmap_RLE*>(archiveInfo->get(4))->getPalette();
    // 640x480
    {
        BitmapRLE2BdrBitmap(dynamic_cast<const glArchivItem_Bitmap_RLE*>(archiveInfo->get(4)), tempBMP);
        corners[0] = tempBMP->get(0, 0, 584, 12);
        corners[1] = tempBMP->get(584, 0, 56, 12);
        corners[2] = tempBMP->get(0, 468, 202, 12);
        corners[3] = tempBMP->get(508, 468, 132, 12);
        corners[4] = tempBMP->get(202, 468, 306, 12);
        corners[5] = tempBMP->get(0, 12, 12, 352);
        corners[6] = tempBMP->get(0, 364, 12, 104);
        corners[7] = tempBMP->get(628, 12, 12, 268);
        corners[8] = tempBMP->get(628, 280, 12, 188);
        fillersTop[0] = tempBMP->get(270, 0, 2, 12);
        fillersTop[2] = tempBMP->get(446, 0, 42, 12);
        fillersTop[3] = tempBMP->get(166, 0, 104, 12);
        fillersBottom[0] = tempBMP->get(508, 468, 2, 12);
    }
    // 800x600
    {
        BitmapRLE2BdrBitmap(dynamic_cast<const glArchivItem_Bitmap_RLE*>(archiveInfo->get(7)), tempBMP);
        edgesTop[0] = tempBMP->get(584, 0, 160, 12);
        edgesBottom[0] = tempBMP->get(508, 588, 160, 12);
        edgesLeft[0] = tempBMP->get(0, 364, 12, 120);
        edgesRight[0] = tempBMP->get(788, 280, 12, 120);
        fillersTop[1] = tempBMP->get(583, 0, 32, 12);
    }
    // 1024x768
    {
        BitmapRLE2BdrBitmap(dynamic_cast<const glArchivItem_Bitmap_RLE*>(archiveInfo->get(10)), tempBMP);
        edgesTop[1] = tempBMP->get(644, 0, 224, 12);
        edgesBottom[1] = tempBMP->get(668, 756, 224, 12);
        edgesLeft[1] = tempBMP->get(0, 484, 12, 168);
        edgesRight[1] = tempBMP->get(1012, 400, 12, 168);
        fillersBottom[1] = tempBMP->get(637, 756, 23, 12);
        fillersBottom[2] = tempBMP->get(601, 756, 34, 12);
        fillersBottom[3] = tempBMP->get(103, 756, 42, 12);
        fillersBottom[4] = tempBMP->get(242, 756, 72, 12);
        fillersLeft[0] = tempBMP->get(0, 524, 12, 2);
        fillersLeft[2] = tempBMP->get(0, 222, 12, 17);
        fillersLeft[3] = tempBMP->get(0, 423, 12, 30);
        fillersLeft[4] = tempBMP->get(0, 114, 12, 82);
        fillersRight[0] = tempBMP->get(1012, 280, 12, 2);
        fillersRight[1] = tempBMP->get(1012, 281, 12, 8);
        fillersRight[2] = tempBMP->get(1012, 528, 12, 15);
        fillersRight[3] = tempBMP->get(1012, 291, 12, 29);
        fillersRight[4] = tempBMP->get(1012, 475, 12, 54);
        fillersRight[5] = tempBMP->get(1012, 320, 12, 78);
    }
    // 1280x1024 links
    {
        BdrBitmap* pic1;
        pic1 = new BdrBitmap(640, 1024);
        BitmapRLE2BdrBitmap(dynamic_cast<const glArchivItem_Bitmap_RLE*>(archiveInfo->get(13)), pic1);
        tempBMP->put(0, 0, pic1);
        delete pic1;
    }
    // und rechts
    {
        BdrBitmap* pic2;
        pic2 = new BdrBitmap(640, 1024);
        BitmapRLE2BdrBitmap(dynamic_cast<const glArchivItem_Bitmap_RLE*>(archiveInfo->get(14)), pic2);
        tempBMP->put(640, 0, pic2);
        delete pic2;
        edgesTop[2] = tempBMP->get(968, 0, 256, 12);
        edgesBottom[2] = tempBMP->get(892, 1012, 256, 12);
        edgesLeft[2] = tempBMP->get(0, 652, 12, 256);
        edgesRight[2] = tempBMP->get(1268, 568, 12, 256);
        fillersLeft[1] = tempBMP->get(0, 769, 12, 9);
    }
    delete tempBMP;

    edgesLoaded = true;
    return 0;
}

int32_t CustomBorderBuilder::buildBorder(const uint32_t width, const uint32_t height,
                                     ArchivInfo* borderInfo)
{
    // simples Fehlerabfangen
    if (width < 640 || height < 480)
        return 1; // kleiner geht nicht
    if (!edgesLoaded)
        return 2; // Die Stücken sind noch nicht geladen worden, so gehts nicht!

    // temporäre BdrBitmap's deklarieren
    BdrBitmap* customEdge[4];
    customEdge[0] = new BdrBitmap(width, 12); //oben
    customEdge[1] = new BdrBitmap(width, 12); //unten
    customEdge[2] = new BdrBitmap(12, height - 24); //links
    customEdge[3] = new BdrBitmap(12, height - 24); //rechts


    // den Rahmen zusammenbauen
    {
        // Ecken werden einfach eingefügt
        // horizontale Ecken:
        customEdge[0]->put(0, 0, corners[0]);
        customEdge[0]->put(width - 56, 0, corners[1]);
        customEdge[1]->put(0, 0, corners[2]);
        customEdge[1]->put(width - 132, 0, corners[3]);
        // das Mittelstück, damit das Bedienfeld passt
        customEdge[1]->put(width / 2 - 118, 0, corners[4]);
        // vertikale Ecken:
        customEdge[2]->put(0, 0, corners[5]);
        customEdge[2]->put(0, height - 128, corners[6]);
        customEdge[3]->put(0, 0, corners[7]);
        customEdge[3]->put(0, height - 212, corners[8]);

        // Freie Flächen mit Kanten ausfüllen
        // Kanten
        uint32_t emptyFromPixel;
        uint32_t toFillPixel;
        uint8_t countEdge[3] = {0, 0, 0};
        uint16_t lengthEdge[3];
        // obere Kante
        emptyFromPixel = 584;
        toFillPixel = width - 640;
        for(uint8_t i = 0; i < 3; i++)
            lengthEdge[i] = edgesTop[i]->w;
        FindEdgeDistribution(toFillPixel, lengthEdge, countEdge);
        WriteEdgeDistribution(emptyFromPixel, 0, toFillPixel, false,
                              lengthEdge, countEdge, edgesTop,
                              numFillersTop, fillersTop, customEdge[0]);
        // untere Kante links
        emptyFromPixel = 202;
        toFillPixel = width / 2 - 320;
        for(uint8_t i = 0; i < 3; i++)
            lengthEdge[i] = edgesBottom[i]->w;
        FindEdgeDistribution(toFillPixel, lengthEdge, countEdge);
        WriteEdgeDistribution(emptyFromPixel, 0, toFillPixel, false,
                              lengthEdge, countEdge, edgesTop,
                              numFillersBottom, fillersBottom, customEdge[1]);
        // untere Kante rechts
        emptyFromPixel = width / 2 + 188;
        toFillPixel = width - width / 2 - 320; // hier steht w - w/2 statt w/2, um den Rundungsfehler bei ungeraden w zu kompensieren
        for(uint8_t i = 0; i < 3; i++)
            lengthEdge[i] = edgesBottom[i]->w;
        FindEdgeDistribution(toFillPixel, lengthEdge, countEdge);
        WriteEdgeDistribution(emptyFromPixel, 0, toFillPixel, false,
                              lengthEdge, countEdge, edgesTop,
                              numFillersBottom, fillersBottom, customEdge[1]);
        // linke Kante
        emptyFromPixel = 352;
        toFillPixel = height - 480;
        for(uint8_t i = 0; i < 3; i++)
            lengthEdge[i] = edgesLeft[i]->h;
        FindEdgeDistribution(toFillPixel, lengthEdge, countEdge);
        WriteEdgeDistribution(0, emptyFromPixel, toFillPixel, true,
                              lengthEdge, countEdge, edgesLeft,
                              numFillersLeft, fillersLeft, customEdge[2]);
        // rechte Kante
        emptyFromPixel = 268;
        toFillPixel = height - 480;
        for(uint8_t i = 0; i < 3; i++)
            lengthEdge[i] = edgesRight[i]->h;
        FindEdgeDistribution(toFillPixel, lengthEdge, countEdge);
        WriteEdgeDistribution(0, emptyFromPixel, toFillPixel, true,
                              lengthEdge, countEdge, edgesRight,
                              numFillersRight, fillersRight, customEdge[3]);
    }

    // Bildspeicher für Ausgaberahmen vorbereiten; in glArchivItem_Bitmap_RLE kovertieren
    borderInfo->alloc(4);
    for(uint32_t i = 0; i < 4; i++)
    {
        glArchivItem_Bitmap_RLE* customEdgeRLE = new glArchivItem_Bitmap_RLE;
        customEdgeRLE->setWidth(customEdge[i]->w); customEdgeRLE->setHeight(customEdge[i]->h); customEdgeRLE->tex_alloc();
        BdrBitmap2BitmapRLE2(customEdge[i], customEdgeRLE);
        borderInfo->setC(i, customEdgeRLE);
        delete customEdgeRLE;
    }
    // Speicher der BdrBitmap's wieder freigeben
    for(uint8_t i = 0; i < 4; i++)
        delete customEdge[i];

    return 0;
}


void CustomBorderBuilder::BitmapRLE2BdrBitmap(const glArchivItem_Bitmap_RLE* bitmapRLE, BdrBitmap* bdrBitmap)
{
    uint16_t x, y;
    for(y = 0; y < bitmapRLE->getHeight(); y++)
        for(x = 0; x < bitmapRLE->getWidth(); x++)
        {
            bdrBitmap->put(x, y, bitmapRLE->tex_getPixel(x, y, palette));
        }
}


void CustomBorderBuilder::BdrBitmap2BitmapRLE2(BdrBitmap* bdrBitmap, glArchivItem_Bitmap_RLE* bitmapRLE)
{
    for(uint32_t y = 0; y < bdrBitmap->h; y++)
        for(uint32_t x = 0; x < bdrBitmap->w; x++)
        {
            bitmapRLE->tex_setPixel(x, y, bdrBitmap->get(x, y), palette);
        }
}


void CustomBorderBuilder::FindEdgeDistribution(uint32_t toFill, uint16_t lengths[3], uint8_t (counts)[3])
{
    // Die should-Variablen speichern die bisher als am besten befundene Kombination; die would-Variablen die gerade zu prüfende
    uint8_t* &shouldCounts = counts;
    shouldCounts[0] = 0; shouldCounts[1] = 0; shouldCounts[2] = 0;
    uint8_t wouldCounts[3];
    uint8_t maxCounts[3]; // wieviel mal passt jedes Teil maximal in die Freifläche?
    for(uint8_t i = 0; i < 3; i++)
        maxCounts[i] = toFill / lengths[i];
    uint32_t shouldBeFilled = 0;
    uint8_t shouldNumDifferentTiles = 0;
    // Schleife über alle möglichen Kombinationen
    for(wouldCounts[0] = 0; wouldCounts[0] <= maxCounts[0]; wouldCounts[0]++)
        for(wouldCounts[1] = 0; wouldCounts[1] <= maxCounts[1]; wouldCounts[1]++)
            for(wouldCounts[2] = 0; wouldCounts[2] <= maxCounts[2]; wouldCounts[2]++)
            {
                // Finde, wieviel Platz die Kombination ausfüllen würde
                uint32_t wouldBeFilled = 0;
                for(uint8_t i = 0; i < 3; i++)
                    wouldBeFilled += wouldCounts[i] * lengths[i];
                // wenn die Kombination nicht zu groß ist und weniger oder gleich viel Platz frei ließe als/wie bisher
                if (wouldBeFilled <= toFill) if (wouldBeFilled >= shouldBeFilled)
                    {
                        // Finde, ob mehr verschiedene Stücken benutzt würden als bisher
                        uint8_t wouldNumDifferentTiles = 3;
                        for(uint8_t i = 0; i < 3; i++) if (wouldCounts[i] == 0)
                                wouldNumDifferentTiles--;
                        // wenn mehr Stücke benutzt würden oder weniger Freifläche bleibt
                        if ((wouldNumDifferentTiles > shouldNumDifferentTiles) || (wouldBeFilled > shouldBeFilled))
                        {
                            // Bessere Verteilung gefunden, in should-Variablen speichern
                            for(uint8_t i = 0; i < 3; i++)
                                shouldCounts[i] = wouldCounts[i];
                            shouldNumDifferentTiles = wouldNumDifferentTiles;
                            shouldBeFilled = wouldBeFilled;
                        }
                    }
            }
    for(uint8_t i = 0; i < 3; i++)
        counts[i] = shouldCounts[i];
}


void CustomBorderBuilder::WriteEdgeDistribution(const uint32_t x,
        const uint32_t y,
        const uint32_t toFill,
        const bool direction, // false = waagerecht, true = senkrecht
        const uint16_t edgeLengths[3],
        uint8_t edgeCounts[3],
        BdrBitmap* edges[],
        const uint8_t numFillers,
        BdrBitmap* fillers[],
        BdrBitmap* outBorder)
// Schreibt die übergebene Verteilung ins Bild und füllt die restliche Fläche auf.
{
    uint32_t emptyFromPixel = direction ? y : x;
    uint32_t toFillPixel = toFill;

    // Wieviele große Stücken zu schreiben?
    uint8_t edgesToDistribute = 0;
    for(uint8_t i = 0; i < 3; i++)
        edgesToDistribute += edgeCounts[i];

    // Der Reihe nach schreiben
    uint32_t takeEdgeNum = 0;
    while (edgesToDistribute > 0)
    {
        if (edgeCounts[takeEdgeNum] > 0)
        {
            if (direction)
                outBorder->put(x, emptyFromPixel, edges[takeEdgeNum]);
            else
                outBorder->put(emptyFromPixel, y, edges[takeEdgeNum]);
            emptyFromPixel += edgeLengths[takeEdgeNum];
            toFillPixel -= edgeLengths[takeEdgeNum];
            edgeCounts[takeEdgeNum]--;
            edgesToDistribute--;
        }
        takeEdgeNum = (takeEdgeNum + 1) % 3;
    }

    // Fülle den Rest auf
    uint8_t* numFillersToUse = new uint8_t[numFillers];
    for(uint8_t i = 0; i < numFillers; i++)
        numFillersToUse[i] = 0;
    // Finde, wie oft jedes Füllerstück gebraucht wird. Einfach von groß nach klein einfügen, wenn der Platz jeweils noch reicht.
    uint8_t curFiller = numFillers - 1;
    while (toFillPixel > 0)
    {
        uint16_t length = direction ? fillers[curFiller]->h : fillers[curFiller]->w;
        if (length <= toFillPixel)
        {
            numFillersToUse[curFiller]++;
            toFillPixel -= length;
        }
        else
        {
            if (curFiller > 0) // Das nächstkleinere Füllerstück testen
                curFiller--;
            else // Wenn am Ende weniger Platz freibleibt als das kleinste Füllerstück groß ist (2 Pixel), wird sofort ein passendes Teilstück eingefügt.
            {
                if (direction)
                    outBorder->put(x, emptyFromPixel, fillers[0]->get(0, 0, 12, toFillPixel), true);
                else
                    outBorder->put(emptyFromPixel, y, fillers[0]->get(0, 0, toFillPixel, 12), true);
                emptyFromPixel += toFillPixel;
                toFillPixel = 0;
            }
        }
    }

    // Schreibe die Füllerstückkombination von groß nach klein
    uint8_t numUsedFillers = 0;
    for(uint8_t i = 1; i < numFillers; i++)
        numUsedFillers += numFillersToUse[i];
    for(uint8_t i = numFillers - 1; (i >= 1); i--) //
    {
        for(uint8_t j = 0; j < numFillersToUse[i]; j++)
        {
            // Vor jedem großen zuerst ein paar der kleinsten Füller, damit die großen nicht so aneinander gequetscht sind.
            for(uint8_t j = 0; j < numFillersToUse[0] / (numUsedFillers + 1); j++)
            {
                if (direction)
                    outBorder->put(x, emptyFromPixel, fillers[0]);
                else
                    outBorder->put(emptyFromPixel, y, fillers[0]);
                emptyFromPixel += direction ? fillers[0]->h : fillers[0]->w;
            }
            if (direction)
                outBorder->put(x, emptyFromPixel, fillers[i]);
            else
                outBorder->put(emptyFromPixel, y, fillers[i]);
            emptyFromPixel += direction ? fillers[i]->h : fillers[i]->w;
        }
    }
    // Die restlichen kleinen Füller
    const uint8_t numSmallFillers = numFillersToUse[0] - (numFillersToUse[0] / (numUsedFillers + 1)) * numUsedFillers;
    for(uint8_t j = 0; j < numSmallFillers; j++)
    {
        if (direction)
            outBorder->put(x, emptyFromPixel, fillers[0]);
        else
            outBorder->put(emptyFromPixel, y, fillers[0]);
        emptyFromPixel += direction ? fillers[0]->h : fillers[0]->w;
    }
    delete [] numFillersToUse;

}


/********************************************* CustomBorderBuilder-Klasse ---*/

/*--- BdrBitmap-Klasse *******************************************************/
// public
CustomBorderBuilder::BdrBitmap::BdrBitmap(const uint32_t width, const uint32_t height)
{
    w = width;
    h = height;
    value = new uint8_t [w * h];
    /*  for(uint64_t i = 0; i < w*h; i++)
        value[i] = 254; */ // Initialisieren nicht mehr nötig, da nix transparent bleibt
}

CustomBorderBuilder::BdrBitmap::~BdrBitmap()
{
    delete [] value;
}

CustomBorderBuilder::BdrBitmap* CustomBorderBuilder::BdrBitmap::get(const uint32_t x, const uint32_t y, const uint32_t width, const uint32_t height) const
{
    BdrBitmap* pic = new BdrBitmap(width, height);
    for(uint32_t i = 0; i < pic->h; i++)
        for(uint32_t j = 0; j < pic->w; j++)
        {
            pic->value[pic->getpos(j, i)] = value[getpos(x + j, y + i)];
        }
    return pic;
}

inline uint8_t CustomBorderBuilder::BdrBitmap::get(const uint32_t x, const uint32_t y) const
{
    return value[getpos(x, y)];
}

void CustomBorderBuilder::BdrBitmap::put(const uint32_t x, const uint32_t y, BdrBitmap* pic, bool picGetted)
{
    for(uint32_t i = 0; i < pic->h; i++)
        for(uint32_t j = 0; j < pic->w; j++)
        {
            value[getpos(x + j, y + i)] = pic->value[pic->getpos(j, i)];
        }
    if (picGetted)
        delete pic;
}

inline void CustomBorderBuilder::BdrBitmap::put(const uint32_t x, const uint32_t y, const uint8_t c)
{
    value[getpos(x, y)] = c;
}

// private

inline const uint32_t CustomBorderBuilder::BdrBitmap::getpos(const uint32_t x, const uint32_t y) const
// liefert den Index eines Pixels (x,y) im internen Speicher value[]
{
    return w * y + x;
}

/******************************************************* BdrBitmap-Klasse ---*/

