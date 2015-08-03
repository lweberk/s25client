﻿// Copyright (c) 2005 - 2015 Settlers Freaks (sf-team at siedler25.org)
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

#ifndef Rect_h__
#define Rect_h__

#include "Point.h"

typedef struct Rect
{
    uint16_t left, top, right, bottom;
    Rect(){}
    Rect(uint16_t left, uint16_t top, uint16_t width, uint16_t height): left(left), top(top), right(left + width), bottom(top + height){}
    Rect(Point<uint16_t> lt, Point<uint16_t> size): left(lt.x), top(lt.y), right(left + size.x), bottom(top + size.y){}
} Rect;

#endif // Rect_h__