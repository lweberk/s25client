﻿// $Id: nofDefender.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef NOF_DEFENDER_H_
#define NOF_DEFENDER_H_

#include "nofActiveSoldier.h"

class nofAttacker;
class nofPassiveSoldier;

/// Verteidiger, der rauskommt, wenn ein Angreifer an die Flagge kommt
class nofDefender : public nofActiveSoldier
{
        // Unser Feind-Freund ;)
        friend class nofAttacker;

    private:

        /// angreifender Soldat an der Flagge
        nofAttacker* attacker;

    private:

        /// wenn man gelaufen ist
        void Walked();
        /// Sagt den verschiedenen Zielen Bescheid, dass wir doch nicht mehr kommen können
        void InformTargetsAboutCancelling();

        /// The derived classes regain control after a fight of nofActiveSoldier
        void FreeFightEnded();

    public:

        nofDefender(const MapPoint pt, const unsigned char player, nobBaseMilitary* const building,
                    const unsigned char rank, nofAttacker* const attacker);
        nofDefender(nofPassiveSoldier* other, nofAttacker* const attacker);
        nofDefender(SerializedGameData* sgd, const unsigned obj_id);

        /// Aufräummethoden
    protected:  void Destroy_nofDefender() { Destroy_nofActiveSoldier(); }
    public:     void Destroy() { Destroy_nofDefender(); }

        /// Serialisierungsfunktionen
    protected:  void Serialize_nofDefender(SerializedGameData* sgd) const;
    public:     void Serialize(SerializedGameData* sgd) const { Serialize_nofDefender(sgd); }

        GO_Type GetGOT() const { return GOT_NOF_DEFENDER; }

        /// Der Verteidiger geht gerade rein und es kommt ein neuer Angreifer an die Flagge, hiermit wird der Ver-
        /// teidiger darüber informiert, damit er dann gleich wieder umdrehen kann
        void NewAttacker(nofAttacker* attacker) { this->attacker = attacker; }
        /// Der Angreifer konnte nicht mehr an die Flagge kommen
        void AttackerArrested();

        /// Wenn ein Heimat-Militärgebäude bei Missionseinsätzen zerstört wurde
        void HomeDestroyed();
        /// Wenn er noch in der Warteschleife vom Ausgangsgebäude hängt und dieses zerstört wurde
        void HomeDestroyedAtBegin();
        /// Wenn ein Kampf gewonnen wurde
        void WonFighting();
        /// Wenn ein Kampf verloren wurde (Tod)
        void LostFighting();

        /// Is the defender waiting at the flag for an attacker?
        bool IsWaitingAtFlag() const
        { return (state == STATE_DEFENDING_WAITING); }
        bool IsFightingAtFlag() const {return (state == STATE_FIGHTING);}
        /// Informs the defender that a fight between him and an attacker has started
        void FightStarted()
        { state = STATE_FIGHTING; }


};


#endif // !NOF_DEFENDER_H_
