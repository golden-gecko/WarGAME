
//------------------------------------------------------------------------------
// PowerReactor.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Part.h"
#include "PowerReactorDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PowerReactor : public Part {

		public:

			PowerReactorDesc* m_powerReactorDesc;

			PowerReactor(Object* parent) : Part(parent), m_powerReactorDesc(NULL) { }

			void set(string powerReactorName);
			void set(PowerReactorDesc* powerReactorDesc);

			virtual string toString(){

				return "";

			}

	};

};

//------------------------------------------------------------------------------
