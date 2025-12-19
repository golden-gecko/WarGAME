
//------------------------------------------------------------------------------
// PartDescManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "ArmourDesc.h"
#include "BodyDesc.h"
#include "EngineDesc.h"
#include "PartDesc.h"
#include "WeaponDesc.h"

//------------------------------------------------------------------------------
// PartDescManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class PartDescManager : public Singleton<PartDescManager> {

		public:

			typedef list<PartDesc*>				List;
			typedef list<PartDesc*>::iterator	Iterator;

		private:

			List m_modules;

		public:

			~PartDescManager();

			void add(PartDesc* descriptor);

			void destroy(PartDesc* descriptor);

			void destroyAll();

			PartDesc* getByName(string name);

			int getCount();

			Iterator getFirst();

			Iterator getLast();

	};

};

//------------------------------------------------------------------------------
