#ifndef GAME_COMMANDS_H_
#define GAME_COMMANDS_H_

#include "Serializer.h"
#include "gameData/GameConsts.h"
#include "gameTypes/MapTypes.h"
#include "gameData/MilitaryConsts.h"
#include <vector>
#include <cassert>

class GameClient;
class GameServer;
class GameWorldGame;
class GameClientPlayer;

namespace gc
{

    enum Type
    {
        NOTSEND = 0,
        NOTHING,
        SETFLAG,
        DESTROYFLAG,
        BUILDROAD,
        DESTROYROAD,
        CHANGEDISTRIBUTION,
        CHANGEBUILDORDER,
        SETBUILDINGSITE,
        DESTROYBUILDING,
        CHANGETRANSPORT,
        CHANGEMILITARY,
        CHANGETOOLS,
        CALLGEOLOGIST,
        CALLSCOUT,
        ATTACK,
        SWITCHPLAYER,
        STOPGOLD,
        STOPPRODUCTION,
        CHANGEINVENTORYSETTING,
        CHANGEALLINVENTORYSETTINGS,
        CHANGERESERVE,
        SUGGESTPACT,
        ACCEPTPACT,
        CANCELPACT,
        CHANGESHIPYARDMODE,
        STARTEXPEDITION,
        STARTATTACKINGEXPEDITION,
        EXPEDITION_COMMAND,
        SEAATTACK,
        STARTEXPLORATIONEXPEDITION,
        TRADEOVERLAND,
        SURRENDER,
        CHEAT_ARMAGEDDON,
        DESTROYALL,
        UPGRADEROAD,
		SENDSOLDIERSHOME,
		ORDERNEWSOLDIERS,
		NOTIFYALLIESOFLOCATION
    };


    class GameCommand
    {
            /// Typ dieses Command
            const Type gst;
        public:
            virtual ~GameCommand(void) {}

            /// Erzeugt GameCommand anhand von Typen
            static GameCommand* CreateGameCommand(const Type gst, Serializer* ser);

            GameCommand(const Type gst) : gst(gst) {}

            /// Gibt den entsprechenden Typen zurück
            Type GetType() const { return gst; }
            /// Serialisiert dieses GameCommand
            virtual void Serialize(Serializer* ser) const = 0;

            /// Führt das GameCommand aus
            virtual void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid) = 0;
    };



/// Basisklasse für sämtliche GameCommands mit Koordinaten
    class Coords : public GameCommand
    {
        private: MapPoint PopMapPoint(Serializer* ser)
                 {
                     MapPoint pt;
                     pt.x = ser->PopUnsignedShort();
                     pt.y = ser->PopUnsignedShort();
                     return pt;
                 }
        protected:
            /// Koordinaten auf der Map, die dieses Command betreffen
            const MapPoint pt;
        public:
            Coords(const Type gst, const MapPoint pt)
                : GameCommand(gst), pt(pt) {}
            Coords(const Type gst, Serializer* ser)
                : GameCommand(gst), pt(PopMapPoint(ser)){}

            virtual void Serialize(Serializer* ser) const
            {
                ser->PushUnsignedShort(pt.x);
                ser->PushUnsignedShort(pt.y);
            }

    };

/// Flagge setzen
    class SetFlag : public Coords
    {
            friend class GameClient;
        public:
            SetFlag(const MapPoint pt)
                : Coords(SETFLAG, pt) {}
            SetFlag(Serializer* ser)
                : Coords(SETFLAG, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Flagge zerstören
    class DestroyFlag : public Coords
    {
            friend class GameClient;
        public:
            DestroyFlag(const MapPoint pt)
                : Coords(DESTROYFLAG, pt) {}
            DestroyFlag(Serializer* ser)
                : Coords(DESTROYFLAG, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Straße bauen
    class BuildRoad : public Coords
    {
            friend class GameClient;
            /// Boot-Straße oder nicht?
            const bool boat_road;
            /// Beschreibung der Straße mittels einem Array aus Richtungen
            std::vector<uint8_t> route;
        public:
            BuildRoad(const MapPoint pt, const bool boat_road, const std::vector<uint8_t>& route)
                : Coords(BUILDROAD, pt), boat_road(boat_road), route(route) {}
            BuildRoad(Serializer* ser)
                : Coords(BUILDROAD, ser),
                  boat_road(ser->PopBool()),
                  route(ser->PopUnsignedInt())
            {
                for(uint32_t i = 0; i < route.size(); ++i)
                    route[i] = ser->PopUnsignedChar();
            }

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);

                ser->PushBool(boat_road);
                ser->PushUnsignedInt(route.size());
                for(uint32_t i = 0; i < route.size(); ++i)
                    ser->PushUnsignedChar(route[i]);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Straße zerstören
    class DestroyRoad : public Coords
    {
            friend class GameClient;
            /// Richtung in der von der Flagge an x;y aus gesehen die Straße zerstört werden soll
            const uint8_t start_dir;
        public:
            DestroyRoad(const MapPoint pt, const uint8_t start_dir)
                : Coords(DESTROYROAD, pt), start_dir(start_dir) {}
            DestroyRoad(Serializer* ser)
                : Coords(DESTROYROAD, ser),
                  start_dir(ser->PopUnsignedChar()) {}

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);

                ser->PushUnsignedChar(start_dir);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Straße aufwerten
    class UpgradeRoad : public Coords
    {
            friend class GameClient;
            /// Richtung in der von der Flagge an x;y aus gesehen die Straße zerstört werden soll
            const uint8_t start_dir;
        public:
            UpgradeRoad(const MapPoint pt, const uint8_t start_dir)
                : Coords(UPGRADEROAD, pt), start_dir(start_dir) {}
            UpgradeRoad(Serializer* ser)
                : Coords(UPGRADEROAD, ser), start_dir(ser->PopUnsignedChar()) {}

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);
                ser->PushUnsignedChar(start_dir);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Warenverteilung ändern
    class ChangeDistribution : public GameCommand
    {
            friend class GameClient;
            /// Größe der Distributionsdaten
            static const uint32_t DATA_SIZE = 23;
            /// Daten der Distribution (einzelne Prozente der Waren in Gebäuden)
            std::vector<uint8_t> data;
        public:
            ChangeDistribution(const std::vector<uint8_t>& data)
                : GameCommand(CHANGEDISTRIBUTION), data(data) { assert(data.size() == DATA_SIZE); }
            ChangeDistribution(Serializer* ser)
                : GameCommand(CHANGEDISTRIBUTION), data(DATA_SIZE)
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    data[i] = ser->PopUnsignedChar();
            }

            virtual void Serialize(Serializer* ser) const
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    ser->PushUnsignedChar(data[i]);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Baureihenfolge ändern
    class ChangeBuildOrder : public GameCommand
    {
            friend class GameClient;
            /// Größe der BuildOrder-Daten
            static const uint32_t DATA_SIZE = 31;
            /// Ordnungs-Typ
            const uint8_t order_type;
            /// Daten der BuildOrder
            std::vector<uint8_t> data;
        public:
            ChangeBuildOrder(const uint8_t order_type, const std::vector<uint8_t>& data)
                : GameCommand(CHANGEBUILDORDER), order_type(order_type), data(data) { assert(data.size() == DATA_SIZE); }
            ChangeBuildOrder(Serializer* ser)
                : GameCommand(CHANGEBUILDORDER), order_type(ser->PopUnsignedChar()), data(DATA_SIZE)
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    data[i] = ser->PopUnsignedChar();
            }

            virtual void Serialize(Serializer* ser) const
            {
                ser->PushUnsignedChar(order_type);
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    ser->PushUnsignedChar(data[i]);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };


/// Baustelle setzen
    class SetBuildingSite : public Coords
    {
            friend class GameClient;
            /// Art des Gebäudes, was gebaut werden soll
            const BuildingType bt;
        public:
            SetBuildingSite(const MapPoint pt, const BuildingType bt)
                : Coords(SETBUILDINGSITE, pt), bt(bt) {}
            SetBuildingSite(Serializer* ser)
                : Coords(SETBUILDINGSITE, ser),
                  bt(BuildingType(ser->PopUnsignedChar())) {}

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);

                ser->PushUnsignedChar(static_cast<uint8_t>(bt));
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Gebäude zerstören
    class DestroyBuilding : public Coords
    {
            friend class GameClient;
        public:
            DestroyBuilding(const MapPoint pt)
                : Coords(DESTROYBUILDING, pt) {}
            DestroyBuilding(Serializer* ser)
                : Coords(DESTROYBUILDING, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Send all highest rank soldiers home (used by ai to upgrade troops instead of changing mil settings all the time)
    class SendSoldiersHome : public Coords
    {
            friend class GameClient;
        public:
            SendSoldiersHome(const MapPoint pt)
                : Coords(SENDSOLDIERSHOME, pt) {}
            SendSoldiersHome(Serializer* ser)
                : Coords(SENDSOLDIERSHOME, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// call for new min rank soldiers (used by ai to upgrade troops instead of changing mil settings all the time)
    class OrderNewSoldiers : public Coords
    {
            friend class GameClient;
        public:
            OrderNewSoldiers(const MapPoint pt)
                : Coords(ORDERNEWSOLDIERS, pt) {}
            OrderNewSoldiers(Serializer* ser)
                : Coords(ORDERNEWSOLDIERS, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };


/// Transportreihenfolge ändern
    class ChangeTransport : public GameCommand
    {
            friend class GameClient;
            /// Größe der Distributionsdaten
            static const uint32_t DATA_SIZE = 14;
            /// Daten der Distribution (einzelne Prozente der Waren in Gebäuden)
            std::vector<uint8_t> data;
        public:
            ChangeTransport(const std::vector<uint8_t>& data)
                : GameCommand(CHANGETRANSPORT), data(data) { assert(data.size() == DATA_SIZE); }
            ChangeTransport(Serializer* ser)
                : GameCommand(CHANGETRANSPORT), data(DATA_SIZE)
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    data[i] = ser->PopUnsignedChar();
            }

            virtual void Serialize(Serializer* ser) const
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    ser->PushUnsignedChar(data[i]);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Transportreihenfolge ändern
    class ChangeMilitary : public GameCommand
    {
            friend class GameClient;
            /// Größe der Distributionsdaten
            static const uint32_t DATA_SIZE = MILITARY_SETTINGS_COUNT;
            /// Daten der Distribution (einzelne Prozente der Waren in Gebäuden)
            std::vector<uint8_t> data;
        public:
            ChangeMilitary(const std::vector<uint8_t>& data)
                : GameCommand(CHANGEMILITARY), data(data) { assert(data.size() == DATA_SIZE); }
            ChangeMilitary(Serializer* ser)
                : GameCommand(CHANGEMILITARY), data(DATA_SIZE)
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    data[i] = ser->PopUnsignedChar();
            }

            virtual void Serialize(Serializer* ser) const
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    ser->PushUnsignedChar(data[i]);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Werkzeugeinstellungen ändern
    class ChangeTools : public GameCommand
    {
            friend class GameClient;
            /// Größe der Distributionsdaten
            static const uint32_t DATA_SIZE = 12;
            /// Daten der Distribution (einzelne Prozente der Waren in Gebäuden)
            std::vector<uint8_t> data;

            int8_t orders[TOOL_COUNT];
        public:
            ChangeTools(const std::vector<uint8_t>& data, int8_t* order_delta = 0)
                : GameCommand(CHANGETOOLS), data(data)
            {
                assert(data.size() == DATA_SIZE);

                if (order_delta != 0)
                {
                    for (uint32_t i = 0; i < TOOL_COUNT; ++i)
                        orders[i] = order_delta[i];
                }
                else
                {
                    for (uint32_t i = 0; i < TOOL_COUNT; ++i)
                        orders[i] = 0;
                }
            }

            ChangeTools(Serializer* ser)
                : GameCommand(CHANGETOOLS), data(DATA_SIZE)
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    data[i] = ser->PopUnsignedChar();

                for (uint32_t i = 0; i < TOOL_COUNT; ++i)
                    orders[i] = (int8_t)ser->PopSignedChar();
            }

            virtual void Serialize(Serializer* ser) const
            {
                for(uint32_t i = 0; i < DATA_SIZE; ++i)
                    ser->PushUnsignedChar(data[i]);

                for (uint32_t i = 0; i < TOOL_COUNT; ++i)
                    ser->PushSignedChar(orders[i]);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Geologen rufen
    class CallGeologist : public Coords
    {
            friend class GameClient;
        public:
            CallGeologist(const MapPoint pt)
                : Coords(CALLGEOLOGIST, pt) {}
            CallGeologist(Serializer* ser)
                : Coords(CALLGEOLOGIST, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Späher rufen
    class CallScout : public Coords
    {
        public:
            CallScout(const MapPoint pt)
                : Coords(CALLSCOUT, pt) {}
            CallScout(Serializer* ser)
                : Coords(CALLSCOUT, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Basisklasse für beide Angriffstypen
    class BaseAttack : public Coords
    {
        protected:
            friend class GameClient;
            /// Anzahl der Soldaten
            const uint32_t soldiers_count;
            /// Starke Soldaten oder schwache Soldaten?
            const bool strong_soldiers;

        public:
            BaseAttack(const Type gst, const MapPoint pt, const uint32_t soldiers_count, const bool strong_soldiers)
                : Coords(gst, pt), soldiers_count(soldiers_count), strong_soldiers(strong_soldiers) {}
            BaseAttack(const Type gst, Serializer* ser)
                : Coords(gst, ser),
                  soldiers_count(ser->PopUnsignedInt()), strong_soldiers(ser->PopBool()) {}

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);

                ser->PushUnsignedInt(soldiers_count);
                ser->PushBool(strong_soldiers);
            }

    };


/// Angriff starten
    class Attack : public BaseAttack
    {
        public:
            Attack(const MapPoint pt, const uint32_t soldiers_count, const bool strong_soldiers)
                : BaseAttack(ATTACK, pt, soldiers_count, strong_soldiers) {}
            Attack(Serializer* ser)
                : BaseAttack(ATTACK, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// See-Angriff starten
    class SeaAttack : public BaseAttack
    {
        public:
            SeaAttack(const MapPoint pt, const uint32_t soldiers_count, const bool strong_soldiers)
                : BaseAttack(SEAATTACK, pt, soldiers_count, strong_soldiers) {}
            SeaAttack(Serializer* ser)
                : BaseAttack(SEAATTACK, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Spielerwechsel
    class SwitchPlayer : public GameCommand
    {
            friend class GameClient;
            friend class GameServer;
            /// ID des Spielers, zu den hingewechselt werden soll
            const uint32_t new_player_id;

        public:
            SwitchPlayer(const uint8_t new_player_id)
                : GameCommand(SWITCHPLAYER), new_player_id(new_player_id) {}
            SwitchPlayer(Serializer* ser)
                : GameCommand(SWITCHPLAYER), new_player_id(ser->PopUnsignedChar()) {}

            virtual void Serialize(Serializer* ser) const
            {
                ser->PushUnsignedChar(new_player_id);
            }

            const uint32_t GetNewPlayerId() const { return new_player_id; }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Goldzufuhr in einem Gebäude stoppen/erlauben
    class StopGold : public Coords
    {
            friend class GameClient;
        public:
            StopGold(const MapPoint pt)
                : Coords(STOPGOLD, pt) {}
            StopGold(Serializer* ser)
                : Coords(STOPGOLD, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Produktivität in einem Gebäude deaktivieren/aktivieren
    class StopProduction : public Coords
    {
            friend class GameClient;
        public:
            StopProduction(const MapPoint pt)
                : Coords(STOPPRODUCTION, pt) {}
            StopProduction(Serializer* ser)
                : Coords(STOPPRODUCTION, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Produktivität in einem Gebäude deaktivieren/aktivieren
    class NotifyAlliesOfLocation : public Coords
    {
            friend class GameClient;
        public:
            NotifyAlliesOfLocation(const MapPoint pt)
                : Coords(NOTIFYALLIESOFLOCATION, pt) {}
            NotifyAlliesOfLocation(Serializer* ser)
                : Coords(NOTIFYALLIESOFLOCATION, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Einlagerungseinstellungen von einem Lagerhaus verändern
    class ChangeInventorySetting : public Coords
    {
            /// Kategorie (Waren, Menschen), Status (Einlagern/Auslagern), type (welche Ware, welcher Mensch)
            const uint8_t category, state, type;
        public:
            ChangeInventorySetting(const MapPoint pt, const uint8_t category,
                                   const uint8_t state, const uint8_t type)
                : Coords(CHANGEINVENTORYSETTING, pt), category(category), state(state), type(type) {}
            ChangeInventorySetting(Serializer* ser)
                : Coords(CHANGEINVENTORYSETTING, ser),
                  category(ser->PopUnsignedChar()),
                  state(ser->PopUnsignedChar()),
                  type(ser->PopUnsignedChar())
            {}

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);

                ser->PushUnsignedChar(category);
                ser->PushUnsignedChar(state);
                ser->PushUnsignedChar(type);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Alle Einlagerungseinstellungen (für alle Menschen oder Waren) von einem Lagerhaus verändern
    class ChangeAllInventorySettings : public Coords
    {
            friend class GameClient;
            /// Kategorie (Waren, Menschen), Status (Einlagern/Auslagern), type (welche Ware, welcher Mensch)
            const uint8_t category, state;
        public:
            ChangeAllInventorySettings(const MapPoint pt, const uint8_t category,
                                       const uint8_t state)
                : Coords(CHANGEALLINVENTORYSETTINGS, pt), category(category), state(state) {}
            ChangeAllInventorySettings(Serializer* ser)
                : Coords(CHANGEALLINVENTORYSETTINGS, ser),
                  category(ser->PopUnsignedChar()),
                  state(ser->PopUnsignedChar())
            {}

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);

                ser->PushUnsignedChar(category);
                ser->PushUnsignedChar(state);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Verändert die Reserve im HQ auf einen bestimmten Wert
    class ChangeReserve : public Coords
    {
            friend class GameClient;
            /// Rang des Soldaten, der verändert werden soll
            const uint8_t rank;
            /// Anzahl der Reserve für diesen Rang
            const uint8_t count;
        public:
            ChangeReserve(const MapPoint pt, const uint8_t rank, const uint8_t count)
                : Coords(CHANGERESERVE, pt), rank(rank), count(count) {}
            ChangeReserve(Serializer* ser)
                : Coords(CHANGERESERVE, ser),
                  rank(ser->PopUnsignedChar()),
                  count(ser->PopUnsignedChar())
            {}

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);

                ser->PushUnsignedChar(rank);
                ser->PushUnsignedChar(count);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Alle Fahnen zerstören
    class CheatArmageddon : public GameCommand
    {
            friend class GameClient;
        public:
            CheatArmageddon()
                : GameCommand(CHEAT_ARMAGEDDON) {}
            CheatArmageddon(Serializer* ser)
                : GameCommand(CHEAT_ARMAGEDDON) {}

            virtual void Serialize(Serializer* ser) const
            {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Aufgeben
    class Surrender : public GameCommand
    {
            friend class GameClient;
        public:
            Surrender()
                : GameCommand(SURRENDER) {}
            Surrender(Serializer* ser)
                : GameCommand(SURRENDER) {}

            virtual void Serialize(Serializer* ser) const
            {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Alle eigenen Fahnen zerstören
    class DestroyAll : public GameCommand
    {
            friend class GameClient;
        public:
            DestroyAll()
                : GameCommand(DESTROYALL) {}
            DestroyAll(Serializer* ser)
                : GameCommand(DESTROYALL) {}

            virtual void Serialize(Serializer* ser) const
            {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Unterbreitet anderen Spielern einen Bündnisvertrag
    class SuggestPact : public GameCommand
    {
            /// Spieler, dem das Angebot unterbreitet werden soll
            const uint8_t player;
            /// Art des Vertrages
            const PactType pt;
            /// Dauer des Vertrages
            const uint32_t duration;

        public:

            SuggestPact(const uint8_t player, const PactType pt, const uint32_t duration) : GameCommand(SUGGESTPACT),
                player(player), pt(pt), duration(duration) {}
            SuggestPact(Serializer* ser) : GameCommand(SUGGESTPACT),
                player(ser->PopUnsignedChar()), pt(PactType(ser->PopUnsignedChar())), duration(ser->PopUnsignedInt()) {}


            virtual void Serialize(Serializer* ser) const
            {
                ser->PushUnsignedChar(player);
                ser->PushUnsignedChar(static_cast<uint8_t>(pt));
                ser->PushUnsignedInt(duration);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };


/// Antwortet auf einen Bündnisvorschlag mit Annehmen oder Ablehnung
    class AcceptPact : public GameCommand
    {
            /// Vertrag angenommen oder abgelehnt?
            bool accepted;
            /// ID des Vertrages
            const uint32_t id;
            /// Art des Vertrages
            const PactType pt;
            /// Spieler, der das Angebot unterbreitet hat
            const uint8_t player;

        public:

            AcceptPact(const bool accepted, const uint32_t id, const PactType pt, const uint8_t player) : GameCommand(ACCEPTPACT),
                accepted(accepted), id(id), pt(pt), player(player) {}
            AcceptPact(Serializer* ser) : GameCommand(ACCEPTPACT),
                accepted(ser->PopBool()), id(ser->PopUnsignedInt()), pt(PactType(ser->PopUnsignedChar())), player(ser->PopUnsignedChar()) {}


            virtual void Serialize(Serializer* ser) const
            {
                ser->PushBool(accepted);
                ser->PushUnsignedInt(id);
                ser->PushUnsignedChar(static_cast<uint8_t>(pt));
                ser->PushUnsignedChar(player);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };


/// Bündnis abbrechen bzw. das Angebot zurücknehmen, falls dieses schon gestellt wurde
    class CancelPact : public GameCommand
    {
            /// Vertragsart
            const PactType pt;
            /// Anderen Spieler, den dies noch betrifft
            const uint8_t player;

        public:

            CancelPact(const PactType pt, const uint8_t player) : GameCommand(CANCELPACT),
                pt(pt), player(player) {}
            CancelPact(Serializer* ser) : GameCommand(CANCELPACT),
                pt(PactType(ser->PopUnsignedChar())), player(ser->PopUnsignedChar()) {}


            virtual void Serialize(Serializer* ser) const
            {
                ser->PushUnsignedChar(static_cast<uint8_t>(pt));
                ser->PushUnsignedChar(player);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Zwischen Boote und Schiffen beim Schiffsbauer hin- und herschalten
    class ChangeShipYardMode : public Coords
    {
        public:
            ChangeShipYardMode(const MapPoint pt)
                : Coords(CHANGESHIPYARDMODE, pt) {}
            ChangeShipYardMode(Serializer* ser)
                : Coords(CHANGESHIPYARDMODE, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Expedition starten
    class StartExpedition : public Coords
    {
            friend class GameClient;
        public:
            StartExpedition(const MapPoint pt)
                : Coords(STARTEXPEDITION, pt) {}
            StartExpedition(Serializer* ser)
                : Coords(STARTEXPEDITION, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Expedition starten
    class StartExplorationExpedition : public Coords
    {
            friend class GameClient;
        public:
            StartExplorationExpedition(const MapPoint pt)
                : Coords(STARTEXPLORATIONEXPEDITION, pt) {}
            StartExplorationExpedition(Serializer* ser)
                : Coords(STARTEXPLORATIONEXPEDITION, ser) {}

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };

/// Wartendes Schiff einer Expedition Befehle geben
    class ExpeditionCommand : public GameCommand
    {
        public:

            /// Aktion, die ausgeführt wird
            enum Action
            {
                FOUNDCOLONY = 0,
                CANCELEXPEDITION,
                NORTH,
                NORTHEAST,
                SOUTHEAST,
                SOUTH,
                SOUTHWEST,
                NORTHWEST
            };

            ExpeditionCommand(const Action action, const uint32_t ship_id)
                : GameCommand(EXPEDITION_COMMAND), action(action), ship_id(ship_id) {}

            ExpeditionCommand(Serializer* ser)
                : GameCommand(EXPEDITION_COMMAND),
                  action(Action(ser->PopUnsignedChar())),
                  ship_id(ser->PopUnsignedInt()) {}

            virtual void Serialize(Serializer* ser) const
            {
                ser->PushUnsignedChar(static_cast<uint8_t>(action));
                ser->PushUnsignedInt(ship_id);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);

        private:
            /// Die Aktion, die ausgeführt werden soll
            Action action;
            /// Schiff, welches dieses Command betrifft
            uint32_t ship_id;
    };


/// Send wares to another allied player via donkeys
    class TradeOverLand : public Coords
    {
            friend class GameClient;
            /// Type of Ware / Figure
            bool ware_figure;
            GoodType gt;
            Job job;
            /// Number of wares/figures we want to trade
            uint32_t count;

        public:
            TradeOverLand(const MapPoint pt, const bool ware_figure, const GoodType gt, const Job job, const uint32_t count)
                : Coords(TRADEOVERLAND, pt), ware_figure(ware_figure), gt(gt), job(job), count(count) {}
            TradeOverLand(Serializer* ser)
                : Coords(TRADEOVERLAND, ser),
                  ware_figure(ser->PopBool()),
                  gt( ware_figure ? GD_NOTHING : GoodType(ser->PopUnsignedChar())),
                  job( ware_figure ? Job(ser->PopUnsignedChar()) : JOB_NOTHING),
                  count(ser->PopUnsignedInt())
            {}

            virtual void Serialize(Serializer* ser) const
            {
                Coords::Serialize(ser);

                ser->PushBool(ware_figure);
                if(!ware_figure) ser->PushUnsignedChar(static_cast<uint8_t>(gt));
                else ser->PushUnsignedChar(static_cast<uint8_t>(job));
                ser->PushUnsignedInt(count);
            }

            /// Führt das GameCommand aus
            void Execute(GameWorldGame& gwg, GameClientPlayer& player, const uint8_t playerid);
    };


}

#endif



