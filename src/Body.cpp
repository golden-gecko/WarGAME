
//------------------------------------------------------------------------------
// Body.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"

#include "PartDescManager.h"

#include "Body.h"

//------------------------------------------------------------------------------

Body::Body(Object* parent, string bodyName)

	:	Part(parent),
		m_bodyDesc(NULL),
		m_entity(NULL),
		m_sceneNode(NULL)

{

	m_sceneNode = Core::getSingletonPtr()->createSceneNode();

	setBodyDesc(bodyName);

	m_hitPoints = m_bodyDesc->m_maxHitPoints;

}

//------------------------------------------------------------------------------

Body::Body(Object* parent, void* bodyDesc)

	:	Part(parent),
		m_bodyDesc(NULL),
		m_entity(NULL),
		m_sceneNode(NULL)

{

	m_sceneNode = Core::getSingletonPtr()->createSceneNode();

	setBodyDesc((BodyDesc*)bodyDesc);

	m_hitPoints = m_bodyDesc->m_maxHitPoints;

}

//------------------------------------------------------------------------------

Body::~Body(){

	Core::getSingletonPtr()->destroyEntity(m_entity);
	Core::getSingletonPtr()->destroySceneNode(m_sceneNode);

}

//------------------------------------------------------------------------------

Vector3 Body::getDimensions(){

	AxisAlignedBox box;

	box = m_entity->getBoundingBox();

	return box.getMaximum() - box.getMinimum();

}

//------------------------------------------------------------------------------

Vector3 Body::getPosition(){

	return m_sceneNode->getPosition();

}

//------------------------------------------------------------------------------

void Body::setBodyDesc(string bodyName){

	setBodyDesc((BodyDesc*)PartDescManager::getSingletonPtr()->getByName(bodyName));

}

//------------------------------------------------------------------------------

void Body::setBodyDesc(BodyDesc* bodyDesc){

	if (bodyDesc && (bodyDesc->m_type == PartDesc::PDT_BODY)) {

		m_bodyDesc = bodyDesc;

		m_entity = Core::getSingletonPtr()->createEntity(m_bodyDesc->m_meshName);
		m_entity->setCastShadows(m_bodyDesc->m_castShadows);
		m_entity->setUserAny(Any(this));

		m_sceneNode->attachObject(m_entity);

	} else {

		Core::getSingletonPtr()->destroyEntity(m_entity);

		m_bodyDesc = NULL;
		m_entity = NULL;

	}

}

//------------------------------------------------------------------------------

void Body::setPosition(float x, float y, float z){

	m_sceneNode->setPosition(x, y, z);

}

//------------------------------------------------------------------------------

void Body::setPosition(const Vector3& position){

	m_sceneNode->setPosition(position);

}

//------------------------------------------------------------------------------

void Body::setScale(float scale){

	m_sceneNode->setScale(scale, scale, scale);

}

//------------------------------------------------------------------------------

void Body::setScale(float x, float y, float z){

	m_sceneNode->setScale(x, y, z);

}

//------------------------------------------------------------------------------

void Body::setScale(const Vector3& scale){

	m_sceneNode->setScale(scale);

}

//------------------------------------------------------------------------------

string Body::toString(){

	static char text[512];

	sprintf(text, "");

	return text;

}

//------------------------------------------------------------------------------
