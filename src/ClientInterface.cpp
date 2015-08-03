// $Id: ClientInterface.cpp 9357 2014-04-25 15:35:25Z FloSoft $
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
#include "ClientInterface.h"

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void ClientInterface::CI_NextConnectState(const ConnectState cs) {}
void ClientInterface::CI_Error(const ClientError ce) {}

void ClientInterface::CI_NewPlayer(const uint32_t player_id) {}
void ClientInterface::CI_PlayerLeft(const uint32_t player_id) {}

void ClientInterface::CI_GameStarted(GameWorldViewer* gwv) {}

void ClientInterface::CI_PSChanged(const uint32_t player_id, const PlayerState ps) {}
void ClientInterface::CI_NationChanged(const uint32_t player_id, const Nation nation) {}
void ClientInterface::CI_ColorChanged(const uint32_t player_id, const uint8_t color) {}
void ClientInterface::CI_TeamChanged(const uint32_t player_id, const uint8_t team) {}
void ClientInterface::CI_PingChanged(const uint32_t player_id, const uint16_t ping) {}
void ClientInterface::CI_ReadyChanged(const uint32_t player_id, const bool ready) {}
void ClientInterface::CI_PlayersSwapped(const uint32_t player1, const uint32_t player2) {}
void ClientInterface::CI_GGSChanged(const GlobalGameSettings& ggs) {}

void ClientInterface::CI_Chat(const uint32_t player_id, const ChatDestination cd, const std::string& msg) {}
void ClientInterface::CI_Countdown(int32_t countdown) {}
void ClientInterface::CI_CancelCountdown() {}

void ClientInterface::CI_NewPostMessage(const uint32_t postmessages_count) {}
void ClientInterface::CI_PostMessageDeleted(const uint32_t postmessages_count) {}

void ClientInterface::CI_Async(const std::string& checksums_list) {}
void ClientInterface::CI_ReplayAsync(const std::string& msg) {}
void ClientInterface::CI_ReplayEndReached(const std::string& msg) {}
void ClientInterface::CI_GamePaused() {}
void ClientInterface::CI_GameResumed() {}
void ClientInterface::CI_FlagDestroyed(const uint16_t x, const uint16_t y) {}

