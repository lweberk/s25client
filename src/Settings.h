// $Id: Settings.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#pragma once

///////////////////////////////////////////////////////////////////////////////
// Header
#include "Singleton.h"
#include <string>
#include <map>

#undef interface

///////////////////////////////////////////////////////////////////////////////
// Klasse für die Konfiguration
class Settings : public Singleton<Settings>
{
    public:
        Settings(void);

        bool Load(void); // Lädt Einstellungen
        void Save(void); // Speichert Einstellungen

    protected:
        bool LoadDefaults();

    public:
        struct
        {
            uint32_t submit_debug_data;
            uint32_t use_upnp;
        } global;

        struct
        {
            uint16_t fullscreen_width;
            uint16_t fullscreen_height;
            uint16_t windowed_width;
            uint16_t windowed_height;
            bool fullscreen;
            uint16_t vsync;
            bool vbo;
            bool shared_textures;
        } video;

        struct
        {
            std::string language;
        } language;

        struct
        {
            std::string audio;
            std::string video;
        } driver;

        struct
        {
            bool musik;
            uint8_t musik_volume;
            bool effekte;
            uint8_t effekte_volume;
            std::string playlist; ///< musicplayer playlist name
        } sound;

        struct
        {
            std::string name;
            std::string password;
            std::string email;
            bool save_password;
        } lobby;

        struct
        {
            std::string last_ip; ///< last entered ip or hostname
            bool ipv6;           ///< listen/connect on ipv6 as default or not
        } server;

        struct
        {
            std::string proxy; ///< Serveradresse / Hostname
            uint32_t port; ///< Port
            uint8_t typ; ///< Socks 4 oder 5
        } proxy;

        struct
        {
            uint32_t autosave_interval;
            bool revert_mouse;
        } interface;

        struct
        {
            bool scale_statistics;
        } ingame;

        struct
        {
            std::map<uint32_t, uint32_t> configuration;
        } addons;

        static const uint8_t SCREEN_REFRESH_RATES_COUNT;
        static const uint16_t SCREEN_REFRESH_RATES[];

    private:
        static const uint32_t SETTINGS_VERSION;
        static const uint32_t SETTINGS_SECTIONS;
        static const std::string SETTINGS_SECTION_NAMES[];
};

///////////////////////////////////////////////////////////////////////////////
// Makros / Defines
#define SETTINGS Settings::inst()

#endif // SETTINGS_H_INCLUDED
