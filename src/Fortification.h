
//------------------------------------------------------------------------------
// Fortification.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Building.h"
#include "Weapon.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Fortification: public Building {

		public:

			Weapon* m_weapon;
			int		m_objectHits;
			int		m_terrainHits;

		public:

			Fortification();

			virtual ~Fortification();

			virtual void setOrientation(const Quaternion& q = Quaternion::IDENTITY) {

				Building::setOrientation(q);

				// TODO: Fortification::setOrientation - isn't working for a weapon.
				// m_weapon->setOrientation(q);
			}

			virtual void setPosition(const Vector3& position = Vector3::ZERO) {

				Building::setPosition(position);

				m_weapon->setPosition(position + Vector3(0.0f, m_body->getDimensions().y, 0.0f));
			}

			virtual void setSelected(bool selected = false) {

				Building::setSelected(selected);

				m_weapon->setSelected(selected);
			}

			virtual string toString();

			virtual bool update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
