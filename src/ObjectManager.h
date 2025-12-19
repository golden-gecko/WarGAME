
//------------------------------------------------------------------------------
// ObjectManager.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Missile.h"
#include "PowerPlant.h"
#include "Vehicle.h"

//------------------------------------------------------------------------------
// ObjectManager
//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectManager : public Singleton<ObjectManager> {

		public:

			typedef list<Object*>			List;
			typedef list<Object*>::iterator	Iterator;

		private:

			List m_objects;
			List m_selected;

		public:

			~ObjectManager();

			void add(Object* object);

			void addOrderToSelected(ObjectOrder objectOrder){

				for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++) {

					(*itr)->m_orderList.addBack(objectOrder);

				}

			}

			void deselect(Object* object);

			void deselectAll();

			void destroy(Object* object);

			void destroyAll();

			int getCount();

			Iterator getFirst();

			Iterator getLast();

			bool isSelected(Object* object){

				for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++)

					if ((*itr) == object)

						return true;

				return false;

			}

			void select(Object* object);

			void selecteAll();

			void setOrderToSelected(ObjectOrder objectOrder){

				for (Iterator itr = m_selected.begin(); itr != m_selected.end(); itr++) {

					(*itr)->m_orderList.removeAll();
					(*itr)->m_orderList.addFront(objectOrder);

				}

			}

			void update(float deltaTime);

	};

};

//------------------------------------------------------------------------------
