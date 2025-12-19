
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ResourceManager.h"

#include "Object.h"
#include "ObjectDesc.h"

//------------------------------------------------------------------------------
// ObjectManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectManager: public ResourceManager<Object>, public Ogre::Singleton<ObjectManager> {

		public:

			typedef list<Object*>			List;
			typedef list<Object*>::iterator	Iterator;

			Iterator Begin() {

				return m_active.begin();
			}

			Iterator End() {

				return m_active.end();
			}

		public:

			ObjectManager() {

				ResourceManager::init(256);
			}

			Object* create(const string& name, ObjectDesc* objectDesc);

			void getAllInRadius(List& list, Ogre::Vector3 point, float radius);

			Object* getNearest(Object* object);

			void update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
