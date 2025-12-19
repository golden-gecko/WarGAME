#include "PCH.hpp"

#include "Application.hpp"
#include "Scene.hpp"

Scene* scene;

Application::Application(const Ogre::String& pluginFileName, const Ogre::String& configFileName, const Ogre::String& logFileName) : Ogre::Root(pluginFileName, configFileName, logFileName), isRunning(true), input(NULL)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load("Resources.cfg");
 
    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
 
    Ogre::String secName, typeName, archName;

    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;

        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
            archName, typeName, secName);
        }
    }

    // Load from file or show configuration dialog.
    if (restoreConfig() || showConfigDialog())
    {
        saveConfig();

        renderWindow = initialise(true, "WarGAME");

        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();


        scene = new Scene("Level #1");
        scene->load();

        camera = scene->createCamera("Camera #1");
        camera->setFixedYawAxis(true, Ogre::Vector3::UNIT_Y);
        
        viewport = renderWindow->addViewport(camera);
        viewport->setBackgroundColour(Ogre::ColourValue(0.6f, 0.8f, 0.9f));
 
        camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

        /*
        // Create terrain.
        terrainOptions = OGRE_NEW Ogre::TerrainGlobalOptions();
            
        terrainGroup = OGRE_NEW Ogre::TerrainGroup(sceneManager, Ogre::Terrain::ALIGN_X_Z, 513, 12000.0f);
        terrainGroup->setFilenameConvention(Ogre::String("BasicTutorial3Terrain"), Ogre::String("dat"));
        terrainGroup->setOrigin(Ogre::Vector3::ZERO);

        // Configure global
        terrainOptions->setMaxPixelError(8);
        // testing composite map
        terrainOptions->setCompositeMapDistance(3000);

        Ogre::Vector3 lightdir(0.55, -0.3, 0.75);
        lightdir.normalise();
 
        // Create light.
        Ogre::Light* light = sceneManager->createLight("tstLight");
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        light->setDirection(lightdir);
        light->setDiffuseColour(Ogre::ColourValue::White);
        light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
 
        // Important to set these so that the terrain knows what to use for derived (non-realtime) data
        terrainOptions->setLightMapDirection(light->getDerivedDirection());
        terrainOptions->setCompositeMapAmbient(sceneManager->getAmbientLight());
        terrainOptions->setCompositeMapDiffuse(light->getDiffuseColour());
 
        // Configure default import settings for if we use imported image
        Ogre::Terrain::ImportData& defaultimp = terrainGroup->getDefaultImportSettings();
        defaultimp.terrainSize = 513;
        defaultimp.worldSize = 12000.0f;
        defaultimp.inputScale = 600;
        defaultimp.minBatchSize = 33;
        defaultimp.maxBatchSize = 65;
        defaultimp.layerList.resize(3);
        defaultimp.layerList[0].worldSize = 100;
        defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_diffusespecular.dds");
        defaultimp.layerList[0].textureNames.push_back("dirt_grayrocky_normalheight.dds");
        defaultimp.layerList[1].worldSize = 30;
        defaultimp.layerList[1].textureNames.push_back("grass_green-01_diffusespecular.dds");
        defaultimp.layerList[1].textureNames.push_back("grass_green-01_normalheight.dds");
        defaultimp.layerList[2].worldSize = 200;
        defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_diffusespecular.dds");
        defaultimp.layerList[2].textureNames.push_back("growth_weirdfungus-03_normalheight.dds");

        for (long x = 0; x <= 0; ++x)
        {
            for (long y = 0; y <= 0; ++y)
            {
                Ogre::String filename = terrainGroup->generateFilename(x, y);

                if (Ogre::ResourceGroupManager::getSingleton().resourceExists(terrainGroup->getResourceGroup(), filename))
                {
                    terrainGroup->defineTerrain(x, y);
                }
                else
                {
                    Ogre::Image img;
                    img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

                    if (x % 2 != 0)
                    {
                        img.flipAroundY();
                    }

                    if (y % 2 != 0)
                    {
                        img.flipAroundX();
                    }

                    terrainGroup->defineTerrain(x, y, &img);
                }
            }
        }

        terrainGroup->loadAllTerrains(true);

        Ogre::TerrainGroup::TerrainIterator ti = terrainGroup->getTerrainIterator();

        while(ti.hasMoreElements())
        {
            Ogre::Terrain* terrain = ti.getNext()->instance;

            Ogre::TerrainLayerBlendMap* blendMap0 = terrain->getLayerBlendMap(1);
            Ogre::TerrainLayerBlendMap* blendMap1 = terrain->getLayerBlendMap(2);

            Ogre::Real minHeight0 = 70;
            Ogre::Real fadeDist0 = 40;
            Ogre::Real minHeight1 = 70;
            Ogre::Real fadeDist1 = 15;

            float* pBlend0 = blendMap0->getBlendPointer();
            float* pBlend1 = blendMap1->getBlendPointer();

            for (Ogre::uint16 y = 0; y < terrain->getLayerBlendMapSize(); ++y)
            {
                for (Ogre::uint16 x = 0; x < terrain->getLayerBlendMapSize(); ++x)
                {
                    Ogre::Real tx, ty;
 
                    blendMap0->convertImageToTerrainSpace(x, y, &tx, &ty);
                    Ogre::Real height = terrain->getHeightAtTerrainPosition(tx, ty);
                    Ogre::Real val = (height - minHeight0) / fadeDist0;
                    val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
                    *pBlend0++ = val;
 
                    val = (height - minHeight1) / fadeDist1;
                    val = Ogre::Math::Clamp(val, (Ogre::Real)0, (Ogre::Real)1);
                    *pBlend1++ = val;
                }
            }

            blendMap0->dirty();
            blendMap1->dirty();
            blendMap0->update();
            blendMap1->update();
        }

        terrainGroup->freeTemporaryResources();
        */

        /*
        // Create object.
        Ogre::Entity* entity = sceneManager->createEntity("OgreHead #1", "ogrehead.mesh");

        Ogre::SceneNode* sceneNode = sceneManager->getRootSceneNode()->createChildSceneNode();
        sceneNode->attachObject(entity);
        sceneNode->setPosition(Ogre::Vector3::ZERO);
        */

        // Initialize input.
        input = new Input(renderWindow, camera);
 
        // Register as a window listener.
        Ogre::WindowEventUtilities::addWindowEventListener(renderWindow, this);

        // Register as frame listener.
        addFrameListener(this);
    }
}

bool Application::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    // Capture input.
    input->capture();

    // Close application.
    if (input->isKeyDown(OIS::KeyCode::KC_ESCAPE))
    {
        isRunning = false;
    }

    // Move camera.
    Ogre::Vector3 cameraVelocity = Ogre::Vector3::ZERO;

    if (input->isKeyDown(OIS::KeyCode::KC_W))
    {
        cameraVelocity += Ogre::Vector3::NEGATIVE_UNIT_Z;
    }
    else if (input->isKeyDown(OIS::KeyCode::KC_S))
    {
        cameraVelocity += Ogre::Vector3::UNIT_Z;
    }

    if (input->isKeyDown(OIS::KeyCode::KC_Q))
    {
        cameraVelocity += Ogre::Vector3::UNIT_Y;
    }
    else if (input->isKeyDown(OIS::KeyCode::KC_Z))
    {
        cameraVelocity += Ogre::Vector3::NEGATIVE_UNIT_Y;
    }

    if (input->isKeyDown(OIS::KeyCode::KC_A))
    {
        cameraVelocity += Ogre::Vector3::NEGATIVE_UNIT_X;
    }
    else if (input->isKeyDown(OIS::KeyCode::KC_D))
    {
        cameraVelocity += Ogre::Vector3::UNIT_X;
    }

    camera->moveRelative(cameraVelocity * 20.0f * evt.timeSinceLastFrame);

    // Update objects.
    scene->update(evt.timeSinceLastFrame);

    return isRunning;
}
