
//------------------------------------------------------------------------------
// Core.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "BattleFieldCamera.h"
#include "Console.h"
#include "ConstructionPanel.h"
#include "Core.h"
#include "Shield.h"
#include "EventManager.h"
#include "Game.h"
#include "Gui.h"
#include "ObjectManagerTemp.h"
#include "ObjectDescManagerTemp.h"
#include "Ocean.h"
#include "PartDescManagerT.h"
#include "PartManager.h"
#include "PlayerManager.h"
#include "ResourceManager.h"
#include "SoundManagerTemp.h"
#include "Teleporter.h"
#include "TeleporterDesc.h"
#include "Weapon.h"
#include "Xml.h"

//------------------------------------------------------------------------------

Core::Core()

	:	m_root(NULL),
		m_gameSpeed(1.0f),
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
		m_objectUnderMouse(NULL),
		m_state(NORMAL),
		m_activeObject(NULL),
		m_activePlayer(NULL)

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

			m_root->setRenderSystem((*i));

			break;
		}
	}

	m_renderWindow = m_root->initialise(false, "WarGAME p r o j e c t");
	m_renderWindow = m_root->createRenderWindow("WarGAME p r o j e c t", 1280, 1024, true);

	// Scene Manager

	m_sceneManager = m_root->createSceneManager(ST_EXTERIOR_CLOSE, "MainSceneManager");
	m_sceneManager->setShadowFarDistance(512.0f);
	m_sceneManager->setShadowUseInfiniteFarPlane(false);

	// Camera

	m_camera = m_sceneManager->createCamera("PlayerCam");
	m_camera->setDirection(Vector3::UNIT_X);
	m_camera->setPosition(200, 50, 200);
	m_camera->setNearClipDistance(0.5f);
	m_camera->setFarClipDistance(512.0f);

	m_viewport = m_renderWindow->addViewport(m_camera);

	m_camera->setAspectRatio(
		Real(m_viewport->getActualWidth()) / Real(m_viewport->getActualHeight()));

	//ResourceGroupManager::getSingletonPtr()->createResourceGroup("World");
	//ResourceGroupManager::getSingletonPtr()->setWorldResourceGroupName("World");
	ResourceGroupManager::getSingletonPtr()->initialiseAllResourceGroups();
	m_sceneManager->setWorldGeometry("Demo_Map.cfg");

	// Event Processor

	m_eventProcessor = new EventProcessor();
	m_eventProcessor->initialise(m_renderWindow);
	m_eventProcessor->startProcessingEvents();
	m_eventProcessor->addMouseListener(this);
	m_eventProcessor->addMouseMotionListener(this);
	m_eventProcessor->addKeyListener(this);

	m_inputReader = m_eventProcessor->getInputReader();

	m_root->addFrameListener(this);
	m_renderWindow->addListener(this);

	m_viewport->setBackgroundColour(ColourValue(0.0f, 0.5f, 0.75f));
	m_sceneManager->setFog(FOG_LINEAR, ColourValue(0.0f, 0.5f, 0.75f), 0.0f, 256.0f, 512.0f);

	return true;
}

//------------------------------------------------------------------------------

Light* light;
Rectangle2D* r;
ObjectTemp* o;
Entity* e;
SceneNode* sn;
ParticleSystem* ps;

void Core::run() {

	BattleFieldCamera battleFieldCamera;
	battleFieldCamera.init();

	Console console;
	console.init();

	ConstructionPanel constructionPanel;
	constructionPanel.init();

	Ocean ocean;
//	ocean.init();

	//

	console.write("--------------------------------------------------------------------------------");
	console.write("Welcome to WarGAME 1.0 Beta");
	console.write("--------------------------------------------------------------------------------");

	//

	light = m_sceneManager->createLight("a");
	light->setType(Light::LT_POINT);
	light->setPosition(512, 768, 512);
	light->setDiffuseColour(1, 1, 1);

	// Players

	PlayerManager::getSingletonPtr()->create("human", "blue");
	PlayerManager::getSingletonPtr()->create("nature", "green");
	PlayerManager::getSingletonPtr()->create("ally", "yellow");
	PlayerManager::getSingletonPtr()->create("enemy", "red");

	m_activePlayer = PlayerManager::getSingletonPtr()->getByName("human");

	// Part Descriptors

	PartDescManagerTemp::getSingletonPtr()->add(new ArmourDesc("armour - light",	10.0f,	20.0f));
	PartDescManagerTemp::getSingletonPtr()->add(new ArmourDesc("armour - medium",	20.0f,	40.0f));
	PartDescManagerTemp::getSingletonPtr()->add(new ArmourDesc("armour - heavy",	30.0f,	60.0f));

	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("grass1", 10.0f, "grass1.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("grass2", 10.0f, "grass2.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("grass3", 10.0f, "grass3.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("grass4", 10.0f, "grass4.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("grass5", 10.0f, "grass5.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("grass6", 10.0f, "grass6.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("grass7", 10.0f, "grass7.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));

	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub1", 10.0f, "shrub1.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub2", 10.0f, "shrub2.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub3", 10.0f, "shrub3.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub4", 10.0f, "shrub4.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub5", 10.0f, "shrub5.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub6", 10.0f, "shrub6.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub7", 10.0f, "shrub7.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub8", 10.0f, "shrub8.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new BodyDesc("shrub9", 10.0f, "shrub9.mesh", false, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));

	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("plane - medium",		50.0f,	"blade.mesh",			true, AT_ALL, ET_AIR, PRT_NONE, WT_ALL));
	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("plane - heavy",		50.0f,	"predator.mesh",		true, AT_ALL, ET_AIR, PRT_NONE, WT_ALL));
	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("missile",				1.0f,	"missile.mesh",			true, AT_NONE, ET_NONE, PRT_NONE, WT_NONE));
//	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("tower - light",		100.0f,	"tower_light.mesh",		true));
//	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("tower - medium",		100.0f,	"tower_medium.mesh",	true));
	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("tower - heavy",		100.0f,	"tower_heavy.mesh",		true, AT_ALL, ET_NONE, PRT_NONE, WT_ALL));
	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("power plant - #1",	100.0f,	"power_plant_1.mesh",	true, AT_ALL, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("power plant - #2",	120.0f,	"power_plant_1.mesh",	true, AT_ALL, ET_NONE, PRT_NONE, WT_NONE));
	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("vehicle - light",		125.0f,	"vehicle_light.mesh",	true, AT_ALL, ET_GROUND, PRT_NONE, WT_ALL));
	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("vehicle - medium",	150.0f,	"vehicle_medium.mesh",	true, AT_ALL, ET_GROUND, PRT_NONE, WT_ALL));
//	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("vehicle - heavy",		75.0f,	"vehicle_heavy.mesh",	true));
	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("wall - #1",			50.0f,	"wall_1.mesh",			true, AT_ALL, ET_NONE, PRT_NONE, WT_NONE));
//	PartDescManagerTemp::getSingletonPtr()->add(new	BodyDesc("wall - #2",			50.0f,	"wall_2.mesh",			true));

	PartDescManagerTemp::getSingletonPtr()->add(new	EnergyShieldDesc("energy shield - light",	10.0f,	"energy_shield.mesh",	0.4f));
	PartDescManagerTemp::getSingletonPtr()->add(new	EnergyShieldDesc("energy shield - medium",	20.0f,	"energy_shield.mesh",	0.7f));
	PartDescManagerTemp::getSingletonPtr()->add(new	EnergyShieldDesc("energy shield - heavy",	30.0f,	"energy_shield.mesh",	1.0f));

	PartDescManagerTemp::getSingletonPtr()->add(new	EngineDesc("engine - air",			10.0f,	100.0f,	500.0f,	EngineDesc::DT_AIR));
	PartDescManagerTemp::getSingletonPtr()->add(new	EngineDesc("engine - ground",		20.0f,	200.0f,	700.0f,	EngineDesc::DT_GROUND));

//	PartDescManagerTemp::getSingletonPtr()->add(new	EngineDesc("explosive - light",		1.0f,	10.0f,	3.0f));
//	PartDescManagerTemp::getSingletonPtr()->add(new	EngineDesc("explosive - medium",	1.0f,	20.0f,	5.0f));
//	PartDescManagerTemp::getSingletonPtr()->add(new	EngineDesc("explosive - heavy",		1.0f,	30.0f,	8.0f));

	PartDescManagerTemp::getSingletonPtr()->add(new	ReactorDesc("power reactor - light",	10.0f,	150.0f,	10.0f));
	PartDescManagerTemp::getSingletonPtr()->add(new	ReactorDesc("power reactor - medium",	20.0f,	250.0f,	20.0f));
	PartDescManagerTemp::getSingletonPtr()->add(new	ReactorDesc("power reactor - heavy",	30.0f,	350.0f,	30.0f));

	PartDescManagerTemp::getSingletonPtr()->add(new	WeaponDesc("weapon - light",	10.0f,	"weapon_light.mesh",	true,	10.0f,	100.0f,	0.5f,	45.0f,	800.0f));
	PartDescManagerTemp::getSingletonPtr()->add(new	WeaponDesc("weapon - medium",	20.0f,	"weapon_medium.mesh",	true,	20.0f,	300.0f,	1.0f,	25.0f,	500.0f));
//	PartDescManagerTemp::getSingletonPtr()->add(new	WeaponDesc("weapon - heavy",	30.0f,	"weapon_heavy.mesh",	true,	30.0f,	600.0f,	4.0f,	25.0f,	200.0f));

	// ObjectTemp Descriptors

	//*

	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Grass #1", PartDescManagerTemp::getSingletonPtr()->getByName("grass1")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Grass #2", PartDescManagerTemp::getSingletonPtr()->getByName("grass2")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Grass #3", PartDescManagerTemp::getSingletonPtr()->getByName("grass3")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Grass #4", PartDescManagerTemp::getSingletonPtr()->getByName("grass4")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Grass #5", PartDescManagerTemp::getSingletonPtr()->getByName("grass5")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Grass #6", PartDescManagerTemp::getSingletonPtr()->getByName("grass6")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Grass #7", PartDescManagerTemp::getSingletonPtr()->getByName("grass7")->isBodyDesc()));

	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #1", PartDescManagerTemp::getSingletonPtr()->getByName("shrub1")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #2", PartDescManagerTemp::getSingletonPtr()->getByName("shrub2")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #3", PartDescManagerTemp::getSingletonPtr()->getByName("shrub3")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #4", PartDescManagerTemp::getSingletonPtr()->getByName("shrub4")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #5", PartDescManagerTemp::getSingletonPtr()->getByName("shrub5")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #6", PartDescManagerTemp::getSingletonPtr()->getByName("shrub6")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #7", PartDescManagerTemp::getSingletonPtr()->getByName("shrub7")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #8", PartDescManagerTemp::getSingletonPtr()->getByName("shrub8")->isBodyDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(new PlantDesc("Shrub #9", PartDescManagerTemp::getSingletonPtr()->getByName("shrub9")->isBodyDesc()));

	ObjectDescManagerTemp::getSingletonPtr()->add(
		new BuildingDesc(
			"Wall",
			PartDescManagerTemp::getSingletonPtr()->getByName("armour - heavy")->isArmourDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("wall - #1")->isBodyDesc(),
			NULL));
	ObjectDescManagerTemp::getSingletonPtr()->add(
		new PowerPlantDesc(
			"Fussion Power Plant",
			PartDescManagerTemp::getSingletonPtr()->getByName("armour - heavy")->isArmourDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("power plant - #1")->isBodyDesc(),
			NULL,
			PartDescManagerTemp::getSingletonPtr()->getByName("power reactor - light")->isPowerReactorDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(
		new PowerPlantDesc(
			"Geothermal Power Plant",
			PartDescManagerTemp::getSingletonPtr()->getByName("armour - heavy")->isArmourDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("power plant - #2")->isBodyDesc(),
			NULL,
			PartDescManagerTemp::getSingletonPtr()->getByName("power reactor - light")->isPowerReactorDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(
		new FortificationDesc(
			"Gun Tower",
			PartDescManagerTemp::getSingletonPtr()->getByName("armour - heavy")->isArmourDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("tower - heavy")->isBodyDesc(),
			NULL,
			PartDescManagerTemp::getSingletonPtr()->getByName("weapon - medium")->isWeaponDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(
		new VehicleDesc(
			"Tank",
			PartDescManagerTemp::getSingletonPtr()->getByName("armour - heavy")->isArmourDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("vehicle - medium")->isBodyDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("energy shield - heavy")->isEnergyShieldDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("engine - ground")->isEngineDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("weapon - medium")->isWeaponDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(
		new VehicleDesc(
			"Rapid Fire Tank",
			PartDescManagerTemp::getSingletonPtr()->getByName("armour - heavy")->isArmourDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("vehicle - light")->isBodyDesc(),
			NULL,
			PartDescManagerTemp::getSingletonPtr()->getByName("engine - ground")->isEngineDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("weapon - light")->isWeaponDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(
		new VehicleDesc(
			"Predator",
			PartDescManagerTemp::getSingletonPtr()->getByName("armour - heavy")->isArmourDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("plane - heavy")->isBodyDesc(),
			NULL,
			PartDescManagerTemp::getSingletonPtr()->getByName("engine - air")->isEngineDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("weapon - light")->isWeaponDesc()));
	ObjectDescManagerTemp::getSingletonPtr()->add(
		new VehicleDesc(
			"Blade",
			PartDescManagerTemp::getSingletonPtr()->getByName("armour - heavy")->isArmourDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("plane - medium")->isBodyDesc(),
			NULL,
			PartDescManagerTemp::getSingletonPtr()->getByName("engine - air")->isEngineDesc(),
			PartDescManagerTemp::getSingletonPtr()->getByName("weapon - light")->isWeaponDesc()));

	//*/

	// Objects

	//*
	struct ObjData {

		string	m_name;
		string	m_player;
		Vector3	m_position;

	};

	/*

// locate position element & the buffer to go with it
const VertexElement* posElem = vertexData->vertexDeclaration->findElementBySemantic(VES_POSITION);
HardwareVertexBufferSharedPtr vbuf = vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
// lock the buffer for reading
unsigned char* pVertex = static_cast<unsigned char*>(
   vbuf->lock(HardwareBuffer::HBL_READ_ONLY));
Real* pReal;
Vector3 pos;
size_t i = 0;
for (i = 0; i < vertexData->vertexCount; ++i, pVertex += vbuf->getVertexSize())
{
   posElem->baseVertexPointerToElement(pVertex, &pReal);

   pos.x = *pReal++;
   pos.y = *pReal++;
   pos.z = *pReal++;

}
vbuf->unlock(); 
*/

	/*
	CompositorManager::getSingletonPtr()->addCompositor(m_viewport, "Old Movie");
	CompositorManager::getSingletonPtr()->setCompositorEnabled(m_viewport, "Old Movie", true);
	//*/

	/*
 using namespace Ogre;

   // Convert screen positions into rays in worldspace
   Ray topLeft = mCamera->getCameraToViewportRay(left, top);
   Ray topRight = mCamera->getCameraToViewportRay(right, top);
   Ray bottomLeft = mCamera->getCameraToViewportRay(left, bottom);
   Ray bottomRight = mCamera->getCameraToViewportRay(right, bottom);

   // Determine the boundry planes using the rays and use these to make up the PlaneBoundedVolume
   // Remember anticlockwise winding to ensure the plane normals point inwards
   PlaneBoundedVolume vol;
   vol.planes.push_back(Plane(topLeft.getOrigin(), topLeft.getPoint(100), topRight.getPoint(100)));   // top plane
   vol.planes.push_back(Plane(topLeft.getOrigin(), bottomLeft.getPoint(100), topLeft.getPoint(100)));   // left plane
   vol.planes.push_back(Plane(topLeft.getOrigin(), bottomRight.getPoint(100), bottomLeft.getPoint(100)));   // bottom plane
   vol.planes.push_back(Plane(topLeft.getOrigin(), topRight.getPoint(100), bottomRight.getPoint(100)));   // right plane
   vol.planes.push_back(Plane(topLeft.getPoint(10000), bottomLeft.getPoint(10000), topRight.getPoint(10000)));   // far plane
   //! far plane could also be coded as the horizontal plane below which the terrain never drops, might be better

   // Setup the final data structure required by the SceneQuery
   PlaneBoundedVolumeList volList;
   volList.push_back(vol);
   // Create the query
   PlaneBoundedVolumeListSceneQuery* boxQuery = mSceneMgr->createPlaneBoundedVolumeQuery(volList);
   // Execute the query
    SceneQueryResult &result = boxQuery->execute();

   // Loop over the results and perform your logic
   // ... 
	//*/

	const int size = 32;

	const ObjData objData[size] = {

		"Grass #1",					"nature",	getTerrainHeightVec(Vector3(200, 0, 200)),
		"Grass #2",					"nature",	getTerrainHeightVec(Vector3(210, 0, 200)),
		"Grass #3",					"nature",	getTerrainHeightVec(Vector3(220, 0, 200)),
		"Grass #4",					"nature",	getTerrainHeightVec(Vector3(230, 0, 200)),
		"Grass #5",					"nature",	getTerrainHeightVec(Vector3(240, 0, 200)),
		"Grass #6",					"nature",	getTerrainHeightVec(Vector3(250, 0, 200)),
		"Grass #7",					"nature",	getTerrainHeightVec(Vector3(260, 0, 200)),

		"Shrub #1",					"nature",	getTerrainHeightVec(Vector3(200, 0, 210)),
		"Shrub #2",					"nature",	getTerrainHeightVec(Vector3(210, 0, 210)),
		"Shrub #3",					"nature",	getTerrainHeightVec(Vector3(220, 0, 210)),
		"Shrub #4",					"nature",	getTerrainHeightVec(Vector3(230, 0, 210)),
		"Shrub #5",					"nature",	getTerrainHeightVec(Vector3(240, 0, 210)),
		"Shrub #6",					"nature",	getTerrainHeightVec(Vector3(250, 0, 210)),
		"Shrub #7",					"nature",	getTerrainHeightVec(Vector3(260, 0, 210)),
		"Shrub #8",					"nature",	getTerrainHeightVec(Vector3(270, 0, 210)),
		"Shrub #9",					"nature",	getTerrainHeightVec(Vector3(280, 0, 210)),

		"Wall",						"enemy",	getTerrainHeightVec(Vector3(230, 0, 290)),
		"Wall",						"enemy",	getTerrainHeightVec(Vector3(238, 0, 290)),
		"Wall",						"enemy",	getTerrainHeightVec(Vector3(246, 0, 290)),
		"Wall",						"enemy",	getTerrainHeightVec(Vector3(254, 0, 290)),
		"Wall",						"enemy",	getTerrainHeightVec(Vector3(262, 0, 290)),
		"Fussion Power Plant",		"enemy",	getTerrainHeightVec(Vector3(250, 0, 250)),
		"Geothermal Power Plant",	"enemy",	getTerrainHeightVec(Vector3(270, 0, 250)),
		"Gun Tower",				"enemy",	getTerrainHeightVec(Vector3(250, 0, 230)),
		"Gun Tower",				"enemy",	getTerrainHeightVec(Vector3(250, 0, 235)),
		"Tank",						"enemy",	getTerrainHeightVec(Vector3(270, 0, 220)),
		"Tank",						"enemy",	getTerrainHeightVec(Vector3(290, 0, 220)),
		"Rapid Fire Tank",			"enemy",	getTerrainHeightVec(Vector3(310, 0, 220)),

		"Tank",						"human",	getTerrainHeightVec(Vector3(280, 0, 270)),
		"Rapid Fire Tank",			"human",	getTerrainHeightVec(Vector3(300, 0, 270)),
		"Tank",						"human",	getTerrainHeightVec(Vector3(320, 0, 270)),
		"Rapid Fire Tank",			"human",	getTerrainHeightVec(Vector3(340, 0, 270))

	};

	for (int i = 16; i < size; i++) {

		o = ObjectManagerTemp::getSingletonPtr()->create(
			ObjectDescManagerTemp::getSingletonPtr()->getByName(objData[i].m_name),
			PlayerManager::getSingletonPtr()->getByName(objData[i].m_player),
			objData[i].m_position);
	}

	PartDescManagerTemp::getSingletonPtr()->add(new TeleporterDesc("Teleporter", 750.0f, "teleporter_gate.mesh", true, "teleporter_active"));

	/*
	t = new Teleporter(NULL);
	t->setDesc(PartDescManagerTemp::getSingletonPtr()->getByName("Teleporter"));
	t->setPosition(getTerrainHeightVec(230, 220));

	t = new Teleporter(NULL);
	t->setDesc(PartDescManagerTemp::getSingletonPtr()->getByName("Teleporter"));
	t->setPosition(getTerrainHeightVec(330, 220));
	t->setOrientation(Quaternion(Radian(Degree(145.0f)), Vector3::UNIT_Y));
	*/

	//*/

	/*
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
	//*/

	/*
	r = new Rectangle2D(true);
	r->setCorners(0.5, -0.5, 1.0, -1.0);
	r->setRenderQueueGroup(RENDER_QUEUE_BACKGROUND);
	r->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 100000.0*Vector3::UNIT_SCALE));
	r->setMaterial("rect");
	SceneNode* s1 = createSceneNode();
	s1->attachObject(r);
	//*/

	/*
	ps = createParticleSystem("fence");

	sn = createSceneNode();
	sn->attachObject(ps);
	sn->setPosition(getTerrainHeightVec(230, 200) + Vector3(0, 5, 0));
	//*/

	m_root->startRendering();
}

//------------------------------------------------------------------------------

void Core::quit() {

	m_notQuit = false;
}

//------------------------------------------------------------------------------

void getScreenCoordinates(const Vector3& position, Real& x, Real& y)
{
   Vector3 hcsPosition =
	   Core::getSingletonPtr()->getCamera()->getProjectionMatrix()
	   *
	   (Core::getSingletonPtr()->getCamera()->getViewMatrix() * position);

   x = 1.0f - ((hcsPosition.x * 0.5f) + 0.5f);// 0 <= x <= 1 // left := 0,right := 1
   y = ((hcsPosition.y * 0.5f) + 0.5f);// 0 <= y <= 1 // bottom := 0,top := 1
}

//------------------------------------------------------------------------------

void Core::preViewportUpdate(const RenderTargetViewportEvent& evt) {

	m_sceneManager->clearSpecialCaseRenderQueues();

	if (evt.source != m_viewport) {

		m_sceneManager->addSpecialCaseRenderQueue(RENDER_QUEUE_OVERLAY);
		m_sceneManager->setSpecialCaseRenderQueueMode(SceneManager::SCRQM_EXCLUDE);
	}
}

//------------------------------------------------------------------------------

bool Core::frameStarted(const FrameEvent& evt) {

	m_elapsedTime += evt.timeSinceLastFrame;

	// Speed Control.

	static float m_timeSinceLastFrame = 0.0f;

	if (evt.timeSinceLastFrame < 1.0f / 30.0f)

		m_timeSinceLastFrame = evt.timeSinceLastFrame;

	else

		m_timeSinceLastFrame = 1.0f / 30.0f;

	// Update system.

	if (m_gameSpeed) {

		BattleFieldCamera::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		Gui::getSingletonPtr()->updateGameInfo();
//		Gui::getSingletonPtr()->updateViewer();
		ObjectManagerTemp::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
		PlayerManager::getSingletonPtr()->update(m_timeSinceLastFrame * m_gameSpeed);
	}

	static AxisAlignedBox box;

	m_sceneManager->getOption("Size", &box);
/*
	static int mapX = box.getMaximum().x;
	static int mapZ = box.getMaximum().z;

	static float timeToNextCheck = 1000.0f;

	timeToNextCheck += m_elapsedTime;

	if (timeToNextCheck >= 1000.0f) {

		timeToNextCheck = 0.0f;

		static const int size = 512;
		static TexturePtr m_texturePtr = (TexturePtr)TextureManager::getSingletonPtr()->getByName(
			"Demo_Map_fog_of_war");
		//Vector3 v = o1->getPosition();
		//Vector3 v1 = o2->getPosition();

		static HardwarePixelBufferSharedPtr m_buffer = m_texturePtr->getBuffer(0, 0);

		m_buffer->lock(HardwareBuffer::HBL_DISCARD);

		const PixelBox &pb = m_buffer->getCurrentLock();

		for (unsigned int z = 0; z < size; z++) {

			unsigned int* data = static_cast<unsigned int*>(pb.data) + z * pb.rowPitch;

			for (unsigned int x = 0; x < size; x++) {

				//if (
					
					
					//((x - v.x / mapX * 512) * (x - v.x / mapX * 512) + (z - v.z / mapZ * 512) * (z - v.z / mapZ * 512) <= 1024)

					//||

					//(((x - v1.x / mapX * 512) * (x - v1.x / mapX * 512) + (z - v1.z / mapZ * 512) * (z - v1.z / mapZ * 512) <= 1024))

					//)

					data[x] = 0x00000000;

				//else

					//data[x] = 0xFF000000;

			}

		}

		m_buffer->unlock();

	}

//*/


	m_inputReader->capture();

	if (m_inputReader->isKeyDown(KC_ESCAPE))

		return false;


	// Camera

	float speed = 15.0f;

	if (m_inputReader->isKeyDown(KC_RIGHT))// || m_inputReader->isKeyDown(KC_D))

		m_camera->moveRelative(Vector3( speed * evt.timeSinceLastFrame, 0, 0));

	else if (m_inputReader->isKeyDown(KC_LEFT))// || m_inputReader->isKeyDown(KC_A))

		m_camera->moveRelative(Vector3(-speed * evt.timeSinceLastFrame, 0, 0));

	if (m_inputReader->isKeyDown(KC_UP))// || m_inputReader->isKeyDown(KC_W))

		m_camera->moveRelative(Vector3(0, 0, -speed * evt.timeSinceLastFrame));

	else if (m_inputReader->isKeyDown(KC_DOWN))// || m_inputReader->isKeyDown(KC_S))

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

		for (itr = result.begin(); itr != result.end(); itr++) {

			if (itr->movable && (itr->distance <= 512.0f) && (itr->movable->getUserAny().isEmpty() == false)) {

				Part* part = ogreAnyToPart(itr->movable->getUserAny());

				if ((part->m_type != Part::PT_ENERGY_SHIELD) && (part->m_parent->m_state != ObjectTemp::OS_DEAD) && (part->m_parent->m_type != ObjectTemp::OT_MISSILE)) {

					m_objectUnderMouse = part->m_parent;

					break;
				}
			}
		}

		if (m_objectUnderMouse == NULL) {

			for (itr = result.begin(); itr != result.end(); itr++) {

				if (itr != result.end() && itr->worldFragment) {

					m_mouse3DPos = itr->worldFragment->singleIntersection;

					break;

				}
			}
		}
	}

	if (m_objectUnderMouse && m_objectUnderMouse->m_state != ObjectTemp::OS_DEAD) {

		Gui::getSingletonPtr()->m_objectInfoText->setPosition(
			CEGUI::Point(m_mouse2DPos.x - 0.1f, m_mouse2DPos.y - 0.065f));
		Gui::getSingletonPtr()->m_objectInfoText->setVisible(true);

		if (m_activePlayer == m_objectUnderMouse->m_player) {

			Gui::getSingletonPtr()->m_objectInfoText->setText(m_objectUnderMouse->toStringShort());
		}

		else {

			Gui::getSingletonPtr()->m_objectInfoText->setText(m_objectUnderMouse->toStringEnemy());
		}

	} else {

		Gui::getSingletonPtr()->m_objectInfo->setVisible(false);
		Gui::getSingletonPtr()->m_objectInfoText->setVisible(false);
	}

	return m_notQuit;
}

//------------------------------------------------------------------------------

void Core::keyPressed(KeyEvent* e) {

	static ObjectTemp* o = NULL;

	m_keys[e->getKey()] = true;

	switch (e->getKey()) {

		case KC_F1: Console::getSingletonPtr()->changeVisible();				break;
		case KC_F2: Gui::getSingletonPtr()->changeViewerVisible();				break;
		case KC_F5: ConstructionPanel::getSingletonPtr()->changeVisible();		break;
		case KC_F6: Gui::getSingletonPtr()->changeObjectViewerVisible();		break;
		case KC_F7: Gui::getSingletonPtr()->changePartViewerVisible();			break;
		case KC_F8: Gui::getSingletonPtr()->changePartDescViewerVisible();		break;

		// Pause.

		case KC_P:

			if (m_gameSpeed)

				m_gameSpeed = 0.0f;

			else

				m_gameSpeed = 1.0f;

			break;

		// Increase game speed.

		case KC_ADD:

			if (m_gameSpeed < 2.0f)	m_gameSpeed += 0.1f;
			if (m_gameSpeed > 2.0f)	m_gameSpeed  = 2.0f;

			break;

		// Decrease game speed.

		case KC_SUBTRACT:

			if (m_gameSpeed > 0.0f)	m_gameSpeed -= 0.1f;
			if (m_gameSpeed < 0.0f)	m_gameSpeed  = 0.0f;

			break;

		// Follow an object.

		case KC_F:

			if (o = ObjectManagerTemp::getSingletonPtr()->getFirstSelected())

				BattleFieldCamera::getSingletonPtr()->follow(o);

			else

				BattleFieldCamera::getSingletonPtr()->follow(NULL);

			break;

		// Track an object.

		case KC_T:

			if (o = ObjectManagerTemp::getSingletonPtr()->getFirstSelected())

				BattleFieldCamera::getSingletonPtr()->track(o);

			else

				BattleFieldCamera::getSingletonPtr()->track(NULL);

			break;

		// Make a screenshot.

		case KC_SYSRQ:

			{
				SYSTEMTIME st;
				char fileName[MAX_PATH];

				GetLocalTime(&st);

				sprintf(fileName, "..\\screens\\WarGAME.screen.%i-%.2i-%.2i.%.2i-%.2i-%.2i.png",
					st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

				m_renderWindow->writeContentsToFile(fileName);

				break;
			}

		// Shadows on/off

		case KC_S:

			if (e->isControlDown() && e->isShiftDown())

				if (m_sceneManager->getShadowTechnique() == SHADOWTYPE_NONE)

					m_sceneManager->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);

				else

					m_sceneManager->setShadowTechnique(SHADOWTYPE_NONE);

			break;

		case KC_RETURN:

			Console::getSingletonPtr()->enter();

			break;

	} // switch (e->getKey())


	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectChar(e->getKeyChar());
	CEGUI::System::getSingletonPtr()->injectKeyDown(e->getKey());

	e->consume();
}

//------------------------------------------------------------------------------

void Core::keyReleased(KeyEvent* e) {

	m_keys[e->getKey()] = false;


	// Update CEGUI.

	CEGUI::System::getSingletonPtr()->injectKeyUp(e->getKey());

	e->consume();
}

//------------------------------------------------------------------------------

void Core::mousePressed(MouseEvent* e) {

	if (Gui::getSingletonPtr()->isMouseOverGui() == false) {

		switch (e->getButtonID()) {

			case MouseEvent::BUTTON0_MASK:

				if (m_state == NORMAL) {

					m_mouseButton[0] = true;

					if (m_objectUnderMouse && (m_objectUnderMouse->m_player == m_activePlayer)) {

						if (m_keys[KC_LSHIFT] || m_keys[KC_RSHIFT]) {

							if (ObjectManagerTemp::getSingletonPtr()->isSelected(m_objectUnderMouse)) {

								ObjectManagerTemp::getSingletonPtr()->deselect(m_objectUnderMouse);

							} else {

								ObjectManagerTemp::getSingletonPtr()->select(m_objectUnderMouse);

								m_lastSelectedObject = m_objectUnderMouse;
							}

						} else {

							ObjectManagerTemp::getSingletonPtr()->deselectAll();

							ObjectManagerTemp::getSingletonPtr()->select(m_objectUnderMouse);

							m_lastSelectedObject = m_objectUnderMouse;
						}

					} else if (!(m_keys[KC_LSHIFT]) && !(m_keys[KC_RSHIFT])) {

						ObjectManagerTemp::getSingletonPtr()->deselectAll();

						m_lastSelectedObject = NULL;
					}

				} else {

					ObjectManagerTemp::getSingletonPtr()->create(
						Gui::getSingletonPtr()->getSelectedObjectDesc(),
						m_activePlayer,
						getTerrainHeightVec(m_mouse3DPos));

					m_state = NORMAL;
				}

				break;

			case MouseEvent::BUTTON1_MASK:

				m_mouseButton[1] = true;

				if (m_mouse3DPos != Vector3(-1.0f)) {

					if (m_keys[KC_LSHIFT] || m_keys[KC_RSHIFT])

						ObjectManagerTemp::getSingletonPtr()->addOrderToSelected(ObjectOrder(ObjectOrder::OOT_MOVE, m_mouse3DPos));

					else

						ObjectManagerTemp::getSingletonPtr()->setOrderToSelected(ObjectOrder(ObjectOrder::OOT_MOVE, m_mouse3DPos));

				} else if (m_objectUnderMouse && (m_objectUnderMouse->m_player != m_activePlayer)) {

					if (m_keys[KC_LSHIFT] || m_keys[KC_RSHIFT])

						ObjectManagerTemp::getSingletonPtr()->addOrderToSelected(ObjectOrder(ObjectOrder::OOT_ATTACK_OBJECT, Vector3::ZERO, m_objectUnderMouse));

					else

						ObjectManagerTemp::getSingletonPtr()->setOrderToSelected(ObjectOrder(ObjectOrder::OOT_ATTACK_OBJECT, Vector3::ZERO, m_objectUnderMouse));

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

void Core::mouseReleased(MouseEvent* e) {

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
			
void Core::mouseMoved(MouseEvent* e) {

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

void Core::mouseDragged(MouseEvent* e) {

	mouseMoved(e);
}

//------------------------------------------------------------------------------

RaySceneQueryResult Core::whatWouldHit(const Vector3& pos, const Vector3& dir) {

	static RaySceneQuery* raySceneQuery = m_sceneManager->createRayQuery(Ray());
	static Ray ray;

	ray.setOrigin(pos);
	ray.setDirection(dir);

	raySceneQuery->setRay(ray);
	raySceneQuery->setSortByDistance(true);

	return raySceneQuery->execute();
}

//------------------------------------------------------------------------------

float Core::getTerrainHeight(float x, float z) {

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

CEGUI::MouseButton Core::convertOgreButtonToCEGUI(int buttonID) {

	switch (buttonID) {

		case MouseEvent::BUTTON0_MASK: return CEGUI::LeftButton;
		case MouseEvent::BUTTON1_MASK: return CEGUI::RightButton;
		case MouseEvent::BUTTON2_MASK: return CEGUI::MiddleButton;
		case MouseEvent::BUTTON3_MASK: return CEGUI::X1Button;

		default: return CEGUI::LeftButton;
	}
}

//------------------------------------------------------------------------------

ObjectTemp* Core::ogreAnyToObject(Ogre::Any ogreAny) {

	if (ogreAny.getType() == typeid(Body*))

		return Ogre::any_cast<Body*>(ogreAny)->m_parent;

	else if (ogreAny.getType() == typeid(Shield*))

		return Ogre::any_cast<Shield*>(ogreAny)->m_parent;

	else if (ogreAny.getType() == typeid(Weapon*))

		return Ogre::any_cast<Weapon*>(ogreAny)->m_parent;

	return NULL;
}

//------------------------------------------------------------------------------

Part* Core::ogreAnyToPart(Ogre::Any ogreAny) {

	if (ogreAny.getType() == typeid(Body*))

		return Ogre::any_cast<Body*>(ogreAny);

	else if (ogreAny.getType() == typeid(Shield*))

		return Ogre::any_cast<Shield*>(ogreAny);

	else if (ogreAny.getType() == typeid(Weapon*))

		return Ogre::any_cast<Weapon*>(ogreAny);

	return NULL;
}

//------------------------------------------------------------------------------

string Core::positionToStr(float x, float z) {

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

	return string(textNS) + textWE;
}

//------------------------------------------------------------------------------
