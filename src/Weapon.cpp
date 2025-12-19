
//------------------------------------------------------------------------------
// Weapon.cpp
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"
#include "Object.h"
#include "PartDescManager.h"
#include "Vehicle.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

Weapon::Weapon(Object* parent)

	:	Part(parent),
		m_entity(NULL),
		m_sceneNode(NULL),
		m_weaponDesc(NULL),
		m_yaw(0.0f),
		m_pitch(0.0f),
		m_reloadTime(0.0f),
		m_ammunition(0)

{
	m_sceneNode = Core::getSingletonPtr()->createSceneNode();

	//m_sceneNode = m_parent->m_body->m_sceneNode->createChildSceneNode(Vector3(0, 25, 0));

}

//------------------------------------------------------------------------------

Weapon::~Weapon(){

	Core::getSingletonPtr()->destroyEntity(m_entity);
	Core::getSingletonPtr()->destroySceneNode(m_sceneNode);

}

//------------------------------------------------------------------------------

Vector3 Weapon::getDimensions(){

	AxisAlignedBox box;

	box = m_entity->getBoundingBox();

	return box.getMaximum() - box.getMinimum();

}

//------------------------------------------------------------------------------

void Weapon::set(string weaponName){

	set((WeaponDesc*)PartDescManager::getSingletonPtr()->getByName(weaponName));

}

//------------------------------------------------------------------------------

void Weapon::set(WeaponDesc* weaponDesc){

	if (weaponDesc && (weaponDesc->m_type == PartDesc::PDT_WEAPON)) {

		m_weaponDesc = weaponDesc;

		m_ammunition = m_weaponDesc->m_maxAmmunition;
		m_reloadTime = m_weaponDesc->m_maxReloadTime;
		m_turnSpeed = m_weaponDesc->m_maxTurnSpeed;

		m_entity = Core::getSingletonPtr()->createEntity(m_weaponDesc->m_meshName);
		m_entity->setCastShadows(m_weaponDesc->m_castShadows);
		m_entity->setUserAny(Any(this));

		m_sceneNode->attachObject(m_entity);

	} else {

		Core::getSingletonPtr()->destroyEntity(m_entity);

		m_entity = NULL;
		m_weaponDesc = NULL;

	}

}

//------------------------------------------------------------------------------

void Weapon::setPosition(float x, float y, float z){

	m_sceneNode->setPosition(x, y, z);

}

//------------------------------------------------------------------------------

void Weapon::setPosition(const Vector3& position){

	m_sceneNode->setPosition(position);

}

//------------------------------------------------------------------------------

void Weapon::setScale(float x, float y, float z){

	m_sceneNode->setScale(x, y, z);

}

//------------------------------------------------------------------------------

float leftOrRight(Ogre::Vector3 t, float& angle, float speed){

	// Rotate left or right?

	float sinY = sin(Ogre::Math::DegreesToRadians(-angle));
	float cosY = cos(Ogre::Math::DegreesToRadians(-angle));

	Ogre::Vector3 tRotY = Ogre::Vector3(t.z * sinY + t.x * cosY, 0.0f, t.z * cosY - t.x * sinY);

	sinY = -tRotY.z / sqrt(tRotY.x * tRotY.x + tRotY.z * tRotY.z);

	// Rotate left / right

	if (abs(sinY) > 0.01f) {

		if (sinY > 0.0f)

			angle += speed;

		else

			angle -= speed;
	}

	return sinY;

}

//------------------------------------------------------------------------------

float upOrDown(Ogre::Vector3 t, float& angle, float speed){

	float sinZ = sin(Ogre::Math::DegreesToRadians(angle));
	float cosZ = cos(Ogre::Math::DegreesToRadians(angle));

	t.x = sqrt(t.x * t.x + t.z * t.z);

	Ogre::Vector3 tRotZ = Ogre::Vector3(t.y * sinZ + t.x * cosZ, t.y * cosZ - t.x * sinZ, 0.0f);

	sinZ = tRotZ.y / sqrt(tRotZ.x * tRotZ.x + tRotZ.y * tRotZ.y);

	// Rotate up / down

	if (abs(sinZ) > 0.01f) {

		if (sinZ > 0.0f)

			angle += speed;

		else

			angle -= speed;

	}

	return sinZ;

}

//------------------------------------------------------------------------------

string Weapon::toString(){

	char text[512];

	sprintf(text,
		"\
		Name - %s\n\
		Damage - %.2f\n\
		Range -  %.2f\n\
		Ammunition - %i/%i\n\
		Reload Time - %.2f/%.2f",
		m_weaponDesc->m_name.c_str(),
		m_weaponDesc->m_damage,
		m_weaponDesc->m_range,
		m_ammunition, m_weaponDesc->m_maxAmmunition,
		m_reloadTime, m_weaponDesc->m_maxReloadTime);

	return text;

}

//------------------------------------------------------------------------------

bool Weapon::update(float deltaTime){

	if (m_reloadTime < m_weaponDesc->m_maxReloadTime)

		m_reloadTime += deltaTime;

	else if (m_reloadTime > m_weaponDesc->m_maxReloadTime)

		m_reloadTime = m_weaponDesc->m_maxReloadTime;


	Vector3 v;
	
	if (Core::getSingletonPtr()->m_objectUnderMouse)

		v = Core::getSingletonPtr()->m_objectUnderMouse->getPosition() + Vector3(0, 1, 0);

	else

		v = Core::getSingletonPtr()->getMouse3DPos();


	float sinYaw = leftOrRight(
		v - m_sceneNode->getPosition(),
		m_yaw,
		m_turnSpeed * deltaTime);


	float sinPitch = upOrDown(
		v -  m_sceneNode->getPosition(),
		m_pitch,
		m_weaponDesc->m_maxTurnSpeed * deltaTime);

	Quaternion y, z;

	y.FromAngleAxis(Ogre::Radian(Ogre::Degree(m_yaw)), Vector3::UNIT_Y);
	z.FromAngleAxis(Ogre::Radian(Ogre::Degree(m_pitch)), Vector3::UNIT_Z);

	m_sceneNode->setOrientation(y * z);

	if ((fabs(sinYaw) <= 0.01f )&& (fabs(sinPitch) <= 0.01f)) {

		RaySceneQueryResult result = Core::getSingletonPtr()->whatWouldHit(
			m_sceneNode->getPosition(),
			m_sceneNode->getOrientation().xAxis());

		for (Ogre::RaySceneQueryResult::iterator itr = result.begin(); itr != result.end(); itr++)

			if (itr->worldFragment)

				break;

			else if (itr->movable && itr->movable->getUserAny().isEmpty() == false) {

				Object* o = Core::getSingletonPtr()->ogreAnyToObject(itr->movable->getUserAny());

				if ((o != m_parent) && o->isEnemy(m_parent) && fire()) {

					//o->decreaseHitPoints(m_weaponDesc->m_damage);

					break;

				}

			}

	}

	return true;

}

//------------------------------------------------------------------------------
