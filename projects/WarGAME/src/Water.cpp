#include "Dependencies.h"
#include "Water.h"

Water* Ogre::Singleton<Water>::ms_Singleton = NULL;

void Water::init(Ogre::SceneManager* scene, float level)
{
	mScene = scene;
	mLevel = level;
}

void Water::load(const std::string& material)
{
	Ogre::Plane plane;

	plane.normal = Ogre::Vector3::UNIT_Y;

	mMesh = Ogre::MeshManager::getSingleton().createPlane(
		"Water", "Water", plane,
		2500.0f, 2500.0f, 50, 50, true, 1, 1.0f, 1.0f, Ogre::Vector3::UNIT_Z).getPointer();

	mEntity = mScene->createEntity("Water", "Water");
	mEntity->setCastShadows(false);
	mEntity->setMaterialName(material);

	mNode = mScene->getRootSceneNode()->createChildSceneNode();
	mNode->attachObject(mEntity);
	mNode->setPosition(1250.0f, mLevel, 1250.0f);
}

void Water::unload()
{
	mScene->destroySceneNode(mNode->getName());
	mScene->destroyEntity(mEntity);

	Ogre::MeshManager::getSingleton().remove(mMesh->getHandle());
}
