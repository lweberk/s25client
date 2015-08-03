// $Id: BurnedWarehouse.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef BURNED_WAREHOUSE_H_
#define BURNED_WAREHOUSE_H_

#include "nodeObjs/noCoordBase.h"

/// Unsichtbares Objekt, welches die fliehenden Leute aus einem ehemaligen abgebrannten Lagerhaus/HQ spuckt
class BurnedWarehouse : public noCoordBase
{
        /// Spieler des ehemaligen Lagerhauses
        const uint8_t player;
        /// Aktuelle Rausgeh-Phase
        uint32_t go_out_phase;
        // Leute, die noch rauskommen müssen
        uint32_t people[30];

    public:

        BurnedWarehouse(const MapPoint pt, const uint8_t player, const uint32_t* people);
        BurnedWarehouse(SerializedGameData* sgd, const uint32_t obj_id);

        ~BurnedWarehouse();

        void Destroy(void);


        /// Serialisierungsfunktionen
    protected:  void Serialize_BurnedWarehouse(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_BurnedWarehouse(sgd); }

        GO_Type GetGOT() const { return GOT_BURNEDWAREHOUSE; }

        /// Benachrichtigen, wenn neuer GF erreicht wurde.
        void HandleEvent(const uint32_t id);

        void Draw(int32_t x, int32_t y) {}
};

#endif
