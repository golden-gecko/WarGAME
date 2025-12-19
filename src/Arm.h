
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartWithMesh.h"

#include "ArmDesc.h"
#include "EffectManager.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Arm: public PartWithMesh {

		protected:

			ObjectDesc*	m_targetDesc;
			Object*		m_targetObj;
			Stream*		m_stream;

		public:

			Arm()
				:	PartWithMesh(PT_ARM),
					m_targetDesc(NULL),
					m_targetObj(NULL),
					m_stream(NULL) { }

			void create() {

				m_stream = EffectManager::getSingletonPtr()->createStream();
			}

			void destroy() {

				EffectManager::getSingletonPtr()->destroyStream(m_stream);
			}

			void construct(ObjectDesc* targetDesc) {

				m_targetDesc	= targetDesc;
				m_state			= PS_CONSTRUCT;
			}
			
			void modyfi(Object* targetObj, ObjectDesc* targetDesc) {

				m_targetDesc	= targetDesc;
				m_targetObj		= targetObj;
				m_state			= PS_MODIFY;
			}

			void repair(Object* targetObj) {

				m_targetObj	= targetObj;
				m_state		= PS_REPAIR;
			}

			void resupply(Object* targetObj) {

				m_targetObj	= targetObj;
				m_state		= PS_RESUPPLY;
			}

			void stop() {

				m_targetDesc	= NULL;
				m_targetObj		= NULL;
				m_state			= PS_NORMAL;
			}

			string toString();

			bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
