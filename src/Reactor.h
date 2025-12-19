

//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Part.h"

#include "ReactorDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Reactor: public Part {

		public:

			Reactor(): Part(PT_REACTOR) { }

			ReactorDesc* getReactorDesc() {

				return m_reactorDesc;
			}

			void setParent(Object* parent);

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
