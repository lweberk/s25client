// $Id: nofCatapultMan.cpp 9357 2014-04-25 15:35:25Z FloSoft $
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
#include "nofCatapultMan.h"
#include "GameWorld.h"
#include "Random.h"
#include "buildings/nobMilitary.h"
#include "GameClient.h"
#include "buildings/nobUsual.h"
#include "CatapultStone.h"
#include "MapGeometry.h"
#include "gameData/MapConsts.h"

const int32_t STONE_STARTS[12] = { -4, -48, -3, -47, -13, -47, -11, -48, -13, -47, -2, -47};


nofCatapultMan::nofCatapultMan(const MapPoint pos,
                               const uint8_t player,
                               nobUsual* workplace)
    : nofBuildingWorker(JOB_HELPER, pos, player, workplace),
      wheel_steps(0)
{
}

nofCatapultMan::nofCatapultMan(SerializedGameData* sgd,
                               const uint32_t obj_id)
    : nofBuildingWorker(sgd, obj_id),
      wheel_steps( sgd->PopSignedInt() ), target( sgd )
{

}


void nofCatapultMan::Serialize_nofCatapultMan(SerializedGameData* sgd) const
{
    Serialize_nofBuildingWorker(sgd);

    sgd->PushSignedInt(wheel_steps);
    target.Serialize_PossibleTarget(sgd);
}


void nofCatapultMan::WalkedDerived()
{
}


void nofCatapultMan::DrawWorking(int32_t x, int32_t y)
{
    switch(state)
    {
        default: return;
        case STATE_CATAPULT_TARGETBUILDING:
        {
            int32_t step = GAMECLIENT.Interpolate(std::abs(wheel_steps) + 1, current_ev);

            if(step <= std::abs(wheel_steps))
            {

                if(wheel_steps < 0)
                    step = -step;

                // Katapult auf dem Dach mit Stein drehend zeichnen
                LOADER.GetImageN("rom_bobs", 1781 + (7 + step) % 6)->Draw(x - 7, y - 19, 0, 0, 0, 0, 0, 0, COLOR_WHITE, COLOR_WHITE);
            }
            //else
            //  // Katapult schießend zeichnen
            //  LOADER.GetImageN("rom_bobs", 1787+(7+wheel_steps)%6)->Draw(x-7,y-19);

        } break;
        case STATE_CATAPULT_BACKOFF:
        {
            int32_t step = GAMECLIENT.Interpolate((std::abs(wheel_steps) + 3) * 2, current_ev);

            if(step < 2 * 3)
                // Katapult nach Schießen zeichnen (hin und her wippen
                LOADER.GetImageN("rom_bobs", 1787 + (step % 2) * 6 + (7 + wheel_steps) % 6)->Draw(x - 7, y - 19, 0, 0, 0, 0, 0, 0, COLOR_WHITE, COLOR_WHITE);
            else
            {
                step = (step - 6) / 2;

                if(wheel_steps < 0)
                    step = -(step);

                // Katapult auf dem Dach mit Stein drehend zeichnen (zurück in Ausgangsposition: Richtung 4)
                LOADER.GetImageN("rom_bobs", 1775 + (7 + wheel_steps - step) % 6)->Draw(x - 7, y - 19, 0, 0, 0, 0, 0, 0, COLOR_WHITE, COLOR_WHITE);
            }

        } break;

    }
}


//void nofCatapultMan::HandleStateTargetBuilding()
//{
//}
//
//void nofCatapultMan::HandleStateBackOff()
//{
//}



void nofCatapultMan::HandleDerivedEvent(const uint32_t id)
{
    switch(state)
    {
        default:
            break;
        case STATE_WAITING1:
        {
            // Fertig mit warten --> anfangen zu arbeiten

            // Liste von potentiellen Zielen
            std::vector<PossibleTarget> pts;

            nobBaseMilitarySet buildings = gwg->LookForMilitaryBuildings(pos, 3);
            for(nobBaseMilitarySet::iterator it = buildings.begin(); it != buildings.end(); ++it)
            {
                // Auch ein richtiges Militärgebäude (kein HQ usw.),
                if((*it)->GetGOT() == GOT_NOB_MILITARY && GAMECLIENT.GetPlayer(player)->IsPlayerAttackable((*it)->GetPlayer()))
                {
                    // Was nicht im Nebel liegt und auch schon besetzt wurde (nicht neu gebaut)?
                    if(gwg->GetNode((*it)->GetPos()).fow[player].visibility == VIS_VISIBLE
                            && !static_cast<nobMilitary*>((*it))->IsNewBuilt())
                    {
                        // Entfernung ausrechnen
                        uint32_t distance = gwg->CalcDistance(pos, (*it)->GetPos());

                        // Entfernung nicht zu hoch?
                        if(distance < 14)
                        {
                            // Mit in die Liste aufnehmen
                            pts.push_back(PossibleTarget((*it)->GetPos(), distance));
                        }
                    }
                }
            }

            // Gibts evtl keine Ziele?
            if(pts.empty())
            {
                // Weiter warten, vielleicht gibts ja später wieder mal was
                current_ev = em->AddEvent(this, CATAPULT_WAIT1_LENGTH, 1);
                StartNotWorking();
                return;
            }

            // Waren verbrauchen
            workplace->ConsumeWares();

            // Eins zufällig auswählen
            target = pts[RANDOM.Rand(__FILE__, __LINE__, obj_id, pts.size())];

            // Richtung, in die sich der Katapult drehen soll, bestimmen
            uint8_t shooting_dir;

            // Normale X-Distanz (ohne Beachtung der Kartenränderüberquerung)
            uint32_t x_dist = std::abs(int(target.pos.x) - int(pos.x));
            // Distanzen jeweils bei Überquerung des linken und rechten Randes
            uint32_t x_dist1 = std::abs(int(target.pos.x) - int(pos.x) + gwg->GetWidth());
            uint32_t x_dist2 = std::abs(int(target.pos.x) - int(pos.x) - gwg->GetWidth());
            // Minimale, d.h. im Endeffekt reale Distanz
            uint32_t min_dist_x = std::min(std::min(x_dist, x_dist1), x_dist2);

            // Normale Y-Distanz (ohne Beachtung der Kartenränderüberquerung)
            uint32_t y_dist = std::abs(int(target.pos.y) - int(pos.y));
            // Distanzen jeweils bei Überquerung des linken und rechten Randes
            uint32_t y_dist1 = std::abs(int(target.pos.y) - int(pos.y) + gwg->GetHeight());
            uint32_t y_dist2 = std::abs(int(target.pos.y) - int(pos.y) - gwg->GetHeight());
            // Minimale, d.h. im Endeffekt reale Distanz
            uint32_t min_dist_y = std::min(std::min(y_dist, y_dist1), y_dist2);

            bool side_x = (pos.x < target.pos.x);
            if(x_dist > x_dist1 || x_dist > x_dist2) side_x = !side_x; // Wenn er über Kartengrenze schießt, Richtung umkehren
            bool side_y = (pos.y < target.pos.y);
            if(y_dist > y_dist1 || y_dist > y_dist2) side_y = !side_y;

            // Y-Abstand nur unwesentlich klein --> Richtung 0 und 3 (direkt gegenüber) nehmen
            if(min_dist_y <= min_dist_x / 5)
                shooting_dir = (side_x) ? 3 : 0;
            else
            {
                // Ansonsten noch y mit berücksichtigen und je einen der 4 Quadranten nehmen
                if(side_y)
                    shooting_dir = (side_x) ? 4 : 5;
                else
                    shooting_dir = (side_x) ? 2 : 1;
            }

            // "Drehschritte" ausrechnen, da von Richtung 4 aus gedreht wird
            wheel_steps = int(shooting_dir) - 4;
            if(wheel_steps < -3)
                wheel_steps = 6 + wheel_steps;

            current_ev = em->AddEvent(this, 15 * (std::abs(wheel_steps) + 1), 1);

            state = STATE_CATAPULT_TARGETBUILDING;

            // wir arbeiten
            workplace->is_working = true;

        } break;
        case STATE_CATAPULT_TARGETBUILDING:
        {
            // Stein in Bewegung setzen

            // Soll das Gebäude getroffen werden (70%)
            bool hit = (RANDOM.Rand(__FILE__, __LINE__, obj_id, 99) < 70);

            // Radius fürs Treffen und Nicht-Treffen,  (in Pixeln), nur visuell
            const int32_t RADIUS_HIT = 15; // nicht nach unten hin!

            // Zielkoordinaten als (Map-Koordinaten!)
            MapPoint destMap;

            if(hit)
            {
                // Soll getroffen werden --> Aufschlagskoordinaten gleich dem eigentlichem Ziel
                destMap = target.pos;
            }
            else
            {
                // Ansonsten zufälligen Punkt rundrum heraussuchen
                uint32_t d = RANDOM.Rand(__FILE__, __LINE__, obj_id, 6);

                destMap = gwg->GetNeighbour(target.pos, d);
            }

            uint8_t shooting_dir = (7 + wheel_steps) % 6;

            // Größe der Welt in Pixeln bestimmen
            int32_t world_width = gwg->GetWidth() * TR_W;
            int32_t world_height = gwg->GetHeight() * TR_H;

            // Startpunkt bestimmen
            int32_t start_x = int(gwg->GetTerrainX(pos)) + STONE_STARTS[(7 + wheel_steps) % 6 * 2];
            int32_t start_y = int(gwg->GetTerrainY(pos)) + STONE_STARTS[shooting_dir * 2 + 1];
            // (Visuellen) Aufschlagpunkt bestimmen
            int32_t dest_x = int(gwg->GetTerrainX(destMap));
            int32_t dest_y = int(gwg->GetTerrainY(destMap));

            // Kartenränder beachten
            // Wenn Abstand kleiner is, den kürzeren Abstand über den Kartenrand wählen
            if(std::abs(start_x + world_width - dest_x) < std::abs(start_x - dest_x))
                start_x += world_width;
            else if(std::abs(start_x - world_width - dest_x) < std::abs(start_x - dest_x))
                start_x -= world_width;
            if(std::abs(start_y + world_height - dest_y) < std::abs(start_y - dest_y))
                start_y += world_height;
            else if(std::abs(start_y - world_height - dest_y) < std::abs(start_y - dest_y))
                start_y -= world_height;

            // Bei getroffenen den Aufschlagspunkt am Gebäude ein bisschen variieren
            if(hit)
            {
                dest_x += (RANDOM.Rand(__FILE__, __LINE__, obj_id, RADIUS_HIT * 2) - RADIUS_HIT);
                // hier nicht nach unten gehen, da die Tür (also Nullpunkt
                // ja schon ziemlich weit unten ist!
                dest_y -= RANDOM.Rand(__FILE__, __LINE__, obj_id, RADIUS_HIT);
            }

            // Stein erzeugen
            gwg->AddCatapultStone(new CatapultStone(target.pos, destMap, start_x, start_y, dest_x, dest_y, 80));

            // Katapult wieder in Ausgangslage zurückdrehen
            current_ev = em->AddEvent(this, 15 * (std::abs(wheel_steps) + 3), 1);

            state = STATE_CATAPULT_BACKOFF;
        } break;
        case STATE_CATAPULT_BACKOFF:
        {
            current_ev = 0;
            // wir arbeiten nicht mehr
            workplace->is_working = false;
            // Wieder versuchen, zu arbeiten
            TryToWork();

        } break;
    }
}

void nofCatapultMan::WorkArborted()
{
}

