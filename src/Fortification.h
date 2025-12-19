
//------------------------------------------------------------------------------
// Fortification.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Building.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Fortification : public Building {

		public:

			Weapon* m_weapon;

			Fortification(	string armourName,
							string bodyName,
							string weaponName,
							const Vector3& position);

			Fortification(	ArmourDesc* amourDesc,
							BodyDesc* bodyDesc,
							WeaponDesc* weaponDesc,
							const Vector3& position);

			virtual ~Fortification(){

				delete m_weapon;

			}

			virtual void setDimensionY(float y, bool mode = true);

			virtual void setOrientation(const Quaternion& q){

				Building::setOrientation(q);

				m_weapon->setOrientation(q);

			}

			virtual void setPosition(const Vector3& position = Vector3::ZERO);

			virtual void setSelected(bool selected);

			void setWeapon(string weaponName);
			void setWeapon(WeaponDesc* weaponDesc);

			virtual string toString();

			virtual bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
