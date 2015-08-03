// $Id: dskOptions.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef dskOPTIONS_H_INCLUDED
#define dskOPTIONS_H_INCLUDED

#pragma once

#include "Desktop.h"
#include "../driver/src/VideoDriver.h"
#include "GlobalGameSettings.h"

/// Klasse des Optionen Desktops.
class dskOptions: public Desktop
{
    public:
        dskOptions(void);
        ~dskOptions();

    private:
        void Msg_OptionGroupChange(const uint32_t ctrl_id, const uint16_t selection);
        void Msg_ButtonClick(const uint32_t ctrl_id);
        void Msg_MsgBoxResult(const uint32_t msgbox_id, const MsgboxResult mbr);

        void Msg_Group_ButtonClick(const uint32_t group_id, const uint32_t ctrl_id);
        void Msg_Group_ProgressChange(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t position);
        void Msg_Group_ComboSelectItem(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        void Msg_Group_OptionGroupChange(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);

    private:
        GlobalGameSettings ggs;
        std::vector<VideoDriver::VideoMode> video_modes; ///< Vector für die Auflösungen
};

#endif // !dskOPTIONS_H_INCLUDED
