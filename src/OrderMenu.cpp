
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "OrderMenu.h"

#include "Core.h"
#include "Object.h"
#include "ObjectDescManager.h"

//------------------------------------------------------------------------------

bool OrderMenu::orderMenu_MouseButtonDown(const CEGUI::EventArgs& e) {
	
	const CEGUI::MouseEventArgs& m = static_cast<const CEGUI::MouseEventArgs&>(e);

	switch (m.button) {

		case CEGUI::RightButton:

			setVisible(false);

			break;
	}

	return true;
}

//------------------------------------------------------------------------------

bool OrderMenu::orderMenu_Shown(const CEGUI::EventArgs& e) {

	return true;
}

//------------------------------------------------------------------------------

bool OrderMenu::orderMenu_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_orderMenu->getSelectedCount()) {

		switch ((int)m_orderMenu->getFirstSelectedItem()->getUserData()) {

			case ObjectOrder::OOT_ATTACK_POSITION:
			case ObjectOrder::OOT_MOVE_TO_POSITION:
			case ObjectOrder::OOT_PATROL:

				Core::getSingletonPtr()->m_selected.front()->order(ObjectOrder(
					ObjectOrder::ObjectOrderType((int)m_orderMenu->getFirstSelectedItem()->getUserData()),
					Core::getSingletonPtr()->getMouse3DPos()));

				break;

			case ObjectOrder::OOT_CONSTRUCT:

				Core::getSingletonPtr()->m_selected.front()->order(ObjectOrder(
					ObjectOrder::ObjectOrderType((int)m_orderMenu->getFirstSelectedItem()->getUserData()),
					Ogre::Vector3::ZERO,
					ObjectDescManager::getSingletonPtr()->getByName("light tank")));

				break;

			case ObjectOrder::OOT_ATTACK_OBJECT:
			case ObjectOrder::OOT_FOLLOW:
			case ObjectOrder::OOT_MOVE_TO_OBJECT:
			case ObjectOrder::OOT_REPAIR:
			case ObjectOrder::OOT_RESUPPLY:

				Core::getSingletonPtr()->m_selected.front()->order(ObjectOrder(
					ObjectOrder::ObjectOrderType((int)m_orderMenu->getFirstSelectedItem()->getUserData()),
					Ogre::Vector3::ZERO,
					Core::getSingletonPtr()->m_hovered.front()));

				break;

			case ObjectOrder::OOT_SELF_DESTRUCT:
			case ObjectOrder::OOT_STOP:

				Core::getSingletonPtr()->m_selected.front()->order(ObjectOrder(
					ObjectOrder::ObjectOrderType((int)m_orderMenu->getFirstSelectedItem()->getUserData())));

				break;
		}

		setVisible(false);
	}

	return true;
}

//------------------------------------------------------------------------------

bool OrderMenu::orderMenu_MouseMove(const CEGUI::EventArgs& e) {

	

	return true;
}

//------------------------------------------------------------------------------

void OrderMenu::init() {

	m_orderMenu = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("OrderMenu");

	m_orderMenu->subscribeEvent(
		CEGUI::Listbox::EventMouseButtonDown,
		CEGUI::Event::Subscriber(&OrderMenu::orderMenu_MouseButtonDown, this));
	m_orderMenu->subscribeEvent(
		CEGUI::Listbox::EventShown,
		CEGUI::Event::Subscriber(&OrderMenu::orderMenu_Shown, this));
	m_orderMenu->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&OrderMenu::orderMenu_SelectionChanged, this));
	m_orderMenu->subscribeEvent(
		CEGUI::Listbox::EventMouseMove,
		CEGUI::Event::Subscriber(&OrderMenu::orderMenu_MouseMove, this));

	add("attack object", (void*)ObjectOrder::OOT_ATTACK_OBJECT);
	add("attack position", (void*)ObjectOrder::OOT_ATTACK_POSITION);
	add("construct", (void*)ObjectOrder::OOT_CONSTRUCT);
	add("follow", (void*)ObjectOrder::OOT_FOLLOW);
	add("move to object", (void*)ObjectOrder::OOT_MOVE_TO_OBJECT);
	add("move to position", (void*)ObjectOrder::OOT_MOVE_TO_POSITION);
	add("patrol", (void*)ObjectOrder::OOT_PATROL);
	add("repair", (void*)ObjectOrder::OOT_REPAIR);
	add("ressuply", (void*)ObjectOrder::OOT_RESUPPLY);
	add("self-destruct", (void*)ObjectOrder::OOT_SELF_DESTRUCT);
	add("stop", (void*)ObjectOrder::OOT_STOP);
}

//------------------------------------------------------------------------------
