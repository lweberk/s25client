// $Id: CollisionDetection.cpp 9357 2014-04-25 15:35:25Z FloSoft $
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

///////////////////////////////////////////////////////////////////////////////
// Header
#include "defines.h"
#include "CollisionDetection.h"
#include "Rect.h"
#include <cstdlib>
#include <cmath>

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////

bool Coll(const int32_t x, const int32_t y, const Rect& rect)
{
    return ( x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom );
}

bool Coll(const int32_t x, const int32_t y, const int32_t rx, const int32_t ry, const int32_t rwidth, const int32_t rheight)
{
    return ( x >= rx && x < (rx + rwidth) && y >= ry && y < (ry + rheight));
}


bool Coll(const int32_t left1, const int32_t right1, const int32_t left2, const int32_t right2)
{
    return( (left1 >= left2 && left1 <= right2) || (right1 >= left2 && right1 <= right2) || (left2 >= left1 && left2 <= right1) || (right2 >= left1 && right2 <= right1) );
}


bool CollEdges(const Rect& rect1, const Rect& rect2)
{
    return ( Coll(rect1.left, rect1.top, rect2) || Coll(rect1.right, rect1.top, rect2) ||
             Coll(rect1.left, rect1.bottom, rect2) || Coll(rect1.right, rect1.bottom, rect2) ||
             Coll(rect2.left, rect2.top, rect1) || Coll(rect2.right, rect2.top, rect1) ||
             Coll(rect2.left, rect2.bottom, rect1) || Coll(rect2.right, rect2.bottom, rect1) );
}



bool Coll(const Rect& rect1, const Rect& rect2)
{
    // Radius berechnen
    int32_t Radius1X = (rect1.right - rect1.left) / 2;
    int32_t Radius1Y = (rect1.bottom - rect1.top) / 2;

    int32_t Radius2X = (rect2.right - rect2.left) / 2;
    int32_t Radius2Y = (rect2.bottom - rect2.top) / 2;

    // die Mitte der Bounding Box berechnen
    int32_t Center1X = rect1.left + Radius1X;
    int32_t Center1Y = rect1.top + Radius1Y;

    int32_t Center2X = rect2.left + Radius2X;
    int32_t Center2Y = rect2.top + Radius2Y;

    // Abstand berechnen
    int32_t OffsetX = std::abs(Center1X - Center2X);
    int32_t OffsetY = std::abs(Center1Y - Center2Y);

    return CollEdges(rect1, rect2) || (OffsetX < Radius1X + Radius2X && OffsetY < Radius1Y + Radius2Y);
}


