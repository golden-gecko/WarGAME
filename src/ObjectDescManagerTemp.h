
//------------------------------------------------------------------------------
// ObjectDescManagerTemp.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PlantDesc.h"
#include "PowerPlantDesc.h"
#include "ResourceManagerTemp.h"
#include "VehicleDesc.h"

//------------------------------------------------------------------------------
// ObjectDescManagerTemp
//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectDescManagerTemp : public ResourceManagerTemp<ObjectDescManagerTemp, ObjectDesc> {

		public:

			typedef list<ObjectDesc*>			List;
			typedef list<ObjectDesc*>::iterator	Iterator;

		public:

			void add(ObjectDesc* object);

			ObjectDesc* getByName(string name);

			Iterator getFirst();

			Iterator getLast();

	};

};

//------------------------------------------------------------------------------
