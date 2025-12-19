
//------------------------------------------------------------------------------
// Object.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Armour.h"
#include "Body.h"
#include "Engine.h"
#include "Explosive.h"
#include "Reactor.h"
#include "Shield.h"
#include "Teleporter.h"
#include "Weapon.h"

#include "ObjectOrder.h"

#include "Player.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Object {

		public:

			enum ObjectType {

				OT_BUILDING			= 0x0080 + Part::PT_ARMOUR + Part::PT_BODY,
				OT_FORTIFICATION	= 0x0100 + Part::PT_ARMOUR + Part::PT_BODY + Part::PT_WEAPON,
				OT_MISSILE			= 0x0200 + Part::PT_BODY + Part::PT_EXPLOSIVE,
				OT_OBJECT			= 0x0400 + Part::PT_BODY,
				OT_PLANT			= 0x0800 + Part::PT_BODY,
				OT_POWER_PLANT		= 0x1000 + Part::PT_ARMOUR + Part::PT_BODY + Part::PT_POWER_REACTOR,
				OT_VEHICLE			= 0x2000 + Part::PT_ARMOUR + Part::PT_BODY + Part::PT_ENGINE + Part::PT_WEAPON

			};

			enum ObjectState {

				OS_IDLE,
				OS_DEAD

			};

		public:

			string			m_name;

			Armour*			m_armour;
			Body*			m_body;
			Engine*			m_engine;
			Explosive*		m_explosive;
			Reactor*		m_reactor;
			Shield*			m_shield;
			Teleporter*		m_teleporter;
			Weapon*			m_weapon;

			Vector3			m_velocity;
			Quaternion		m_angularVelocity;

			ObjectType		m_type;
			ObjectState		m_state;
			Player*			m_player;
			float			m_timeSinceLastAiCheck;
			float			m_timeToNextAiCheck;
			ObjectOrderList	m_orderList;

		public:

			Object();

			virtual ~Object();

			void onDamage(float damage) {

			}

			virtual void decreaseHitPoints(float hitPoints) {

				m_body->m_hitPoints -= hitPoints;
			}

			virtual float getBoundingRadius() {

				return m_body->getBoundingRadius();
			}

			virtual Vector3 getDimensions() {

				return m_body->getDimensions();
			}

			Vector3 getDirection() {

				return m_body->getDirection();
			}

			float getHeight();

			float getHitPoints() {

				return	(m_armour ? m_armour->getHitPoints() : 0.0f) +
						(m_body ? m_body->getHitPoints() : 0.0f) +
						(m_engine ? m_engine->getHitPoints() : 0.0f) +
						(m_explosive ? m_explosive->getHitPoints() : 0.0f) +
						(m_reactor ? m_reactor->getHitPoints() : 0.0f) +
						(m_shield ? m_shield->getHitPoints() : 0.0f) +
						(m_weapon ? m_weapon->getHitPoints() : 0.0f);
			}

			float getMaxHitPoints() {

				return	(m_armour ? m_armour->getMaxHitPoints() : 0.0f) +
						(m_body ? m_body->getMaxHitPoints() : 0.0f) +
						(m_engine ? m_engine->getMaxHitPoints() : 0.0f) +
						(m_explosive ? m_explosive->getMaxHitPoints() : 0.0f) +
						(m_reactor ? m_reactor->getMaxHitPoints() : 0.0f) +
						(m_shield ? m_shield->getMaxHitPoints() : 0.0f) +
						(m_weapon ? m_weapon->getMaxHitPoints() : 0.0f);
			}

			Quaternion getOrientation() {

				return m_body->getOrientation();
			}

			Vector3 getPosition() {

				return m_body->getPosition();
			}
			
			Vector3 getWorldCenter() {

				return m_body->getWorldCenter();
			}

			Object* is(ObjectType type) { return (m_type == type) ? this : NULL; }
			Building* isBuilding() { return (Building*)is(OT_BUILDING); }
			Fortification* isFortification() { return (Fortification*)is(OT_FORTIFICATION); }
			Missile* isMissile() { return (Missile*)is(OT_BUILDING); }
			PowerPlant* isPowerPlant() { return (PowerPlant*)is(OT_POWER_PLANT); }
			Vehicle* isVehicle() { return (Vehicle*)is(OT_VEHICLE); }

			bool isEnemy(Object* object) {

				if (m_player == object->m_player)

					return false;

				return true;
			}

			virtual void setPlayer(Player* player = NULL) {

				m_player = player;
			}

			virtual void setOrientation(const Quaternion& q = Quaternion::IDENTITY) {

				m_body->setOrientation(q);
			}

			virtual void setPosition(const Vector3& position = Vector3::ZERO) {

				m_body->setPosition(position);
			}

			virtual void setSelected(bool selected = false) {

				m_body->setSelected(selected);
			}

			void setVelocity(const Vector3& velocity = Vector3::ZERO) {

				m_velocity = velocity;
			}

			void setAngularVelocity(const Quaternion& angularVelocity = Quaternion::IDENTITY) {

				m_angularVelocity = angularVelocity;
			}

			virtual string toString();

			virtual string toStringShort() {

				static char text[128];

				sprintf(text, "\n%.2f/%.2f", getHitPoints(), getMaxHitPoints());

				return m_name + text;

			}

			virtual string toStringEnemy() {

				static const string hitPointsLevel[] = {
					"Almost Dead (1% -  20%)",
					"Bad (21% -  40%)",
					"Average (41% -  60%)",
					"Good (61% -  80%)",
					"Very Good (81% - 100%)"
				};

				if (getHitPoints() >= getMaxHitPoints())

					return m_name + "\n" + hitPointsLevel[4];

				else if (getHitPoints() <= 0.0f)

					return m_name + "\nDead";

				else

					return m_name + "\n" + hitPointsLevel[(int)(getHitPoints() / getMaxHitPoints() * 5.0f)];

			}

			virtual bool update(float deltaTime);

			float leftOrRight(Vector3& t, float& angle, float speed);
			float upOrDown(Vector3& t, float& angle, float speed);

	};
};

//------------------------------------------------------------------------------
