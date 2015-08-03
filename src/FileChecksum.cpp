// $Id: FileChecksum.cpp 9357 2014-04-25 15:35:25Z FloSoft $
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
#include "FileChecksum.h"
#include <cstdio>

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

uint32_t CalcChecksumOfFile(const char* const path)
{
    FILE* dat = fopen(path, "rb");
    if(!dat)
        return 0;

    fseek(dat, 0, SEEK_END);
    uint32_t length = (int32_t)ftell(dat);
    fseek(dat, 0, SEEK_SET);

    uint32_t checksum = 0;

    for(uint32_t i = 0; i < length; ++i)
        checksum += fgetc(dat);

    fclose(dat);

    return checksum;
}

uint32_t CalcChecksumOfBuffer(const uint8_t* buffer, uint32_t size)
{
    if(!buffer || size == 0)
        return 0;

    uint32_t checksum = 0;
    for(uint32_t i = 0; i < size; ++i)
    {
        //LOG.lprintf("%d - %d\n", i, checksum);
        checksum += (uint32_t)buffer[i];
    }
    return checksum;
}

