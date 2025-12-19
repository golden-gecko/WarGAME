
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Resource.h"

#include "Object.h"
#include "PartDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Part: public Resource {

		public:

			enum PartType {

				// Arm constructs and repairs building and units.
				PT_ARM			= 0x0001,
				// Armour decreaes damage given to all others parts installed on the same object.
				PT_ARMOUR		= 0x0002,
				// Body is a base part, it must be installed in any object.
				PT_BODY			= 0x0004,
				// Engine moves unit.
				PT_ENGINE		= 0x0008,
				// Explosive dameges all objects in the given radius.
				PT_EXPLOSIVE	= 0x0010,
				// Radar locates objects and identifies its types.
				PT_RADAR		= 0x0020,
				// Reactor produces energy.
				PT_REACTOR		= 0x0040,
				// Shield decreaes damage given to all other parts installed on the same object,
				// it can regenerate itself.
				PT_SHIELD		= 0x0080,
				// Storage stores ammunition, energy and or fuel.
				PT_STORAGE		= 0x0100,
				// Teleporter can move units to other teleporter.
				PT_TELEPORTER	= 0x0200,
				// Weapon creates and fires missiles.
				PT_WEAPON		= 0x0400

			};

			enum PartState {

				// Part is very damaged and cannot process orders.
				// If it's not repaired, it will be destroyed after a short period of time,
				PS_BROKEN				= 0x0001,
				// Part is dead, cannot process orders.
				PS_DEAD					= 0x0002,
				// Part can process orders.
				PS_NORMAL				= 0x0004,
				// Objects is processig an order.
				PS_PROCESSING_ORDER		= 0x0008,
				// Part has just finished processing order or the order is invalid,
				// the first order from the object order list will be removed.
				PS_ORDER_FINISHED		= 0x0010,
				// Part is under construction and cannot process any orders.
				// Parent object of this part is also under construction and cannot process any orders.
				PS_UNDER_CONSTRUCTION	= 0x0020,

				PS_FOLLOW				= 0x0040,
				PS_MOVE_TO_POSITION		= 0x0080,
				PS_MOVE_TO_OBJECT		= 0x0100,

				PS_CONSTRUCT			= 0x0200,
				PS_MODIFY				= 0x0400,
				PS_REPAIR				= 0x0800,
				PS_RESUPPLY				= 0x1000

			};

		protected:

			Object*		m_parent;
			PartType	m_type;
			PartState	m_state;
			float		m_hitPoints;

			union {

				ArmDesc*			m_armDesc;
				ArmourDesc*			m_armourDesc;
				BodyDesc*			m_bodyDesc;
				EngineDesc*			m_engineDesc;
				ExplosiveDesc*		m_explosiveDesc;
				PartDesc*			m_partDesc;
				PartWithMeshDesc*	m_partWithMeshDesc;
				ReactorDesc*		m_reactorDesc;
				ShieldDesc*			m_shieldDesc;
				TeleporterDesc*		m_teleporterDesc;
				WeaponDesc*			m_weaponDesc;

			};

			Part(PartType type): m_parent(NULL), m_type(type), m_state(PS_NORMAL), m_hitPoints(0.0f), m_partDesc(NULL) { }

		public:

			float getHitPoints() {

				return m_hitPoints;
			}
			float getEnergyCost() {

				return m_partDesc->getEnergyCost();
			}
			float getMaxHitPoints() {

				return m_partDesc->getMaxHitPoints();
			}
			Object* getParent() {

				return m_parent;
			}
			PartState getState() {

				return m_state;
			}
			PartType getType() {

				return m_type;
			}

			virtual void setParent(Object* parent) {
				
				m_parent = parent;
			}
			virtual void setPartDesc(PartDesc* partDesc) {
				
				m_partDesc = partDesc;

				m_hitPoints = (m_partDesc ? m_partDesc->getMaxHitPoints() : 0.0f);
			}
			void setState(PartState state) {

				m_state = state;
			}

			void damage(float damage) {

				m_hitPoints -= damage;
			}

			virtual bool update(float deltaTime) {

				return (m_partDesc ? true : false);
			}

	};

};

//------------------------------------------------------------------------------
