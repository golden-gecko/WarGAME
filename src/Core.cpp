
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Console.h"
#include "Core.h"
#include "Game.h"
#include "EffectManager.h"
#include "Gui.h"
#include "ObjectDescManager.h"
#include "ObjectDescViewer.h"
#include "ObjectInfoBar.h"
#include "ObjectManager.h"
#include "ObjectViewer.h"
#include "OrderMenu.h"
#include "PartDescManager.h"
#include "PartDescViewer.h"
#include "PartManager.h"
#include "PartViewer.h"
#include "PlayerManager.h"
#include "PlayerViewer.h"
#include "SelectionMenu.h"

//------------------------------------------------------------------------------

Core::Core()

	:	m_camera(NULL),
		m_eventProcessor(NULL),
		m_inputReader(NULL),
		m_renderWindow(NULL),
		m_root(NULL),
		m_sceneManager(NULL),
		m_viewport(NULL),
		m_objectSelectedByRightClick(NULL),
		m_positionSelectedByRightClick(Ogre::Vector3::ZERO),
		m_notQuit(true),
		m_gameSpeed(1.0f)
{
	srand(GetTickCount());

	for (int i = 0; i < 3; i++)		m_mouseButton[i] = false;
	for (int i = 0; i < 0xEE; i++)	m_keys[i] = false;
}

//------------------------------------------------------------------------------

Core::~Core() {

	if (m_eventProcessor)	delete m_eventProcessor;
	if (m_root)				delete m_root;
}

//------------------------------------------------------------------------------

bool Core::init() {

	// Root

	m_root = new Ogre::Root("Plugins.cfg", "Ogre.cfg", "Ogre.log");

	// Resources

	Ogre::ConfigFile cf;

	cf.load("Resources.cfg");

	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

	string secName, typeName, archName;

	while (seci.hasMoreElements()) {

		secName = seci.peekNextKey();

		Ogre::ConfigFile::SettingsMultiMap* settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i) {

			typeName = i->first;
			archName = i->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}
	}


	// Render Window

	Ogre::RenderSystemList* renderSystemList = m_root->getAvailableRenderers();

	for (Ogre::RenderSystemList::iterator i = renderSystemList->begin(); i != renderSystemList->end(); i++) {

		if ((*i)->getName() == "Direct3D9 Rendering Subsystem") {

			m_root->setRenderSystem((*i));

			break;
		}
	}

	m_root->initialise(false);

	m_renderWindow = m_root->createRenderWindow("WarGAME p r o j e c t", 1280, 1024, false);

	// Scene Manager

	m_sceneManager = m_root->createSceneManager(Ogre::ST_EXTERIOR_CLOSE, "MainSceneManager");
	m_sceneManager->setShadowFarDistance(512.0f);
	m_sceneManager->setShadowUseInfiniteFarPlane(false);

	// Camera

	m_camera = m_sceneManager->createCamera("PlayerCam");
	m_camera->setDirection(Ogre::Vector3::UNIT_X);
	m_camera->setPosition(200, 50, 200);
	m_camera->setNearClipDistance(0.5f);
	m_camera->setFarClipDistance(512.0f);

	m_viewport = m_renderWindow->addViewport(m_camera);

	m_camera->setAspectRatio(
		Ogre::Real(m_viewport->getActualWidth()) / Ogre::Real(m_viewport->getActualHeight()));

	Ogre::ResourceGroupManager::getSingletonPtr()->createResourceGroup("World");
	Ogre::ResourceGroupManager::getSingletonPtr()->setWorldResourceGroupName("World");
	Ogre::ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
	m_sceneManager->setWorldGeometry("Demo_Map.cfg");

	// Event Processor

	m_eventProcessor = new Ogre::EventProcessor();
	m_eventProcessor->initialise(m_renderWindow);
	m_eventProcessor->startProcessingEvents();
	m_eventProcessor->addMouseListener(this);
	m_eventProcessor->addMouseMotionListener(this);
	m_eventProcessor->addKeyListener(this);

	m_inputReader = m_eventProcessor->getInputReader();

	m_root->addFrameListener(this);

	m_viewport->setBackgroundColour(Ogre::ColourValue(0.0f, 0.5f, 0.75f));
	m_sceneManager->setFog(Ogre::FOG_LINEAR, Ogre::ColourValue(0.0f, 0.5f, 0.75f), 0.0f, 256.0f, 512.0f);

	return true;
}

//------------------------------------------------------------------------------

void Core::run() {

	// Console

	Console console;
	console.init();

	console.write("--------------------------------------------------------------------------------");
	console.write("Welcome to WarGAME 1.0 Beta");
	console.write("--------------------------------------------------------------------------------");

	// ObjectInfoBar

	ObjectInfoBar objectInfoBar;
	objectInfoBar.init();

	// SelectionMenu

	SelectionMenu selectionMenu;
	selectionMenu.init();

	// OrderMenu

	OrderMenu orderMenu;
	orderMenu.init();

	// EffectManager

	EffectManager effectManager;
	effectManager.init();

	// PartDescViewer

	PartDescViewer partDescViewer;
	partDescViewer.init();

	// PartViewer

	PartViewer partViewer;
	partViewer.init();

	// ObjectDescViewer

	ObjectDescViewer objectDescViewer;
	objectDescViewer.init();

	// ObjectViewer

	ObjectViewer objectViewer;
	objectViewer.init();

	// PlayerViewer

	PlayerViewer playerViewer;
	playerViewer.init();

	// PlayerManager

	PlayerManager playerManager;

	PlayerManager::getSingletonPtr()->create("human", "blue");
	PlayerManager::getSingletonPtr()->create("nature", "green");
	PlayerManager::getSingletonPtr()->create("ally", "yellow");
	PlayerManager::getSingletonPtr()->create("enemy", "red");

	m_activePlayer = PlayerManager::getSingletonPtr()->getByName("human");

	// PartDescManager

	PartDescManager::ArmDescManager armDescManager;
	PartDescManager::ArmourDescManager armourDescManager;
	PartDescManager::BodyDescManager bodyDescManager;
	PartDescManager::EngineDescManager engineDescManager;
	PartDescManager::ExplosiveDescManager explosiveDescManager;
	PartDescManager::ReactorDescManager reactorDescManager;
	PartDescManager::ShieldDescManager shieldDescManager;
	PartDescManager::TeleporterDescManager teleporterDescManager;
	PartDescManager::WeaponDescManager weaponDescManager;

	PartDescManager::ArmDescManager::getSingletonPtr()->create("arm", 15.0f, "armfav_weapon.mesh", 5.0f);

	PartDescManager::ArmourDescManager::getSingletonPtr()->create("armour, light", 5.0f, 15.0f);
	PartDescManager::ArmourDescManager::getSingletonPtr()->create("armour, medium", 6.0f, 30.0f);
	PartDescManager::ArmourDescManager::getSingletonPtr()->create("armour, heavy", 7.0f, 45.0f);

	PartDescManager::BodyDescManager::getSingletonPtr()->create("grass",  500.0f, "grass1.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("pyramid",  500.0f, "pyramid.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("factory",  100.0f, "armvp.mesh");
	//PartDescManager::BodyDescManager::getSingletonPtr()->create("laboratory", 100.0f, "laboratory.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("power plant, fussion", 500.0f, "power_plant_1.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("power plant, geothermal", 300.0f, "power_plant_2.mesh");
	//PartDescManager::BodyDescManager::getSingletonPtr()->create("tower, small", 50.0f, "tower_small.mesh");
	//PartDescManager::BodyDescManager::getSingletonPtr()->create("tower, medium", 70.0f, "tower_medium.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("tower, heavy", 1500.0f, "tower_heavy.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("vehicle, small", 100.0f, "vehicle_light.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("vehicle, medium", 200.0f, "vehicle_medium.mesh");
	//PartDescManager::BodyDescManager::getSingletonPtr()->create("vehicle, big", 300.0f, "vehicle_big.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("missile", 1.0f, "missile.mesh");
	PartDescManager::BodyDescManager::getSingletonPtr()->create("wall", 75.0f, "wall.mesh");

	PartDescManager::EngineDescManager::getSingletonPtr()->create("engine, small", 5.0f, 1500.0f, 200.0f);
	PartDescManager::EngineDescManager::getSingletonPtr()->create("engine, medium", 10.0f, 1800.0f, 300.0f);
	PartDescManager::EngineDescManager::getSingletonPtr()->create("engine, big", 15.0f, 2000.0f, 400.0f);

	PartDescManager::ExplosiveDescManager::getSingletonPtr()->create("explosive, light", 1.0f, 15.0f, 1.0f);
	PartDescManager::ExplosiveDescManager::getSingletonPtr()->create("explosive, medium", 1.0f, 20.0f, 3.0f);
	PartDescManager::ExplosiveDescManager::getSingletonPtr()->create("explosive, heavy", 1.0f, 40.0f, 2.0f);

	PartDescManager::ReactorDescManager::getSingletonPtr()->create("reactor, small", 10.0f, 100.0f, 10.0f);
	PartDescManager::ReactorDescManager::getSingletonPtr()->create("reactor, medium", 20.0f, 200.0f, 20.0f);
	PartDescManager::ReactorDescManager::getSingletonPtr()->create("reactor, big", 30.0f, 300.0f, 30.0f);

	PartDescManager::ShieldDescManager::getSingletonPtr()->create("shield, light", 20.0f, "energy_shield.mesh", 0.1f);
	//PartDescManager::ShieldDescManager::getSingletonPtr()->create("shield, medium", 25.0f, "shield_medium.mesh", 0.3f);
	//PartDescManager::ShieldDescManager::getSingletonPtr()->create("shield, heavy", 35.0f, "shield_heavy.mesh", 0.7f);

	PartDescManager::TeleporterDescManager::getSingletonPtr()->create("teleporter, star gate", 500.0f, "teleporter.mesh");

	PartDescManager::WeaponDescManager::getSingletonPtr()->create("weapon, light", 20.0f, "weapon_light.mesh", 3.0f, 45.0f, 180.0f, 180.0f, 100.0f, 300.0f);
	PartDescManager::WeaponDescManager::getSingletonPtr()->create("weapon, medium", 20.0f, "weapon_medium.mesh", 5.0f, 35.0f, 180.0f, 180.0f, 105.0f, 200.0f);
	//PartDescManager::WeaponDescManager::getSingletonPtr()->create("weapon, heavy", 20.0f, "armfav_weapon.mesh", 3.0f, 25.0f, 180.0f, 180.0f, 3000.0f, 100.0f);

	// PartManager

	PartManager::ArmManager armManager;
	PartManager::ArmourManager armourManager;
	PartManager::BodyManager bodyManager;
	PartManager::EngineManager engineManager;
	PartManager::ExplosiveManager explosiveManager;
	PartManager::ReactorManager reactorManager;
	PartManager::ShieldManager shieldManager;
	PartManager::TeleporterManager teleporterManager;
	PartManager::WeaponManager weaponManager;

	// ObjectDescManager

	ObjectDescManager objectDescManager;

	ObjectDescManager::getSingletonPtr()->create("grass", NULL, NULL,
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("grass"), NULL, NULL, NULL, NULL, NULL, NULL);

	ObjectDescManager::getSingletonPtr()->create("wall", NULL, NULL,
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("wall"), NULL, NULL, NULL, NULL, NULL, NULL);

	ObjectDescManager::getSingletonPtr()->create("pyramid", NULL, NULL,
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("pyramid"), NULL, NULL, NULL, NULL, NULL, NULL);

	ObjectDescManager::getSingletonPtr()->create("factory", NULL, NULL,
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("factory"), NULL, NULL, NULL, NULL, NULL, NULL);

	ObjectDescManager::getSingletonPtr()->create("laboratory", NULL, NULL,
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("laboratory"), NULL, NULL, NULL, NULL, NULL, NULL);

	ObjectDescManager::getSingletonPtr()->create("power plant, fussion", NULL, NULL,
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("power plant, fussion"), NULL, NULL,
		PartDescManager::ReactorDescManager::getSingletonPtr()->getByName("reactor, small"), NULL, NULL, NULL);
	ObjectDescManager::getSingletonPtr()->create("power plant, geothermal", NULL, NULL,
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("power plant, geothermal"), NULL, NULL,
		PartDescManager::ReactorDescManager::getSingletonPtr()->getByName("reactor, small"), NULL, NULL, NULL);

	ObjectDescManager::getSingletonPtr()->create("light tank", NULL,
		PartDescManager::ArmourDescManager::getSingletonPtr()->getByName("armour, light"),
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("vehicle, small"),
		PartDescManager::EngineDescManager::getSingletonPtr()->getByName("engine, small"), NULL, NULL, NULL, NULL,
		PartDescManager::WeaponDescManager::getSingletonPtr()->getByName("weapon, medium"));

	ObjectDescManager::getSingletonPtr()->create("fast light tank", NULL,
		PartDescManager::ArmourDescManager::getSingletonPtr()->getByName("armour, light"),
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("vehicle, small"),
		PartDescManager::EngineDescManager::getSingletonPtr()->getByName("engine, big"), NULL, NULL, NULL, NULL,
		PartDescManager::WeaponDescManager::getSingletonPtr()->getByName("weapon, medium"));

	ObjectDescManager::getSingletonPtr()->create("heavy tank", NULL,
		PartDescManager::ArmourDescManager::getSingletonPtr()->getByName("armour, heavy"),
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("vehicle, medium"),
		PartDescManager::EngineDescManager::getSingletonPtr()->getByName("engine, big"), NULL, NULL, NULL, NULL,
		PartDescManager::WeaponDescManager::getSingletonPtr()->getByName("weapon, medium"));

	ObjectDescManager::getSingletonPtr()->create("missile", NULL, NULL,
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("missile"), NULL,
		PartDescManager::ExplosiveDescManager::getSingletonPtr()->getByName("explosive, light"), NULL, NULL, NULL, NULL);

	ObjectDescManager::getSingletonPtr()->create("kbot",
		PartDescManager::ArmDescManager::getSingletonPtr()->getByName("arm"),
		PartDescManager::ArmourDescManager::getSingletonPtr()->getByName("armour, heavy"),
		PartDescManager::BodyDescManager::getSingletonPtr()->getByName("vehicle, medium"),
		PartDescManager::EngineDescManager::getSingletonPtr()->getByName("engine, big"), NULL, NULL, NULL, NULL, NULL);

	// ObjectManager

	ObjectManager objectManager;

	Object* o = NULL;

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("grass"));
	o->setPosition(getTerrainHeightVec(220, 320));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("nature"));

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("grass"));
	o->setPosition(getTerrainHeightVec(220, 320));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("nature"));

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("wall"));
	o->setPosition(getTerrainHeightVec(250, 300));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("human"));

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("factory"));
	o->setPosition(getTerrainHeightVec(320, 200));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("human"));

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("power plant, fussion"));
	o->setPosition(getTerrainHeightVec(220, 220));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("human"));

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("power plant, geothermal"));
	o->setPosition(getTerrainHeightVec(220, 250));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("human"));

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("light tank"));
	o->setPosition(getTerrainHeightVec(230, 200));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("human"));

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("fast light tank"));
	o->setPosition(getTerrainHeightVec(230, 180));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("human"));
	o->getBody()->setHitPoints(20.0f);

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("fast light tank"));
	o->setPosition(getTerrainHeightVec(280, 210));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("enemy"));

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("fast light tank"));
	o->setPosition(getTerrainHeightVec(290, 220));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("enemy"));
	o->getBody()->setHitPoints(15.0f);

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("kbot"));
	o->setPosition(getTerrainHeightVec(240, 210));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("human"));
	o->getBody()->setHitPoints(5.0f);

	o = ObjectManager::getSingletonPtr()->createObject(ObjectDescManager::getSingletonPtr()->getByName("kbot"));
	o->setPosition(getTerrainHeightVec(250, 210));
	o->setPlayer(PlayerManager::getSingletonPtr()->getByName("human"));
	o->getBody()->setHitPoints(5.0f);

	// Run

	m_root->startRendering();
}

//------------------------------------------------------------------------------

void Core::quit() {

	m_notQuit = false;
}

//------------------------------------------------------------------------------

bool Core::frameStarted(const Ogre::FrameEvent& evt) {

	float m_timeSinceLastFrame = 0.0f;

	m_elapsedTime += evt.timeSinceLastFrame;

	// Speed Control

	static bool m_speedControl = false;

	/*
	if (evt.timeSinceLastFrame < 1.0f / 30.0f) {
	//*/

		m_timeSinceLastFrame = evt.timeSinceLastFrame;

	/*
		m_speedControl = false;

	} else {

		 m_timeSinceLastFrame = 1.0f / 30.0f;
		 m_speedControl = true;
	}
	//*/

	// Game Info

	//*
	CEGUI::StaticText* m_gameInfo = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("GameInfo");

	m_gameInfo->setVisible(true);

	static char str[512];

	sprintf(
		str,
		"WarGAME\n\nFPS\n  Best - %.2f\n  Average - %.2f\n  Worst - %.2f\n\nSpeed Control\n  %s",
		m_renderWindow->getBestFPS(),
		m_renderWindow->getAverageFPS(),
		m_renderWindow->getWorstFPS(),
		(m_speedControl ? "Enabled" : "Disabled"));

	m_gameInfo->setText(str);
	//*/

	// Update system

	ObjectInfoBar::getSingletonPtr()->update(m_timeSinceLastFrame);

	if (m_gameSpeed) {

		PlayerManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);

		PartManager::ArmManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PartManager::ArmourManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PartManager::BodyManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PartManager::EngineManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PartManager::ExplosiveManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PartManager::ReactorManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PartManager::ShieldManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PartManager::TeleporterManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PartManager::WeaponManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);

		ObjectManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
	}
	//*/

	// Mouse Picking

	//*
	m_mouse3DPos = Ogre::Vector3(-1.0f);
	m_hovered.clear();

	if (Gui::getSingletonPtr()->isMouseOverGui() == false) {

		static Ogre::RaySceneQuery* m_raySceneQuery = m_sceneManager->createRayQuery(Ogre::Ray());

		m_raySceneQuery->setRay(m_camera->getCameraToViewportRay(m_mouse2DPos.x, m_mouse2DPos.y));
		m_raySceneQuery->setSortByDistance(true);

		static Ogre::RaySceneQueryResult& result = m_raySceneQuery->execute();

		result = m_raySceneQuery->execute();

		static Ogre::RaySceneQueryResult::iterator itr = result.begin();

		for (itr = result.begin(); itr != result.end(); itr++) {

			if (itr->movable && (itr->distance <= 768.0f) && (itr->movable->getUserAny().isEmpty() == false)) {

				m_hovered.remove(ogreAnyToObject(itr->movable->getUserAny()));
				m_hovered.push_back(ogreAnyToObject(itr->movable->getUserAny()));

			} else if (itr->worldFragment) {

				m_mouse3DPos = itr->worldFragment->singleIntersection;

				break;
			}
		}
	}
	//*/

	// Selection Menu,
	//  show menu when left mouse button is pressed for 0.5 s.

	//*
	static float timeSinceLeftButtonDown = 0.0f;

	if (m_mouseButton[0]) {

		timeSinceLeftButtonDown += m_timeSinceLastFrame;

		if (timeSinceLeftButtonDown >= 0.5f) {

			if (SelectionMenu::getSingletonPtr()->isVisible() == false)

				SelectionMenu::getSingletonPtr()->setPosition(m_mouse2DPos.x - 0.01f, m_mouse2DPos.y - 0.01f);

			SelectionMenu::getSingletonPtr()->setVisible(true);
		}

	} else {

		timeSinceLeftButtonDown = 0.0f;
	}
	//*/

	// Order Menu,
	//  show menu when right mouse button is pressed for 0.5 s.

	//*
	static float timeSinceRightButtonDown = 0.0f;

	if (m_mouseButton[1]) {

		timeSinceRightButtonDown += m_timeSinceLastFrame;

		if (timeSinceRightButtonDown >= 0.5f) {

			if (OrderMenu::getSingletonPtr()->isVisible() == false)

				OrderMenu::getSingletonPtr()->setPosition(m_mouse2DPos.x - 0.01f, m_mouse2DPos.y - 0.01f);

			OrderMenu::getSingletonPtr()->setVisible(true);
		}

	} else {

		timeSinceRightButtonDown = 0.0f;
	}
	//*/

	//

	//*
	Ogre::AxisAlignedBox box;

	m_sceneManager->getOption("Size", &box);

	m_inputReader->capture();
	//*/

	if (m_inputReader->isKeyDown(Ogre::KC_ESCAPE))

		return false;

	// Camera

	float speed = 15.0f;

	if (m_inputReader->isKeyDown(Ogre::KC_RIGHT))// || m_inputReader->isKeyDown(KC_D))

		m_camera->moveRelative(Ogre::Vector3( speed * evt.timeSinceLastFrame, 0, 0));

	else if (m_inputReader->isKeyDown(Ogre::KC_LEFT))// || m_inputReader->isKeyDown(KC_A))

		m_camera->moveRelative(Ogre::Vector3(-speed * evt.timeSinceLastFrame, 0, 0));

	if (m_inputReader->isKeyDown(Ogre::KC_UP))// || m_inputReader->isKeyDown(KC_W))

		m_camera->moveRelative(Ogre::Vector3(0, 0, -speed * evt.timeSinceLastFrame));

	else if (m_inputReader->isKeyDown(Ogre::KC_DOWN))// || m_inputReader->isKeyDown(KC_S))

		m_camera->moveRelative(Ogre::Vector3(0, 0,  speed * evt.timeSinceLastFrame));

	//*
	static Ogre::Vector3 camPos;

	camPos = m_camera->getPosition();

	if (m_inputReader->isKeyDown(Ogre::KC_PGUP))

		camPos.y += 20.0f * evt.timeSinceLastFrame;

	else if (m_inputReader->isKeyDown(Ogre::KC_PGDOWN))

		camPos.y -= 20.0f * evt.timeSinceLastFrame;


	if (camPos.x < box.getMinimum().x) camPos.x = box.getMinimum().x;
	if (camPos.z < box.getMinimum().z) camPos.z = box.getMinimum().z;
	if (camPos.x > box.getMaximum().x) camPos.x = box.getMaximum().x;
	if (camPos.z > box.getMaximum().z) camPos.z = box.getMaximum().z;

	if (camPos.y < getTerrainHeight(camPos.x, camPos.z) + 1.75f)

		camPos.y = getTerrainHeight(camPos.x, camPos.z) + 1.75f;

	m_camera->setPosition(camPos);
	//*/

	return m_notQuit;
}

//------------------------------------------------------------------------------

void Core::keyPressed(Ogre::KeyEvent* e) {

	m_keys[e->getKey()] = true;

	switch (e->getKey()) {

		case Ogre::KC_F1: Console::getSingletonPtr()->changeMode();				break;
		case Ogre::KC_F2: ObjectInfoBar::getSingletonPtr()->changeVisible();	break;
		case Ogre::KC_F4: PlayerViewer::getSingletonPtr()->changeVisible();		break;
		case Ogre::KC_F5: PartDescViewer::getSingletonPtr()->changeVisible();	break;
		case Ogre::KC_F6: PartViewer::getSingletonPtr()->changeVisible();		break;
		case Ogre::KC_F7: ObjectDescViewer::getSingletonPtr()->changeVisible();	break;
		case Ogre::KC_F8: ObjectViewer::getSingletonPtr()->changeVisible();		break;

		// Pause.

		case Ogre::KC_P:

			if (m_gameSpeed)

				m_gameSpeed = 0.0f;

			else

				m_gameSpeed = 1.0f;

			break;

		// Increase game speed.

		case Ogre::KC_ADD:

			if (m_gameSpeed < 2.0f)	m_gameSpeed += 0.1f;
			if (m_gameSpeed > 2.0f)	m_gameSpeed  = 2.0f;

			break;

		// Decrease game speed.

		case Ogre::KC_SUBTRACT:

			if (m_gameSpeed > 0.0f)	m_gameSpeed -= 0.1f;
			if (m_gameSpeed < 0.0f)	m_gameSpeed  = 0.0f;

			break;

		// Make a screenshot.

		case Ogre::KC_SYSRQ:

			{
				SYSTEMTIME st;
				char fileName[MAX_PATH];

				GetLocalTime(&st);

				sprintf(fileName, "..\\screens\\WarGAME.screen.%i-%.2i-%.2i.%.2i-%.2i-%.2i.png",
					st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

				m_renderWindow->writeContentsToFile(fileName);

				break;
			}

		// Shadows on / off.

		case Ogre::KC_S:

			if (e->isControlDown() && e->isShiftDown())

				if (m_sceneManager->getShadowTechnique() == Ogre::SHADOWTYPE_NONE)

					m_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

				else

					m_sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

			break;

	} // switch (e->getKey())

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectChar(e->getKeyChar());
	CEGUI::System::getSingletonPtr()->injectKeyDown(e->getKey());

	e->consume();
}

//------------------------------------------------------------------------------

void Core::keyReleased(Ogre::KeyEvent* e) {

	m_keys[e->getKey()] = false;

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectKeyUp(e->getKey());

	e->consume();
}

//------------------------------------------------------------------------------

void Core::mousePressed(Ogre::MouseEvent* e) {

	switch (e->getButtonID()) {

		case Ogre::MouseEvent::BUTTON0_MASK: m_mouseButton[0] = true; break;
		case Ogre::MouseEvent::BUTTON1_MASK: m_mouseButton[1] = true; break;
		case Ogre::MouseEvent::BUTTON2_MASK: m_mouseButton[2] = true; break;
	}

	//

	if (m_hovered.size())

		m_objectSelectedByRightClick = m_hovered.front();

	else

		m_objectSelectedByRightClick = NULL;

	if (m_mouse3DPos != Ogre::Vector3(-1.0f))

		m_positionSelectedByRightClick = m_mouse3DPos;

	else

		m_positionSelectedByRightClick != Ogre::Vector3(-1.0f);

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectMouseButtonDown(
		convertOgreButtonToCEGUI(e->getButtonID()));

	e->consume();
}

//------------------------------------------------------------------------------

void Core::mouseReleased(Ogre::MouseEvent* e) {

	switch (e->getButtonID()) {

		case Ogre::MouseEvent::BUTTON0_MASK:
			
			m_mouseButton[0] = false;

			// Select / Deselect objects.

			if (Gui::getSingletonPtr()->isMouseOverGui() == false) {

				if (e->getButtonID() & Ogre::MouseEvent::BUTTON0_MASK) {

					deselectAll();

					if (m_hovered.size()) {

						select(m_hovered.front());
					}
				}
			}

			break;

		case Ogre::MouseEvent::BUTTON1_MASK:
			
			m_mouseButton[1] = false;

			// Give an order to selected objects.

			if ((Gui::getSingletonPtr()->isMouseOverGui() == false)) {

				if (m_hovered.size()) {

					for (list<Object*>::iterator itr = m_selected.begin(); itr != m_selected.end(); itr++) {

						if ((*itr)->getWeapon()) {

							(*itr)->order(ObjectOrder(
								ObjectOrder::OOT_ATTACK_OBJECT,
								Ogre::Vector3::ZERO,
								m_hovered.front()));

						} else if ((*itr)->getArm()) {

							(*itr)->order(ObjectOrder(
								ObjectOrder::OOT_REPAIR,
								Ogre::Vector3::ZERO,
								m_hovered.front()));

							(*itr)->order(ObjectOrder(
								ObjectOrder::OOT_RESUPPLY,
								Ogre::Vector3::ZERO,
								m_hovered.front()),
								false);

						} else if ((*itr)->getEngine()) {

							(*itr)->order(ObjectOrder(
								ObjectOrder::OOT_MOVE_TO_OBJECT,
								Ogre::Vector3::ZERO,
								m_hovered.front()));
						}
					}

				} else if (m_mouse3DPos != Ogre::Vector3(-1.0f)) {

					for (list<Object*>::iterator itr = m_selected.begin(); itr != m_selected.end(); itr++) {

						(*itr)->order(ObjectOrder(ObjectOrder::OOT_MOVE_TO_POSITION, m_mouse3DPos));
					}
				}
			}

			break;

		case Ogre::MouseEvent::BUTTON2_MASK:

			m_mouseButton[2] = false;

			break;
	}

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectMouseButtonUp(
		convertOgreButtonToCEGUI(e->getButtonID()));
}

//------------------------------------------------------------------------------
			
void Core::mouseMoved(Ogre::MouseEvent* e) {

	m_mouse2DPos.x = e->getX();
	m_mouse2DPos.y = e->getY();

	// Free look.

	if (m_mouseButton[2]) {

		m_camera->yaw(
			Ogre::Degree(e->getRelX() * m_renderWindow->getWidth() * -0.15f));
		m_camera->pitch(
			Ogre::Degree(e->getRelY() * m_renderWindow->getWidth() * -0.15f));
	}

	// Update CEGUI.

	CEGUI::System::getSingleton().injectMouseMove(
		e->getRelX() * m_renderWindow->getWidth(),
		e->getRelY() * m_renderWindow->getHeight());

	e->consume();
}

//------------------------------------------------------------------------------

void Core::mouseDragged(Ogre::MouseEvent* e) {

	mouseMoved(e);
}

//------------------------------------------------------------------------------

Ogre::RaySceneQueryResult Core::whatWouldHit(const Ogre::Vector3& pos, const Ogre::Vector3& dir) {

	static Ogre::RaySceneQuery* raySceneQuery = m_sceneManager->createRayQuery(Ogre::Ray());
	static Ogre::Ray ray;

	ray.setOrigin(pos);
	ray.setDirection(dir);

	raySceneQuery->setRay(ray);
	raySceneQuery->setSortByDistance(true);

	return raySceneQuery->execute();
}

//------------------------------------------------------------------------------

float Core::getTerrainHeight(float x, float z) {

	Ogre::RaySceneQuery* raySceneQuery = m_sceneManager->createRayQuery(Ogre::Ray());
	Ogre::Ray ray(Ogre::Vector3(x, 1000.0f, z), Ogre::Vector3::NEGATIVE_UNIT_Y);

	raySceneQuery->setRay(ray);

	Ogre::RaySceneQueryResult& raySceneQueryResult = raySceneQuery->execute();
	Ogre::RaySceneQueryResult::iterator itr = raySceneQueryResult.begin();

	if (itr != raySceneQueryResult.end() && itr->worldFragment)

		return itr->worldFragment->singleIntersection.y;

	return 0.0f;
}

//------------------------------------------------------------------------------

CEGUI::MouseButton Core::convertOgreButtonToCEGUI(int buttonID) {

	switch (buttonID) {

		case Ogre::MouseEvent::BUTTON0_MASK: return CEGUI::LeftButton;
		case Ogre::MouseEvent::BUTTON1_MASK: return CEGUI::RightButton;
		case Ogre::MouseEvent::BUTTON2_MASK: return CEGUI::MiddleButton;
		case Ogre::MouseEvent::BUTTON3_MASK: return CEGUI::X1Button;

		default: return CEGUI::LeftButton;
	}
}

//------------------------------------------------------------------------------

string Core::positionToStr(float x, float z) {

	Ogre::AxisAlignedBox box;

	m_sceneManager->getOption("Size", &box);

	char textNS[128];
	char textWE[128];

	if (x < box.getMaximum().x / 2)

		sprintf(
			textNS,
			"%.2f* N",
			90 * (1 - (x / (box.getMaximum().x / 2))));

	else

		sprintf(
			textNS,
			"%.2f* S",
			-90 * (1 - (x / (box.getMaximum().x / 2))));

	if (z < box.getMaximum().z / 2)

		 sprintf(
			textWE,
			"%.2f* W",
			180 * (1 - (z / (box.getMaximum().z / 2))));

	else

		sprintf(
			textWE,
			"%.2f* E",
			-180 * (1 - (z / (box.getMaximum().z / 2))));

	return string(textNS) + textWE;
}

//------------------------------------------------------------------------------
