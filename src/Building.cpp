
//------------------------------------------------------------------------------
// Building.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Building.h"

//------------------------------------------------------------------------------

Building::Building() : m_armour(NULL) {

	m_name = "Building #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_BUILDING;
	m_armour = new Armour(this);
	m_shield = new Shield(this);
}

//------------------------------------------------------------------------------

string Building::toString() {

	return ObjectTemp::toString() + "\n\n" + m_armour->toString();
}

//------------------------------------------------------------------------------

bool Building::update(float deltaTime) {

	switch (m_state) {

		case OS_IDLE:

			if (m_orderList.getCount()) {

				switch (m_orderList.getFirst().getType()) {

					case ObjectOrder::OOT_STOP:

						m_orderList.removeAll();
						m_orderList.addFront();

						break;

				} // switch (m_orderList.getFirst().getType())

			} // if (m_orderList.getCount())

			break;

	} // switch (m_state)

	m_armour->update(deltaTime);
	m_shield->update(deltaTime);

	return ObjectTemp::update(deltaTime);
}

//------------------------------------------------------------------------------
