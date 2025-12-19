
//------------------------------------------------------------------------------
// BattleFieldCamera.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class BattleFieldCameraOrder {

		public:

			Vector3						m_vector;
			Quaternion					m_quaternion;

		public:

			BattleFieldCameraOrder(	
				Vector3		vector		= Vector3::ZERO,
				Quaternion	quaternion	= Quaternion::IDENTITY)

				:	m_vector(vector),
					m_quaternion(quaternion) { }

	};

	class BattleFieldCameraOrderList {

		public:

			list<BattleFieldCameraOrder> m_list;

		public:

			~BattleFieldCameraOrderList() {

				removeAll();
			}

			void addFront(BattleFieldCameraOrder order) {

				m_list.push_front(order);
			}

			void addBack(BattleFieldCameraOrder order) {

				m_list.push_back(order);
			}

			void removeFront() {

				m_list.pop_front();
			}

			void removeBack() {

				m_list.pop_back();
			}

			void removeAll() {

				m_list.clear();
			}

			int getCount() {

				return (int)m_list.size();
			}

			BattleFieldCameraOrder getFirst() {

				return (*(m_list.begin()));
			}

	};

	class BattleFieldCamera: public Singleton<BattleFieldCamera> {

		public:

			enum CameraState {

				CS_IDLE,
				CS_TRACK_OBJECT,
				CS_FOLLOW_OBJECT

			};

		public:

			CameraState					m_state;
			Camera*						m_ogreCamera;
			float						m_speed;
			float						m_turnSpeed;
			ObjectTemp*						m_target;
			BattleFieldCameraOrderList	m_orderList;

		public:

			BattleFieldCamera()
				:	m_state(CS_IDLE),
					m_ogreCamera(NULL),
					m_speed(15.0f),
					m_turnSpeed(25.0f),
					m_target(NULL) { }

			void init();

			void follow(ObjectTemp* target) {

				m_target = target;

				if (m_target)

					m_state = CS_FOLLOW_OBJECT;

				else

					m_state = CS_IDLE;

			}

			void track(ObjectTemp* target) {

				m_target = target;

				if (m_target)

					m_state = CS_TRACK_OBJECT;

				else

					m_state = CS_IDLE;

			}

			void update(float deltaTime);

	};
};

//------------------------------------------------------------------------------
