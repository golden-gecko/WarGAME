
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMesh.h"

#include "ShieldDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Shield: public PartWithMesh {

		protected:

			Ogre::Technique*	m_pulseMaterialTech;
			float				m_pulseTime;
			float				m_pulseMode;

		public:

			Shield():	PartWithMesh(PT_SHIELD),
						m_pulseMaterialTech(NULL),
						m_pulseTime(0.0f),
						m_pulseMode(1.0f) { }

			ShieldDesc* getShieldDesc() {

				return m_shieldDesc;
			}

			void setParent(Object* parent);
			void setPartDesc(PartDesc* partDesc);

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
