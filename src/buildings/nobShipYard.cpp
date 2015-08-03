
#include "defines.h"
#include "nobShipYard.h"
#include "SerializedGameData.h"

nobShipYard::nobShipYard(const MapPoint pos, const uint8_t player, const Nation nation)
    : nobUsual(BLD_SHIPYARD, pos, player, nation), mode(nobShipYard::BOATS)
{
}

nobShipYard::nobShipYard(SerializedGameData* sgd, const uint32_t obj_id)
    : nobUsual(sgd, obj_id), mode(nobShipYard::Mode(sgd->PopUnsignedChar()))
{
}

/// Serialisierungsfunktionen
void nobShipYard::Serialize(SerializedGameData* sgd) const
{
    Serialize_nobUsual(sgd);

    sgd->PushUnsignedChar(static_cast<uint8_t>(mode));
}

/// Schaltet Modus entsprechend um
void nobShipYard::ToggleMode()
{
    if(mode == nobShipYard::BOATS)
        mode = nobShipYard::SHIPS;
    else
        mode = nobShipYard::BOATS;
}
