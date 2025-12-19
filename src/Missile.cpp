
//------------------------------------------------------------------------------
// Missile.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"
#include "Missile.h"

//------------------------------------------------------------------------------

Missile::Missile(BodyDesc* bodyDesc, const Vector3& position)

	:	Object(bodyDesc, position)

{

	//setOrientation(Quaternion(Vector3(0, 1, 0), Vector3::ZERO, Vector3::ZERO));

}

//------------------------------------------------------------------------------

bool Missile::update(float deltaTime){

	m_body->setPosition(m_body->getPosition() + Vector3::UNIT_X * 5.0f * deltaTime);

	return Object::update(deltaTime);

}

//------------------------------------------------------------------------------
