
//------------------------------------------------------------------------------
// PowerPlant.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"

#include "PartDescManager.h"

#include "PowerPlant.h"

//------------------------------------------------------------------------------

PowerPlant::PowerPlant(	string armourName,
						string bodyName,
						string powerReactorName,
						const Vector3& position)

	:	Building(armourName, bodyName, position)

{

	m_name = "Power Plant #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_POWER_PLANT;

	m_powerReactor = new PowerReactor(this);

	m_powerReactor->m_powerReactorDesc = (PowerReactorDesc*)PartDescManager::getSingletonPtr()->getByName(powerReactorName);

	//m_body->m_entity->getMesh()->getSubMesh(0)->setMaterialName("green");

}

//------------------------------------------------------------------------------

PowerPlant::PowerPlant(	ArmourDesc* armourDesc,
						BodyDesc* bodyDesc,
						PowerReactorDesc* powerReactorDesc,
						const Vector3& position)

	:	Building(armourDesc, bodyDesc, position)

{

	m_type = OT_POWER_PLANT;

	m_powerReactor = new PowerReactor(this);

	m_powerReactor->m_powerReactorDesc = powerReactorDesc;

}

//------------------------------------------------------------------------------
