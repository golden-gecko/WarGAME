
//------------------------------------------------------------------------------
// Building.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Armour.h"
#include "Shield.h"
#include "ObjectTemp.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Building : public ObjectTemp {

		public:

			Armour*			m_armour;
			Shield*	m_shield;

			Building();

			virtual ~Building() {

				delete m_armour;
				delete m_shield;
			}

			virtual float getHitPoints() {

				return ObjectTemp::getHitPoints() + m_armour->getHitPoints();
			}

			virtual float getMaxHitPoints() {

				return ObjectTemp::getMaxHitPoints() + m_armour->getMaxHitPoints();
			}

			virtual string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
