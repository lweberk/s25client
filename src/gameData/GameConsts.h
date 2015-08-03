// $Id: GameConsts.h 9394 2014-05-04 12:39:31Z FloSoft $
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

#ifndef GAMECONSTS_H_
#define GAMECONSTS_H_

#include <cstdint>

/// Maximale Anzahl an Spielern
const uint32_t MAX_PLAYERS = 8;

#define NATIVE_NAT_COUNT 4

#include "mygettext.h"

#include "gameData/NationConsts.h"
#include "gameTypes/JobTypes.h"
#include "gameTypes/BuildingTypes.h"
#include "gameTypes/GoodTypes.h"

/// Team
enum Team
{
    TM_NOTEAM = 0,
    TM_RANDOMTEAM,
    TM_TEAM1,
    TM_TEAM2,
    TM_TEAM3,
    TM_TEAM4,
    TM_RANDOMTEAM2,
    TM_RANDOMTEAM3,
    TM_RANDOMTEAM4
};

/// Anzahl der Team-Optionen
const uint32_t TEAM_COUNT = 6; //teamrandom2,3,4 dont count

const BuildingQuality TERRAIN_BQ[] =
{
    BQ_DANGER,
    BQ_FLAG,
    BQ_NOTHING,
    BQ_CASTLE,
    BQ_MINE,
    BQ_MINE,
    BQ_MINE,
    BQ_MINE,
    BQ_CASTLE,
    BQ_CASTLE,
    BQ_CASTLE,
    BQ_CASTLE,
    BQ_CASTLE,
    BQ_CASTLE,
    BQ_NOTHING,
    BQ_DANGER
};

struct RoadWindowInfo
{
    bool flag;
    int32_t mx, my;
};

/// Tierarten
enum Species
{
    SPEC_POLARBEAR = 0,
    SPEC_RABBITWHITE,
    SPEC_RABBITGREY,
    SPEC_FOX,
    SPEC_STAG,
    SPEC_DEER,
    SPEC_DUCK,
    SPEC_SHEEP,
    SPEC_NOTHING
};

const uint32_t SPEC_COUNT = SPEC_NOTHING;

/// Informationen über die  einzelnen Tierarten
struct AnimalConst
{
    /// IDs in der map_lst, wo die Lauf-IDs von der jeweiligen Tierart beginnen
    uint16_t walking_id;
    /// IDs in der map_lst, wo die Schatten-IDs von der jeweiligen Tierart beginnen
    uint16_t shadow_id;
    /// IDs in der map_lst, wo die Totes-ID der jeweiligen Tierart liegt
    uint16_t dead_id;
    /// IDs in der map_lst, wo die Schatten-Totes-ID der jeweiligen Tierart liegt
    uint16_t shadow_dead_id;
    /// Anzahl Animationsschritte der einzelnen Tierarten
    uint16_t animation_steps;
    /// Schnelligkeit (Laufzeit in GF)
    uint16_t speed;
};

// 0 bedeutet --> kein Bild!

const AnimalConst ANIMALCONSTS[8] =
{
    {1600, 0, 1648, 1649, 8, 20}, // Polarbär
    {1700, 0, 1736, 1737, 6, 20}, // Hase hell
    {1740, 0, 1776, 1777, 6, 20}, // Hase dunkel
    {1800, 1840, 1836, 0, 6, 20}, // Fuchs
    {1850, 1900, 1898, 0, 8, 20}, // Hirsch
    {1910, 1960, 1958, 0, 8, 20}, // Reh
    {1970, 1976, 0, 0, 1, 50}, // Ente
    {2060, 0, 2072, 2073, 2, 16} // Schaf
};

const uint32_t ANIMAL_MAX_ANIMATION_STEPS = 8;

/// Verfügbare Statistikarten
enum StatisticType
{
    STAT_COUNTRY = 0,
    STAT_BUILDINGS,
    STAT_INHABITANTS,
    STAT_MERCHANDISE,
    STAT_MILITARY,
    STAT_GOLD,
    STAT_PRODUCTIVITY,
    STAT_VANQUISHED,
    STAT_TOURNAMENT
};

/// Anzahl Statistikarten
const uint32_t STAT_TYPE_COUNT = 9;

/// Anzahl Warenstatistikarten
const uint32_t STAT_MERCHANDISE_TYPE_COUNT = 14;

/// Statistikzeiträume
enum StatisticTime
{
    STAT_15M = 0,
    STAT_1H,
    STAT_4H,
    STAT_16H
};

/// Anzahl Statistikzeiträume
const uint32_t STAT_TIME_COUNT = 4;

/// Anzahl der Statistikschritte, die gespeichert werden
const uint32_t STAT_STEP_COUNT = 30;

/// Konvertierungstabelle von RttR-Nation-Indizes in Original-S2-Nation-Indizes
const uint8_t NATION_RTTR_TO_S2[4] =
{
    3,
    2,
    0,
    1
};
/// Konvertierungstabelle von Rohstoff-Indizes von den Bergwerken --> Map
const uint8_t RESOURCES_MINE_TO_MAP[5] = {3, 0, 1, 2, 4};

/// Geschwindigkeitsabstufungen - Längen der GFs in ms
const uint32_t SPEED_GF_LENGTHS[6] = {80, 60, 50, 40, 30, 1};

/// Macht ggf. aus den verschiedenen Schilden der Nationen jeweils immer das römische normale Schild für
/// die Warensysteme usw
inline GoodType ConvertShields(const GoodType& good)
{
    return (good == GD_SHIELDVIKINGS ||
            good == GD_SHIELDAFRICANS ||
            good == GD_SHIELDJAPANESE) ? GD_SHIELDROMANS : good;
}

/// Umgekehrte Konvertierung: Gibt den Schildtyp für jede Nation an
const GoodType SHIELD_TYPES[NAT_COUNT] =
{
    GD_SHIELDAFRICANS,
    GD_SHIELDJAPANESE,
    GD_SHIELDROMANS,
    GD_SHIELDVIKINGS,
    GD_SHIELDJAPANESE
};

/// Reichweite der Bergarbeiter
const uint32_t MINER_RADIUS = 2;

/// Vertragsypen
enum PactType
{
    TREATY_OF_ALLIANCE = 0,
    NON_AGGRESSION_PACT
};

/// Anzahl der unterschiedlichen Bündnisse
const uint32_t PACTS_COUNT = 2;

/// Namen der Verträge
const std::string PACT_NAMES[32] =
{
    gettext_noop("Treaty of alliance"),
    gettext_noop("Non-aggression pact")
};

/// Post-Nachrichten-Kategorien
enum PostMessageCategory
{
    PMC_MILITARY, // ImagePostMsgWithLocation
    PMC_GEOLOGIST, // PostMsgWithLocation
    PMC_GENERAL, // ImagePostMsgWithLocation
    PMC_SAVEWARNING, // PostMsg
    PMC_DIPLOMACY, // DiplomacyPostQuestion (man braucht vll noch verschiedene?)
    PMC_OTHER  // PostMsg
};

/// Post-Nachrichten-Typen (entspricht den Klassen in PostMsg.h)
enum PostMessageType
{
    PMT_NORMAL,               // PostMsg
    PMT_WITH_LOCATION,        // PostMsgWithLocation
    PMT_IMAGE_WITH_LOCATION,  // ImagePostMsgWithLocation
    PMT_DIPLOMACYQUESTION,             // DiplomacyPostQuestion
    PMT_DIPLOMACYINFO,            // DiplomacyPostInfo
    PMT_SHIP
};

/// Maximale Nachrichtenanzahl im Briefkasten
const uint32_t MAX_POST_MESSAGES = 20;

/// Konstante für die Pfadrichtung bei einer Schiffsverbindung
const uint8_t SHIP_DIR = 100;

/// Anzahl der Späher bei einer Erkundungs-Expedition
const uint32_t SCOUTS_EXPLORATION_EXPEDITION = 3;

/// Number of "classical" objectives in a friendly match
const uint32_t OBJECTIVES_COUNT = 3;
/// tournament modes
const uint32_t TOURNAMENT_MODES_COUNT = 5;
const uint32_t TOURNAMENT_MODES_DURATION[TOURNAMENT_MODES_COUNT] =
{
    30, 60, 90, 120, 240
};

#endif
