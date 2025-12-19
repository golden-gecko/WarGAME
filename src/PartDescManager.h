
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "ArmourDesc.h"
#include "EngineDesc.h"
#include "ReactorDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	namespace PartDescManager {

		class ArmourDescManager: public ResourceManager<ArmourDesc> {

			public:

				ArmourDesc* create(const string& name, float maxHitPoints, float mass, float defence) {

					ArmourDesc* armourDesc = ResourceManager::create(name);

					armourDesc->setMaxHitPoints(maxHitPoints);
					armourDesc->setMass(mass);
					armourDesc->setDefence(defence);

					return armourDesc;
				}

		};

		class EngineDescManager: public ResourceManager<EngineDesc> {

			public:

				EngineDesc* create(const string& name, float maxHitPoints, float mass, float power) {

					EngineDesc* engineDesc = ResourceManager::create(name);

					engineDesc->setMaxHitPoints(maxHitPoints);
					engineDesc->setMass(mass);
					engineDesc->setPower(power);

					return engineDesc;
				}

		};

		class ReactorDescManager: public ResourceManager<ReactorDesc> {

			public:

				ReactorDesc* create(const string& name, float maxHitPoints, float mass, float power) {

					ReactorDesc* reactorDesc = ResourceManager::create(name);

					reactorDesc->setMaxHitPoints(maxHitPoints);
					reactorDesc->setMass(mass);
					reactorDesc->setPower(power);

					return reactorDesc;
				}

		};

	};

};

//------------------------------------------------------------------------------
