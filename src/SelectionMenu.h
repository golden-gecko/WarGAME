
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class SelectionMenu: public Ogre::Singleton<SelectionMenu> {

		private:

			CEGUI::Listbox*			m_selectionMenu;
			CEGUI::ListboxTextItem*	m_item;

			bool selectionMenu_MouseButtonDown(const CEGUI::EventArgs& e);
			bool selectionMenu_Shown(const CEGUI::EventArgs& e);
			bool selectionMenu_SelectionChanged(const CEGUI::EventArgs& e);

		public:

			SelectionMenu(): m_selectionMenu(NULL), m_item(NULL) { }

			void init();

			void add(const string& text, void* userData) {

				m_item = new CEGUI::ListboxTextItem(text);
				
				m_item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
				m_item->setUserData(userData);

				m_selectionMenu->addItem(m_item);
			}

			bool isVisible() {

				return m_selectionMenu->isVisible();
			}

			void reset() {

				m_selectionMenu->resetList();
			}

			void setPosition(float x, float y) {

				m_selectionMenu->setPosition(CEGUI::Point(x, y));
			}

			void setVisible(bool visible) {

				m_selectionMenu->setVisible(visible);
			}

	};

};

//------------------------------------------------------------------------------
