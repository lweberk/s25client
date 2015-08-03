// $Id: GameMessage.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef GAMEMESSAGE_H_INCLUDED
#define GAMEMESSAGE_H_INCLUDED

#pragma once

#include "Message.h"

class GameMessage : public Message
{
    public:
        /// Spieler-ID, von dem diese Nachricht stammt
        uint8_t player;
    public:
        GameMessage(const uint16_t id) : Message(id) {}
        /// Konstruktor von @p GameMessage.
        GameMessage(const uint16_t id, const uint8_t player)
            : Message(id), player(player)
        {
            PushUnsignedChar(player);
        }
        /// Konstruktor, um Message aus vorhandenem Datenblock heraus zu erstellen
        GameMessage(const uint32_t id, const uint8_t* const data, const uint32_t length)
            : Message(id, data, length), player(PopUnsignedChar())
        {
        }
        /// Destruktor von @p GameMessage.
        virtual ~GameMessage(void) {};

        /// Run Methode für GameMessages, wobei PlayerID ggf. schon in der Message festgemacht wurde
        virtual void Run(MessageInterface* callback) = 0;

        virtual void run(MessageInterface* callback, uint32_t id)
        {
            player = PopUnsignedChar();
            if(id != 0xFFFFFFFF)
                player = static_cast<uint8_t>(id);
            Run(callback);
        }

        /// Gibt Netto-Länge der Message zurück ohne zusätzliche Daten (Player usw)
        uint32_t GetNetLength() const { return GetLength() - 1; }

        static Message* create_game(uint16_t id);
        virtual Message* create(uint16_t id) const { return create_game(id); }
};

#endif // GAMEMESSAGE_H_INCLUDED
