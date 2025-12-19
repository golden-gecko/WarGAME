
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectOrder {

		public:

			enum ObjectOrderType {

				OOT_NULL				= 0x0000,

				OOT_ATTACK_OBJECT		= 0x0001,
				OOT_ATTACK_POSITION		= 0x0002,
				OOT_CONSTRUCT			= 0x0004,
				OOT_DECONSTRUCT			= 0x0008,
				OOT_FOLLOW				= 0x0010,
				OOT_MOVE_TO_OBJECT		= 0x0020,
				OOT_MOVE_TO_POSITION	= 0x0040,
				OOT_PATROL				= 0x0080,
				OOT_REPAIR				= 0x0100,
				OOT_RESUPPLY			= 0x0200,
				OOT_SELF_DESTRUCT		= 0x0400,
				OOT_STOP				= 0x0800

			};

		public:

			ObjectOrderType	m_type;
			Ogre::Vector3	m_vector;
			void*			m_param;

		public:

			ObjectOrder(ObjectOrderType type = OOT_NULL, const Ogre::Vector3& vector = Ogre::Vector3::ZERO, void* param = NULL)
				:	m_type(type),
					m_vector(vector),
					m_param(param) { }

			ObjectOrderType getType() {

				return m_type;
			}

			Ogre::Vector3 getVector() {

				return m_vector;
			}

			void* getParam() {

				return m_param;
			}

			string toString();

	};

	class ObjectOrderList {

		public:

			typedef list<ObjectOrder>			List;
			typedef list<ObjectOrder>::iterator	Iterator;

			Iterator Begin() {

				return m_objectOrders.begin();
			}

			Iterator End() {

				return m_objectOrders.end();
			}

		private:

			List m_objectOrders;

		public:

			void addBack(const ObjectOrder& objectOrder = ObjectOrder()) {

				m_objectOrders.push_back(objectOrder);
			}

			void addFront(const ObjectOrder& objectOrder = ObjectOrder()) {

				m_objectOrders.push_front(objectOrder);
			}

			int getCount() {

				return (int)m_objectOrders.size();
			}

			ObjectOrder getFirst() {

				return m_objectOrders.front();
			}

			ObjectOrder getLast() {

				return m_objectOrders.back();
			}

			void removeAll() {

				m_objectOrders.clear();
			}

			void removeBack() {

				m_objectOrders.pop_back();
			}

			void removeFront() {

				m_objectOrders.pop_front();
			}

	};
};

//------------------------------------------------------------------------------
