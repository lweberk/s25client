﻿// $Id: oem.h 9357 2014-04-25 15:35:25Z FloSoft $
//
// Copyright (c) 2005-2009 Settlers Freaks (sf-team at siedler25.org)
//
// This file is part of Siedler II.5 RTTR.
//
// Siedler II.5 RTTR is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Siedler II.5 RTTR is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Siedler II.5 RTTR. If not, see <http://www.gnu.org/licenses/>.
#ifndef OEM_H_INCLUDED
#define OEM_H_INCLUDED

#pragma once

#ifndef _WIN32

/// Wandelt einen String vom ANSI ins OEM Format um.
char* AnsiToOem(const char* from, char* to, unsigned int length = 0);

/// Wandelt einen String vom OEM ins ANSI Format um.
char* OemToAnsi(const char* from, char* to, unsigned int length = 0);

#endif // !_WIN32

#endif // !OEM_H_INCLUDED
