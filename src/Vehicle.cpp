
//------------------------------------------------------------------------------
// Vehicle.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "ObjectManagerTemp.h"
#include "PartDescManagerT.h"
#include "Vehicle.h"

//------------------------------------------------------------------------------

Vehicle::Vehicle() : m_engine(NULL) {

	m_name = "Vehicle #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_VEHICLE;
	m_engine = new Engine(this);
}

//------------------------------------------------------------------------------

string Vehicle::toString() {

	return Fortification::toString() + "\n\n" + m_engine->toString();
}

//------------------------------------------------------------------------------

bool Vehicle::update(float deltaTime) {

	switch (m_state) {

		case OS_IDLE:

			if (m_orderList.getCount()) {

				switch (m_orderList.getFirst().getType()) {

					//
					// OOT_ATTACK_OBJECT
					//

					case ObjectOrder::OOT_ATTACK_OBJECT:

						m_engine->stop();

						break;

					//
					// OOT_ATTACK_POSITION
					//

					case ObjectOrder::OOT_ATTACK_POSITION:

						m_engine->stop();

						break;

					//
					// OOT_MOVE
					//

					case ObjectOrder::OOT_MOVE:

						if ((m_orderList.getFirst().getVector() - getPosition()).length() < 1.0f) {

							m_orderList.removeFront();

							m_engine->stop();

						} else

							m_engine->move(m_orderList.getFirst().getVector());

						break;

					} // switch (m_orderList.getFirst().getType())

			} // if (m_orderList.getCount())

			break;

	} // switch (m_state)

	return Fortification::update(deltaTime) && m_engine->update(deltaTime);
}

//------------------------------------------------------------------------------
