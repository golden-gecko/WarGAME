
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "OrderMenu.h"

#include "Core.h"
#include "Object.h"
#include "ObjectDescManager.h"

//------------------------------------------------------------------------------

bool OrderMenu::orderMenu_MouseButtonUp(const CEGUI::EventArgs& e) {

	switch (static_cast<const CEGUI::MouseEventArgs&>(e).button) {

		case CEGUI::RightButton:
 
			if (m_orderMenu->getSelectedCount()) {

				switch ((int)m_orderMenu->getFirstSelectedItem()->getUserData()) {

					case ObjectOrder::OOT_ATTACK_POSITION:
					case ObjectOrder::OOT_MOVE_TO_POSITION:
					case ObjectOrder::OOT_PATROL:

						if (Core::getSingletonPtr()->m_positionSelectedByRightClick != Ogre::Vector3(-1.0f))

							Core::getSingletonPtr()->m_selected.front()->order(ObjectOrder(
								ObjectOrder::ObjectOrderType((int)m_orderMenu->getFirstSelectedItem()->getUserData()),
								Core::getSingletonPtr()->m_positionSelectedByRightClick));

						break;

					case ObjectOrder::OOT_ATTACK_OBJECT:
					case ObjectOrder::OOT_FOLLOW:
					case ObjectOrder::OOT_MOVE_TO_OBJECT:
					case ObjectOrder::OOT_REPAIR:
					case ObjectOrder::OOT_RESUPPLY:

						if (Core::getSingletonPtr()->m_objectSelectedByRightClick)

							Core::getSingletonPtr()->m_selected.front()->order(ObjectOrder(
								ObjectOrder::ObjectOrderType((int)m_orderMenu->getFirstSelectedItem()->getUserData()),
								Ogre::Vector3::ZERO,
								Core::getSingletonPtr()->m_objectSelectedByRightClick));

						break;

					case ObjectOrder::OOT_SELF_DESTRUCT:
					case ObjectOrder::OOT_STOP:

						Core::getSingletonPtr()->m_selected.front()->order(ObjectOrder(
							ObjectOrder::ObjectOrderType((int)m_orderMenu->getFirstSelectedItem()->getUserData())));

						break;
				}
			}

			setVisible(false);

			break;
	}

	return true;
}

//------------------------------------------------------------------------------

bool OrderMenu::orderMenu_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_orderMenu->getSelectedCount()) {

		switch ((int)m_orderMenu->getFirstSelectedItem()->getUserData()) {

			case ObjectOrder::OOT_CONSTRUCT:

				m_constructionMenu->resetList();
				m_constructionMenu->setPosition(
					CEGUI::Point(
						m_orderMenu->getXPosition() + m_orderMenu->getWidth(),
						m_orderMenu->getYPosition()
					)
				);
				m_constructionMenu->setVisible(true);

				for (ObjectDescManager::Iterator itr = ObjectDescManager::getSingletonPtr()->Begin(); itr != ObjectDescManager::getSingletonPtr()->End(); itr++)

					add(m_constructionMenu, (*itr)->getName(), (*itr));

				break;

			default:

				m_constructionMenu->setVisible(false);

				break;
		}
	}

	return true;
}

//------------------------------------------------------------------------------

bool OrderMenu::mouseMove(const CEGUI::EventArgs& e) {

	CEGUI::System::getSingletonPtr()->injectMouseButtonDown(CEGUI::LeftButton);

	return true;
}

//------------------------------------------------------------------------------

bool OrderMenu::constructionMenu_MouseButtonUp(const CEGUI::EventArgs& e) {

	if (m_constructionMenu->getSelectedCount())

		Core::getSingletonPtr()->m_objectSelectedByRightClick->order(ObjectOrder(
			ObjectOrder::OOT_CONSTRUCT,
			Ogre::Vector3::ZERO,
			(ObjectDesc*)m_constructionMenu->getFirstSelectedItem()->getUserData()));

	m_orderMenu->setVisible(false);
	m_constructionMenu->setVisible(false);

	return true;
}

//------------------------------------------------------------------------------

void OrderMenu::init() {

	m_orderMenu = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("OrderMenu");
	m_constructionMenu = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionMenu");

	m_orderMenu->subscribeEvent(
		CEGUI::Listbox::EventMouseMove,
		CEGUI::Event::Subscriber(&OrderMenu::mouseMove, this));
	m_constructionMenu->subscribeEvent(
		CEGUI::Listbox::EventMouseMove,
		CEGUI::Event::Subscriber(&OrderMenu::mouseMove, this));

	m_orderMenu->subscribeEvent(
		CEGUI::Listbox::EventMouseButtonUp,
		CEGUI::Event::Subscriber(&OrderMenu::orderMenu_MouseButtonUp, this));
	m_orderMenu->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&OrderMenu::orderMenu_SelectionChanged, this));

	m_constructionMenu->subscribeEvent(
		CEGUI::Listbox::EventMouseButtonUp,
		CEGUI::Event::Subscriber(&OrderMenu::constructionMenu_MouseButtonUp, this));

	add(m_orderMenu, "attack object", (void*)ObjectOrder::OOT_ATTACK_OBJECT);
	add(m_orderMenu, "attack position", (void*)ObjectOrder::OOT_ATTACK_POSITION);
	add(m_orderMenu, "construct", (void*)ObjectOrder::OOT_CONSTRUCT);
	add(m_orderMenu, "follow", (void*)ObjectOrder::OOT_FOLLOW);
	add(m_orderMenu, "move to object", (void*)ObjectOrder::OOT_MOVE_TO_OBJECT);
	add(m_orderMenu, "move to position", (void*)ObjectOrder::OOT_MOVE_TO_POSITION);
	add(m_orderMenu, "patrol", (void*)ObjectOrder::OOT_PATROL);
	add(m_orderMenu, "repair", (void*)ObjectOrder::OOT_REPAIR);
	add(m_orderMenu, "ressuply", (void*)ObjectOrder::OOT_RESUPPLY);
	add(m_orderMenu, "self-destruct", (void*)ObjectOrder::OOT_SELF_DESTRUCT);
	add(m_orderMenu, "stop", (void*)ObjectOrder::OOT_STOP);
	add(m_orderMenu, "cancel", NULL);
}

//------------------------------------------------------------------------------
