
//------------------------------------------------------------------------------
// Weapon.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Part.h"
#include "WeaponDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Weapon : public Part {

		public:

			WeaponDesc*	m_weaponDesc;
			Entity*		m_entity;
			SceneNode*	m_sceneNode;
			float		m_yaw;
			float		m_pitch;
			float		m_reloadTime;
			int			m_ammunition;
			float		m_turnSpeed;

		public:

			Weapon(Object* parent);

			~Weapon();

			bool fire(){

				if ((m_reloadTime >= m_weaponDesc->m_maxReloadTime) && m_ammunition) {

					m_reloadTime = 0.0f;

					m_ammunition--;

					return true;

				}

				return false;

			}

			Vector3 getDimensions();

			void set(string weaponName);
			void set(WeaponDesc* weaponDesc);

			virtual void setOrientation(const Quaternion& q){

				//m_sceneNode->setOrientation(q);

			}

			void setPosition(float x, float y, float z);
			void setPosition(const Vector3& position = Vector3::ZERO);

			void setScale(float x, float y, float z);

			virtual string toString();

			virtual bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
