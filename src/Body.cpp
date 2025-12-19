
//------------------------------------------------------------------------------
// Body.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Body.h"
#include "Core.h"
#include "ObjectTemp.h"
#include "PartDescManagerT.h"

//------------------------------------------------------------------------------

Body::Body(ObjectTemp* parent)
	:	Part(parent),
		m_entity(NULL),
		m_sceneNode(NULL)
{
	m_name = "Body #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = PT_BODY;
	m_sceneNode = Core::getSingletonPtr()->createSceneNode();
}

//------------------------------------------------------------------------------

Body::~Body() {

	Core::getSingletonPtr()->destroyEntity(m_entity);
	Core::getSingletonPtr()->destroySceneNode(m_sceneNode);
}

//------------------------------------------------------------------------------

void Body::setDesc(PartDesc* partDesc) {

	Core::getSingletonPtr()->destroyEntity(m_entity);

	if (partDesc && partDesc->isBodyDesc()) {

		Part::setDesc(partDesc);

		m_entity = Core::getSingletonPtr()->createEntity(m_partDesc->isBodyDesc()->m_meshName);
		m_entity->setCastShadows(m_partDesc->isBodyDesc()->m_castShadows);
		m_entity->setUserAny(Any(this));

		m_sceneNode->attachObject(m_entity);

	} else {

		Part::setDesc(NULL);

		m_entity = NULL;
	}
}

//------------------------------------------------------------------------------

Vector3 Body::getDimensions() {

	AxisAlignedBox box;

	box = m_entity->getBoundingBox();

	return box.getMaximum() - box.getMinimum();
}

//------------------------------------------------------------------------------

string Body::toString() {

	if (m_partDesc)

		return "Body\n" + Part::toString() + "\n" + m_partDesc->toString();

	return "Body\n" + Part::toString() + "No Body Desc";
}

//------------------------------------------------------------------------------

bool Body::update(float deltaTime) {

	return true;
}

//------------------------------------------------------------------------------
