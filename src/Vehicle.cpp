
//------------------------------------------------------------------------------
// Vehicle.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"
#include "PartDescManager.h"
#include "Vehicle.h"

//------------------------------------------------------------------------------

Vehicle::Vehicle(	string armourName,
					string bodyName,
					string engineName,
					string weaponName,
					const Vector3& position)

	:	Fortification(armourName, bodyName, weaponName, position),
		m_engine(NULL)

{

	m_name = "Vehicle #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_VEHICLE;

	m_engine = new Engine(this, engineName);

	m_engine->m_engineDesc = (EngineDesc*)PartDescManager::getSingletonPtr()->getByName(engineName);

}

//------------------------------------------------------------------------------

Vehicle::Vehicle(	ArmourDesc* amourDesc,
					BodyDesc* bodyDesc,
					EngineDesc* engineDesc,
					WeaponDesc* weaponDesc,
					const Vector3& position)

	:	Fortification(amourDesc, bodyDesc, weaponDesc, position),
		m_engine(NULL)

{

	m_type = OT_VEHICLE;

	m_engine = new Engine(this, engineDesc);

}

//------------------------------------------------------------------------------

string Vehicle::toString(){

	return Fortification::toString() + "\n" + m_engine->toString();

}

//------------------------------------------------------------------------------

bool Vehicle::update(float deltaTime){

	if (m_orderList.getCount()) {

		switch ((*m_orderList.getFirst()).getType()) {

			case ObjectOrder::OOT_ATTACK_OBJECT:

				m_engine->stop();

				break;

			case ObjectOrder::OOT_ATTACK_POSITION:

				m_engine->stop();

				break;

			case ObjectOrder::OOT_DEFAULT:

				break;

			case ObjectOrder::OOT_MOVE:

				if (((*m_orderList.getFirst()).getVector() - getPosition()).length() <= 1.0f) {

					m_engine->stop();

					m_orderList.removeFront();

				} else

					m_engine->move((*m_orderList.getFirst()).getVector());

				break;

			case ObjectOrder::OOT_PATROL:

				break;

			case ObjectOrder::OOT_STOP:

				m_engine->stop();

				break;

		}

	}

	return Fortification::update(deltaTime) && m_engine->update(deltaTime);

}

//------------------------------------------------------------------------------
