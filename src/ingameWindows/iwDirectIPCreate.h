// $Id: iwDirectIPCreate.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef iwDIRECTIPCREATE_H_INCLUDED
#define iwDIRECTIPCREATE_H_INCLUDED

#pragma once

#include "IngameWindow.h"
#include "LobbyInterface.h"

/// Struktur zur Weitergabe der Spiel-Eröffnungsdaten
struct CreateServerInfo
{
    uint8_t type;    ///< Typ des Servers.
    uint16_t port;   ///< Port des Servers
    std::string gamename;  ///< Name des Servers.
    std::string password;  ///< Passwort des Servers.
    bool ipv6;             ///< Soll IPv6 verwendet werden?
    bool use_upnp;
};

class iwDirectIPCreate : public IngameWindow, public LobbyInterface
{
    public:
        iwDirectIPCreate(uint32_t server_type);

        void LC_Status_Error(std::string error);

    protected:
        void Msg_EditChange(const uint32_t ctrl_id);
        void Msg_EditEnter(const uint32_t ctrl_id);
        void Msg_ButtonClick(const uint32_t ctrl_id);
        void Msg_OptionGroupChange(const uint32_t ctrl_id, const uint16_t selection);

    private:
        void SetText(const std::string& text, uint32_t color, bool button);

    private:
        uint32_t server_type;
};

#endif // !iwDIRECTIPCREATE_H_INCLUDED
