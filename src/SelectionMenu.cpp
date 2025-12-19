
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "SelectionMenu.h"

#include "Core.h"
#include "Object.h"

//------------------------------------------------------------------------------

bool SelectionMenu::selectionMenu_MouseButtonDown(const CEGUI::EventArgs& e) {
	
	const CEGUI::MouseEventArgs& m = static_cast<const CEGUI::MouseEventArgs&>(e);

	switch (m.button) {

		case CEGUI::RightButton:

			setVisible(false);

			break;
	}

	return true;
}

//------------------------------------------------------------------------------

bool SelectionMenu::selectionMenu_Shown(const CEGUI::EventArgs& e) {

	reset();

	for (list<Object*>::iterator itr = Core::getSingletonPtr()->m_hovered.begin(); itr != Core::getSingletonPtr()->m_hovered.end(); itr++)

		add((*itr)->getName() + ((*itr)->getSelected() ? ", selected" : ", not selected"), (*itr));

	return true;
}

//------------------------------------------------------------------------------

bool SelectionMenu::selectionMenu_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_selectionMenu->getSelectedCount()) {

		Core::getSingletonPtr()->deselectAll();

		Core::getSingletonPtr()->select((Object*)m_selectionMenu->getFirstSelectedItem()->getUserData());

		setVisible(false);
	}

	return true;
}

//------------------------------------------------------------------------------

void SelectionMenu::init() {

	m_selectionMenu = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("SelectionMenu");

	m_selectionMenu->subscribeEvent(
		CEGUI::Listbox::EventMouseButtonDown,
		CEGUI::Event::Subscriber(&SelectionMenu::selectionMenu_MouseButtonDown, this));
	m_selectionMenu->subscribeEvent(
		CEGUI::Listbox::EventShown,
		CEGUI::Event::Subscriber(&SelectionMenu::selectionMenu_Shown, this));
	m_selectionMenu->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&SelectionMenu::selectionMenu_SelectionChanged, this));
}

//------------------------------------------------------------------------------
