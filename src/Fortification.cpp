
//------------------------------------------------------------------------------
// Fortification.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Fortification.h"

//------------------------------------------------------------------------------

Fortification::Fortification()

	:	m_weapon(NULL),
		m_objectHits(0),
		m_terrainHits(0)

{
	m_name = "Fortification #" + Core::getSingletonPtr()->getDataCounterStr();
	m_type = OT_FORTIFICATION;
	m_weapon = new Weapon(this);
}

//------------------------------------------------------------------------------

Fortification::~Fortification() {

	delete m_weapon;
}

//------------------------------------------------------------------------------

string Fortification::toString() {

	static char str[512];

	sprintf(str, "\nObject Hits %i\nTerrain Hits %i", m_objectHits, m_terrainHits);

	return Building::toString() + "\n\n" + m_weapon->toString() + str;
}

//------------------------------------------------------------------------------

bool Fortification::update(float deltaTime) {

	switch (m_state) {

		case OS_IDLE:

			if (m_orderList.getCount()) {

				switch (m_orderList.getFirst().getType()) {

					case ObjectOrder::OOT_ATTACK_OBJECT:

						if (((ObjectTemp*)m_orderList.getFirst().getParam())->m_state == OS_DEAD)

							m_orderList.removeFront();

						else

							m_weapon->attack((ObjectTemp*)m_orderList.getFirst().getParam());

						break;

					case ObjectOrder::OOT_ATTACK_POSITION:

						m_weapon->attack(m_orderList.getFirst().getVector());

						break;

					case ObjectOrder::OOT_STOP:

						m_weapon->stop();

						break;

				} // switch (m_orderList.getFirst().getType())

			} // if (m_orderList.getCount())

			break;

	} // switch (m_state)

	return Building::update(deltaTime) && m_weapon->update(deltaTime);
}

//------------------------------------------------------------------------------
