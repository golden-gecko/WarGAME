
//------------------------------------------------------------------------------
// PartDescManagerT.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManagerTemp.h"

#include "ArmourDesc.h"
#include "BodyDesc.h"
#include "EngineDesc.h"
#include "ReactorDesc.h"
#include "WeaponDesc.h"

//------------------------------------------------------------------------------
// PartDescManagerTemp
//------------------------------------------------------------------------------

namespace WarGAME {

	class PartDescManagerTemp : public ResourceManagerTemp<PartDescManagerTemp, PartDesc> {

		public:

			typedef list<PartDesc*>				List;
			typedef list<PartDesc*>::iterator	Iterator;

		public:

			void add(PartDesc* descriptor);

			PartDesc* getByName(string name);

			Iterator getFirst();

			Iterator getLast();

	};

};

//------------------------------------------------------------------------------
