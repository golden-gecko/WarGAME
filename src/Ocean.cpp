
//------------------------------------------------------------------------------
// Ocean.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Ocean.h"

//------------------------------------------------------------------------------

Ocean::Ocean(): m_entity(NULL), m_sceneNode(NULL), m_height(16.0f) {

	/*
	MeshManager::getSingletonPtr()->createPlane(
		"water",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0.0f),
		2048.0f, 2048.0f, 50, 50, true, 1, 1.0f, 1.0f, Vector3::UNIT_Z);

	m_entity = Core::getSingletonPtr()->createEntity("water");
	m_entity->setMaterialName("water");
	m_entity->setUserAny(Any(this));

	m_sceneNode = Core::getSingletonPtr()->createSceneNode();
	m_sceneNode->attachObject(m_entity);
	m_sceneNode->setPosition(1024.0f, m_height, 1024.0f);
	//*/
}

//------------------------------------------------------------------------------
