
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class OrderMenu: public Ogre::Singleton<OrderMenu> {

		private:

			CEGUI::Listbox*			m_orderMenu;
			CEGUI::Listbox*			m_constructionMenu;
			CEGUI::ListboxTextItem*	m_item;

			bool mouseMove(const CEGUI::EventArgs& e);
			bool orderMenu_MouseButtonUp(const CEGUI::EventArgs& e);
			bool orderMenu_SelectionChanged(const CEGUI::EventArgs& e);
			bool constructionMenu_MouseButtonUp(const CEGUI::EventArgs& e);

		public:

			OrderMenu(): m_orderMenu(NULL), m_constructionMenu(NULL), m_item(NULL) { }

			void init();

			void add(CEGUI::Listbox* listBox, const string& text, void* userData = NULL) {

				m_item = new CEGUI::ListboxTextItem(text);
				
				m_item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
				m_item->setUserData(userData);

				listBox->addItem(m_item);
			}

			bool isVisible() {

				return m_orderMenu->isVisible();
			}

			void reset() {

				m_orderMenu->resetList();
			}

			void setPosition(float x, float y) {

				m_orderMenu->setPosition(CEGUI::Point(x, y));
			}

			void setVisible(bool visible) {

				m_orderMenu->setVisible(visible);
			}
	};
};

//------------------------------------------------------------------------------
