// $Id: GamePlayerInfo.h 9357 2014-04-25 15:35:25Z FloSoft $
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

#ifndef GAMEPLAYERINFO_H_INCLUDED
#define GAMEPLAYERINFO_H_INCLUDED

#include <cstdint>

#include "GameProtocol.h"
#include "Socket.h"
#include "gameData/GameConsts.h"

class Serializer;

enum PlayerState
{
    PS_FREE = 0,
    PS_RESERVED,
    PS_OCCUPIED,
    PS_LOCKED,
    PS_KI
};

namespace AI
{
    enum Level
    {
        EASY = 0,
        MEDIUM,
        HARD
    };

    enum Type
    {
        DUMMY = 0,
        DEFAULT
    };

    struct Info
    {
        Type type;
        Level level;
        Info(Type t = DUMMY, Level l = EASY) : type(t), level(l) { }
    };
}



class GamePlayerInfo
{
    public:
        GamePlayerInfo(const uint32_t playerid);
        /// Deserialisierungskonstruktor
        GamePlayerInfo(const uint32_t playerid, Serializer* ser);

        virtual ~GamePlayerInfo();

        void clear();

        /// Spielerplatz belegt?
        bool isValid() const { return (ps == PS_RESERVED || ps == PS_OCCUPIED); }

        /// Ist Spieler besiegt?
        bool isDefeated() const { return defeated; }

        /// serialisiert die Daten.
        void serialize(Serializer* ser) const;

        uint32_t getPlayerID() const { return playerid; }

    protected:
        /// Wechselt Spieler
        void SwapPlayer(GamePlayerInfo& two);

    protected:
        /// Player-ID
        uint32_t playerid;
        /// Besiegt?
        bool defeated;

    public:
        /// Spielertyp (Mensch, KI oder geschlossen..?)
        PlayerState ps;
        /// Wenn KI, was für eine?
        AI::Info aiInfo;

        /// Spielername
        std::string name;
        /// ehemaliger Spielername bei einem geladenen Spiel
        std::string origin_name;

        bool is_host;

        Nation nation;
        Team team;
        uint8_t color;

        uint32_t ping;
        uint32_t rating;

        int32_t checksum;
        uint32_t obj_cnt;
        uint32_t obj_id_cnt;
        bool ready;
};

#endif // GAMEPLAYERINFO_H_INCLUDED
