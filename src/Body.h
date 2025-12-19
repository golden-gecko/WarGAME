
//------------------------------------------------------------------------------
// Body
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "BodyDesc.h"
#include "Part.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Body : public Part {

		public:

			BodyDesc*	m_bodyDesc;
			Entity*		m_entity;
			SceneNode*	m_sceneNode;

			Body(Object* parent, string bodyName);
			Body(Object* parent, void* bodyDesc);

			virtual ~Body();

			BodyDesc* getBodyDesc(){

				return m_bodyDesc;

			}

			Vector3 getDimensions();

			Vector3 getPosition();

			void setBodyDesc(string bodyName);
			void setBodyDesc(BodyDesc* bodyDesc);

			__forceinline virtual void setOrientation(const Quaternion& q){

				m_sceneNode->setOrientation(q);

			}

			void setPosition(float x, float y, float z);
			void setPosition(const Vector3& position = Vector3::ZERO);

			void setScale(float scale = 1.0f);
			void setScale(float x, float y, float z);
			void setScale(const Vector3& scale);

			virtual string toString();

	};

};

//------------------------------------------------------------------------------
