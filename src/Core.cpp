
//------------------------------------------------------------------------------
// Core.cpp
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

#include "Xml.h"

//------------------------------------------------------------------------------

Core::Core()

	:	m_root(NULL),
		m_renderWindow(NULL),
		m_sceneManager(NULL),
		m_camera(NULL),
		m_viewport(NULL),
		m_eventProcessor(NULL),
		m_inputReader(NULL),
		m_elapsedTime(0.0f),
		m_notQuit(true),
		m_dataCounter(0),
		m_mouse2DPos(Vector2::ZERO),
		m_mouse3DPos(Vector3::ZERO),
		m_objectUnderMouse(NULL)

{

	for (int i = 0; i < 3; i++)

		m_mouseButton[i] = false;

	for (int i = 0; i < 0xEE; i++)

		m_keys[i] = false;

}

//------------------------------------------------------------------------------

Core::~Core(){

	if (m_eventProcessor)	delete m_eventProcessor;
	if (m_root)				delete m_root;

}

//------------------------------------------------------------------------------

void initBox(){

	ManualObject* box = Core::getSingletonPtr()->createManualObject();

	box->estimateVertexCount(8);
	box->estimateIndexCount(24);

	box->begin("Color/White", RenderOperation::OT_LINE_LIST);

		box->position( 1.0f,  1.0f, -1.0f);
		box->position(-1.0f,  1.0f, -1.0f);
		box->position(-1.0f,  1.0f,  1.0f);
		box->position( 1.0f,  1.0f,  1.0f);

		box->position( 1.0f, -1.0f, -1.0f);
		box->position(-1.0f, -1.0f, -1.0f);
		box->position(-1.0f, -1.0f,  1.0f);
		box->position( 1.0f, -1.0f,  1.0f);

		box->index(0);
		box->index(1);
		box->index(1);
		box->index(2);
		box->index(2);
		box->index(3);
		box->index(3);
		box->index(0);

		box->index(4);
		box->index(5);
		box->index(5);
		box->index(6);
		box->index(6);
		box->index(7);
		box->index(7);
		box->index(4);

		box->index(0);
		box->index(4);
		box->index(1);
		box->index(5);
		box->index(2);
		box->index(6);
		box->index(3);
		box->index(7);

	box->end();

	MeshPtr meshPtr = box->convertToMesh("Box");

}

void initCylinder(){

	ManualObject* cylinder = Core::getSingletonPtr()->createManualObject();

	cylinder->estimateVertexCount(16);
	cylinder->estimateIndexCount(48);

	cylinder->begin("Color/White", RenderOperation::OT_LINE_LIST);

		for (int i = 0; i < 8; i++) {

			cylinder->position(
				 Math::Cos(Radian(Degree(i * 45.0f))),
				 Math::Sin(Radian(Degree(i * 45.0f))),
				 1.0f);

			cylinder->position(
				 Math::Cos(Radian(Degree(i * 45.0f))),
				 Math::Sin(Radian(Degree(i * 45.0f))),
				-1.0f);

		}

		for (int i = 0; i < 16; i++)

			cylinder->index(i);

		for (int i = 0; i < 14; i += 2) {

			cylinder->index(i);
			cylinder->index(i + 2);

			cylinder->index(i + 1);
			cylinder->index(i + 3);

		}

		cylinder->index(14);
		cylinder->index(0);

		cylinder->index(15);
		cylinder->index(1);

	cylinder->end();

	MeshPtr meshPtr = cylinder->convertToMesh("Cylinder");

}

void initSphere(){

	ManualObject* sphere = Core::getSingletonPtr()->createManualObject();

	//sphere->estimateVertexCount(16);
	//sphere->estimateIndexCount(48);

	sphere->begin("Color/White", RenderOperation::OT_LINE_LIST);

		for (int i = 0; i < 8; i++) {

			sphere->position(
				Math::Cos(Radian(Degree(i * 45.0f))),
				Math::Sin(Radian(Degree(i * 45.0f))),
				0.0f);

		}

		for (int i = 0; i < 8; i++) {

			sphere->position(
				Math::Cos(Radian(Degree(i * 45.0f))),
				0.0f,
				Math::Sin(Radian(Degree(i * 45.0f))));

		}

		for (int i = 0; i < 8; i++) {

			sphere->position(
				0.0f,
				Math::Cos(Radian(Degree(i * 45.0f))),
				Math::Sin(Radian(Degree(i * 45.0f))));

		}

		for (int i = 0; i < 7; i++) {

			sphere->index(i);
			sphere->index(i + 1);

		}

		sphere->index(7);
		sphere->index(0);

		for (int i = 8; i < 15; i++) {

			sphere->index(i);
			sphere->index(i + 1);

		}

		sphere->index(15);
		sphere->index(8);

		for (int i = 16; i < 23; i++) {

			sphere->index(i);
			sphere->index(i + 1);

		}

		sphere->index(23);
		sphere->index(16);

	sphere->end();

	MeshPtr meshPtr = sphere->convertToMesh("Sphere");

}

bool Core::init(){

	// Root

	m_root = new Root("Plugins.cfg", "Ogre.cfg", "Ogre.log");


	// Resources

	ConfigFile cf;

	cf.load("Resources.cfg");

	ConfigFile::SectionIterator seci = cf.getSectionIterator();

	string secName, typeName, archName;

	while (seci.hasMoreElements()) {

		secName = seci.peekNextKey();

		ConfigFile::SettingsMultiMap* settings = seci.getNext();
		ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i) {

			typeName = i->first;
			archName = i->second;

			ResourceGroupManager::getSingleton().addResourceLocation(
				archName, typeName, secName);
		}

	}


	// Render Window

	RenderSystemList* renderSystemList = m_root->getAvailableRenderers();

	for (RenderSystemList::iterator i = renderSystemList->begin(); i != renderSystemList->end(); i++) {

		if ((*i)->getName() == "Direct3D9 Rendering Subsystem") {

			//*
			//(*i)->setConfigOption("Allow NVPerfHUD", "No");
			//(*i)->setConfigOption("Anti aliasing", "6");
			//(*i)->setConfigOption("Floating-point mode", "Fastest");
			//(*i)->setConfigOption("Full Screen", "Yes");
			//(*i)->setConfigOption("Rendering Device", "RADEON 9600 SERIES");
			//(*i)->setConfigOption("VSync", "Yes");
			//(*i)->setConfigOption("Video Mode", "1024 x 768 @ 32-bit colour");
			//*/

			m_root->setRenderSystem((*i));

			break;

		}
	}

	m_renderWindow = m_root->initialise(false, "WarGAME p r o j e c t");
	m_renderWindow = m_root->createRenderWindow("WarGAME p r o j e c t", 1024, 768, true);

	// Scene Manager

	m_sceneManager =
		m_root->createSceneManager(ST_EXTERIOR_CLOSE, "SceneManager");


	// Camera

	m_camera = m_sceneManager->createCamera("PlayerCam");
	m_camera->setPosition(Vector3(1, 50, 1));
	m_camera->lookAt(Vector3(50, 50, 20));
	m_camera->setNearClipDistance(1.0f);
	m_camera->setFarClipDistance(512.0f);

	m_sceneManager->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
	m_sceneManager->setShadowFarDistance(512.0f);
	m_sceneManager->setShadowUseInfiniteFarPlane(false);

	m_viewport = m_renderWindow->addViewport(m_camera);

	m_camera->setAspectRatio(
		Real(m_viewport->getActualWidth()) / Real(m_viewport->getActualHeight()));

	//ResourceGroupManager::getSingletonPtr()->createResourceGroup("World");
	//ResourceGroupManager::getSingletonPtr()->setWorldResourceGroupName("World");

	ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();

	m_sceneManager->setWorldGeometry("Demo_Map.cfg");

	ColourValue fadeColour( 0, 0, 0);
	m_viewport->setBackgroundColour(fadeColour);
	m_sceneManager->setFog( FOG_LINEAR, fadeColour, 0, 256, 512);


	// Event Processor

	m_eventProcessor = new EventProcessor();
	m_eventProcessor->initialise(m_renderWindow);
	m_eventProcessor->startProcessingEvents();
	m_eventProcessor->addMouseListener(this);
	m_eventProcessor->addMouseMotionListener(this);
	m_eventProcessor->addKeyListener(this);

	m_inputReader = m_eventProcessor->getInputReader();

	m_root->addFrameListener(this);

	//initBox();
	//initCylinder();
	//initSphere();

	return true;

}

//------------------------------------------------------------------------------

Light* light;
SceneNode* scene;
Entity* entity;

Player* m_humanPlayer = NULL;

Object* o1;
Object* o2;

void Core::run(){
//*
	light = m_sceneManager->createLight("a");
	light->setType(Light::LT_POINT);
	light->setPosition(512, 768, 512);
	light->setDiffuseColour(1, 1, 1);
//*/

//*
	m_humanPlayer = PlayerManager::getSingletonPtr()->add(new Player("Human"));

	PlayerManager::getSingletonPtr()->add(new Player("Computer"));
	PlayerManager::getSingletonPtr()->add(new Player("Nature"));
//*/

	PartDescManager::getSingletonPtr()->add(
		new BodyDesc("MissileBody", 1.0f, "missile.mesh", false));

	Object* mis = new Missile(
		PartDescManager::getSingletonPtr()->getByName("MissileBody")->isBodyDesc(),
		getTerrainHeightVec(20.0f, 20.0f) + Vector3(0, 10, 0));
	mis->setDimensionY(0.25f);
	mis->setPlayer(PlayerManager::getSingletonPtr()->get("Human"));
	ObjectManager::getSingletonPtr()->add(mis);


	PartDescManager::getSingletonPtr()->add(
		new ArmourDesc("ArmourTypeLight", 5.0f, 5.0f));

	PartDescManager::getSingletonPtr()->add(
		new ArmourDesc("ArmourTypeMedium", 5.0f, 25.0f));

	PartDescManager::getSingletonPtr()->add(
		new BodyDesc("tree5", 25.0f, "tree5.mesh", false));

	PartDescManager::getSingletonPtr()->add(
		new BodyDesc("armfus", 25.0f, "armfus.mesh", true));

	PartDescManager::getSingletonPtr()->add(
		new BodyDesc("armbull_body", 260.0f, "armbull_body.mesh", true));

	PartDescManager::getSingletonPtr()->add(
		new BodyDesc("armcroc_body", 260.0f, "armcroc_body.mesh", true));

	PartDescManager::getSingletonPtr()->add(
		new BodyDesc("armhlt", 10.0f, "armhlt.mesh", true));

	PartDescManager::getSingletonPtr()->add(
		new BodyDesc("cordrag", 50.0f, "cordrag.mesh", true));

	PartDescManager::getSingletonPtr()->add(
		new EngineDesc("EngineTypeSlow", 10.0f, 15.0f, 500.0f));

	PartDescManager::getSingletonPtr()->add(
		new PowerReactorDesc("PowerReactor", 10.0f, 150.0f, 5.0f));

	PartDescManager::getSingletonPtr()->add(
		new BodyDesc("armvp", 20.0f, "armvp.mesh", true));

	PartDescManager::getSingletonPtr()->add(
		new WeaponDesc("armbull_weapon", 10.0f, "armbull_weapon.mesh", true, 25.0f, 500.0f, 5.0f, 30.0f, 200.0f));

	PartDescManager::getSingletonPtr()->add(
		new WeaponDesc("armcroc_weapon", 20.0f, "armcroc_weapon.mesh", true, 35.0f, 400.0f, 2.0f, 22.0f, 200.0f));





	ObjectDescManager::getSingletonPtr()->add(
		new FortificationDesc(
			"Tower",
			PartDescManager::getSingletonPtr()->getByName("ArmourTypeLight")->isArmourDesc(),
			PartDescManager::getSingletonPtr()->getByName("armhlt")->isBodyDesc(),
			PartDescManager::getSingletonPtr()->getByName("armbull_weapon")->isWeaponDesc()
		)
	);

	ObjectDescManager::getSingletonPtr()->add(
		new VehicleDesc(
			"Vehicle",
			PartDescManager::getSingletonPtr()->getByName("ArmourTypeLight")->isArmourDesc(),
			PartDescManager::getSingletonPtr()->getByName("armbull_body")->isBodyDesc(),
			PartDescManager::getSingletonPtr()->getByName("EngineTypeSlow")->isEngineDesc(),
			PartDescManager::getSingletonPtr()->getByName("armbull_weapon")->isWeaponDesc()
		)
	);


	Object* o = NULL;
	//*
	o = new Vehicle("ArmourTypeLight", "armbull_body", "EngineTypeSlow", "armcroc_weapon", getTerrainHeightVec(20.0f, 20.0f));
	o->setDimensionY(2.0f);
	o->setPlayer(PlayerManager::getSingletonPtr()->get("Human"));
	ObjectManager::getSingletonPtr()->add(o);

	o1 = o;
	//*/
	o = new PowerPlant("ArmourTypeMedium", "armfus", "PowerReactor", getTerrainHeightVec(50.0f, 20.0f));
	o->setDimensionY(10.0f);
	o->setPlayer(PlayerManager::getSingletonPtr()->get("Human"));
	ObjectManager::getSingletonPtr()->add(o);

	o2 = o;


	o = new Vehicle("ArmourTypeLight", "armcroc_body", "EngineTypeSlow", "armbull_weapon", getTerrainHeightVec(20.0f, 30.0f));
	o->setDimensionY(2.0f);
	o->setPlayer(PlayerManager::getSingletonPtr()->get("Human"));
	o->m_orderList.addFront(ObjectOrder(ObjectOrder::OOT_MOVE, getTerrainHeightVec(30, 50)));
	o->m_orderList.addFront(ObjectOrder(ObjectOrder::OOT_MOVE, getTerrainHeightVec(40, 55)));
	o->m_orderList.addFront(ObjectOrder(ObjectOrder::OOT_MOVE, getTerrainHeightVec(60, 70)));
	ObjectManager::getSingletonPtr()->add(o);

	o = new Object(PartDescManager::getSingletonPtr()->getByName("tree5")->isBodyDesc(), getTerrainHeightVec(10.0f, 10.0f));
	o->setDimensionY(10.0f);
	o->setPlayer(PlayerManager::getSingletonPtr()->get("Nature"));
	ObjectManager::getSingletonPtr()->add(o);

	o = new Building("ArmourTypeMedium", "cordrag", getTerrainHeightVec(10.0f, 15.0f));
	o->setDimensionY(1.0f);
	o->setPlayer(PlayerManager::getSingletonPtr()->get("Human"));
	ObjectManager::getSingletonPtr()->add(o);





	o = new Fortification("ArmourTypeLight", "armhlt", "armbull_weapon", getTerrainHeightVec(10.0f, 20.0f));
	o->setDimensionY(3.0f);
	o->setPlayer(PlayerManager::getSingletonPtr()->get("Human"));
	ObjectManager::getSingletonPtr()->add(o);


	o = new Fortification("ArmourTypeLight", "armhlt", "armbull_weapon", getTerrainHeightVec(10.0f, 30.0f));
	o->setDimensionY(3.0f);
	o->setPlayer(PlayerManager::getSingletonPtr()->get("Computer"));
	ObjectManager::getSingletonPtr()->add(o);





	//*
	o = new Building("ArmourTypeLight", "armvp", getTerrainHeightVec(50.0f, 55.0f));
	o->setDimensionY(10.0f);
	o->setPlayer(PlayerManager::getSingletonPtr()->get("Human"));
	ObjectManager::getSingletonPtr()->add(o);



	{
	TexturePtr						m_texturePtr;
	HardwarePixelBufferSharedPtr	m_buffer;
	static const int size = 128;
	m_texturePtr = TextureManager::getSingletonPtr()->createManual(
		"MiniMapTexture",
		"General",
		TEX_TYPE_2D,
		size,
		size,
		0,
		PF_A8R8G8B8, 
		TU_DYNAMIC_WRITE_ONLY);



	m_buffer = m_texturePtr->getBuffer(0, 0);

	m_buffer->lock(HardwareBuffer::HBL_DISCARD);

	const PixelBox &pb = m_buffer->getCurrentLock();

	for (unsigned int y = 0; y < size; y++) {

		unsigned int* data = static_cast<unsigned int*>(pb.data) + y * pb.rowPitch;

		for (unsigned int x = 0; x < size; x++) {

			if ((x - 20) * (x - 20) + (y - 20) * (y - 20) <= 50 || (x - 75) * (x - 75) + (y - 50) * (y - 50) <= 25)

				data[x] = 0x00000000;

			else

				data[x] = 0xFF000000;

		}

	}

	m_buffer->unlock();
	}



	{
	TexturePtr						m_texturePtr;
	HardwarePixelBufferSharedPtr	m_buffer;
	static const int size = 512;

	m_texturePtr = TextureManager::getSingletonPtr()->createManual(
		"Demo_Map_fog_of_war",
		"General",
		TEX_TYPE_2D,
		size,
		size,
		0,
		PF_A8R8G8B8, 
		TU_DYNAMIC_WRITE_ONLY);
	}


	MaterialPtr m = (MaterialPtr)MaterialManager::getSingletonPtr()->getByName("Demo.Map.Custom.Material");

	m->getTechnique(0)->getPass(2)->createTextureUnitState("Demo_Map_fog_of_war");


	// -0.75, 0.75, 0.75, -0.75);

	Rectangle2D* r1 = new Rectangle2D(true);
	r1->setCorners(0.5, -0.5, 1.0, -1.0);
	r1->setRenderQueueGroup(RENDER_QUEUE_BACKGROUND);
	r1->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE));
	r1->setMaterial("Examples/DynaTest");
	SceneNode* s1 = createSceneNode();
	s1->attachObject(r1);

	/*
	{
	ParticleSystem* ps0 = createParticleSystem("smoke_damage");
	SceneNode* sn0 = createSceneNode();
	sn0->attachObject(ps0);
	sn0->setPosition(getTerrainHeightVec(20, 20));
	}
	//*/

	/*
	{
	ParticleSystem* ps1 = createParticleSystem("stream");
	SceneNode* sn1 = createSceneNode();
	sn1->attachObject(ps1);
	sn1->setPosition(getTerrainHeightVec(30, 30));
	}
	//*/

	m_root->startRendering();

}

//------------------------------------------------------------------------------

void Core::quit(){

	m_notQuit = false;

}

//------------------------------------------------------------------------------

bool Core::frameStarted(const FrameEvent& evt){

	m_elapsedTime += evt.timeSinceLastFrame;


	// Update all.
//*
	Gui::getSingletonPtr()->updateGameInfo();
	Gui::getSingletonPtr()->updateViewer();
	ObjectManager::getSingletonPtr()->update(evt.timeSinceLastFrame);
	PlayerManager::getSingletonPtr()->update(evt.timeSinceLastFrame);

//*


	static AxisAlignedBox box;

	m_sceneManager->getOption("Size", &box);
	static int mapX = box.getMaximum().x;
	static int mapZ = box.getMaximum().z;

	static float timeToNextCheck = 1000.0f;

	timeToNextCheck += m_elapsedTime;

	if (timeToNextCheck >= 1000.0f) {

		timeToNextCheck = 0.0f;

		static const int size = 512;
		static TexturePtr m_texturePtr = (TexturePtr)TextureManager::getSingletonPtr()->getByName(
			"Demo_Map_fog_of_war");
		Vector3 v = o1->getPosition();
		Vector3 v1 = o2->getPosition();

		static HardwarePixelBufferSharedPtr m_buffer = m_texturePtr->getBuffer(0, 0);

		m_buffer->lock(HardwareBuffer::HBL_DISCARD);

		const PixelBox &pb = m_buffer->getCurrentLock();

		for (unsigned int z = 0; z < size; z++) {

			unsigned int* data = static_cast<unsigned int*>(pb.data) + z * pb.rowPitch;

			for (unsigned int x = 0; x < size; x++) {

				if (
					
					
					((x - v.x / mapX * 512) * (x - v.x / mapX * 512) + (z - v.z / mapZ * 512) * (z - v.z / mapZ * 512) <= 1024)

					||

					(((x - v1.x / mapX * 512) * (x - v1.x / mapX * 512) + (z - v1.z / mapZ * 512) * (z - v1.z / mapZ * 512) <= 1024))

					)

					data[x] = 0x00000000;

				else

					data[x] = 0xFF000000;

			}

		}

		m_buffer->unlock();

	}

//*/


	m_inputReader->capture();

	if (m_inputReader->isKeyDown(KC_ESCAPE))

		quit();


	// Camera

	float speed = 5.0f;

	if (m_inputReader->isKeyDown(KC_RIGHT) || m_inputReader->isKeyDown(KC_D))

		m_camera->moveRelative(Vector3( speed * evt.timeSinceLastFrame, 0, 0));

	else if (m_inputReader->isKeyDown(KC_LEFT) || m_inputReader->isKeyDown(KC_A))

		m_camera->moveRelative(Vector3(-speed * evt.timeSinceLastFrame, 0, 0));

	if (m_inputReader->isKeyDown(KC_UP) || m_inputReader->isKeyDown(KC_W))

		m_camera->moveRelative(Vector3(0, 0, -speed * evt.timeSinceLastFrame));

	else if (m_inputReader->isKeyDown(KC_DOWN) || m_inputReader->isKeyDown(KC_S))

		m_camera->moveRelative(Vector3(0, 0,  speed * evt.timeSinceLastFrame));

	static Vector3 camPos;

	camPos = m_camera->getPosition();

	if (m_inputReader->isKeyDown(KC_PGUP))

		camPos.y += 20.0f * evt.timeSinceLastFrame;

	else if (m_inputReader->isKeyDown(KC_PGDOWN))

		camPos.y -= 20.0f * evt.timeSinceLastFrame;


	if (camPos.x < box.getMinimum().x) camPos.x = box.getMinimum().x;
	if (camPos.z < box.getMinimum().z) camPos.z = box.getMinimum().z;
	if (camPos.x > box.getMaximum().x) camPos.x = box.getMaximum().x;
	if (camPos.z > box.getMaximum().z) camPos.z = box.getMaximum().z;

	if (camPos.y < getTerrainHeight(camPos.x, camPos.z) + 1.75f)

		camPos.y = getTerrainHeight(camPos.x, camPos.z) + 1.75f;

	m_camera->setPosition(camPos);


	// Selecting objects.

	m_mouse3DPos = Vector3(-1.0f);
	m_objectUnderMouse = NULL;

	if (Gui::getSingletonPtr()->isMouseOverGui() == false) {

		static RaySceneQuery* m_raySceneQuery = m_sceneManager->createRayQuery(Ray());

		m_raySceneQuery->setRay(m_camera->getCameraToViewportRay(m_mouse2DPos.x, m_mouse2DPos.y));
		m_raySceneQuery->setSortByDistance(true);

		static RaySceneQueryResult& result = m_raySceneQuery->execute();

		result = m_raySceneQuery->execute();

		static Ogre::RaySceneQueryResult::iterator itr = result.begin();

		for (itr = result.begin(); itr != result.end(); itr++)

			if (itr->movable && (itr->movable->getUserAny().isEmpty() == false)) {

				if (itr->distance <= 512.0f)

					m_objectUnderMouse = ogreAnyToObject(itr->movable->getUserAny());

				break;

			}

		if (m_objectUnderMouse == NULL)

			for (itr = result.begin(); itr != result.end(); itr++)

				if (itr != result.end() && itr->worldFragment) {

					m_mouse3DPos = itr->worldFragment->singleIntersection;

					break;

				}

	}

	if (m_objectUnderMouse)

		Gui::getSingletonPtr()->updateObjectInfo(m_objectUnderMouse);

	else if (m_lastSelectedObject)

		Gui::getSingletonPtr()->updateObjectInfo(m_lastSelectedObject);

	else

		Gui::getSingletonPtr()->updateObjectInfo(NULL);

	return m_notQuit;

}

//------------------------------------------------------------------------------

void Core::keyPressed(KeyEvent* e){

	m_keys[e->getKey()] = true;

	switch (e->getKey()) {

		case KC_F1: Gui::getSingletonPtr()->changeObjectViewerVisible();		break;
		case KC_F2: Gui::getSingletonPtr()->changeObjectDescViewerVisible();	break;
		case KC_F3: Gui::getSingletonPtr()->changePartDescViewerVisible();		break;

		// Make a screenshot.

		case KC_SYSRQ:

			{

				SYSTEMTIME st;
				char fileName[MAX_PATH];

				GetLocalTime(&st);

				sprintf(fileName, "..\\screens\\WarGAME.screen.%i-%i-%i.%i-%i-%i.png",
					st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

				m_renderWindow->writeContentsToFile(fileName);

				break;

			}

	}

}

//------------------------------------------------------------------------------

void Core::keyReleased(KeyEvent* e){

	m_keys[e->getKey()] = false;

}

//------------------------------------------------------------------------------

void Core::mousePressed(MouseEvent* e){

	if (Gui::getSingletonPtr()->isMouseOverGui() == false) {

		switch (e->getButtonID()) {

			case MouseEvent::BUTTON0_MASK:

				m_mouseButton[0] = true;

				if (m_objectUnderMouse && (m_objectUnderMouse->m_player == m_humanPlayer)) {

					if (m_keys[KC_LSHIFT] || m_keys[KC_RSHIFT]) {

						if (ObjectManager::getSingletonPtr()->isSelected(m_objectUnderMouse)) {

							ObjectManager::getSingletonPtr()->deselect(m_objectUnderMouse);

						} else {

							ObjectManager::getSingletonPtr()->select(m_objectUnderMouse);

							m_lastSelectedObject = m_objectUnderMouse;

						}

					} else {

						ObjectManager::getSingletonPtr()->deselectAll();

						ObjectManager::getSingletonPtr()->select(m_objectUnderMouse);

						m_lastSelectedObject = m_objectUnderMouse;

					}

				} else if (!(m_keys[KC_LSHIFT]) && !(m_keys[KC_RSHIFT])) {

					ObjectManager::getSingletonPtr()->deselectAll();

					m_lastSelectedObject = NULL;

				}

				break;

			case MouseEvent::BUTTON1_MASK:

				m_mouseButton[1] = true;

				if (m_mouse3DPos != Vector3(-1.0f)) {

					if (m_keys[KC_LSHIFT] || m_keys[KC_RSHIFT])

						ObjectManager::getSingletonPtr()->addOrderToSelected(ObjectOrder(ObjectOrder::OOT_MOVE, m_mouse3DPos));

					else

						ObjectManager::getSingletonPtr()->setOrderToSelected(ObjectOrder(ObjectOrder::OOT_MOVE, m_mouse3DPos));

				} else if (m_objectUnderMouse && (m_objectUnderMouse->m_player != m_humanPlayer)) {

					if (m_keys[KC_LSHIFT] || m_keys[KC_RSHIFT])

						ObjectManager::getSingletonPtr()->addOrderToSelected(ObjectOrder(ObjectOrder::OOT_ATTACK_OBJECT, Vector3::ZERO, m_objectUnderMouse));

					else

						ObjectManager::getSingletonPtr()->setOrderToSelected(ObjectOrder(ObjectOrder::OOT_ATTACK_OBJECT, Vector3::ZERO, m_objectUnderMouse));

				}

				break;

			case MouseEvent::BUTTON2_MASK:

				m_mouseButton[2] = true;

				break;

		}

	}

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectMouseButtonDown(
		convertOgreButtonToCEGUI(e->getButtonID()));

	e->consume();

}

//------------------------------------------------------------------------------

void Core::mouseReleased(MouseEvent* e){

	switch (e->getButtonID()) {

		case MouseEvent::BUTTON0_MASK: m_mouseButton[0] = false; break;
		case MouseEvent::BUTTON1_MASK: m_mouseButton[1] = false; break;
		case MouseEvent::BUTTON2_MASK: m_mouseButton[2] = false; break;

	}

	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectMouseButtonUp(
		convertOgreButtonToCEGUI(e->getButtonID()));

}

//------------------------------------------------------------------------------
			
void Core::mouseMoved(MouseEvent* e){

	m_mouse2DPos.x = e->getX();
	m_mouse2DPos.y = e->getY();

	// Free look.

	if (m_mouseButton[2]) {

		m_camera->yaw(
			Degree(e->getRelX() * m_renderWindow->getWidth() * -0.15f));
		m_camera->pitch(
			Degree(e->getRelY() * m_renderWindow->getWidth() * -0.15f));

	}

	// Update CEGUI.

	CEGUI::System::getSingleton().injectMouseMove(
		e->getRelX() * m_renderWindow->getWidth(),
		e->getRelY() * m_renderWindow->getHeight());

	e->consume();

}

//------------------------------------------------------------------------------

void Core::mouseDragged(MouseEvent* e){

	mouseMoved(e);

}

//------------------------------------------------------------------------------

RaySceneQueryResult Core::whatWouldHit(Vector3 pos, Vector3 dir){

	static RaySceneQuery* raySceneQuery = m_sceneManager->createRayQuery(Ray());
	static Ray ray;

	ray.setOrigin(pos);
	ray.setDirection(dir);

	raySceneQuery->setRay(ray);
	raySceneQuery->setSortByDistance(true);

	return raySceneQuery->execute();

}

//------------------------------------------------------------------------------

float Core::getTerrainHeight(float x, float z){

	static RaySceneQuery* raySceneQuery = m_sceneManager->createRayQuery(Ray());
	static Ray ray;

	ray.setOrigin(Vector3(x, 1000.0f, z));
	ray.setDirection(Vector3::NEGATIVE_UNIT_Y);

	raySceneQuery->setRay(ray);

	RaySceneQueryResult& raySceneQueryResult = raySceneQuery->execute();
	RaySceneQueryResult::iterator itr = raySceneQueryResult.begin();

	if (itr != raySceneQueryResult.end() && itr->worldFragment)

		return itr->worldFragment->singleIntersection.y;

	return 0.0f;

}

//------------------------------------------------------------------------------

CEGUI::MouseButton Core::convertOgreButtonToCEGUI(int buttonID){

	switch (buttonID) {

		case MouseEvent::BUTTON0_MASK: return CEGUI::LeftButton;
		case MouseEvent::BUTTON1_MASK: return CEGUI::RightButton;
		case MouseEvent::BUTTON2_MASK: return CEGUI::MiddleButton;
		case MouseEvent::BUTTON3_MASK: return CEGUI::X1Button;

		default: return CEGUI::LeftButton;

	}
}

//------------------------------------------------------------------------------

Object* Core::ogreAnyToObject(Ogre::Any ogreAny){

	if (ogreAny.getType() == typeid(Body*))

		return Ogre::any_cast<Body*>(ogreAny)->m_parent;

	else if (ogreAny.getType() == typeid(Weapon*))

		return Ogre::any_cast<Weapon*>(ogreAny)->m_parent;

	return NULL;

}

//------------------------------------------------------------------------------

string Core::positionToStr(float x, float z){

	static AxisAlignedBox box;

	m_sceneManager->getOption("Size", &box);

	static char textNS[128];
	static char textWE[128];

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

	static char text[512];

	sprintf(text, "%s %s", textNS, textWE);

	return text;

}

//------------------------------------------------------------------------------
