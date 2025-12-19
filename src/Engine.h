
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

			EngineDesc*	m_engineDesc;
			float		m_yaw;
			Vector3		m_target;
			ParticleSystem* ps;

			Engine(Object* parent, string engineDescName)
				:	Part(parent),
					m_engineDesc(NULL),
					m_yaw(0.0f),
					m_target(Vector3(-1.0f)),
					ps(NULL) { }

			Engine(Object* parent, EngineDesc* engineDesc)
				:	Part(parent),
					m_engineDesc(engineDesc),
					m_yaw(0.0f),
					m_target(Vector3(-1.0f)) { }

			void move(Vector3 target){

				m_target = target;

			}

			void stop(){

				m_target = Vector3(-1.0f);

			}

			virtual string toString(){

				static char text[512];

				return text;

			}

			virtual bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
