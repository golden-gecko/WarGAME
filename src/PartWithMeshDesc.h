
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PartWithMeshDesc: public PartDesc {

		protected:

			string	m_meshName;
			bool	m_castShadows;

			PartWithMeshDesc(PartDescType type): PartDesc(type), m_meshName(""), m_castShadows(false) { }

		public:

			string getMeshName() {

				return m_meshName;
			}
			bool getCastShadows() {

				return m_castShadows;
			}

			void setMeshName(const string& meshName) {

				m_meshName = meshName;
			}
			void setCastShadows(bool castShadows) {

				m_castShadows = castShadows;
			}

	};

};

//------------------------------------------------------------------------------
