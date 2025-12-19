
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Part.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PartWithMesh: public Part {

		protected:

			Ogre::Entity*		m_entity;
			Ogre::SceneNode*	m_sceneNode;
			float				m_yaw;
			float				m_pitch;
			bool				m_selected;

		public:

			PartWithMesh(PartType type): Part(type), m_entity(NULL), m_sceneNode(NULL), m_yaw(0.0f), m_pitch(0.0f), m_selected(false) { }

			Ogre::Vector3 getDimensions() {

				return m_entity->getBoundingBox().getMaximum() - m_entity->getBoundingBox().getMaximum();
			}
			Ogre::Vector3 getDirection() {

				return m_sceneNode->getOrientation().zAxis() * -1.0f;
			}
			float getBoundingRadius() {

				return m_entity->getBoundingRadius();
			}
			Ogre::Vector3 getMaximum() {

				return m_entity->getBoundingBox().getMaximum();
			}
			Ogre::Vector3 getMinimum() {

				return m_entity->getBoundingBox().getMinimum();
			}
			Ogre::Quaternion getOrientation() {

				return m_sceneNode->getOrientation();
			}
			PartWithMeshDesc* getPartWithMeshDesc() {

				return m_partWithMeshDesc;
			}
			Ogre::Vector3 getPosition() {

				return m_sceneNode->getPosition();
			}
			bool getSelected() {

				return m_selected;
			}
			Ogre::AxisAlignedBox getWorldBoundingBox() {

				return m_entity->getWorldBoundingBox();
			}
			Ogre::Vector3 getWorldCenter() {

				return getWorldBoundingBox().getCenter();
			}

			void setOrientation(const Ogre::Quaternion& orientation) {

				m_sceneNode->setOrientation(orientation);
			}
			void setPosition(const Ogre::Vector3& position) {

				m_sceneNode->setPosition(position);
			}
			void setSelected(bool selected) {

				m_sceneNode->showBoundingBox(m_selected = selected);
			}
			virtual void setPartDesc(PartDesc* partDesc);

			void rotate(const Ogre::Quaternion& q) {

				m_sceneNode->rotate(q, Ogre::Node::TS_WORLD);
			}

			virtual string toString() = 0;

			virtual bool update(float deltaTime) = 0;

	};

};

//------------------------------------------------------------------------------
