
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMesh.h"

#include "Core.h"
#include "PartWithMeshDesc.h"

//------------------------------------------------------------------------------

void PartWithMesh::setPartDesc(PartDesc* partDesc) {

	if (m_partWithMeshDesc) {

		Core::getSingletonPtr()->destroyEntity(m_entity);
		Core::getSingletonPtr()->destroySceneNode(m_sceneNode);
	}

	Part::setPartDesc(partDesc);

	if (m_partWithMeshDesc) {

		m_entity = Core::getSingletonPtr()->createEntity(m_partWithMeshDesc->getMeshName());
		m_entity->setCastShadows(m_partWithMeshDesc->getCastShadows());
		m_entity->setUserAny(Ogre::Any(this));

		m_sceneNode = Core::getSingletonPtr()->createSceneNode();
		m_sceneNode->attachObject(m_entity);
	}
}

//------------------------------------------------------------------------------
