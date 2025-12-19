
//------------------------------------------------------------------------------
// ObjectDescManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "PlantDesc.h"
#include "PowerPlantDesc.h"
#include "ResourceManagerTemp.h"
#include "VehicleDesc.h"

//------------------------------------------------------------------------------
// ObjectDescManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectDescManager : public ResourceManagerTemp<ObjectDescManager, ObjectDesc> {

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
