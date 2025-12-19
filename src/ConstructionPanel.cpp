
//------------------------------------------------------------------------------
// ConstructionPanel.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ConstructionPanel.h"
#include "Core.h"
#include "Gui.h"
#include "ObjectDescManagerTemp.h"
#include "PartDescManagerT.h"

//------------------------------------------------------------------------------

void ConstructionPanel::init() {

	// Ogre

	m_sceneManager = Core::getSingletonPtr()->getRoot()->createSceneManager(
			ST_EXTERIOR_CLOSE, "ConstructionPanel/SceneManager");

	m_camera = m_sceneManager->createCamera("ConstructionPanel/Camera");

	m_camera->setPosition(10, 10, 10);
	m_camera->lookAt(0, 0, 0);
	m_camera->setNearClipDistance(0.5f);
	m_camera->setFarClipDistance(64.0f);
	m_camera->setAspectRatio(1.0f);

	RenderTexture* ogreTexture =
		Core::getSingletonPtr()->getRoot()->getRenderSystem()->createRenderTexture(
			"RenderToTexure", 512, 512, TEX_TYPE_2D, PF_R8G8B8);

	m_viewport = ogreTexture->addViewport(m_camera);
	m_viewport->setClearEveryFrame(true);

	CEGUI::Texture* ceguiTexture =
		Gui::getSingletonPtr()->getRenderer()->createTexture(
			"RenderToTexure");

	CEGUI::Imageset* imageSet =
		CEGUI::ImagesetManager::getSingleton().createImageset(
			"Imageset", ceguiTexture);

	imageSet->defineImage("Image",
		CEGUI::Point(0.0f, 0.0f),
		CEGUI::Size(ceguiTexture->getWidth(), ceguiTexture->getHeight()),
		CEGUI::Point(0.0f, 0.0f));

	m_bodyNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();
	m_weaponNode = m_bodyNode->createChildSceneNode();


	// CEGUI

	m_constructionPanel = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel");
	m_name = (CEGUI::Editbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/Name");
	m_objectDescList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/ObjectDescList");
	m_viewer = (CEGUI::StaticImage*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/Viewer");
	m_armourList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/ArmourList");
	m_bodyList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/BodyList");
	m_engineList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/EngineList");
	m_explosiveList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/ExplosiveList");
	m_powerReactorList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/PowerReactorList");
	m_weaponList = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/WeaponList");
	m_add = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/Add");
	m_rot = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/Change");
	m_remove = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/Remove");
	m_close = (CEGUI::PushButton*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("ConstructionPanel/Close");

	m_constructionPanel->subscribeEvent(
		CEGUI::FrameWindow::EventShown,
		CEGUI::Event::Subscriber(&ConstructionPanel::constructionPanel_Shown, this));
	m_constructionPanel->subscribeEvent(
		CEGUI::FrameWindow::EventHidden,
		CEGUI::Event::Subscriber(&ConstructionPanel::constructionPanel_Hidden, this));
	m_objectDescList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&ConstructionPanel::objectDescList_SelectionChanged, this));
	m_bodyList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&ConstructionPanel::bodyList_SelectionChanged, this));
	m_weaponList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&ConstructionPanel::weaponList_SelectionChanged, this));
	m_add->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&ConstructionPanel::add_MouseClicked, this));
	m_rot->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&ConstructionPanel::change_MouseClicked, this));
	m_remove->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&ConstructionPanel::remove_MouseClicked, this));
	m_close->subscribeEvent(
		CEGUI::PushButton::EventMouseClick,
		CEGUI::Event::Subscriber(&ConstructionPanel::close_MouseClicked, this));

	m_constructionPanel->setCaptionColour(CEGUI::colour(1.0f, 1.0f, 1.0f));
	m_viewer->setImage(&imageSet->getImage("Image"));
}

//------------------------------------------------------------------------------

bool ConstructionPanel::constructionPanel_Shown(const CEGUI::EventArgs& e) {

	Core::getSingletonPtr()->m_gameSpeed = 0.0f;

	static CEGUI::ListboxTextItem* item = NULL;

	m_objectDescList->resetList();

	for (ObjectDescManagerTemp::Iterator itr = ObjectDescManagerTemp::getSingletonPtr()->getFirst(); itr != ObjectDescManagerTemp::getSingletonPtr()->getLast(); itr++) {	

		item = new CEGUI::ListboxTextItem((*itr)->m_name);

		item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
		item->setUserData(*itr);

		m_objectDescList->addItem(item);
	}

	m_armourList->resetList();
	m_bodyList->resetList();
	m_engineList->resetList();
	m_explosiveList->resetList();
	m_powerReactorList->resetList();
	m_weaponList->resetList();

	for (PartDescManagerTemp::Iterator itr = PartDescManagerTemp::getSingletonPtr()->getFirst(); itr != PartDescManagerTemp::getSingletonPtr()->getLast(); itr++) {

		item = new CEGUI::ListboxTextItem((*itr)->m_name);

		item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
		item->setUserData(*itr);
		item->setTooltipText((*itr)->toString());

		switch ((*itr)->m_type) {

			case PartDesc::PDT_ARMOUR_DESC:			m_armourList->addItem(item);		break;
			case PartDesc::PDT_BODY_DESC:			m_bodyList->addItem(item);			break;
			case PartDesc::PDT_ENGINE_DESC:			m_engineList->addItem(item);		break;
			case PartDesc::PDT_EXPLOSIVE_DESC:		m_explosiveList->addItem(item);		break;
			case PartDesc::PDT_POWER_REACTOR_DESC:	m_powerReactorList->addItem(item);	break;
			case PartDesc::PDT_WEAPON_DESC:			m_weaponList->addItem(item);		break;
		}
	}

	return true;
}

//------------------------------------------------------------------------------

bool ConstructionPanel::constructionPanel_Hidden(const CEGUI::EventArgs& e) {

	Core::getSingletonPtr()->m_gameSpeed = 1.0f;

	m_name->setText("");

	m_sceneManager->destroyAllEntities();

	m_bodyEnt = NULL;
	m_weaponEnt = NULL;

	return true;
}

//------------------------------------------------------------------------------

bool ConstructionPanel::objectDescList_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_objectDescList->getSelectedCount()) {

		m_name->setText(m_objectDescList->getFirstSelectedItem()->getText());

		static ObjectDesc* objectDesc = NULL;

		objectDesc = (ObjectDesc*)m_objectDescList->getFirstSelectedItem()->getUserData();

		// Select an armour.

		if (objectDesc->hasPartDesc(PartDesc::PDT_ARMOUR_DESC))

			for (size_t i = 0; i < m_armourList->getItemCount(); i++) {

				if (m_armourList->getListboxItemFromIndex(i)->getUserData() == ((BuildingDesc*)objectDesc)->m_armourDesc) {

					m_armourList->setEnabled(true);
					m_armourList->clearAllSelections();
					m_armourList->getListboxItemFromIndex(i)->setSelected(true);
					m_armourList->activate();
					
					break;
				}

			}

		// Select a body.

		for (size_t i = 0; i < m_bodyList->getItemCount(); i++) {

			if (m_bodyList->getListboxItemFromIndex(i)->getUserData() == objectDesc->m_bodyDesc) {

				m_bodyList->setEnabled(true);
				m_bodyList->clearAllSelections();
				m_bodyList->getListboxItemFromIndex(i)->setSelected(true);
				m_bodyList->activate();

				break;
			}
		}
	}

	return true;
}

//------------------------------------------------------------------------------

bool ConstructionPanel::bodyList_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_bodyEnt) {

		m_bodyNode->detachObject(m_bodyEnt);
		m_sceneManager->destroyEntity(m_bodyEnt);
		m_bodyEnt = NULL;
	}

	if (m_bodyList->getSelectedCount()) {

		static BodyDesc* bodyDesc = NULL;
		
		bodyDesc = (BodyDesc*)m_bodyList->getFirstSelectedItem()->getUserData();

		m_bodyEnt = m_sceneManager->createEntity(
			Core::getSingletonPtr()->getDataCounterStr(),
			bodyDesc->m_meshName);

		m_bodyNode->attachObject(m_bodyEnt);

		if (bodyDesc->m_armourType == AT_NONE)
			
			m_armourList->clearAllSelections();

		if (bodyDesc->m_engineType == ET_NONE)
			
			m_engineList->clearAllSelections();

		if (bodyDesc->m_powerReactorType == PRT_NONE)
			
			m_powerReactorList->clearAllSelections();

		if (bodyDesc->m_weaponType == WT_NONE) {

			m_weaponList->clearAllSelections();

			if (m_weaponEnt) {

				m_weaponNode->detachObject(m_weaponEnt);
				m_sceneManager->destroyEntity(m_weaponEnt);
				m_weaponEnt = NULL;
			}
		}

		if (m_weaponEnt)

			m_weaponNode->setPosition(Vector3(
					0.0f,
					m_bodyEnt->getBoundingBox().getMaximum().y - m_bodyEnt->getBoundingBox().getMinimum().y,
					0.0f));

	}

	return true;
}

//------------------------------------------------------------------------------

bool ConstructionPanel::weaponList_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_weaponEnt) {

		m_weaponNode->detachObject(m_weaponEnt);
		m_sceneManager->destroyEntity(m_weaponEnt);
		m_weaponEnt = NULL;
	}

	if (m_weaponList->getSelectedCount()) {

		m_weaponEnt = m_sceneManager->createEntity(
			Core::getSingletonPtr()->getDataCounterStr(),
			((WeaponDesc*)m_weaponList->getFirstSelectedItem()->getUserData())->m_meshName);

		m_weaponNode->attachObject(m_weaponEnt);

		if (m_bodyEnt)

			m_weaponNode->setPosition(
				Vector3(
					0.0f,
					m_bodyEnt->getBoundingBox().getMaximum().y - m_bodyEnt->getBoundingBox().getMinimum().y,
					0.0f));

		else 

			m_weaponNode->setPosition(Vector3::ZERO);

	}

	return true;
}

//------------------------------------------------------------------------------

bool ConstructionPanel::add_MouseClicked(const CEGUI::EventArgs& e) {

	if (m_objectDescList->getSelectedCount())

		m_objectDescList->getFirstSelectedItem()->setSelected(false);

	if (m_name->getText().length() == 0)

		m_name->setText("ObjectDesc #" + Core::getSingletonPtr()->getDataCounterStr());

	ObjectDesc* objectDesc = new ObjectDesc(m_name->getText().c_str(), NULL);
	ObjectDescManagerTemp::getSingletonPtr()->add(objectDesc);

	CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(m_name->getText());
	item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
	item->setUserData(objectDesc);
	m_objectDescList->addItem(item);

	m_name->setText("");

	return true;
}

//------------------------------------------------------------------------------

bool ConstructionPanel::change_MouseClicked(const CEGUI::EventArgs& e) {

	if (m_objectDescList->getSelectedCount()) {

		m_objectDescList->getFirstSelectedItem()->setText(m_name->getText());
		m_objectDescList->activate();

		ObjectDesc* objectDesc = (ObjectDesc*)m_objectDescList->getFirstSelectedItem()->getUserData();

		objectDesc->m_name = m_name->getText().c_str();

		switch (objectDesc->m_type) {

			case ObjectDesc::ODT_BUILDING_DESC:

				break;

			case ObjectDesc::ODT_FORTIFICATION_DESC:

				break;

			case ObjectDesc::ODT_POWER_PLANT_DESC:

				break;

			case ObjectDesc::ODT_VEHICLE_DESC:

				break;

		}
	}

	return true;
}

//------------------------------------------------------------------------------

bool ConstructionPanel::remove_MouseClicked(const CEGUI::EventArgs& e) {

	if (m_objectDescList->getSelectedCount()) {

		ObjectDescManagerTemp::getSingletonPtr()->destroy
			((ObjectDesc*)m_objectDescList->getFirstSelectedItem()->getUserData());

		m_objectDescList->removeItem(m_objectDescList->getFirstSelectedItem());

	}

	return true;
}

//------------------------------------------------------------------------------

bool ConstructionPanel::close_MouseClicked(const CEGUI::EventArgs& e) {

	m_constructionPanel->setVisible(false);

	return true;
}

//------------------------------------------------------------------------------
