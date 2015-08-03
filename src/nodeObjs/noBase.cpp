﻿// $Id: noBase.cpp 9357 2014-04-25 15:35:25Z FloSoft $
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
#include "noBase.h"
#include "SerializedGameData.h"

noBase::noBase(SerializedGameData* sgd, const uint32_t obj_id) : GameObject(sgd, obj_id)
{
    nop = NodalObjectType(sgd->PopUnsignedChar());
}

void noBase::Serialize_noBase(SerializedGameData* sgd) const
{
    Serialize_GameObject(sgd);

    sgd->PushUnsignedChar(static_cast<uint8_t>(nop));
}

FOWObject* noBase::CreateFOWObject() const
{
    return NULL;
}

noBase::BlockingManner noBase::GetBM() const
{
    return BM_NOTBLOCKING;
}

/// Gibt zurück, ob sich das angegebene Objekt zwischen zwei Punkten bewegt
bool noBase::IsMoving() const
{
    return false;
}
