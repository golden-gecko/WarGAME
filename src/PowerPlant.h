
//------------------------------------------------------------------------------
// PowerPlant.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Building.h"
#include "PowerReactor.h"
#include "ReactorDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PowerPlant: public Building {

		public:

			PowerReactor* m_powerReactor;

			PowerPlant();

			virtual ~PowerPlant();

			virtual float getHitPoints() {

				return Building::getHitPoints() + m_powerReactor->getHitPoints();
			}

			virtual float getMaxHitPoints() {

				return Building::getMaxHitPoints() + m_powerReactor->getMaxHitPoints();
			}

			virtual string toString();

			virtual bool update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
