﻿// $Id: BuildingConsts.h 9504 2014-11-29 10:47:38Z marcus $
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

#ifndef BUILD_COSTS_H_
#define BUILD_COSTS_H_

#include "gameData/GameConsts.h"
#include "gameTypes/BuildingTypes.h"

// Konstanten für die Baukosten der Gebäude von allen 4 Völkern
const BuildingCost BUILDING_COSTS[NAT_COUNT][40] =
{
	// Nubier
	{
		{0, 0}, {2, 0}, {2, 3}, {0, 0}, {3, 5}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {4, 7},
		{4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {0, 0}, {4, 2}, {2, 0}, {2, 0}, {2, 0},
		{2, 0}, {2, 2}, {2, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {4, 3}, {3, 3}, {4, 3},
		{0, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 0}, {2, 3}, {3, 3}, {3, 3}, {4, 6}
	},
		// Japaner
	{
		{0, 0}, {2, 0}, {2, 3}, {0, 0}, {3, 5}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {4, 7},
		{4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {0, 0}, {4, 2}, {2, 0}, {2, 0}, {2, 0},
		{2, 0}, {2, 2}, {2, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {4, 3}, {3, 3}, {4, 3},
		{0, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 0}, {2, 3}, {3, 3}, {3, 3}, {4, 6}
	},
		// Römer
	{
		{0, 0}, {2, 0}, {2, 3}, {0, 0}, {3, 5}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {4, 7},
		{4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {0, 0}, {4, 2}, {2, 0}, {2, 0}, {2, 0},
		{2, 0}, {2, 2}, {2, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {4, 3}, {3, 3}, {4, 3},
		{0, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 0}, {2, 3}, {3, 3}, {3, 3}, {4, 6}
	},
		// Wikinger
	{
		{0, 0}, {2, 0}, {2, 3}, {0, 0}, {3, 5}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {4, 7},
		{4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {0, 0}, {4, 2}, {2, 0}, {2, 0}, {2, 0},
		{2, 0}, {2, 2}, {2, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {4, 3}, {3, 3}, {4, 3},
		{0, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 0}, {2, 3}, {3, 3}, {3, 3}, {4, 6}
	},
		// Babylonier
	{
		{0, 0}, {2, 0}, {2, 3}, {0, 0}, {3, 5}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {4, 7},
		{4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {0, 0}, {4, 2}, {2, 0}, {2, 0}, {2, 0},
		{2, 0}, {2, 2}, {2, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {4, 3}, {3, 3}, {4, 3},
		{0, 0}, {2, 2}, {2, 2}, {2, 2}, {2, 2}, {2, 0}, {2, 3}, {3, 3}, {3, 3}, {4, 6}
	}
};

// Bauqualitäten der Gebäude
const BuildingQuality BUILDING_SIZE[40] =
{
    BQ_CASTLE,
    BQ_HUT,
    BQ_HUT,
    BQ_NOTHING,
    BQ_HOUSE,
    BQ_NOTHING,
    BQ_NOTHING,
    BQ_NOTHING,
    BQ_NOTHING,
    BQ_CASTLE,
    BQ_MINE,
    BQ_MINE,
    BQ_MINE,
    BQ_MINE,
    BQ_HUT,
    BQ_NOTHING,
    BQ_HOUSE,
    BQ_HUT,
    BQ_HUT,
    BQ_HUT,
    BQ_HUT,
    BQ_HOUSE,
    BQ_HUT,
    BQ_HOUSE,
    BQ_HOUSE,
    BQ_HOUSE,
    BQ_HOUSE,
    BQ_CASTLE,
    BQ_CASTLE,
    BQ_HOUSE,
    BQ_NOTHING,
    BQ_HOUSE,
    BQ_HOUSE,
    BQ_HOUSE,
    BQ_HOUSE,
    BQ_HUT,
    BQ_HOUSE,
    BQ_CASTLE,
    BQ_CASTLE,
    BQ_HARBOR
};




const UsualBuilding USUAL_BUILDING_CONSTS[30] =
{
    {JOB_MINER, GD_STONES, 3, {GD_FISH, GD_MEAT, GD_BREAD}},
    {JOB_MINER, GD_COAL, 3, {GD_FISH, GD_MEAT, GD_BREAD}},
    {JOB_MINER, GD_IRON, 3, {GD_FISH, GD_MEAT, GD_BREAD}},
    {JOB_MINER, GD_GOLD, 3, {GD_FISH, GD_MEAT, GD_BREAD}},
    {JOB_SCOUT, GD_NOTHING, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_NOTHING, GD_NOTHING, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_HELPER, GD_NOTHING, 1, {GD_STONES, GD_NOTHING, GD_NOTHING}},
    {JOB_WOODCUTTER, GD_WOOD, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_FISHER, GD_FISH, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_STONEMASON, GD_STONES, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_FORESTER, GD_NOTHING, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_BUTCHER, GD_MEAT, 1, {GD_HAM, GD_NOTHING, GD_NOTHING}},
    {JOB_HUNTER, GD_MEAT, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_BREWER, GD_BEER, 2, {GD_GRAIN, GD_WATER, GD_NOTHING}},
    {JOB_ARMORER, GD_SWORD, 2, {GD_IRON, GD_COAL, GD_NOTHING}},
    {JOB_METALWORKER, GD_TONGS, 2, {GD_IRON, GD_BOARDS, GD_NOTHING}},
    {JOB_IRONFOUNDER, GD_IRON, 2, {GD_IRONORE, GD_COAL, GD_NOTHING}},
    {JOB_CHARBURNER, GD_COAL, 2, {GD_WOOD, GD_GRAIN, GD_NOTHING}},
    {JOB_PIGBREEDER, GD_HAM, 2, {GD_GRAIN, GD_WATER, GD_NOTHING}},
    {JOB_NOTHING, GD_NOTHING, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_NOTHING, GD_NOTHING, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_MILLER, GD_FLOUR, 1, {GD_GRAIN, GD_NOTHING, GD_NOTHING}},
    {JOB_BAKER, GD_BREAD, 2, {GD_FLOUR, GD_WATER}},
    {JOB_CARPENTER, GD_BOARDS, 1, {GD_WOOD, GD_NOTHING}},
    {JOB_MINTER, GD_COINS, 2, {GD_GOLD, GD_COAL, GD_NOTHING}},
    {JOB_HELPER, GD_WATER, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_SHIPWRIGHT, GD_BOAT, 1, {GD_BOARDS, GD_NOTHING, GD_NOTHING}},
    {JOB_FARMER, GD_GRAIN, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
    {JOB_DONKEYBREEDER, GD_NOTHING, 2, {GD_GRAIN, GD_WATER, GD_NOTHING}},
    {JOB_NOTHING, GD_NOTHING, 0, {GD_NOTHING, GD_NOTHING, GD_NOTHING}},
};

/// Rauchkonstanten für alle 4 Völker unterschiedlich und erst beginnend nach den Militärgebäuden, denn die rauchen nicht
const SmokeConst BUILDING_SMOKE_CONSTS[NAT_COUNT][30] =
{
    // Nubier
    {
        {0, 0, 0}, // BLD_GRANITEMINE
        {0, 0, 0}, // BLD_COALMINE
        {0, 0, 0}, // BLD_IRONMINE
        {0, 0, 0}, // BLD_GOLDMINE
        {0, 0, 0}, // BLD_LOOKOUTTOWER
        {0, 0, 0}, // BLD_NOTHING7
        {0, 0, 0}, // BLD_CATAPULT
        {0, 0, 0}, // BLD_WOODCUTTER
        {0, 0, 0}, // BLD_FISHERY
        {1, 3, -32}, // BLD_QUARRY
        {0, 0, 0}, // BLD_FORESTER
        {0, 0, 0}, // BLD_SLAUGHTERHOUSE
        {0, 0, 0}, // BLD_HUNTER
        {0, 0, 0}, // BLD_BREWERY
        {1, -32, -23}, // BLD_ARMORY
        {4, -26, -47}, // BLD_METALWORKS
        {2, -20, -37}, // BLD_IRONSMELTER
        {2, -22, -57}, // BLD_CHARBURNER
        {0, 0, 0}, // BLD_PIGFARM
        {0, 0, 0}, // BLD_STOREHOUSE
        {0, 0, 0}, // BLD_NOTHING9
        {0, 0, 0}, // BLD_MILL
        {4, 27, -39}, // BLD_BAKERY
        {0, 0, 0}, // BLD_SAWMILL
        {1, 17, -52}, // BLD_MINT
        {0, 0, 0}, // BLD_WELL
        {0, 0, 0}, // BLD_SHIPYARD
        {0, 0, 0}, // BLD_FARM
        {0, 0, 0}, // BLD_DONKEYBREEDER
        {0, 0, 0} // BLD_HARBORBUILDING
    },
    // Japaner
    {
        {0, 0, 0}, // BLD_GRANITEMINE
        {0, 0, 0}, // BLD_COALMINE
        {0, 0, 0}, // BLD_IRONMINE
        {0, 0, 0}, // BLD_GOLDMINE
        {0, 0, 0}, // BLD_LOOKOUTTOWER
        {0, 0, 0}, // BLD_NOTHING7
        {0, 0, 0}, // BLD_CATAPULT
        {0, 0, 0}, // BLD_WOODCUTTER
        {0, 0, 0}, // BLD_FISHERY
        {0, 0, 0}, // BLD_QUARRY
        {0, 0, 0}, // BLD_FORESTER
        {0, 0, 0}, // BLD_SLAUGHTERHOUSE
        {0, 0, 0}, // BLD_HUNTER
        {0, 0, 0}, // BLD_BREWERY
        {1, -22, -43}, // BLD_ARMORY
        {0, 0, 0}, // BLD_METALWORKS
        {0, 0, 0}, // BLD_IRONSMELTER
        {2, -33, -57}, // BLD_CHARBURNER
        {0, 0, 0}, // BLD_PIGFARM
        {0, 0, 0}, // BLD_STOREHOUSE
        {0, 0, 0}, // BLD_NOTHING9
        {0, 0, 0}, // BLD_MILL
        {4, -30, -39}, // BLD_BAKERY
        {0, 0, 0}, // BLD_SAWMILL
        {3, 18, -58}, // BLD_MINT
        {0, 0, 0}, // BLD_WELL
        {0, 0, 0}, // BLD_SHIPYARD
        {0, 0, 0}, // BLD_FARM
        {0, 0, 0}, // BLD_DONKEYBREEDER
        {0, 0, 0} // BLD_HARBORBUILDING
    },
    // Römer
    {
        {0, 0, 0}, // BLD_GRANITEMINE
        {0, 0, 0}, // BLD_COALMINE
        {0, 0, 0}, // BLD_IRONMINE
        {0, 0, 0}, // BLD_GOLDMINE
        {0, 0, 0}, // BLD_LOOKOUTTOWER
        {0, 0, 0}, // BLD_NOTHING7
        {0, 0, 0}, // BLD_CATAPULT
        {0, 0, 0}, // BLD_WOODCUTTER
        {0, 0, 0}, // BLD_FISHERY
        {0, 0, 0}, // BLD_QUARRY
        {0, 0, 0}, // BLD_FORESTER
        {0, 0, 0}, // BLD_SLAUGHTERHOUSE
        {0, 0, 0}, // BLD_HUNTER
        {1, -26, -45}, // BLD_BREWERY
        {2, -36, -34}, // BLD_ARMORY
        {0, 0, 0}, // BLD_METALWORKS
        {1, -16, -34}, // BLD_IRONSMELTER
        {2, -44, -50}, // BLD_CHARBURNER
        {0, 0, 0}, // BLD_PIGFARM
        {0, 0, 0}, // BLD_STOREHOUSE
        {0, 0, 0}, // BLD_NOTHING9
        {0, 0, 0}, // BLD_MILL
        {4, -15, -26}, // BLD_BAKERY
        {0, 0, 0}, // BLD_SAWMILL
        {4, 20, -50}, // BLD_MINT
        {0, 0, 0}, // BLD_WELL
        {0, 0, 0}, // BLD_SHIPYARD
        {0, 0, 0}, // BLD_FARM
        {0, 0, 0}, // BLD_DONKEYBREEDER
        {0, 0, 0} // BLD_HARBORBUILDING
    },
    // Wikinger
    {
        {0, 0, 0}, // BLD_GRANITEMINE
        {0, 0, 0}, // BLD_COALMINE
        {0, 0, 0}, // BLD_IRONMINE
        {0, 0, 0}, // BLD_GOLDMINE
        {0, 0, 0}, // BLD_LOOKOUTTOWER
        {0, 0, 0}, // BLD_NOTHING7
        {0, 0, 0}, // BLD_CATAPULT
        {1, 2, -36}, // BLD_WOODCUTTER
        {1, 4, -36}, // BLD_FISHERY
        {1, 0, -34}, // BLD_QUARRY
        {1, -5, -29}, // BLD_FORESTER
        {1, 7, -41}, // BLD_SLAUGHTERHOUSE
        {1, -6, -38}, // BLD_HUNTER
        {3, 5, -39}, // BLD_BREWERY
        {3, -23, -36}, // BLD_ARMORY
        {1, -9, -35}, // BLD_METALWORKS
        {2, -2, -38}, // BLD_IRONSMELTER
        {2, -22, -55}, // BLD_CHARBURNER
        {2, -30, -37}, // BLD_PIGFARM
        {0, 0, 0}, // BLD_STOREHOUSE
        {0, 0, 0}, // BLD_NOTHING9
        {0, 0, 0}, // BLD_MILL
        {4, -21, -26}, // BLD_BAKERY
        {1, -11, -45}, // BLD_SAWMILL
        {1, 16, -38}, // BLD_MINT
        {0, 0, 0}, // BLD_WELL
        {0, 0, 0}, // BLD_SHIPYARD
        {1, -17, -48}, // BLD_FARM
        {4, -27, -40}, // BLD_DONKEYBREEDER
        {0, 0, 0} // BLD_HARBORBUILDING
    },
    // Babylonier
    {
        {0, 0, 0}, // BLD_GRANITEMINE
        {0, 0, 0}, // BLD_COALMINE
        {0, 0, 0}, // BLD_IRONMINE
        {0, 0, 0}, // BLD_GOLDMINE
        {0, 0, 0}, // BLD_LOOKOUTTOWER
        {0, 0, 0}, // BLD_NOTHING7
        {0, 0, 0}, // BLD_CATAPULT
        {0, 0, 0}, // BLD_WOODCUTTER
        {0, 0, 0}, // BLD_FISHERY
        {0, 0, 0}, // BLD_QUARRY
        {0, 0, 0}, // BLD_FORESTER
        {0, 0, 0}, // BLD_SLAUGHTERHOUSE
        {0, 0, 0}, // BLD_HUNTER
        {2, -18, -43}, // BLD_BREWERY
        {1, -22, -47}, // BLD_ARMORY
        {0, 0, 0}, // BLD_METALWORKS
        {2, -23, -36}, // BLD_IRONSMELTER
        {0, 0, 0}, // BLD_CHARBURNER
        {0, 0, 0}, // BLD_PIGFARM
        {0, 0, 0}, // BLD_STOREHOUSE
        {0, 0, 0}, // BLD_NOTHING9
        {0, 0, 0}, // BLD_MILL
        {4, -27, -32}, // BLD_BAKERY
        {0, 0, 0}, // BLD_SAWMILL
        {3, 11, -58}, // BLD_MINT
        {0, 0, 0}, // BLD_WELL
        {0, 0, 0}, // BLD_SHIPYARD
        {0, 0, 0}, // BLD_FARM
        {0, 0, 0}, // BLD_DONKEYBREEDER
        {0, 0, 0} // BLD_HARBORBUILDING
    }
};

const BuildingSignConst BUILDING_SIGN_CONSTS[NAT_COUNT][40] =
{
    // Nubier
    {
        {0, 0}, {19, -4}, {19, -3}, {0, 0}, {23, -19}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {29, -23},
        { -2, -15}, {2, -13}, { -5, -16}, { -5, -15}, {0, 0}, {0, 0}, {0, 0}, {4, -16}, {9, -12}, {7, -10},
        {28, -18}, { -6, -16}, { -3, -15}, {21, -11}, {14, -7}, { -14, -9}, {11, -9}, { -8, -21}, { -18, -34}, {0, 0},
        {0, 0}, {3, -13}, {13, -13}, { -4, -20}, {7, -14}, {15, -4}, {0, 0}, { -22, -16}, { -14, -8}, {0, 0}
    },
    // Japaner
    {   {0, 0}, {12, -10}, {13, -10}, {0, 0}, {25, -22}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {10, -14},
        {20, -2}, {12, -14}, {14, -13}, {13, -14}, {0, 0}, {0, 0}, {0, 0}, { -8, -6}, {0, 0}, { -13, -7},
        {14, -11}, {15, -10}, { -13, -7}, {16, -11}, {21, -3}, { -6, -2}, {14, -14}, { -5, -22}, {30, -25}, {0, 0},
        {0, 0}, {0, -22}, { -30, -13}, {35, -20}, {13, -34}, {19, -15}, { -22, -10}, {37, -13}, { -15, -36}, {0, 0}
    },
    // Römer
    {
        {0, 0}, {15, -3}, {14, -2}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {20, -39},
        {15, -2}, {26, 4}, {21, 4}, {21, 4}, {0, 0}, {0, 0}, {0, 0}, { -29, -10}, {0, 0}, { -4, 4},
        {7, -20}, {3, -13}, {0, 0}, {22, -8}, {18, -11}, {6, -14}, {23, -10}, { -36, -23}, {35, -27}, {0, 0},
        {0, 0}, {2, -21}, {15, -13}, {11, -30}, {23, -5}, {10, -9}, {0, -25}, {41, -43}, { -34, -19}, {0, 0}
    },
    // Wikinger
    {
        {0, 0}, { -5, 0}, { -5, 0}, {0, 0}, { -7, -5}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {17, -10},
        {20, 2}, {20, 0}, {20, -2}, {20, 0}, {0, 0}, {0, 0}, {13, -5}, {15, -6}, { -7, 2}, {17, -8},
        { -5, 0}, { -3, 2}, { -6, 0}, { -7, 0}, { -32, -2}, { -13, -3}, { -8, -2}, { -22, -18}, { -25, -8}, {0, 0},
        {0, 0}, { -8, -2}, { -17, -4}, {28, -16}, { -1, 0}, {8, -9}, {16, -15}, { -2, -25}, { -29, -9}, {0, 0}
    },
    // Babylonier
    {

        {0, 0}, {19, -6}, {19, -20}, {0, 0}, {5, -15}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {20, -10},
        {15, -10}, {15, -10}, {15, -10}, {15, -10}, {0, 0}, {0, 0}, {13, -5}, { -5, -13}, {15, -20}, {15, -1},
        {11, -7}, { 1, -22}, {7, -12}, {14, -16}, {21, -18}, {13, -11}, { 5, -17}, { -6, -33}, {18, -20}, {0, 0},
        {0, 0}, {14, -13}, {3, -17}, {0, -18}, {12, -10}, {16, 0}, {4, -16}, { -15, -11}, { -24, -9}, {0, 0}
    }
};

/// Position der nubischen Feuer für alle 4 Bergwerke
/// (Granit, Kohle, Eisen, Gold)
const int NUBIAN_MINE_FIRE[4][2] =
{
    {31, -18}, {34, -10}, {30, -11}, {32, -10},
};


/// Hilfetexte für Gebäude
extern const char* const BUILDING_HELP_STRINGS[40];

#endif
