
//------------------------------------------------------------------------------
// Engine.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "EngineDesc.h"
#include "Part.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Engine : public Part {

		public:

			enum EngineOrderType {

				EOT_CHASE,
				EOT_CHASE_75,
				EOT_CHASE_50,
				EOT_CHASE_25,
				EOT_HOLD_POSITION

			};

			float		m_yaw;
			Vector3		m_target;
			ParticleSystem* ps;

			Engine(ObjectTemp* parent);

			void move(Vector3 target) {

				//m_state = PS_PROCCESSING_ORDER;
				m_target = target;
			}

			virtual void setDesc(PartDesc* partDesc = NULL);

			void stop() {

				m_target = Vector3(-1.0f);
			}

			virtual string toString();

			virtual bool update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
