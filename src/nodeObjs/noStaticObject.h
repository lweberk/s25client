﻿// $Id: noStaticObject.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef NOSTATICOBJECT_H_INCLUDED
#define NOSTATICOBJECT_H_INCLUDED

#pragma once

#include "noCoordBase.h"

class noStaticObject : public noCoordBase
{
    public:
        noStaticObject(const MapPoint pt, uint16_t id, uint16_t file = 0xFFFF, uint8_t size = 0, NodalObjectType type = NOP_OBJECT);
        noStaticObject(SerializedGameData* sgd, const uint32_t obj_id);

        void Destroy() { Destroy_noStaticObject(); }

        /// gibt die Item-ID zurück (nr in der jeweiligen File)
        uint16_t GetItemID() const { return id; }
        /// gibt die Nr der File zurück)
        uint16_t GetItemFile() const { return file; }
        /// gibt die Größe des Objekts zurück.
        uint8_t GetSize(void) const { return size; }

        virtual BlockingManner GetBM() const { return BlockingManner(unsigned(BM_HUT) + size); }

        /// zeichnet das Objekt.
        void Draw(int32_t x, int32_t y);

        /// Serialisierungsfunktionen
    protected:  void Serialize_noStaticObject(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_noStaticObject(sgd); }

        GO_Type GetGOT() const { return GOT_STATICOBJECT; }

    protected:
        void Destroy_noStaticObject();

    protected:

        uint16_t id;
        uint16_t file;
        uint8_t size;
};

#endif // !NOSTATICOBJECT_H_INCLUDED
