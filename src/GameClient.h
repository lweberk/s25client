// $Id: GameClient.h 9540 2014-12-14 11:32:47Z marcus $
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
#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include "Singleton.h"
#include "Socket.h"
#include "BinaryFile.h"

#include "GameMessageInterface.h"

#include "GamePlayerList.h"

#include "EventManager.h"
#include "GameSavegame.h"
#include "GameReplay.h"
#include "GameWorld.h"
#include "GlobalGameSettings.h"
#include "ai/AIEventManager.h"

class Window;
class GameClientPlayer;
class WorldManager;
class ClientInterface;
class GameMessage;
class AIBase;

namespace gc { class GameCommand; }

class GameClient : public Singleton<GameClient>, public GameMessageInterface
{
    public:
        enum ClientState
        {
            CS_STOPPED = 0,
            CS_CONNECT,
            CS_CONFIG,
            CS_GAME
        };

        GameClient(void);
        ~GameClient(void);

        void SetInterface(ClientInterface* ci) { this->ci = ci; }
        bool IsHost() const { return clientconfig.host; }
        bool IsSavegame() const { return mapinfo.map_type == MAPTYPE_SAVEGAME; }
        std::string GetGameName() const { return clientconfig.gamename; }

        inline uint8_t GetPlayerID() const { return playerid; }
        inline uint32_t GetPlayerCount() const { return players.getCount(); }
        /// Liefert einen Player zurück
        inline GameClientPlayer* GetPlayer(const uint32_t id) { return players.getElement(id); }
        inline GameClientPlayer* GetLocalPlayer(void) { return GetPlayer(playerid); }
        /// Erzeugt einen KI-Player, der mit den Daten vom GameClient gefüttert werden muss (zusätzlich noch mit den GameServer)
        AIBase* CreateAIPlayer(const uint32_t playerid);

        /// Gibt GGS zurück
        const GlobalGameSettings& GetGGS() const { return ggs; }
        void LoadGGS();

        bool Connect(const std::string& server, const std::string& password, uint8_t servertyp, uint16_t port, bool host, bool use_ipv6);
        void Run();
        void Stop();

        // Gibt GameWorldViewer zurück (VORLÄUFIG, soll später verschwinden!!)
        GameWorldViewer* QueryGameWorldViewer() const { return static_cast<GameWorldViewer*>(gw); }
        /// Gibt Map-Titel zurück
        const std::string& GetMapTitle() const { return mapinfo.title; }
        /// Gibt Pfad zu der Map zurück
        const std::string& GetMapPath() const  { return clientconfig.mapfilepath; }
        /// Gibt Map-Typ zurück
        const MapType GetMapType() const { return mapinfo.map_type; }

        // Initialisiert und startet das Spiel
        void StartGame(const uint32_t random_init);
        /// Wird aufgerufen, wenn das GUI fertig mit Laden ist und es losgehen kann
        void RealStart();

        /// Beendet das Spiel, zerstört die Spielstrukturen
        void ExitGame();

        ClientState GetState() const { return state; }
        inline uint32_t GetGFNumber() const { return framesinfo.nr; }
        inline uint32_t GetGFLength() const { return framesinfo.gf_length; }
        inline uint32_t GetNWFLength() const { return framesinfo.nwf_length; }
        inline uint32_t GetFrameTime() const { return framesinfo.frame_time; }
        uint32_t GetGlobalAnimation(const uint16_t max, const uint8_t factor_numerator, const uint8_t factor_denumerator, const uint32_t offset);
        uint32_t Interpolate(uint32_t max_val, EventManager::EventPointer ev);
        int32_t Interpolate(int32_t x1, int32_t x2, EventManager::EventPointer ev);
        /// Gibt Geschwindigkeits-Faktor zurück

        /// Fügt ein GameCommand für den Spieler hinzu und gibt bei Erfolg true zurück, ansonstn false (in der Pause oder wenn Spieler besiegt ist)
        bool AddGC(gc::GameCommand* gc);

        void Command_SetFlag2(const MapPoint pt, uint8_t player);
        void Command_Chat(const std::string& text, const ChatDestination cd );
        void Command_ToggleNation();
        void Command_ToggleTeam(Team newteam);
        void Command_ToggleColor();
        void Command_ToggleReady();

        void IncreaseSpeed();

        /// Lädt ein Replay und startet dementsprechend das Spiel (0 = alles OK, alles andere entsprechende Fehler-ID!)
        uint32_t StartReplay(const std::string& path, GameWorldViewer*& gwv);
        /// Replay-Geschwindigkeit erhöhen/verringern
        void IncreaseReplaySpeed();
        void DecreaseReplaySpeed();
        void SetReplayPause(bool pause);
        void ToggleReplayPause() { SetReplayPause(!framesinfo.pause); }
        /// Schaltet FoW im Replaymodus ein/aus
        void ToggleReplayFOW() { replayinfo.all_visible = !replayinfo.all_visible; }
        /// Prüft, ob FoW im Replaymodus ausgeschalten ist
        bool IsReplayFOWDisabled() const { return replayinfo.all_visible; }
        /// Gibt Replay-Ende (GF) zurück
        uint32_t GetLastReplayGF() const { return replayinfo.replay.last_gf; }
        /// Wandelt eine GF-Angabe in eine Zeitangabe um (HH:MM:SS oder MM:SS wenn Stunden = 0)
        std::string FormatGFTime(const uint32_t gf) const;

        /// Gibt Replay-Dateiname zurück
        const std::string& GetReplayFileName() const { return replayinfo.filename; }
        /// Wird ein Replay abgespielt?
        bool IsReplayModeOn() const { return replay_mode; }

        const Replay GetReplay() const { return replayinfo.replay; }

        /// Is tournament mode activated (0 if not)? Returns the durations of the tournament mode in gf otherwise
        uint32_t GetTournamentModeDuration() const;

        void SkipGF(uint32_t gf);

        /// Wechselt den aktuellen Spieler (nur zu Debugzwecken !!)
        void ChangePlayer(const uint8_t old_id, const uint8_t new_id);

        /// Wechselt den aktuellen Spieler im Replaymodus
        void ChangeReplayPlayer(const uint32_t new_id);
        /// Laggt ein bestimmter Spieler gerade?
        bool IsLagging(const uint32_t id) { return GetPlayer(id)->is_lagging; }
        /// Spiel pausiert?
        bool IsPaused() const { return framesinfo.pause; }
        /// Schreibt Header der Save-Datei
        uint32_t WriteSaveHeader(const std::string& filename);
        /// Visuelle Einstellungen aus den richtigen ableiten
        void GetVisualSettings();

        /// Schreibt ggf. Pathfinding-Results in das Replay, falls erforderlich
        void AddPathfindingResult(const uint8_t dir, const uint32_t* const length, const MapPoint* const next_harbor);
        /// Gibt zurück, ob Pathfinding-Results zur Verfügung stehen
        bool ArePathfindingResultsAvailable() const;
        /// Gibt Pathfinding-Results zurück aus einem Replay
        bool ReadPathfindingResult( uint8_t* dir, uint32_t* length, MapPoint* next_harbor);

        void SystemChat(std::string text);
        
        void ToggleHumanAIPlayer();
    private:
        /// Versucht einen neuen GameFrame auszuführen, falls die Zeit dafür gekommen ist
        void ExecuteGameFrame(const bool skipping = false);
        void ExecuteGameFrame_Replay();
        void ExecuteGameFrame_Game();
        /// Filtert aus einem Network-Command-Paket alle Commands aus und führt sie aus, falls ein Spielerwechsel-Command
        /// dabei ist, füllt er die übergebenen IDs entsprechend aus
        void ExecuteAllGCs(const GameMessage_GameCommand& gcs,  uint8_t* player_switch_old_id, uint8_t* player_switch_new_id);
        /// Sendet ein NC-Paket ohne Befehle
        void SendNothingNC(int32_t checksum = -1);
        /// Findet heraus, ob ein Spieler laggt und setzt bei diesen Spieler den entsprechenden flag
        bool IsPlayerLagging();

        /// Führt notwendige Dinge für nächsten GF aus
        void NextGF();

        /// Führt für alle Spieler einen Statistikschritt aus, wenn die Zeit es verlangt
        void StatisticStep();

        //  Netzwerknachrichten
        virtual void OnNMSDeadMsg(uint32_t id);

        virtual void OnNMSPing(const GameMessage_Ping& msg);

        virtual void OnNMSServerTypeOK(const GameMessage_Server_TypeOK& msg);
        virtual void OnNMSServerPassword(const GameMessage_Server_Password& msg);
        virtual void OnNMSServerName(const GameMessage_Server_Name& msg);
        virtual void OnNMSServerStart(const GameMessage_Server_Start& msg);
        virtual void OnNMSServerChat(const GameMessage_Server_Chat& msg);
        virtual void OnNMSServerAsync(const GameMessage_Server_Async& msg);
        virtual void OnNMSServerCountdown(const GameMessage_Server_Countdown& msg);
        virtual void OnNMSServerCancelCountdown(const GameMessage_Server_CancelCountdown& msg);

        virtual void OnNMSPlayerId(const GameMessage_Player_Id& msg);
        virtual void OnNMSPlayerList(const GameMessage_Player_List& msg);
        virtual void OnNMSPlayerToggleState(const GameMessage_Player_Toggle_State& msg);
        virtual void OnNMSPlayerToggleNation(const GameMessage_Player_Toggle_Nation& msg);
        virtual void OnNMSPlayerToggleTeam(const GameMessage_Player_Toggle_Team& msg);
        virtual void OnNMSPlayerToggleColor(const GameMessage_Player_Toggle_Color& msg);
        virtual void OnNMSPlayerKicked(const GameMessage_Player_Kicked& msg);
        virtual void OnNMSPlayerPing(const GameMessage_Player_Ping& msg);
        virtual void OnNMSPlayerNew(const GameMessage_Player_New& msg);
        virtual void OnNMSPlayerReady(const GameMessage_Player_Ready& msg);
        virtual void OnNMSPlayerSwap(const GameMessage_Player_Swap& msg);

        void OnNMSMapInfo(const GameMessage_Map_Info& msg);
        void OnNMSMapData(const GameMessage_Map_Data& msg);
        void OnNMSMapChecksumOK(const GameMessage_Map_ChecksumOK& msg);

        virtual void OnNMSPause(const GameMessage_Pause& msg);
        virtual void OnNMSServerDone(const GameMessage_Server_NWFDone& msg);
        virtual void OnNMSGameCommand(const GameMessage_GameCommand& msg);
        virtual void OnNMSServerSpeed(const GameMessage_Server_Speed& msg);

        void OnNMSGGSChange(const GameMessage_GGSChange& msg);

        void OnNMSGetAsyncLog(const GameMessage_GetAsyncLog& msg);

        /// Wird aufgerufen, wenn der Server gegangen ist (Verbindung verloren, ungültige Nachricht etc.)
        void ServerLost();

        // Replaymethoden

        /// Schreibt den Header der Replaydatei
        void WriteReplayHeader(const uint32_t random_init);

// Post-Sachen
    public:

        void SendPostMessage(PostMsg* msg);
        const std::list<PostMsg*>& GetPostMessages() { return postMessages; }
        void DeletePostMessage(PostMsg* msg);

        void SendAIEvent(AIEvent::Base* ev, uint32_t receiver);

    private:
        std::list<PostMsg*> postMessages;

    public:
        /// Virtuelle Werte der Einstellungsfenster, die aber noch nicht wirksam sind, nur um die Verzögerungen zu
        /// verstecken
        struct VisualSettings
        {
            /// Verteilung
            std::vector<uint8_t> distribution;
            /// Art der Reihenfolge (0 = nach Auftraggebung, ansonsten nach build_order)
            uint8_t order_type;
            /// Baureihenfolge
            std::vector<uint8_t> build_order;
            /// Transport-Reihenfolge
            std::vector<uint8_t> transport_order;
            /// Militäreinstellungen (die vom Militärmenü)
            std::vector<uint8_t> military_settings;
            /// Werkzeugeinstellungen (in der Reihenfolge wie im Fenster!)
            std::vector<uint8_t> tools_settings;

            VisualSettings() : distribution(23), build_order(31), transport_order(14), military_settings(MILITARY_SETTINGS_COUNT), tools_settings(12)
            {}

        } visual_settings, default_settings;
		/// skip ahead how many gf?
		uint32_t skiptogf;
    private:
        /// Spielwelt
        GameWorld* gw;
        /// EventManager
        EventManager* em;
        /// Spieler
        GameClientPlayerList players;
        /// Spieler-ID dieses Clients
        uint8_t playerid;
        /// Globale Spieleinstellungen
        GlobalGameSettings ggs;

        MessageQueue recv_queue, send_queue;
        Socket socket;
        // Was soll das sein? oO
        uint32_t temp_ul;
        uint32_t temp_ui;

        ClientState state;

        class ClientConfig
        {
            public:
                ClientConfig() { Clear(); }
                void Clear();

                std::string server;
                std::string gamename;
                std::string password;
                std::string mapfile;
                std::string mapfilepath;
                uint8_t servertyp;
                uint16_t port;
                bool host;
        } clientconfig;

        class MapInfo
        {
            public:
                MapInfo() { Clear(); }
                void Clear();

                MapType map_type;
                uint32_t partcount;
                uint32_t ziplength;
                uint32_t length;
                uint32_t checksum;
                std::string title;
                uint8_t* zipdata;
                Savegame savegame;
        } mapinfo;

        class FramesInfo
        {
            public:
                FramesInfo() { Clear(); }
                void Clear();

                /// Aktueller GameFrame (der wievielte seit Beginn)
                uint32_t nr;
                uint32_t nr_srv;
                /// Länge der GameFrames in ms (= Geschwindigkeit des Spiels)
                uint32_t gf_length;
                uint32_t gf_length_new;
                /// Länge der Network-Frames in gf(!)
                uint32_t nwf_length;

                /// Zeit in ms seit dem letzten Frame
                uint32_t frame_time;

                uint32_t lasttime;
                uint32_t lastmsgtime;
                uint32_t pausetime;

                bool pause;
				uint32_t pause_gf;
        } framesinfo;

        class RandCheckInfo
        {
            public:
                RandCheckInfo() { Clear(); }
                void Clear();

                int32_t rand;
        } randcheckinfo;


        ClientInterface* ci;
        
        AIBase *human_ai;

        /// GameCommands, die vom Client noch an den Server gesendet werden müssen
        std::vector<gc::GameCommand*> gcs;

        struct ReplayInfo
        {
            public:
                ReplayInfo() { Clear(); }
                void Clear();

                /// Replaydatei
                Replay replay;
                /// Replay asynchron (Meldung nur einmal ausgeben!)
                int32_t async;
                bool end;
                // Nächster Replay-Command-Zeitpunkt (in GF)
                uint32_t next_gf;
                /// Replay-Dateiname
                std::string filename;
                /// Alles sichtbar (FoW deaktiviert)
                bool all_visible;
        } replayinfo;

        /// Replaymodus an oder aus?
        bool replay_mode;
		

        /// Spiel-Log für Asyncs
        FILE* game_log;
};

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#define GAMECLIENT GameClient::inst()

#endif
