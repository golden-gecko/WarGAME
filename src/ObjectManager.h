
//------------------------------------------------------------------------------
// ObjectManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

#include "Object.h"
#include "ResourceManagerTemp.h"

//------------------------------------------------------------------------------
// ObjectManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectManager: public ResourceManagerTemp<ObjectManager, Object> {

		public:

			WORD			m_numObject;
			WORD			m_maxNumObject;
			vector<Object>	m_objectList;

		public:

			ObjectManager(): m_numObject(0), m_maxNumObject(1024) { }

			bool init() {

//				m_objectList.resize(m_maxNumObject);

				return true;
			}

			Object* createObject(ObjectDesc* objectDesc) {

				if (m_numObject == m_maxNumObject)

					m_objectList.resize(m_maxNumObject *= 2);

				return NULL;
			}

		public:

			typedef list<Object*>			List;
			typedef list<Object*>::iterator	Iterator;

		private:

			List m_selected;

		public:

			void onDamage(const Vector3& position, float radius, float damage) {

				/*
				List list;

				getAllInRadius(position, radius, list);

				for (Iterator itr = list.begin(); itr != list.end(); itr++)

					(*itr)->onDamage(damage);
				*/
			}

			virtual void destroy(Object* object) {

				deselect(object);

				ResourceManagerTemp::destroy(object);
			}

			virtual void destroyAll() {

				ResourceManagerTemp::destroyAll();

				m_selected.clear();
			}

			void add(Object* object);

			void addOrderToSelected(ObjectOrder objectOrder) {

				for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++) {

					(*itr)->m_orderList.addBack(objectOrder);

				}

			}

			Object* create(ObjectDesc* objectDesc, Player* player, const Vector3& position);

			void deselect(Object* object);

			void deselectAll();

			Iterator getFirst();

			Object* getFirstSelected() {

				if (getSelectedCount())

					return *(m_selected.begin());

				return NULL;
			}

			Iterator getLast();

			void getAllInRadius(Object* object, float radius, List* allInRadius);

			Object* getNearest(Object* object);

			Object* getNearestEnemy(Object* object);

			int getSelectedCount() {

				return (int)m_selected.size();
			}

			bool isSelected(Object* object) {

				for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++)

					if ((*itr) == object)

						return true;

				return false;

			}

			void select(Object* object);

			void selecteAll();

			void setOrderToSelected(ObjectOrder objectOrder) {

				for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++) {

					(*itr)->m_orderList.removeAll();
					(*itr)->m_orderList.addFront(objectOrder);

				}

			}

			void update(float deltaTime);
	};
};

//------------------------------------------------------------------------------
