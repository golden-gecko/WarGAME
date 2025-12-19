
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "Building.h"
#include "BuildingDesc.h"
#include "Object.h"
#include "ObjectDesc.h"
#include "Projectile.h"
#include "ProjectileDesc.h"
#include "Unit.h"
#include "UnitDesc.h"

//------------------------------------------------------------------------------
// ObjectManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectManager: public Ogre::Singleton<ObjectManager> {

		public:

			typedef list<Object*>			List;
			typedef list<Object*>::iterator	Iterator;

		private:

			ResourceManager<Building>	m_building;
			ResourceManager<Object>		m_object;
			ResourceManager<Projectile>	m_projectile;
			ResourceManager<Unit>		m_unit;

		public:

			ObjectManager() {

				m_building.init(256);
				m_object.init(256);
				m_projectile.init(256);
				m_unit.init(256);
			}

			Building* createBuilding(BuildingDesc* buildingDesc, const string& name = "building");
			Object* createObject(ObjectDesc* objectDesc, const string& name = "object");
			Projectile* createProjectile(ProjectileDesc* projectileDesc, const string& name = "projectile");
			Unit* createUnit(UnitDesc* unitDesc, const string& name = "unit");

			void destroyBuilding(Building* building) { }
			void destroyObject(Object* object);
			void destroyProjectile(Projectile* projectile) { }
			void destroyUnit(Unit* unit) { }

			void getAllInRadius(List& list, Ogre::Vector3 point, float radius);

			Object* getNearest(Object* object);

			void update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
