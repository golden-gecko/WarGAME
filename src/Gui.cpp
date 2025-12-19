
//------------------------------------------------------------------------------
// Gui.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"
#include "Gui.h"

#include "EventManager.h"
#include "PartDescManager.h"
#include "ObjectManager.h"
#include "ObjectDescManager.h"
#include "PlayerManager.h"
#include "SoundManager.h"

//------------------------------------------------------------------------------

bool Gui::init(){

	// Setup Ogre CEGUI Renderer and CEGUI system.

	m_renderer = new CEGUI::OgreCEGUIRenderer(
		Core::getSingletonPtr()->getRenderWindow(),
		RENDER_QUEUE_OVERLAY,
		false,
		3000,
		Core::getSingletonPtr()->getSceneManager());

	m_system = new CEGUI::System(m_renderer);


	// Load scheme and setup defaults.

	CEGUI::SchemeManager::getSingleton().loadScheme("TaharezLook.scheme");

	m_system->setDefaultMouseCursor("TaharezLook", "MouseArrow");
	m_system->setDefaultFont("BlueHighway-10");


	// Load layout and setup defaults.

	m_system->setGUISheet(
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("Gui.xml"));

	m_system->getGUISheet()->setAlpha(0.75f);


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
		"Player"
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

		if (itr.getCurrentValue() != m_system->getGUISheet()) {

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


	return true;

}

//------------------------------------------------------------------------------

bool Gui::mouseEntersLeaves(const CEGUI::EventArgs& e){

	m_mouseOverGui = !m_mouseOverGui;

	return true;

}

//------------------------------------------------------------------------------

bool Gui::type_SelectionChanged(const CEGUI::EventArgs& e){

	m_list->resetList();
	m_text->setText("");

	CEGUI::ListboxTextItem* item = NULL;

	if (m_type->getSelectedCount()) {

		if (m_type->getFirstSelectedItem()->getText() == "PartDescs")

			for (PartDescManager::Iterator itr = PartDescManager::getSingletonPtr()->getFirst(); itr != PartDescManager::getSingletonPtr()->getLast(); itr++) {

				item = new CEGUI::ListboxTextItem((*itr)->m_name);

				item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
				item->setUserData(*itr);

				m_list->addItem(item);

			}

		else if (m_type->getFirstSelectedItem()->getText() == "ObjectDescs")

			;

		else if (m_type->getFirstSelectedItem()->getText() == "Objects")

			for (ObjectManager::Iterator itr = ObjectManager::getSingletonPtr()->getFirst(); itr != ObjectManager::getSingletonPtr()->getLast(); itr++) {

				item = new CEGUI::ListboxTextItem((*itr)->m_name);

				item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
				item->setUserData(*itr);

				m_list->addItem(item);

			}

		else if (m_type->getFirstSelectedItem()->getText() == "Players")

			for (PlayerManager::Iterator itr = PlayerManager::getSingletonPtr()->getFirst(); itr != PlayerManager::getSingletonPtr()->getLast(); itr++) {

				item = new CEGUI::ListboxTextItem((*itr)->getName());

				item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
				item->setUserData(*itr);

				m_list->addItem(item);

			}

	}

	return true;

}

//------------------------------------------------------------------------------

bool Gui::list_SelectionChanged(const CEGUI::EventArgs& e){

	m_text->setText("");

	if (m_list->getSelectedCount()) {

		if (m_type->getFirstSelectedItem()->getText() == "PartDescs")

			m_text->setText(((PartDesc*)m_list->getFirstSelectedItem()->getUserData())->toString());

		else if (m_type->getFirstSelectedItem()->getText() == "ObjectDescs")

			;

		else if (m_type->getFirstSelectedItem()->getText() == "Objects")

			m_text->setText(((Object*)m_list->getFirstSelectedItem()->getUserData())->toString());

		else if (m_type->getFirstSelectedItem()->getText() == "Players")

			m_text->setText(((Player*)m_list->getFirstSelectedItem()->getUserData())->toString());

	}

	return true;

}

//------------------------------------------------------------------------------

bool Gui::objectList_SelectionChanged(const CEGUI::EventArgs& e){

	if (m_objectList->getSelectedCount())

		m_objectText->setText(((Object*)m_objectList->getFirstSelectedItem()->getUserData())->toString());

	else

		m_objectText->setText("");

	return true;

}

//------------------------------------------------------------------------------

bool Gui::objectDescList_SelectionChanged(const CEGUI::EventArgs& e){

	if (m_objectDescList->getSelectedCount())

		m_objectDescText->setText(((ObjectDesc*)m_objectDescList->getFirstSelectedItem()->getUserData())->toString());

	else

		m_objectDescText->setText("");

	return true;

}

//------------------------------------------------------------------------------

bool Gui::partDescList_SelectionChanged(const CEGUI::EventArgs& e){

	if (m_partDescList->getSelectedCount())

		m_partDescText->setText(((PartDesc*)m_partDescList->getFirstSelectedItem()->getUserData())->toString());

	else

		m_partDescText->setText("");

	return true;

}

//------------------------------------------------------------------------------

void Gui::setObjectViewerVisible(bool visible){

	if (visible) {

		m_objectList->resetList();

		CEGUI::ListboxTextItem* item = NULL;

		for (ObjectManager::Iterator itr = ObjectManager::getSingletonPtr()->getFirst(); itr != ObjectManager::getSingletonPtr()->getLast(); itr++) {

			item = new CEGUI::ListboxTextItem((*itr)->m_name);

			item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
			item->setUserData(*itr);

			m_objectList->addItem(item);

		}

	}

	m_objectViewer->setVisible(visible);

}

//------------------------------------------------------------------------------

void Gui::setObjectDescViewerVisible(bool visible){

	if (visible) {

		m_objectDescList->resetList();

		CEGUI::ListboxTextItem* item = NULL;

		for (ObjectDescManager::Iterator itr = ObjectDescManager::getSingletonPtr()->getFirst(); itr != ObjectDescManager::getSingletonPtr()->getLast(); itr++) {

			item = new CEGUI::ListboxTextItem((*itr)->m_name);

			item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
			item->setUserData(*itr);

			m_objectDescList->addItem(item);

		}

	}

	m_objectDescViewer->setVisible(visible);

}

//------------------------------------------------------------------------------

void Gui::setPartDescViewerVisible(bool visible){

	if (visible) {

		m_partDescList->resetList();

		CEGUI::ListboxTextItem* item = NULL;

		for (PartDescManager::Iterator itr = PartDescManager::getSingletonPtr()->getFirst(); itr != PartDescManager::getSingletonPtr()->getLast(); itr++) {

			item = new CEGUI::ListboxTextItem((*itr)->m_name);

			item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
			item->setUserData(*itr);

			m_partDescList->addItem(item);

		}

	}

	m_partDescViewer->setVisible(visible);

}

//------------------------------------------------------------------------------

void Gui::changeObjectViewerVisible(){

	setObjectViewerVisible(!m_objectViewer->isVisible());

}

//------------------------------------------------------------------------------

void Gui::changeObjectDescViewerVisible(){

	setObjectDescViewerVisible(!m_objectDescViewer->isVisible());

}

//------------------------------------------------------------------------------

void Gui::changePartDescViewerVisible(){

	setPartDescViewerVisible(!m_partDescViewer->isVisible());

}

//------------------------------------------------------------------------------

void Gui::updateGameInfo(){

	static char text[512];

	sprintf(text,"\
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

	m_gameInfoText->setText(text);

}

//------------------------------------------------------------------------------

void Gui::updateObjectInfo(Object* object){

	m_objectInfoOrderList->resetList();

	if (object) {

		m_objectInfoText->setText(object->toString());

		if (object->m_orderList.getCount())

			for (ObjectOrderList::Iterator itr = object->m_orderList.getFirst(); itr != object->m_orderList.getLast(); itr++) {

				static CEGUI::ListboxTextItem* item = NULL;

				item = new CEGUI::ListboxTextItem((*itr).toString());
				item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");

				m_objectInfoOrderList->addItem(item);

			}

	} else

		m_objectInfoText->setText("No Object");

}

//------------------------------------------------------------------------------

void Gui::updateViewer(){

	if (m_viewer->isVisible() && m_type->getSelectedCount() && m_list->getSelectedCount())

		if (m_type->getFirstSelectedItem()->getText() == "Objects")

			m_text->setText(((Object*)m_list->getFirstSelectedItem()->getUserData())->toString());

		else if (m_type->getFirstSelectedItem()->getText() == "Players")

			m_text->setText(((Player*)m_list->getFirstSelectedItem()->getUserData())->toString());

}

//------------------------------------------------------------------------------
