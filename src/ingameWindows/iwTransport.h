﻿// $Id: iwTransport.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef iwTRANSPORT_H_INCLUDED
#define iwTRANSPORT_H_INCLUDED

#pragma once

#include "IngameWindow.h"

class iwTransport : public IngameWindow
{
    private:

        glArchivItem_Bitmap* TRANSPORT_SPRITES[14]; ///< Einzelne Bilder für die Waren.

        /// Einstellungen nach dem letzten Netzwerk-Versenden nochmal verändert?
        bool settings_changed;

    public:

        iwTransport();
        ~iwTransport();

    private:

        /// Updatet die Steuerelemente mit den aktuellen Einstellungen aus dem Spiel
        void UpdateSettings();
        /// Sendet veränderte Einstellungen (an den Client), falls sie verändert wurden
        void TransmitSettings();

        void Msg_ButtonClick(const unsigned int ctrl_id);
        void Msg_Timer(const unsigned int ctrl_id);
};

#endif // !iwTRANSPORT_H_INCLUDED
