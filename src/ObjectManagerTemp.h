
//------------------------------------------------------------------------------
// ObjectManagerTemp.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectTemp.h"
#include "ResourceManagerTemp.h"

//------------------------------------------------------------------------------
// ObjectManagerTemp
//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectManagerTemp: public ResourceManagerTemp<ObjectManagerTemp, ObjectTemp> {

		public:

			typedef list<ObjectTemp*>			List;
			typedef list<ObjectTemp*>::iterator	Iterator;

		private:

			List m_selected;

		public:

			virtual void destroy(ObjectTemp* object) {

				deselect(object);

				ResourceManagerTemp::destroy(object);
			}

			virtual void destroyAll() {

				ResourceManagerTemp::destroyAll();

				m_selected.clear();
			}

			void add(ObjectTemp* object);

			void addOrderToSelected(ObjectOrder objectOrder) {

				for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++) {

					(*itr)->m_orderList.addBack(objectOrder);

				}

			}

			ObjectTemp* create(ObjectDesc* objectDesc, Player* player, const Vector3& position);

			void deselect(ObjectTemp* object);

			void deselectAll();

			Iterator getFirst();

			ObjectTemp* getFirstSelected() {

				if (getSelectedCount())

					return *(m_selected.begin());

				return NULL;
			}

			Iterator getLast();

			void getAllInRadius(ObjectTemp* object, float radius, List* allInRadius);

			ObjectTemp* getNearest(ObjectTemp* object);

			ObjectTemp* getNearestEnemy(ObjectTemp* object);

			int getSelectedCount() {

				return (int)m_selected.size();
			}

			bool isSelected(ObjectTemp* object) {

				for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++)

					if ((*itr) == object)

						return true;

				return false;

			}

			void select(ObjectTemp* object);

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
