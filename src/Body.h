
//------------------------------------------------------------------------------
// Body
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "BodyDesc.h"
#include "Part.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Body : public Part {

		public:

			Entity*		m_entity;
			SceneNode*	m_sceneNode;

			Body(ObjectTemp* parent);

			virtual ~Body();

			float getBoundingRadius() {

				return m_entity->getBoundingRadius();
			}

			Vector3 getDimensions();

			Vector3 getDirection() {

				return m_sceneNode->getOrientation().xAxis();
			}

			Quaternion getOrientation() {

				return m_sceneNode->getOrientation();
			}

			Vector3 getPosition() {

				return m_sceneNode->getPosition();
			}

			Vector3 getWorldCenter() {

				return m_entity->getWorldBoundingBox().getCenter();
			}

			void scale(float s) {

				m_sceneNode->scale(s, s, s);
			}

			virtual void setDesc(PartDesc* partDesc = NULL);

			void setOrientation(const Quaternion& q = Quaternion::IDENTITY) {

				m_sceneNode->setOrientation(q);
			}

			void setPosition(const Vector3& position = Vector3::ZERO) {

				m_sceneNode->setPosition(position);
			}

			void setSelected(bool selected = false) {

				m_sceneNode->showBoundingBox(selected);
			}

			virtual string toString();

			virtual bool update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
