
//------------------------------------------------------------------------------
// Object.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"

#include "PartDescManager.h"

#include "Object.h"

//------------------------------------------------------------------------------

Object::Object(string bodyName, const Vector3& position)

	:	m_name("Object #" + Core::getSingletonPtr()->getDataCounterStr()),
		m_type(OT_OBJECT),
		m_body(NULL),
		m_player(NULL)

{

	m_body = new Body(this, bodyName);

	setPosition(position);

}

//------------------------------------------------------------------------------

Object::Object(void* bodyDesc, const Vector3& position)

	:	m_name("Object #" + Core::getSingletonPtr()->getDataCounterStr()),
		m_type(OT_OBJECT),
		m_body(NULL),
		m_player(NULL)

{

	m_body = new Body(this, bodyDesc);

	setPosition(position);

}

//------------------------------------------------------------------------------

Vector3 Object::getDimensions(){

	return m_body->getDimensions();

}

//------------------------------------------------------------------------------

Vector3 Object::getPosition(){

	return m_body->getPosition();

}

//------------------------------------------------------------------------------

void Object::setDimensionY(float y, bool mode){

	if (mode)

		m_body->setScale(
			y / getDimensions().y,
			y / getDimensions().y,
			y / getDimensions().y);

	else

		m_body->setScale(
			y / getDimensions().x,
			y / getDimensions().y,
			y / getDimensions().z);

}

//------------------------------------------------------------------------------

void Object::setPosition(const Vector3& position){

	m_body->setPosition(position);

}

//------------------------------------------------------------------------------

void Object::setScale(const Vector3& scale){

	m_body->setScale(scale);

}

//------------------------------------------------------------------------------

void Object::setSelected(bool selected){

	m_body->m_sceneNode->showBoundingBox(selected);

}

//------------------------------------------------------------------------------

string Object::toString(){

	static char text[512];

	sprintf(text,
		"\
		Body Name   %s\n\
		Position    %.2f:%.2f:%.2f\n\
		Dimensions  %.2f:%.2f:%.2f\n\
		Hit Points  %.0f/%.0f\n\
		Player Name %s",
		m_body->m_bodyDesc->m_name.c_str(),
		getPosition().x, getPosition().y, getPosition().z,
		getDimensions().x, getDimensions().y, getDimensions().z,
		getHitPoints(), getMaxHitPoints(),
		m_player->getName().c_str());

	return text;

}

//------------------------------------------------------------------------------

bool Object::update(float deltaTime){

	if (m_body->m_hitPoints <= 0.0f)

		return false;

	if (m_orderList.getCount()) {

		switch ((*m_orderList.getFirst()).getType()) {

			case ObjectOrder::OOT_DEFAULT:

				m_orderList.addBack(*m_orderList.getFirst());
				m_orderList.removeFront();

				break;

			case ObjectOrder::OOT_STOP:

				m_orderList.removeAll();

				break;

		}

	}

	return true;

}

//------------------------------------------------------------------------------
