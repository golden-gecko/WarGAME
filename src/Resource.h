
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Resource {

		protected:

			string m_name;

		public:

			Resource(): m_name("") { }

			string getName() {

				return m_name;
			}

			void setName(const string& name) {

				m_name = name;
			}

			virtual string toString() {

				static char str[64];

				sprintf_s(str, 64, "resource\n  name - %s", m_name.c_str());
				
				return str;
			}

	};

};

//------------------------------------------------------------------------------
