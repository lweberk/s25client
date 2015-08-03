﻿// $Id: nofCarpenter.h 9357 2014-04-25 15:35:25Z FloSoft $
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

#ifndef NOF_CARPENTER_H_
#define NOF_CARPENTER_H_

#include "nofWorkman.h"

class nobUsualBuilding;

/// Klasse für den Schreiner
class nofCarpenter : public nofWorkman
{
        /// Zeichnet ihn beim Arbeiten
        void DrawWorking(int32_t x, int32_t y);
        /// Gibt die ID in JOBS.BOB zurück, wenn der Beruf Waren rausträgt (bzw rein)
        uint16_t GetCarryID() const { return 62; }
        /// Der Arbeiter erzeugt eine Ware
        GoodType ProduceWare();

    public:

        nofCarpenter(const MapPoint pt, const uint8_t player, nobUsual* workplace);
        nofCarpenter(SerializedGameData* sgd, const uint32_t obj_id);

        GO_Type GetGOT() const { return GOT_NOF_CARPENTER; }
};

#endif
