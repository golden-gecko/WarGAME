
//------------------------------------------------------------------------------
// Building.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"
#include "Building.h"
#include "PartDescManager.h"

//------------------------------------------------------------------------------

Building::Building(string armourName, string bodyName, const Vector3& position)

	:	Object(bodyName, position)

{

	m_name = "Building #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_BUILDING;

	m_armour = new Armour(this);

}

//------------------------------------------------------------------------------

Building::Building(ArmourDesc* armourDesc, BodyDesc* bodyDesc, const Vector3& position)

	:	Object(bodyDesc, position)

{

	m_type = OT_BUILDING;

	m_armour = new Armour(this);

}

//------------------------------------------------------------------------------

string Building::toString(){

	return Object::toString();

}

//------------------------------------------------------------------------------
