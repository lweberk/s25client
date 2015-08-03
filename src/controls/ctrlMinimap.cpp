﻿// $Id: ctrlMinimap.cpp 9357 2014-04-25 15:35:25Z FloSoft $
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
#include "ctrlMinimap.h"
#include "gameData/MinimapConsts.h"
#include "Minimap.h"

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
/**
 *
 *
 *  @author OLiver
 */
ctrlMinimap::ctrlMinimap( Window* parent,
                          const uint32_t id,
                          const uint16_t x,
                          const uint16_t y,
                          const uint16_t width,
                          const uint16_t height,
                          const uint16_t padding_x,
                          const uint16_t padding_y,
                          const uint16_t map_width,
                          const uint16_t map_height)
    : Window(x, y, id, parent, width, height), padding_x(padding_x), padding_y(padding_y), map_width(map_width), map_height(map_height)
{
    SetDisplaySize(width, height, map_width, map_height);
}

///////////////////////////////////////////////////////////////////////////////
/**
 *  Größe ändern
 *
 *  @author Divan
 */
void ctrlMinimap::Resize_(uint16_t width, uint16_t height)
{
    SetDisplaySize(width, height, map_width, map_height);
}

///////////////////////////////////////////////////////////////////////////////
/**
 *
 *
 *  @author OLiver
 */
void ctrlMinimap::SetDisplaySize(const uint16_t width, const uint16_t height, const uint16_t map_width, const uint16_t map_height)
{
    this->width = width;
    this->height = height;

    this->map_width = map_width;
    this->map_height = map_height;

    uint16_t scaled_map_width = static_cast<uint16_t>(map_width * MINIMAP_SCALE_X);
    double x_scale = double(scaled_map_width) / double(width - padding_x * 2);
    double y_scale = double(map_height) / double(height - padding_y * 2);

    bool scale_width = false;

    if(x_scale > y_scale)
        scale_width = false;
    else
        scale_width = true;

    assert(map_height != 0);
    assert(scaled_map_width != 0);

    if(scale_width)
    {
        height_show = height - padding_y * 2;
        width_show  = (scaled_map_width * height_show / map_height) & 0xFFFF; // to mask uint32_t to uint16_t (VS debugger crying)
    }
    else
    {
        width_show  = width - padding_x * 2;
        height_show = map_height * width_show / scaled_map_width;
    }
}

///////////////////////////////////////////////////////////////////////////////
/**
 *
 *
 *  @author OLiver
 */
void ctrlMinimap::DrawMap(Minimap& map)
{
    // Map ansich zeichnen
    map.Draw(GetX() + GetLeft(), GetY() + GetTop(), width_show, height_show);
}

///////////////////////////////////////////////////////////////////////////////
/**
 *
 *
 *  @author OLiver
 */
void ctrlMinimap::RemoveBoundingBox(const uint16_t width_min, const uint16_t height_min)
{
    width  = max<uint16_t>( width_show + padding_x * 2,  width_min);
    height = max<uint16_t>(height_show + padding_y * 2, height_min);
}
