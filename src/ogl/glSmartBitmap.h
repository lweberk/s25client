// $Id: glBitmap.cpp 8155 2012-09-06 02:11:55Z Maqs $
//
// Copyright (c) 2005 - 2012 Settlers Freaks (sf-team at siedler25.org)
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

#ifndef GLBITMAP_H_INCLUDED
#define GLBITMAP_H_INCLUDED

#pragma once

#include <vector>
#include "oglIncludes.h"

#include "glArchivItem_Bitmap.h"
#include "glArchivItem_Bitmap_Player.h"

enum glBitmapItemType
{
    TYPE_ARCHIVITEM_BITMAP = 0,
    TYPE_ARCHIVITEM_BITMAP_PLAYER,
    TYPE_ARCHIVITEM_BITMAP_SHADOW
};

class glBitmapItem
{
    public:
        glBitmapItem(libsiedler2::baseArchivItem_Bitmap* b, bool shadow = false) {bmp = b; type = shadow ? TYPE_ARCHIVITEM_BITMAP_SHADOW : TYPE_ARCHIVITEM_BITMAP; b->getVisibleArea(x, y, w, h); nx = b->getNx() - x; ny = b->getNy() - y;}
        glBitmapItem(libsiedler2::baseArchivItem_Bitmap_Player* b) {bmp = b; type = TYPE_ARCHIVITEM_BITMAP_PLAYER; b->getVisibleArea(x, y, w, h); nx = b->getNx() - x; ny = b->getNy() - y;}

        libsiedler2::baseArchivItem_Bitmap* bmp;
        glBitmapItemType type;

        int32_t nx, ny;
        int32_t w, h;
        int32_t x, y;
};

class glSmartBitmap
{
    private:
        int32_t w, h;
        int32_t nx, ny;

        bool sharedTexture;
        uint32_t texture;

        bool hasPlayer;

        struct GL_T2F_C4UB_V3F_Struct
        {
            GLfloat tx, ty;
            GLubyte r, g, b, a;
            GLfloat x, y, z;
        };

        std::vector<glBitmapItem> items;

    public:
        GL_T2F_C4UB_V3F_Struct tmp[8];

        glSmartBitmap() : w(0), h(0), nx(0), ny(0), sharedTexture(false), texture(0), hasPlayer(false)
        {
            tmp[0].z = tmp[1].z = tmp[2].z = tmp[3].z = 0.0f;
            tmp[4].z = tmp[5].z = tmp[6].z = tmp[7].z = 0.0f;
        }
        ~glSmartBitmap();
        void reset();

        inline int32_t getWidth() {return(w);}
        inline int32_t getHeight() {return(h);}

        inline int32_t getTexWidth() {return(hasPlayer ? w << 1 : w);}
        inline int32_t getTexHeight() {return(h);}

        inline bool isGenerated() {return(texture != 0);}
        inline bool isPlayer() {return(hasPlayer);}

        inline void setSharedTexture(uint32_t tex) {if (tex != 0) {sharedTexture = true; texture = tex;} else {sharedTexture = false; texture = 0;}}

        void calcDimensions();

        void generateTexture();
        void draw(int32_t x, int32_t y, uint32_t color = 0xFFFFFFFF, uint32_t player_color = 0x00000000);
        void drawPercent(int32_t x, int32_t y, uint32_t percent, uint32_t color = 0xFFFFFFFF, uint32_t player_color = 0x00000000);

        void drawTo(uint8_t* buffer, uint32_t stride, uint32_t height, int32_t x_offset = 0, int32_t y_offset = 0);

        void add(libsiedler2::baseArchivItem_Bitmap* bmp) {if (bmp) items.push_back(glBitmapItem(bmp));}
        void add(libsiedler2::baseArchivItem_Bitmap_Player* bmp) {if (bmp) items.push_back(glBitmapItem(bmp));}
        void addShadow(libsiedler2::baseArchivItem_Bitmap* bmp) {if (bmp) items.push_back(glBitmapItem(bmp, true));}

        static uint32_t nextPowerOfTwo(uint32_t k);
};

class glSmartTexturePackerNode;

class glSmartTexturePackerNode
{
        int32_t x, y;
        int32_t w, h;

        glSmartBitmap* bmp;

        glSmartTexturePackerNode* child[2];

    public:
        glSmartTexturePackerNode() : x(0), y(0), w(0), h(0), bmp(NULL) {child[0] = child[1] = NULL;}
        glSmartTexturePackerNode(int32_t w, int32_t h) : x(0), y(0), w(w), h(h), bmp(NULL) {child[0] = child[1] = NULL;}

        bool insert(glSmartBitmap* b, uint8_t* buffer, uint32_t gw, uint32_t gh, uint32_t reserve = 0);
        void destroy(uint32_t reserve = 0);
};

class glSmartTexturePacker
{
    private:
        std::vector<uint32_t> textures;
        std::vector<glSmartBitmap*> items;

        bool packHelper(std::vector<glSmartBitmap*> &list);
        static bool sortSmartBitmap(glSmartBitmap* a, glSmartBitmap* b);
    public:
        ~glSmartTexturePacker();

        bool pack();

        void add(glSmartBitmap& bmp) {items.push_back(&bmp);}
};

#endif

