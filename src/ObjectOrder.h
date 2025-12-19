
//------------------------------------------------------------------------------
// ObjectOrder.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectOrder {

		public:

			enum ObjectOrderType {

				OOT_ATTACK_OBJECT,
				OOT_ATTACK_POSITION,
				OOT_CONSTRUCT,
				OOT_DEFAULT,
				OOT_MOVE,
				OOT_PATROL,
				OOT_REPAIR,
				OOT_SELF_DESTRUCT,
				OOT_STOP

			};

		public:

			ObjectOrderType	m_type;
			Vector3			m_vector;
			void*			m_param;

		public:

			ObjectOrder(ObjectOrderType type = OOT_DEFAULT, Vector3 vector = Vector3::ZERO, void* param = NULL)
				:	m_type(type),
					m_vector(vector),
					m_param(param) { }

			ObjectOrderType getType() {

				return m_type;
			}

			Vector3 getVector() {

				return m_vector;
			}

			void* getParam() {

				return m_param;
			}

			string toString() {

				static char str[512];

				switch (m_type) {

					case OOT_ATTACK_OBJECT:

						sprintf(str, "Attack ObjectTemp");

						break;

					case OOT_ATTACK_POSITION:

						sprintf(str, "Attack Position");

						break;

					case OOT_CONSTRUCT:

						sprintf(str, "Construct");

						break;

					case OOT_DEFAULT:

						sprintf(str, "Default");

						break;

					case OOT_MOVE:

						sprintf(
							str,
							"Move (%.2f, %.2f, %.2f)",
							m_vector.x, m_vector.y, m_vector.z);

						break;

					case OOT_PATROL:

						sprintf(
							str,
							"Patrol (%.2f, %.2f, %.2f)",
							m_vector.x, m_vector.y, m_vector.z);

						break;

					case OOT_REPAIR:

						sprintf(str, "Repair");

						break;

					case OOT_STOP:

						sprintf(str, "Stop");

						break;

				} // switch (m_type)

				return str;
			}

	};

	class ObjectOrderList {

		public:

			typedef list<ObjectOrder>			List;
			typedef list<ObjectOrder>::iterator	Iterator;

		public:

			List m_objectOrders;

		public:

			~ObjectOrderList() {

				removeAll();
			}

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

				return (*(m_objectOrders.begin()));
			}

			ObjectOrder getLast() {

				return (*(m_objectOrders.end()));
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
