
//------------------------------------------------------------------------------
// Object.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Body.h"
#include "ObjectOrder.h"
#include "Player.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Object {

		public:

			enum ObjectType {

				OT_BUILDING,
				OT_FACTORY,
				OT_FORTIFICATION,
				OT_NULL,
				OT_OBJECT,
				OT_POWER_PLANT,
				OT_RESEARCH_LAB,
				OT_VEHICLE

			};

			enum ObjectAttackOrderType {

				OAOT_FIRE_AT_WILL,
				OAOT_RETURN_FIRE,
				OAOT_HOLD_FIRE

			};

			enum ObjectMoveOrderType {

				OMOT_CHASE,
				OMOT_CHASE_75,
				OMOT_CHASE_50,
				OMOT_CHASE_25,
				OMOT_HOLD_POSITION

			};

		public:

			string			m_name;
			ObjectType		m_type;
			Body*			m_body;
			Player*			m_player;
			ObjectOrderList	m_orderList;

		public:

			Object(string bodyName, const Vector3& position);
			Object(void* bodyDesc, const Vector3& position);

			virtual ~Object(){

				delete m_body;

			}

			virtual void decreaseHitPoints(float hitPoints){

				m_body->m_hitPoints -= hitPoints;

			}

			Body* getBody(){

				return m_body;

			}

			virtual Vector3 getDimensions();

			virtual float getHitPoints(){

				return m_body->m_hitPoints;

			}

			virtual float getMaxHitPoints(){

				return m_body->m_bodyDesc->m_maxHitPoints;

			}

			Quaternion getOrientation(){

				return m_body->m_sceneNode->getOrientation();

			}

			Vector3 getPosition();

			bool isEnemy(Object* object){

				if (m_player == object->m_player)

					return false;

				return true;

			}

			__forceinline void* is(ObjectType type) { return (m_type == type) ? this : NULL; }
			__forceinline Vehicle* isVehicle() { return (Vehicle*)is(OT_VEHICLE); }

			virtual void setDimensionY(float y, bool mode = true);

			virtual void setPlayer(Player* player = NULL){

				m_player = player;

			}

			__forceinline virtual void setOrientation(const Quaternion& q){

				m_body->setOrientation(q);

			}

			virtual void setPosition(const Vector3& position = Vector3::ZERO);

			virtual void setScale(const Vector3& scale = Vector3::ZERO);

			virtual void setSelected(bool selected);

			virtual string toString();

			virtual bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
