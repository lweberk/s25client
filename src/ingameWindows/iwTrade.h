#ifndef IW_TRADE_H_
#define IW_TRADE_H_

#include "IngameWindow.h"

class dskGameInterface;
class nobUsual;
class GameWorldViewer;
class nobBaseWarehouse;

class iwTrade : public IngameWindow
{
        GameWorldViewer* const gwv;
        dskGameInterface* const gi; ///< Das GameInterface
        nobBaseWarehouse* const wh;              ///< Das zugehörige Gebäudeobjekt
        /// Possible wares
        std::vector<GoodType> wares;
        /// Possible figures
        std::vector<Job> jobs;

    public:
        /// Konstruktor von @p iwBuilding.
        iwTrade(GameWorldViewer* const gwv, dskGameInterface* const gi, nobBaseWarehouse* const wh);

    private:

        void Msg_PaintBefore();
        void Msg_PaintAfter();
        void Msg_ButtonClick(const uint32_t ctrl_id);
        void Msg_ComboSelectItem(const uint32_t ctrl_id, const uint16_t selection);
};

#endif // !IW_TRADE_H_
