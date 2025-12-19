#include "PCH.hpp"

#include "Axis.hpp"
#include "City.hpp"
#include "Grid.hpp"
#include "Rectangle.hpp"
#include "Scene.hpp"
#include "Terrain.hpp"
#include "Water.hpp"

void Scene::load()
{
    sceneManager = Ogre::Root::getSingleton().createSceneManager(Ogre::ST_GENERIC, name);
    sceneManager->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
    // sceneManager->setSkyBox(true, "Examples/EarlyMorningSkyBox");
    // sceneManager->setFog(Ogre::FOG_EXP, Ogre::ColourValue(0.9f, 0.9f, 0.9f), 0.005f);

    Ogre::Light* light = sceneManager->createLight();
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(0.4f, -1.0f, 0.8f));

	// Create objects.
    Terrain* terrain = new Terrain("Terrain", this);
    terrain->load();

    objects[terrain->getName()] = terrain;

    // water = new Water("Water", this, terrain);
    // water->load();

	City* city = new City("City", this, Ogre::Vector3(0.0f, 0.01f, 0.0f), Ogre::Vector3(100.0f, 0.0f, 100.0f));
    city->load();

    objects[city->getName()] = city;

	// Create debug objects.
    Debug::Axis* axis = new Debug::Axis("Axis", this);
    axis->load();

    objects[axis->getName()] = axis;

    //Debug::Grid* grid = new Debug::Grid("Grid", this, terrain);
    //grid->load();

	//Debug::Rectangle* rectangle = new Debug::Rectangle("Rectangle", this, city->getPosition(), city->getSize());
	//rectangle->load();
}

void Scene::unload()
{
    Ogre::Root::getSingleton().destroySceneManager(sceneManager);
}

void Scene::update(float time)
{
    for (std::map<std::string, Object*>::iterator i = objects.begin(); i != objects.end(); ++i)
    {
        i->second->update(time);
    }
}

Ogre::Camera* Scene::createCamera(const std::string& name)
{
    Ogre::Camera* camera = sceneManager->createCamera(name);
    camera->setPosition(Ogre::Vector3::UNIT_SCALE * 15.0f);
    camera->lookAt(Ogre::Vector3::ZERO);
    camera->setNearClipDistance(0.5f);

    if (Ogre::Root::getSingleton().getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
    {
        camera->setFarClipDistance(0.0f);
    }
    else
    {
        camera->setFarClipDistance(1000.0f);
    }
    
    return camera;
}
