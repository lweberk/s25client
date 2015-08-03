// $Id: Window.h 9357 2014-04-25 15:35:25Z FloSoft $
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
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#pragma once

#include "CollisionDetection.h"

#include "drivers/MouseAndKeys.h"
#include "Msgbox.h"
#include "gameData/GameConsts.h"
#include "colors.h"
#include "Rect.h"
#include <map>

class WindowManager;

class ctrlAlternativeEdit;
class ctrlBuildingIcon;
class ctrlTextButton;
class ctrlColorButton;
class ctrlImageButton;
class ctrlChat;
class ctrlCheck;
class ctrlComboBox;
class ctrlDeepening;
class ctrlColorDeepening;
class ctrlEdit;
class ctrlGroup;
class ctrlImage;
class ctrlList;
class ctrlPreviewMinimap;
class ctrlMultiline;
class ctrlOptionGroup;
class ctrlPercent;
class ctrlProgress;
class ctrlScrollBar;
class ctrlTab;
class ctrlTable;
class ctrlText;
class ctrlTimer;
class ctrlVarDeepening;
class ctrlVarText;
class ctrlMultiSelectGroup;

class glArchivItem_Map;
class glArchivItem_Font;
class glArchivItem_Bitmap;

/// Die Basisklasse der Fenster.
class Window
{
        friend class WindowManager;

    public:
        /// Konstruktor von @p Window.
        Window(void);
        /// Konstruktor von @p Window mit Parametern.
        Window(uint16_t x, uint16_t y, uint32_t id, Window* parent, uint16_t width = 0, uint16_t height = 0, const std::string& tooltip = "");
        /// virtueller Destruktor von @p Window.
        virtual ~Window(void);
        /// zeichnet das Fenster.
        bool Draw(void);
        /// liefert die X-Koordinate.
        uint16_t GetX(bool absolute = true) const;
        /// liefert die Y-Koordinate.
        uint16_t GetY(bool absolute = true) const;
        /// liefert die Breite des Fensters.
        uint16_t GetWidth(const bool scale = false) const { return (scale) ? ScaleX(width) : width; }
        /// liefert die Höhe des Fensters.
        uint16_t GetHeight(const bool scale = false) const { return (scale) ? ScaleY(height) : height; }
        /// setzt die Größe des Fensters
        void Resize(uint16_t width, uint16_t height) { Resize_(width, height); this->width = width; this->height = height; }
        /// setzt die Breite des Fensters
        void SetWidth(uint16_t width)   { Resize(width, this->height); }
        /// setzt die Höhe des Fensters
        void SetHeight(uint16_t height) { Resize(this->width, height); }
        /// Sendet eine Tastaturnachricht an die Steuerelemente.
        bool RelayKeyboardMessage(bool (Window::*msg)(const KeyEvent&), const KeyEvent& ke);
        /// Sendet eine Mausnachricht weiter an alle Steuerelemente
        bool RelayMouseMessage(bool (Window::*msg)(const MouseCoords&), const MouseCoords& mc);
        /// aktiviert das Fenster.
        void SetActive(bool activate = true);
        /// aktiviert die Steuerelemente des Fensters.
        void ActivateControls(bool activate = true);
        /// Sperrt eine bestimmte Region für Mausereignisse.
        void LockRegion(Window* window, const Rect& rect);
        /// Gibt eine gesperrte Region wieder frei.
        void FreeRegion(Window* window);
        /// Größe verändern oder überhaupt setzen

        /// setzt das Parentfenster.
        void SetParent(Window* parent) { this->parent = parent; }
        /// verschiebt das Fenster.
        void Move(int16_t x, int16_t y, bool absolute = true) { this->x = (absolute ? x : this->x + x); this->y = (absolute ? y : this->y + y); }

        // macht das Fenster sichtbar oder blendet es aus
        virtual void SetVisible(bool visible) { this->visible = visible; }
        /// Ist das Fenster sichtbar?
        bool GetVisible() const { return visible; }
        /// Ist das Fenster aktiv?
        bool GetActive() const { return active; }
        /// liefert das übergeordnete Fenster
        Window* GetParent() const { return parent; }
        const uint32_t GetID(void) const { return id; }

        template<typename T>
        T* GetCtrl(uint32_t id)
        {
            std::map<uint32_t, Window*>::iterator it = idmap.find(id);
            if(it == idmap.end())
                return NULL;

            return dynamic_cast<T*>( it->second );
        }

        template<typename T>
        const T* GetCtrl(uint32_t id) const
        {
            std::map<uint32_t, Window*>::const_iterator it = idmap.find(id);
            if(it == idmap.end())
                return NULL;

            return dynamic_cast<T*>( it->second );
        }

        void DeleteCtrl(uint32_t id)
        {
            std::map<uint32_t, Window*>::iterator it = idmap.find(id);

            if(it == idmap.end())
                return;

            delete it->second;

            idmap.erase(it);
        }

        /// fügt ein BuildingIcon hinzu.
        ctrlBuildingIcon* AddBuildingIcon(uint32_t id, uint16_t x, uint16_t y, BuildingType type, const Nation nation, uint16_t size = 36, const std::string& tooltip = "");
        /// fügt einen Text-ButtonCtrl hinzu.
        ctrlTextButton* AddTextButton(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const TextureColor tc, const std::string& text,  glArchivItem_Font* font, const std::string& tooltip = "");
        /// fügt einen Color-ButtonCtrl hinzu.
        ctrlColorButton* AddColorButton(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const TextureColor tc, const uint32_t fillColor, const std::string& tooltip = "");
        /// fügt einen Image-ButtonCtrl hinzu.
        ctrlImageButton* AddImageButton(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, const TextureColor tc, glArchivItem_Bitmap* const image, const std::string& tooltip = "");

        //ctrlButton *AddButton(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, bool type, const char *text, const char *tooltip, glArchivItem_Font *font, glArchivItem_Bitmap *image = NULL, bool border = true);
        /// fügt ein ChatCtrl hinzu.
        ctrlChat* AddChatCtrl(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, glArchivItem_Font* font);
        /// fügt ein CheckBoxCtrl hinzu.
        ctrlCheck* AddCheckBox(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, const std::string& text, glArchivItem_Font* font, bool readonly = false);
        /// fügt eine ComboBox hinzu.
        ctrlComboBox* AddComboBox(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, glArchivItem_Font* font, uint16_t max_list_height, bool readonly = false);
        /// fügt ein vertieftes TextCtrl hinzu.
        ctrlDeepening* AddDeepening(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, const std::string& text, glArchivItem_Font* font, uint32_t color);
        /// Deepening fille with a color
        ctrlColorDeepening* AddColorDeepening(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, uint32_t fillColor);
        /// fügt ein EditCtrl hinzu.
        ctrlEdit* AddEdit(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, glArchivItem_Font* font, uint16_t maxlength = 0, bool password = false, bool disabled = false, bool notify = false);
        /// fügt eine Gruppe hinzu.
        ctrlGroup* AddGroup(uint32_t id, bool scale = false);
        /// fügt ein ImageCtrl hinzu.
        ctrlImage* AddImage(uint32_t id, uint16_t x, uint16_t y, glArchivItem_Bitmap* image, const std::string& tooltip = "");
        /// fügt eine ListenCtrl hinzu.
        ctrlList* AddList(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, glArchivItem_Font* font);
        /// fügt ein mehrzeilen EditCtrl hinzu.
        ctrlMultiline* AddMultiline(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, glArchivItem_Font* font, uint32_t format = 0);
        /// fügt eine OptionenGruppe hinzu.
        ctrlOptionGroup* AddOptionGroup(uint32_t id, int32_t select_type, bool scale = false);
        /// fügt eine MultiSelectGruppe hinzu.
        ctrlMultiSelectGroup* AddMultiSelectGroup(uint32_t id, int32_t select_type, bool scale = false);
        /// fügt eine prozentuale ProgressBar hinzu.
        ctrlPercent* AddPercent(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, uint32_t text_color, glArchivItem_Font* font, const uint16_t* percentage);
        /// fügt eine ProgressBar hinzu.
        ctrlProgress* AddProgress(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, uint16_t button_minus, uint16_t button_plus, uint16_t maximum,
                                  const std::string& tooltip  = "", uint16_t x_padding = 0, uint16_t y_padding = 0, uint32_t force_color = 0, const std::string& button_minus_tooltip = "", const std::string& button_plus_tooltip = "");
        /// fügt eine Scrollbar hinzu.
        ctrlScrollBar* AddScrollBar(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t button_height, TextureColor tc, uint16_t page_size);
        /// fügt ein TabCtrl hinzu.
        ctrlTab* AddTabCtrl(uint32_t id, uint16_t x, uint16_t y, uint16_t width);
        /// fügt eine Tabelle hinzu.
        ctrlTable* AddTable(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, glArchivItem_Font* font, uint32_t columns, ...);
        /// fügt ein TextCtrl hinzu.
        ctrlText* AddText(uint32_t id, uint16_t x, uint16_t y, const std::string& text, uint32_t color, uint32_t format, glArchivItem_Font* font);
        /// fügt einen Timer hinzu.
        ctrlTimer* AddTimer(uint32_t id, uint32_t timeout);
        /// fügt ein vertieftes variables TextCtrl hinzu.
        ctrlVarDeepening* AddVarDeepening(uint32_t id, uint16_t x, uint16_t y, uint16_t width, uint16_t height, TextureColor tc, const std::string& formatstr, glArchivItem_Font* font, uint32_t color, uint32_t parameters, ...);
        /// fügt ein variables TextCtrl hinzu.
        ctrlVarText* AddVarText(uint32_t id, uint16_t x, uint16_t y,  const std::string& formatstr, uint32_t color, uint32_t format, glArchivItem_Font* font, uint32_t parameters, ...);
        /// Fügt eine MapPreview hinzu
        ctrlPreviewMinimap* AddPreviewMinimap(const uint32_t id,
                                              uint16_t x,
                                              uint16_t y,
                                              uint16_t width,
                                              uint16_t height,
                                              glArchivItem_Map* const map);

        /// Zeichnet einen 3D-Rahmen.
        static void Draw3D(const uint16_t x, const uint16_t y, const uint16_t width, uint16_t height, const TextureColor tc, const uint16_t type, const bool illuminated = false, const bool draw_content = true);
        /// Zeichnet ein Rechteck
        static void DrawRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
        /// Zeichnet eine Linie
        static void DrawLine(uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by, uint16_t width, uint32_t color);

        // GUI-Notify-Messages

        // Nachrichten, die von oben (WindowManager) nach unten (zu Controls) gereicht werden
        virtual void Msg_PaintBefore();
        virtual void Msg_PaintAfter();
        virtual bool Msg_LeftDown(const MouseCoords& mc);
        virtual bool Msg_RightDown(const MouseCoords& mc);
        virtual bool Msg_LeftUp(const MouseCoords& mc);
        virtual bool Msg_RightUp(const MouseCoords& mc);
        virtual bool Msg_WheelUp(const MouseCoords& mc);
        virtual bool Msg_WheelDown(const MouseCoords& mc);
        virtual bool Msg_MouseMove(const MouseCoords& mc);
        virtual bool Msg_KeyDown(const KeyEvent& ke);
        // Wird aufgerufen, nachdem schon ein Mausklick behandelt wurde
        // NUR VORÜBERGEHEND für Edit-Controls, bis richtiger Steuerelement-Fokus
        // eingebaut wurde!
        virtual bool Msg_LeftDown_After(const MouseCoords& mc);
        virtual void Msg_ScreenResize(const ScreenResizeEvent& sr);

        // Nachrichten, die von unten (Controls) nach oben (Fenster) gereicht werden
        virtual void Msg_ButtonClick(const uint32_t ctrl_id);
        virtual void Msg_EditEnter(const uint32_t ctrl_id);
        virtual void Msg_EditChange(const uint32_t ctrl_id);
        virtual void Msg_TabChange(const uint32_t ctrl_id, const uint16_t tab_id);
        virtual void Msg_ListSelectItem(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_ListChooseItem(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_ComboSelectItem(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_CheckboxChange(const uint32_t ctrl_id, const bool checked);
        virtual void Msg_ProgressChange(const uint32_t ctrl_id, const uint16_t position);
        virtual void Msg_ScrollChange(const uint32_t ctrl_id, const uint16_t position);
        virtual void Msg_ScrollShow(const uint32_t ctrl_id, const bool visible);
        virtual void Msg_OptionGroupChange(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Timer(const uint32_t ctrl_id);
        virtual void Msg_TableSelectItem(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_TableChooseItem(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_TableRightButton(const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_TableLeftButton(const uint32_t ctrl_id, const uint16_t selection);

        // Sonstiges
        virtual void Msg_MsgBoxResult(const uint32_t msgbox_id, const MsgboxResult mbr);

        // Nachrichten, die von Controls von ctrlGroup weitergeleitet werden
        virtual void Msg_Group_ButtonClick(const uint32_t group_id, const uint32_t ctrl_id);
        virtual void Msg_Group_EditEnter(const uint32_t group_id, const uint32_t ctrl_id);
        virtual void Msg_Group_EditChange(const uint32_t group_id, const uint32_t ctrl_id);
        virtual void Msg_Group_TabChange(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t tab_id);
        virtual void Msg_Group_ListSelectItem(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_ComboSelectItem(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_CheckboxChange(const uint32_t group_id, const uint32_t ctrl_id, const bool checked);
        virtual void Msg_Group_ProgressChange(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t position);
        virtual void Msg_Group_ScrollShow(const uint32_t group_id, const uint32_t ctrl_id, const bool visible);
        virtual void Msg_Group_OptionGroupChange(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_Timer(const uint32_t group_id, const uint32_t ctrl_id);
        virtual void Msg_Group_TableSelectItem(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_TableRightButton(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);
        virtual void Msg_Group_TableLeftButton(const uint32_t group_id, const uint32_t ctrl_id, const uint16_t selection);

    protected:

        /// gets the extent of the window
        Rect GetRect() const { return Rect(x, y, GetWidth(), GetHeight()); }
        /// scales X- und Y values to fit the screen
        uint16_t ScaleX(const uint16_t val) const;
        uint16_t ScaleY(const uint16_t val) const;
        /// setzt Scale-Wert, ob neue Controls skaliert werden sollen oder nicht.
        void SetScale(bool scale = true) { this->scale = scale; }
        /// zeichnet die Steuerelemente.
        void DrawControls(void);
        /// prüft ob Mauskoordinaten in einer gesperrten Region liegt.
        bool TestWindowInRegion(Window* window, const MouseCoords& mc) const;
        /// zeichnet das Fenster. (virtuelle Memberfunktion)
        virtual bool Draw_() = 0;
        /// Weiterleitung von Nachrichten von abgeleiteten Klassen erlaubt oder nicht?
        virtual bool IsMessageRelayAllowed() const;
        /// Auf Größe verändern evtl. auch individuell reagieren?
        virtual void Resize_(uint16_t width, uint16_t height) {}

        template <typename T>
        T* AddCtrl(uint32_t id, T* ctrl)
        {
            assert(idmap.find(id) == idmap.end());
            // ID auf control mappen
            idmap.insert(std::make_pair(id, ctrl));

            // scale-Eigenschaft weitervererben
            ctrl->scale = scale;

            //// Control zur Liste hinzufügen.
            //controls.push_back(ctrl);

            return ctrl;
        }

    protected:
        enum ButtonState
        {
            BUTTON_UP = 0,
            BUTTON_HOVER,
            BUTTON_PRESSED,
            BUTTON_UNKNOWN = 0xFF
        };

        uint16_t x;         ///< X-Position des Fensters.
        uint16_t y;         ///< Y-Position des Fensters.
        uint16_t width;     ///< Breite des Fensters.
        uint16_t height;    ///< Höhe des Fensters.
        uint32_t id;          ///< ID des Fensters.
        Window* parent;           ///< Handle auf das Parentfenster.
        bool active;              ///< Fenster aktiv?
        bool visible;             ///< Fenster sichtbar?
        bool scale;               ///< Sollen Controls an Fenstergröße angepasst werden?
        std::string tooltip;      ///< Tooltip des Fensters (nur bei Controls benutzt)

        std::map<Window*, Rect> locked_areas;       ///< gesperrte Regionen des Fensters.
        std::map<uint32_t, Window*> idmap; ///< Die Steuerelemente des Fensters.
};

#endif // !WINDOW_H_INCLUDED
