
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Resource.h"

#include "EffectManager.h"
#include "ObjectOrder.h"
#include "Part.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Object: public Resource {

		public:

			enum ObjectType {

				OT_NULL				= 0x0000,

				OT_OBJECT			= Part::PT_BODY,
				OT_BUILDING			= Part::PT_BODY,
				OT_MISSILE			= Part::PT_BODY | Part::PT_EXPLOSIVE,
				OT_UNIT				= Part::PT_BODY | Part::PT_ENGINE,

				OT_REPAIR_BUILDING	= OT_BUILDING + Part::PT_ARM,
				OT_BATTLE_BUILDING	= OT_BUILDING + Part::PT_WEAPON,

				OT_REPAIR_UNIT		= OT_UNIT + Part::PT_ARM,
				OT_BATTLE_UNIT		= OT_UNIT + Part::PT_WEAPON

			};

			enum ObjectState {

				OS_NULL					= 0x00,
				// Object is very damaged and cannot process orders.
				// If it's not repaired, it will be destroyed after a short period of time,
				OS_BROKEN				= 0x01,
				// Object is dead, cannot process orders.
				OS_DEAD					= 0x02,
				// Object can process orders.
				OS_NORMAL				= 0x04,
				// Objects is processig an order.
				OS_PROCESSING_ORDER		= 0x08,
				// Object has just finished processing order or the order is invalid,
				// the first order from the list will be removed.
				OS_ORDER_FINISHED		= 0x10,
				// Object is under construction and cannot process any orders.
				OS_UNDER_CONSTRUCTION	= 0x20,
				// Object cannot process order, push order to bottom of the list.
				OS_ORDER_FAILED			= 0x40

			};

		protected:
		public:

			Arm*			m_arm;
			Armour*			m_armour;
			Body*			m_body;
			Engine*			m_engine;
			Explosive*		m_explosive;
			Reactor*		m_reactor;
			Shield*			m_shield;
			Teleporter*		m_teleporter;
			Weapon*			m_weapon;

			int				m_type;
			int				m_state;
			bool			m_selected;
			Player*			m_player;
			Smoke*			m_smoke;

			Ogre::Vector3	m_linearVelocity;
			Ogre::Vector3	m_linearDamping;

		public:

			ObjectOrderList m_orderList;

			Object();

			void create();
			void destroy();

			Arm* getArm() {

				return m_arm;
			}
			Armour* getArmour() {

				return m_armour;
			}
			Body* getBody() {

				return m_body;
			}
			Engine* getEngine() {

				return m_engine;
			}
			Explosive* getExplosive() {

				return m_explosive;
			}
			Reactor* getReactor() {

				return m_reactor;
			}
			Shield* getShield() {

				return m_shield;
			}
			Teleporter* getTeleporter() {

				return m_teleporter;
			}
			Weapon* getWeapon() {

				return m_weapon;
			}
			int getState() {

				return m_state;
			}
			Player* getPlayer() {

				return m_player;
			}
			int getType() {

				return m_type;
			}
			Ogre::Vector3 getDirection();
			virtual float getEnergyCost();
			virtual float getHitPoints();
			virtual float getMaxHitPoints();
			Ogre::Quaternion getOrientation();
			Ogre::Vector3 getPosition();
			bool getSelected();
			virtual Ogre::AxisAlignedBox getWorldBoundingBox();
			Ogre::Vector3 getWorldCenter();

			void setLinearVelocity(const Ogre::Vector3& linearVelocity) {

				m_linearVelocity = linearVelocity;
			}
			void setState(ObjectState state) {

				m_state = state;
			}
			void setArm(Arm* arm);
			void setArmour(Armour* armour);
			void setBody(Body* body);
			void setEngine(Engine* engine);
			void setExplosive(Explosive* explosive);
			virtual void setOrientation(const Ogre::Quaternion& orientation);
			virtual void setPlayer(Player* player);
			virtual void setPosition(const Ogre::Vector3& position);
			void setReactor(Reactor* reactor);
			virtual void setSelected(bool selected);
			void setShield(Shield* shield);
			void setTeleporter(Teleporter* teleporter);
			void setWeapon(Weapon* weapon);

			bool hasPart(int part) {

				return ((m_type & part) != 0);
			}
			virtual void damage(float damage);
			void order(const ObjectOrder& order, bool remove = true);
			virtual void rotate(const Ogre::Quaternion& q);

			virtual string toString();

			virtual bool update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
