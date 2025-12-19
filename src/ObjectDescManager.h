
//------------------------------------------------------------------------------
// ObjectDescManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "ObjectDesc.h"
#include "FortificationDesc.h"
#include "VehicleDesc.h"

//------------------------------------------------------------------------------
// ObjectDescManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectDescManager : public Singleton<ObjectDescManager> {

		public:

			typedef list<ObjectDesc*>			List;
			typedef list<ObjectDesc*>::iterator	Iterator;

		private:

			List m_objectDescs;

		public:

			~ObjectDescManager();

			void add(ObjectDesc* object);

			void destroy(ObjectDesc* object);

			void destroyAll();

			int getCount();

			Iterator getFirst();

			Iterator getLast();

	};

};

//------------------------------------------------------------------------------
