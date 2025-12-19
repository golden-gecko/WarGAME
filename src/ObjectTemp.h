
//------------------------------------------------------------------------------
// ObjectTemp.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Body.h"
#include "ObjectOrder.h"
#include "Part.h"
#include "Player.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectTemp {

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
			ObjectType		m_type;
			ObjectState		m_state;
			Body*			m_body;
			Player*			m_player;
			float			m_timeSinceLastAiCheck;
			float			m_timeToNextAiCheck;
			ObjectOrderList	m_orderList;

		public:

			ObjectTemp();

			virtual ~ObjectTemp();

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

			virtual float getHitPoints() {

				return m_body->getHitPoints();
			}

			virtual float getMaxHitPoints() {

				return m_body->getMaxHitPoints();
			}

			Quaternion getOrientation() {

				return m_body->getOrientation();
			}

			Vector3 getPosition() {

				return m_body->getPosition();
			}
			
			virtual Vector3 getWorldCenter() {

				return m_body->getWorldCenter();
			}

			bool have(Part::PartType part) {

				return (m_type & part) ? true : false;
			}

			ObjectTemp* is(ObjectType type) { return (m_type == type) ? this : NULL; }
			Building* isBuilding() { return (Building*)is(OT_BUILDING); }
			Fortification* isFortification() { return (Fortification*)is(OT_FORTIFICATION); }
			Missile* isMissile() { return (Missile*)is(OT_BUILDING); }
			PowerPlant* isPowerPlant() { return (PowerPlant*)is(OT_POWER_PLANT); }
			Vehicle* isVehicle() { return (Vehicle*)is(OT_VEHICLE); }

			bool isEnemy(ObjectTemp* object) {

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

			virtual string toString();

			virtual string toStringShort() {

				static char str[128];

				sprintf(str, "\n%.2f/%.2f", getHitPoints(), getMaxHitPoints());

				return m_name + str;

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
