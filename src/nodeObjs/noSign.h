// $Id: noSign.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef NOSIGN_H_INCLUDED
#define NOSIGN_H_INCLUDED

#include "noDisappearingEnvObject.h"
#include "gameData/GameConsts.h"
#include "EventManager.h"

/// Stellt ein Ressourcen-Schild dar
class noSign : public noDisappearingEnvObject
{
    public:
        /// Konstruktor von @p noSign.
        noSign(const MapPoint pt, const uint8_t type, const uint8_t quantity);
        noSign(SerializedGameData* sgd, const uint32_t obj_id);

        /// Aufräummethoden
    protected:  void Destroy_noSign();
    public:     void Destroy() { Destroy_noSign(); }
        /// Serialisierungsfunktionen
    protected:  void Serialize_noSign(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_noSign(sgd); }

        GO_Type GetGOT() const { return GOT_SIGN; }

        /// An x,y zeichnen.
        void Draw(int32_t x, int32_t y);

        void HandleEvent(const uint32_t id);

        uint8_t GetSignType() const { return type; }

    private:

        /// Typ der Ressource (0 = Erz, 1 = Gold, 2 = Kohle, 3 = Granit, 4 = Wasser, 5 = nix)
        const uint8_t type;
        /// Häufigkeit der Ressource
        const uint8_t quantity;
};

#endif // !NOSIGN_H_INCLUDED
