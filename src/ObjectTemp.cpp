
//------------------------------------------------------------------------------
// ObjectTemp.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "ObjectTemp.h"
#include "Vehicle.h"

//------------------------------------------------------------------------------

ObjectTemp::ObjectTemp()

	:	m_name("ObjectTemp #" + Core::getSingletonPtr()->getDataCounterStr()),
		m_type(OT_OBJECT),
		m_state(OS_IDLE),
		m_player(NULL),
		m_timeSinceLastAiCheck(0.0f),
		m_timeToNextAiCheck(rand() % 1000 / 1000.0f)

{
	m_body = new Body(this);
}

//------------------------------------------------------------------------------

ObjectTemp::~ObjectTemp() {

	delete m_body;
}

//------------------------------------------------------------------------------

float ObjectTemp::getHeight(){

	return getPosition().y - Core::getSingletonPtr()->getTerrainHeightVec(getPosition()).y;
}

//------------------------------------------------------------------------------

string ObjectTemp::toString() {

	static char str[512];

	sprintf(
		str,
		"\
		ObjectTemp\n\
		  Name %s\n\
		  Hit Points %.0f/%.0f\n\n",
		m_name.c_str(),
		getHitPoints(), getMaxHitPoints());

	return str + m_body->toString();
}

//------------------------------------------------------------------------------

bool ObjectTemp::update(float deltaTime) {

	switch (m_state) {

		case OS_IDLE:

			if (m_body->getHitPoints() <= 0.0f) {

				m_state = OS_DEAD;

				return true;
			}

			if (m_orderList.getCount()) {

				switch (m_orderList.getFirst().getType()) {

					case ObjectOrder::OOT_STOP:

						m_orderList.removeAll();

						return true;

				}
			}

			return true;

		case OS_DEAD: 

			/*if (m_type == OT_VEHICLE) {

				Vehicle* v = (Vehicle*)(this);

				delete v->m_weapon;
			}*/

//			return true;
			return false;

	} // switch (m_state)

	return true;
}

//------------------------------------------------------------------------------

float ObjectTemp::leftOrRight(Vector3& t, float& angle, float speed) {

	//*
	// Rotate left or right?

	float sinY = sin(Ogre::Math::DegreesToRadians(-angle));
	float cosY = cos(Ogre::Math::DegreesToRadians(-angle));

	Ogre::Vector3 tRotY = Ogre::Vector3(t.z * sinY + t.x * cosY, 0.0f, t.z * cosY - t.x * sinY);

	sinY = -tRotY.z / sqrt(tRotY.x * tRotY.x + tRotY.z * tRotY.z);

	// Rotate left / right

	if (fabs(sinY) > 0.01f)

		angle += speed * sinY / fabs(sinY);

	return sinY;
	//*/

	/*
	float sinY = sin(Math::DegreesToRadians(angle));
	float cosY = cos(Math::DegreesToRadians(angle));

	Vector3 tRotY = Vector3(t.x * cosY - t.z * sinY, 0.0f, t.x * sinY + t.z * cosY);

	sinY = -tRotY.x / sqrt(tRotY.x * tRotY.x + tRotY.z * tRotY.z);

	if (fabs(sinY) > 0.01f)

		angle += speed * sinY / fabs(sinY);

	return sinY;
	//*/
}

//------------------------------------------------------------------------------

float ObjectTemp::upOrDown(Vector3& t, float& angle, float speed) {
	
	//*
	// Rotate up or down?

	float sinZ = sin(Ogre::Math::DegreesToRadians(angle));
	float cosZ = cos(Ogre::Math::DegreesToRadians(angle));

	t.x = sqrt(t.x * t.x + t.z * t.z);

	Ogre::Vector3 tRotZ = Ogre::Vector3(t.y * sinZ + t.x * cosZ, t.y * cosZ - t.x * sinZ, 0.0f);

	sinZ = tRotZ.y / sqrt(tRotZ.x * tRotZ.x + tRotZ.y * tRotZ.y);

	// Rotate up / down

	if (abs(sinZ) > 0.01f)

		angle += speed * sinZ / fabs(sinZ);

	return sinZ;
	//*/

	/*
	float sinX = sin(Math::DegreesToRadians(angle));
	float cosX = cos(Math::DegreesToRadians(angle));

	t.x = sqrt(t.x * t.x + t.z * t.z);

	//t.y = -t.y;

	Vector3 tRotX = Vector3(0.0f, t.y * sinX + t.z * cosX, t.y * cosX - t.z * sinX);

	sinX = -tRotX.z / sqrt(tRotX.z * tRotX.z + tRotX.y * tRotX.y);

	// Rotate up / down

	if (abs(sinX) > 0.01f)

		angle += speed * sinX / fabs(sinX);

	return sinX;
	//*/
}

//------------------------------------------------------------------------------
