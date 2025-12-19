
//------------------------------------------------------------------------------
// Gui.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Gui.h"

#include "EventManager.h"
#include "PartDescManagerT.h"
#include "ObjectManagerTemp.h"
#include "ObjectDescManagerTemp.h"
#include "PlayerManager.h"
#include "SoundManagerTemp.h"

//------------------------------------------------------------------------------

bool Gui::init() {

	// Setup Ogre CEGUI Renderer and CEGUI system.

	m_renderer = new CEGUI::OgreCEGUIRenderer(
		Core::getSingletonPtr()->getRenderWindow(),
		RENDER_QUEUE_OVERLAY,
		false,
		3000,
		Core::getSingletonPtr()->getSceneManager());

	m_system = new CEGUI::System(m_renderer);


	// Load scheme and setup defaults.

	CEGUI::SchemeManager::getSingletonPtr()->loadScheme("TaharezLook.scheme");

	m_system->setDefaultMouseCursor("TaharezLook", "MouseArrow");
	m_system->setDefaultFont("BlueHighway-10");


	// Load layout and setup defaults.

	m_system->setGUISheet(
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Gui.xml"));


	// Find and setup controls.

	m_viewer = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Viewer");
	m_type = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Type");
	m_list = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("List");
	m_text = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Text");

	m_type->setSortingEnabled(true);
	m_list->setSortingEnabled(true);

	string captions[5] = {
		"Events",
		"ObjectDescs",
		"Objects",
		"PartDescs",
		"Players"
	};

	CEGUI::ListboxTextItem* item = NULL;

	for (int i = 0; i < 5; i++) {

		item = new CEGUI::ListboxTextItem(captions[i]);

		item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");

		m_type->addItem(item);

	}

	m_gameInfo = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("GameInfo");
	m_gameInfoText = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("GameInfoText");

	m_objectInfo = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectInfo");
	m_objectInfoText = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectInfoText");
	m_objectInfoOrderList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectInfoOrderList");

	m_viewer = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Viewer");

	m_objectViewer = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectViewer");
	m_objectList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectList");
	m_objectText = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectText");

	m_objectDescViewer = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectDescViewer");
	m_objectDescList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectDescList");
	m_objectDescText = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectDescText");

	m_partDescViewer = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartDescViewer");
	m_partDescList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartDescList");
	m_partDescText = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartDescText");


	// Subscribe events.

	CEGUI::WindowManager::WindowIterator itr = CEGUI::WindowManager::getSingletonPtr()->getIterator();

	itr.toStart();

	while (itr.isAtEnd() == false) {

		if ((itr.getCurrentValue() != m_system->getGUISheet()) && (itr.getCurrentValue() != m_objectInfoText)) {

			itr.getCurrentValue()->subscribeEvent(
				CEGUI::Window::EventMouseEnters,
				CEGUI::Event::Subscriber(&Gui::mouseEntersLeaves, this));

			itr.getCurrentValue()->subscribeEvent(
				CEGUI::Window::EventMouseLeaves,
				CEGUI::Event::Subscriber(&Gui::mouseEntersLeaves, this));
		}

		itr++;
	}


	m_type->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&Gui::type_SelectionChanged, this));
	m_list->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&Gui::list_SelectionChanged, this));

	m_objectList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&Gui::objectList_SelectionChanged, this));

	m_objectDescList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&Gui::objectDescList_SelectionChanged, this));
	m_partDescList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&Gui::partDescList_SelectionChanged, this));

	m_objectDescList->subscribeEvent(
		CEGUI::Listbox::EventMouseDoubleClick,
		CEGUI::Event::Subscriber(&Gui::objectDescList_MouseDoubleClick, this));
	m_objectInfoText->subscribeEvent(
		CEGUI::StaticText::EventMouseDoubleClick,
		CEGUI::Event::Subscriber(&Gui::objectInfoText_MouseDoubleClick, this));

	m_objectMultiList = (CEGUI::MultiColumnList*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectMultiList");

	m_objectMultiList->setVisible(false);

	m_objectMultiList->setSelectionMode(CEGUI::MultiColumnList::RowSingle);

	m_objectMultiList->addColumn("Name",	0, 0.3f);
	m_objectMultiList->addColumn("Type",	1, 0.3f);
	m_objectMultiList->addColumn("HP",		2, 0.3f);
	m_objectMultiList->addColumn("Max HP",	3, 0.3f);

	return true;
}

//------------------------------------------------------------------------------

bool Gui::objectInfoText_MouseDoubleClick(const CEGUI::EventArgs& e) {

	return true;
}

//------------------------------------------------------------------------------

bool Gui::mouseEntersLeaves(const CEGUI::EventArgs& e) {

	m_mouseOverGui = !m_mouseOverGui;

	return true;

}

//------------------------------------------------------------------------------

bool Gui::type_SelectionChanged(const CEGUI::EventArgs& e) {

	m_list->resetList();
	m_text->setText("");

	CEGUI::ListboxTextItem* item = NULL;

	if (m_type->getSelectedCount()) {

		if (m_type->getFirstSelectedItem()->getText() == "PartDescs")

			for (PartDescManagerTemp::Iterator itr = PartDescManagerTemp::getSingletonPtr()->getFirst(); itr != PartDescManagerTemp::getSingletonPtr()->getLast(); itr++) {

				item = new CEGUI::ListboxTextItem((*itr)->m_name);

				item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
				item->setUserData(*itr);

				m_list->addItem(item);

			}

		else if (m_type->getFirstSelectedItem()->getText() == "ObjectDescs")

			;

		else if (m_type->getFirstSelectedItem()->getText() == "Objects")

			for (ObjectManagerTemp::Iterator itr = ObjectManagerTemp::getSingletonPtr()->getFirst(); itr != ObjectManagerTemp::getSingletonPtr()->getLast(); itr++) {

				item = new CEGUI::ListboxTextItem((*itr)->m_name);

				item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
				item->setUserData(*itr);

				m_list->addItem(item);

			}

		else if (m_type->getFirstSelectedItem()->getText() == "Players") {

			for (PlayerManager::Iterator itr = PlayerManager::getSingletonPtr()->Begin(); itr != PlayerManager::getSingletonPtr()->End(); itr++) {

				item = new CEGUI::ListboxTextItem((*itr)->getName());

				item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
				item->setUserData(*itr);

				m_list->addItem(item);
			}
		}
	}

	return true;
}

//------------------------------------------------------------------------------

bool Gui::list_SelectionChanged(const CEGUI::EventArgs& e) {

	m_text->setText("");

	if (m_list->getSelectedCount()) {

		if (m_type->getFirstSelectedItem()->getText() == "PartDescs")

			m_text->setText(((PartDesc*)m_list->getFirstSelectedItem()->getUserData())->toString());

		else if (m_type->getFirstSelectedItem()->getText() == "ObjectDescs")

			;

		else if (m_type->getFirstSelectedItem()->getText() == "Objects")

			m_text->setText(((ObjectTemp*)m_list->getFirstSelectedItem()->getUserData())->toString());

		else if (m_type->getFirstSelectedItem()->getText() == "Players")

			m_text->setText(((Player*)m_list->getFirstSelectedItem()->getUserData())->toString());

	}

	return true;

}

//------------------------------------------------------------------------------

bool Gui::objectList_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_objectList->getSelectedCount())

		m_objectText->setText(((ObjectTemp*)m_objectList->getFirstSelectedItem()->getUserData())->toString());

	else

		m_objectText->setText("");

	return true;

}

//------------------------------------------------------------------------------

bool Gui::objectDescList_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_objectDescList->getSelectedCount())

		m_objectDescText->setText(((ObjectDesc*)m_objectDescList->getFirstSelectedItem()->getUserData())->toString());

	else

		m_objectDescText->setText("");

	return true;

}

//------------------------------------------------------------------------------

bool Gui::partDescList_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_partDescList->getSelectedCount()) {

		m_partDescText->setText(((PartDesc*)m_partDescList->getFirstSelectedItem()->getUserData())->toString());

	} else

		m_partDescText->setText("");

	return true;

}

//------------------------------------------------------------------------------

bool Gui::objectDescList_MouseDoubleClick(const CEGUI::EventArgs& e) {

	if (m_objectDescList->getSelectedCount()) {

		m_objectDescViewer->setVisible(false);

		Core::getSingletonPtr()->m_state = Core::SELECT_PLACE_FOR_OBJECT;

	}

	return true;

}

//------------------------------------------------------------------------------

void Gui::setViewerVisible(bool visible) {

	m_viewer->setVisible(visible);

}

//------------------------------------------------------------------------------

void Gui::setObjectViewerVisible(bool visible) {

	/*
	m_objectMultiList->setVisible(visible);
	m_objectMultiList->resetList();

	for (ObjectManagerTemp::Iterator itr = ObjectManagerTemp::getSingletonPtr()->getFirst(); itr != ObjectManagerTemp::getSingletonPtr()->getLast(); itr++) {

		static CEGUI::ListboxTextItem* item = NULL;

		item = new CEGUI::ListboxTextItem((*itr)->m_name);
		item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
		item->setUserData(*itr);
	}
	//*/

	if (visible) {

		m_objectViewer->activate();
		m_objectList->resetList();

		CEGUI::ListboxTextItem* item = NULL;

		for (ObjectManagerTemp::Iterator itr = ObjectManagerTemp::getSingletonPtr()->getFirst(); itr != ObjectManagerTemp::getSingletonPtr()->getLast(); itr++) {
			item = new CEGUI::ListboxTextItem((*itr)->m_name);

			item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
			item->setUserData(*itr);

			m_objectList->addItem(item);
		}
	}

	m_objectViewer->setVisible(visible);
}

//------------------------------------------------------------------------------

void Gui::setObjectDescViewerVisible(bool visible) {

	if (visible) {

		m_objectDescViewer->activate();

		m_objectDescList->resetList();

		CEGUI::ListboxTextItem* item = NULL;

		for (ObjectDescManagerTemp::Iterator itr = ObjectDescManagerTemp::getSingletonPtr()->getFirst(); itr != ObjectDescManagerTemp::getSingletonPtr()->getLast(); itr++) {
			item = new CEGUI::ListboxTextItem((*itr)->m_name);

			item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
			item->setUserData(*itr);

			m_objectDescList->addItem(item);
		}
	}

	m_objectDescViewer->setVisible(visible);

}

//------------------------------------------------------------------------------

void Gui::setPartDescViewerVisible(bool visible) {

	if (visible) {

		m_partDescViewer->activate();
		m_partDescList->resetList();

		CEGUI::ListboxTextItem* item = NULL;

		for (PartDescManagerTemp::Iterator itr = PartDescManagerTemp::getSingletonPtr()->getFirst(); itr != PartDescManagerTemp::getSingletonPtr()->getLast(); itr++) {
			item = new CEGUI::ListboxTextItem((*itr)->m_name);

			item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
			item->setUserData(*itr);

			m_partDescList->addItem(item);
		}
	}

	m_partDescViewer->setVisible(visible);
}

//------------------------------------------------------------------------------

void Gui::changeViewerVisible() {

	setViewerVisible(!m_viewer->isVisible());
}

//------------------------------------------------------------------------------

void Gui::changeObjectViewerVisible() {

	if (m_objectViewer->isVisible()) {

		if (m_objectViewer->isActive() == false)

			m_objectViewer->activate();

		else

			m_objectViewer->setVisible(false);

	} else

		setObjectViewerVisible(true);

}

//------------------------------------------------------------------------------

void Gui::changeObjectDescViewerVisible() {

	if (m_objectDescViewer->isVisible()) {

		if (m_objectDescViewer->isActive() == false)

			m_objectDescViewer->activate();

		else

			m_objectDescViewer->setVisible(false);

	} else

		setObjectDescViewerVisible(true);

}

//------------------------------------------------------------------------------

void Gui::changePartViewerVisible() {

}

//------------------------------------------------------------------------------

void Gui::changePartDescViewerVisible() {

	if (m_partDescViewer->isVisible()) {

		if (m_partDescViewer->isActive() == false)

			m_partDescViewer->activate();

		else

			m_partDescViewer->setVisible(false);

	} else

		setPartDescViewerVisible(true);

}

//------------------------------------------------------------------------------

void Gui::updateViewer()
{
	/*
	if (m_viewer->isVisible() && m_type->getSelectedCount() && m_list->getSelectedCount())

		if (m_type->getFirstSelectedItem()->getText() == "Objects")

			m_text->setText(((ObjectTemp*)m_list->getFirstSelectedItem()->getUserData())->toString());

		else if (m_type->getFirstSelectedItem()->getText() == "Players")

			m_text->setText(((Player*)m_list->getFirstSelectedItem()->getUserData())->toString());
	*/
}

//------------------------------------------------------------------------------

void Gui::updateGameInfo() {

	static char str[512];

	sprintf(str, "\
		WarGAME p r o j e c t\n\
		\n\
		FPS\n\
		  Best    %.2f\n\
		  Avarage %.2f\n\
		  Worst   %.2f\n\
		\n\
		Cursor\n\
		  2D   %.2f:%.2f\n\
		  3D   %.2f:%.2f:%.2f",
		Core::getSingletonPtr()->getRenderWindow()->getBestFPS(),
		Core::getSingletonPtr()->getRenderWindow()->getAverageFPS(),
		Core::getSingletonPtr()->getRenderWindow()->getWorstFPS(),
		Core::getSingletonPtr()->getMouse2DPos().x,
		Core::getSingletonPtr()->getMouse2DPos().y,
		Core::getSingletonPtr()->getMouse3DPos().x,
		Core::getSingletonPtr()->getMouse3DPos().y,
		Core::getSingletonPtr()->getMouse3DPos().z);

	m_gameInfoText->setText(str);

}

//------------------------------------------------------------------------------

void Gui::updateObjectInfo(ObjectTemp* object) {

	m_objectInfoOrderList->resetList();

	if (object) {

		if (object->m_player == Core::getSingletonPtr()->m_activePlayer) {

			m_objectInfoText->setText(object->toString());

			if (object->m_orderList.getCount())

				for (ObjectOrderList::Iterator itr = object->m_orderList.m_objectOrders.begin(); itr != object->m_orderList.m_objectOrders.end(); itr++) {

					static CEGUI::ListboxTextItem* item = NULL;

					item = new CEGUI::ListboxTextItem((*itr).toString());
					item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");

					m_objectInfoOrderList->addItem(item);
				}

		} else {

			m_objectInfoText->setText(object->toStringEnemy());

		}

	} else

		m_objectInfoText->setText("No ObjectTemp");

}

//------------------------------------------------------------------------------

ObjectDesc* Gui::getSelectedObjectDesc() {

	if (m_objectDescList->getSelectedCount())

		return (ObjectDesc*)m_objectDescList->getFirstSelectedItem()->getUserData();

	return NULL;

}

//------------------------------------------------------------------------------
