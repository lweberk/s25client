// $Id: dskHostGame.h 9357 2014-04-25 15:35:25Z FloSoft $
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

#ifndef WP_HOSTGAME_H_
#define WP_HOSTGAME_H_

#include "Desktop.h"

#include "GameProtocol.h"
#include "GlobalGameSettings.h"

#include "LobbyInterface.h"
#include "ClientInterface.h"

#include "ogl/glArchivItem_Bitmap_Raw.h"

/// Desktop für das Hosten-eines-Spiels-Fenster
class dskHostGame :
    public Desktop,
    public ClientInterface,
    public LobbyInterface
{
    public:

        /// Map übergeben, damit die Kartenvorschau erstellt werden kann
        dskHostGame(bool single_player = false);

        /// Größe ändern-Reaktionen die nicht vom Skaling-Mechanismus erfasst werden.
        void Resize_(uint16_t width, uint16_t height);
    private:

        void TogglePlayerReady(uint8_t player, bool ready);
        // GGS von den Controls auslesen
        void UpdateGGS();
        /// Aktualisiert eine Spielerreihe (löscht Controls und legt neue an)
        void UpdatePlayerRow(const uint32_t row);

        /// Füllt die Felder einer Reihe aus
        void ChangeTeam(const uint32_t i, const uint8_t nr);
        void ChangeReady(const uint32_t i, const bool ready);
        void ChangeNation(const uint32_t i, const Nation nation);
        void ChangePing(const uint32_t i);
        void ChangeColor(const uint32_t i, const uint8_t color);

        void Msg_PaintBefore();
        void Msg_Group_ButtonClick(const uint32_t group_id, const uint32_t ctrl_id);
        void Msg_Group_CheckboxChange(const uint32_t group_id, const uint32_t ctrl_id, const bool checked);
        void Msg_Group_ComboSelectItem(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        void Msg_ButtonClick(const uint32_t ctrl_id);
        void Msg_EditEnter(const uint32_t ctrl_id);
        void Msg_MsgBoxResult(const uint32_t msgbox_id, const MsgboxResult mbr);
        void Msg_ComboSelectItem(const uint32_t ctrl_id, const uint16_t selection);
        void Msg_CheckboxChange(const uint32_t ctrl_id, const bool checked);

        void LC_RankingInfo(const LobbyPlayerInfo& player);

        void CI_Error(const ClientError ce);

        void CI_NewPlayer(const uint32_t player_id);
        void CI_PlayerLeft(const uint32_t player_id);

        void CI_GameStarted(GameWorldViewer* gwv);

        void CI_PSChanged(const uint32_t player_id, const PlayerState ps);
        void CI_NationChanged(const uint32_t player_id, const Nation nation);
        void CI_TeamChanged(const uint32_t player_id, const uint8_t team);
        void CI_PingChanged(const uint32_t player_id, const uint16_t ping);
        void CI_ColorChanged(const uint32_t player_id, const uint8_t color);
        void CI_ReadyChanged(const uint32_t player_id, const bool ready);
        void CI_PlayersSwapped(const uint32_t player1, const uint32_t player2);
        void CI_GGSChanged(const GlobalGameSettings& ggs);

        void CI_Chat(const uint32_t player_id, const ChatDestination cd, const std::string& msg);
        void CI_Countdown(int32_t countdown);
        void CI_CancelCountdown();

        void LC_Status_Error(const std::string& error);

    private:
        int32_t temppunkte; // TODO - wegmachen und durch korrekte punkte ersetzen!
        glArchivItem_Bitmap_Raw preview;
        GlobalGameSettings ggs;
        bool has_countdown;
        bool single_player;
};


#endif
