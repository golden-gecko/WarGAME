
//------------------------------------------------------------------------------
// Fortification.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"
#include "Fortification.h"

//------------------------------------------------------------------------------

Fortification::Fortification(	string armourName,
								string bodyName,
								string weaponName,
								const Vector3& position)

	:	Building(armourName, bodyName, position)

{

	m_name = "Fortification #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_FORTIFICATION;

	m_weapon = new Weapon(this);

	setWeapon(weaponName);
	setPosition(position);

}

//------------------------------------------------------------------------------

Fortification::Fortification(	ArmourDesc* amourDesc,
								BodyDesc* bodyDesc,
								WeaponDesc* weaponDesc,
								const Vector3& position)

	:	Building(amourDesc, bodyDesc, position)

{

	m_type = OT_FORTIFICATION;

	m_weapon = new Weapon(this);

	setWeapon(weaponDesc);
	setPosition(position);

}

//------------------------------------------------------------------------------

void Fortification::setDimensionY(float y, bool mode){

	Object::setDimensionY(y, mode);

	if (mode)

		m_weapon->setScale(
			0.5 / m_weapon->getDimensions().y,
			0.5 / m_weapon->getDimensions().y,
			0.5 / m_weapon->getDimensions().y);

	else

		m_weapon->setScale(
			0.5 / m_weapon->getDimensions().x,
			0.5 / m_weapon->getDimensions().y,
			0.5 / m_weapon->getDimensions().z);

}

//------------------------------------------------------------------------------

void Fortification::setPosition(const Vector3& position){

	m_body->setPosition(position);

	m_weapon->setPosition(
		position.x,
		position.y + 2,
		position.z);

}

//------------------------------------------------------------------------------

void Fortification::setSelected(bool selected){

	Object::setSelected(selected);

	m_weapon->m_sceneNode->showBoundingBox(selected);

}

//------------------------------------------------------------------------------

void Fortification::setWeapon(string weaponName){

	m_weapon->set(weaponName);

}

//------------------------------------------------------------------------------

void Fortification::setWeapon(WeaponDesc* weaponDesc){

	m_weapon->set(weaponDesc);

}

//------------------------------------------------------------------------------

string Fortification::toString(){

	return Building::toString() + "\n" + m_weapon->toString();

}

//------------------------------------------------------------------------------

bool Fortification::update(float deltaTime){

	return Building::update(deltaTime) && m_weapon->update(deltaTime);
}

//------------------------------------------------------------------------------
