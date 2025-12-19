
//------------------------------------------------------------------------------
// ObjectOrder.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

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
				OOT_STOP

			};

			ObjectOrderType	m_type;
			Vector3			m_vector;
			void*			m_param;

			ObjectOrder(ObjectOrderType type = OOT_DEFAULT, Vector3 vector = Vector3::ZERO, void* param = NULL)

				:	m_type(type),
					m_vector(vector),
					m_param(param) { }

			ObjectOrderType getType(){

				return m_type;

			}

			Vector3 getVector(){

				return m_vector;

			}

			void* getParam(){

				return m_param;

			}

			string toString(){

				char text[512];

				switch (m_type) {

					case OOT_ATTACK_OBJECT:

						sprintf(text, "Attack Object");

						break;

					case OOT_ATTACK_POSITION:

						sprintf(text, "Attack Position");

						break;

					case OOT_CONSTRUCT:

						sprintf(text, "Construct");

						break;

					case OOT_DEFAULT:

						sprintf(text, "Default");

						break;

					case OOT_MOVE:

						sprintf(text, "Move");

						break;

					case OOT_PATROL:

						sprintf(text, "Patrol");

						break;

					case OOT_REPAIR:

						sprintf(text, "Repair");

						break;

					case OOT_STOP:

						sprintf(text, "Stop");

						break;

				}

				return text;

			}

	};

	class ObjectOrderList {

		public:

			typedef list<ObjectOrder>			List;
			typedef list<ObjectOrder>::iterator	Iterator;

			List m_objectOrders;

			ObjectOrderList(){

				addFront(ObjectOrder());

			}

			void addBack(ObjectOrder objectOrder){

				m_objectOrders.push_back(objectOrder);

			}

			void addFront(ObjectOrder objectOrder){

				m_objectOrders.push_front(objectOrder);

			}

			int getCount(){

				return (int)m_objectOrders.size();

			}

			Iterator getFirst(){

				return m_objectOrders.begin();

			}

			Iterator getLast(){

				return m_objectOrders.end();

			}

			void removeAll(){

				m_objectOrders.clear();

				addFront(ObjectOrder());

			}

			void removeBack(){

				m_objectOrders.pop_back();

			}

			void removeFront(){

				m_objectOrders.pop_front();

			}

	};

};

//------------------------------------------------------------------------------
