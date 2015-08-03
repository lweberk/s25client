// $Id: Random.h 9363 2014-04-26 15:00:08Z FloSoft $
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
#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#pragma once

#include <cstddef>
#include <cstdint>
#include <list>

#include "Singleton.h"

#ifdef max
    #undef max
#endif

struct RandomEntry
{
    uint32_t counter;
    int32_t max;
    int32_t value;
    const char* src_name;
    uint32_t src_line;
    uint32_t obj_id;

    RandomEntry(uint32_t counter, int32_t max, int32_t value, const char* src_name, uint32_t src_line, uint32_t obj_id) : counter(counter), max(max), value(value), src_name(src_name), src_line(src_line), obj_id(obj_id) {};
    RandomEntry() : counter(0), max(0), value(0), src_name(NULL), src_line(0), obj_id(0) {};
};

class Random : public Singleton<Random>
{
        uint32_t counter;
//  std::list<RandomEntry> async_log;
        RandomEntry async_log[1024];

    public:

        /// Konstruktor von @p Random.
        Random();
        /// Initialisiert den Zufallszahlengenerator.
        void Init(const uint32_t init);
        /// Erzeugt eine Zufallszahl.
        int32_t Rand(const char* const src_name, const uint32_t src_line, const uint32_t obj_id, const int32_t max);

        template <typename T>
        void Shuffle(T* const elements, uint32_t length, uint32_t repeat = 3)
        {
            for(uint32_t i = 0; i < repeat; ++i)
            {
                for(uint32_t j = 0; j < length; j++)
                {
                    uint32_t to = Rand(__FILE__, __LINE__, 0, length);

                    T temp = elements[i];
                    elements[i] = elements[to];
                    elements[to] = temp;
                }
            }
        }

        /// Gibt aktuelle Zufallszahl zurück
        int32_t GetCurrentRandomValue() const { return zahl; }
        void ReplaySet(const uint32_t checksum) { zahl = checksum; }

        std::list<RandomEntry>* GetAsyncLog();

        /// Speichere Log
        void SaveLog(const char* const filename);

    private:
        int32_t zahl; ///< Die aktuelle Zufallszahl.
};

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#define RANDOM Random::inst()

#endif // !RANDOM_H_INCLUDED
