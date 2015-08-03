// $Id: BurnedWarehouse.cpp 9357 2014-04-25 15:35:25Z FloSoft $
//
// Copyright (c) 2005 - 2011 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Return To The Roots.
//
// Return To The Roots is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your oposion) any later version.
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
#include "BurnedWarehouse.h"

#include "SerializedGameData.h"
#include "EventManager.h"
#include "GameWorld.h"
#include "Random.h"
#include "figures/noFigure.h"
#include "ogl/glArchivItem_Map.h"
#include "GameClient.h"
#include "GameClientPlayer.h"
#include "figures/nofPassiveWorker.h"

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#if defined _WIN32 && defined _DEBUG && defined _MSC_VER
#define new new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/// Anzahl der Rausgeh-Etappen
const uint32_t GO_OUT_PHASES = 10;
/// Länge zwischen zwei solchen Phasen
const uint32_t PHASE_LENGTH = 2;

BurnedWarehouse::BurnedWarehouse(const MapPoint pos, const uint8_t player, const uint32_t* people)
    : noCoordBase(NOP_BURNEDWAREHOUSE, pos), player(player), go_out_phase(0)
{
    memcpy(this->people, people, 30 * sizeof(uint32_t));
    // Erstes Event anmelden
    em->AddEvent(this, PHASE_LENGTH, 0);
}

BurnedWarehouse::BurnedWarehouse(SerializedGameData* sgd, const uint32_t obj_id) : noCoordBase(sgd, obj_id),
    player(sgd->PopUnsignedChar()),
    go_out_phase(sgd->PopUnsignedInt())
{
    for(uint32_t i = 0; i < 31; ++i)
        people[i] = sgd->PopUnsignedInt();
}


BurnedWarehouse::~BurnedWarehouse()
{
}


void BurnedWarehouse::Destroy(void)
{
}


void BurnedWarehouse::Serialize_BurnedWarehouse(SerializedGameData* sgd) const
{
    Serialize_noCoordBase(sgd);

    sgd->PushUnsignedChar(player);
    sgd->PushUnsignedInt(go_out_phase);

    for(uint32_t i = 0; i < 31; ++i)
        sgd->PushUnsignedInt(people[i]);
}


void BurnedWarehouse::HandleEvent(const uint32_t id)
{
    for(uint32_t i = 0; i < 30; ++i)
    {
        // Anzahl ausrechnen, die in dieser Runde rausgeht
        uint32_t count = people[i] / (GO_OUT_PHASES - go_out_phase);

        // Letzte Runde? Dann den Rest auch noch mit nehmen
        if(go_out_phase == GO_OUT_PHASES)
            count += people[i];

        // Von der vorhandenen Abzahl abziehen
        people[i] -= count;

        // In Alle Richtungen verteilen
        // Startrichtung zufällig bestimmen
        uint8_t start_dir = RANDOM.Rand(__FILE__, __LINE__, obj_id, 6);

        bool possible[6];
        uint32_t possible_count = 0;

        // Mögliche Richtungen zählen und speichern
        for(uint8_t d = 0; d < 6; ++d)
        {
            if(gwg->IsNodeForFigures(gwg->GetNeighbour(pos, d)))
            {
                possible[d] = true;
                ++possible_count;
            }
            else
                possible[d] = false;
        }

        // GAR KEINE Richtungen?
        if(possible_count == 0)
        {
            // Das ist traurig, dann muss die Titanic mit allen restlichen an Board leider untergehen
            em->AddToKillList(this);
            // restliche Leute von der Inventur abziehen
            for(uint32_t i = 0; i < 30; ++i)
                GAMECLIENT.GetPlayer(player)->DecreaseInventoryJob(Job(i), people[i]);

            return;
        }

        // Letzte mögliche Richtung bestimmen
        uint8_t last_dir = 0xFF;

        for(uint8_t d = 0; d < 6; ++d)
        {
            uint8_t dir = (start_dir + d) % 6;
            if(possible[dir])
                last_dir = dir;
        }

        assert(last_dir < 6);

        for(uint8_t d = 0; d < 6; ++d)
        {
            // Aktuelle Richtung, die jetzt dran ist bestimmen
            uint32_t dir = (start_dir + d) % 6;

            // Wenn Richtung nicht möglich ist --> weglassen
            if(!possible[dir])
                continue;

            // Anzahl jetzt für diese Richtung ausrechnen
            uint32_t dir_count = count / possible_count;
            // Bei letzter Richtung noch den übriggebliebenen Rest dazuaddieren
            if(dir == last_dir)
                dir_count += count % possible_count;

            // Die Figuren schließlich rausschicken
            for(uint32_t z = 0; z < dir_count; ++z)
            {
                // Job erzeugen
                nofPassiveWorker* figure = new nofPassiveWorker(Job(i), pos, player, NULL);
                // Auf die Map setzen
                gwg->AddFigure(figure, pos);
                // Losrumirren in die jeweilige Richtung
                figure->StartWandering(obj_id);
                figure->StartWalking(dir);

            }

        }
    }

    // Nächste Runde
    ++go_out_phase;

    // Nächste Runde anmelden bzw. sich selbst killen, wenn alle Runden erledigt sind
    if(go_out_phase == GO_OUT_PHASES)
    {
        // fertig, sich selbst töten
        em->AddToKillList(this);
#ifndef NDEBUG
        // Prüfen, ob alle evakuiert wurden und keiner mehr an Board ist
        for(uint32_t i = 0; i < 30; ++i)
            assert(people[i] == 0);
#endif
    }
    else
    {
        // Nächstes Event anmelden
        em->AddEvent(this, PHASE_LENGTH, 0);
    }

}

