
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	template <typename ResourceType> class ResourceManager {

		protected:

			vector<ResourceType>	m_list;
			list<ResourceType*>		m_active;
			list<ResourceType*>		m_inactive;

		public:

			ResourceManager(WORD maxNum = 0) {

				m_list.resize(maxNum);

				for (size_t i = 0; i < m_list.size(); i++)

					m_inactive.push_back(&(m_list[i]));
			}

			void init(WORD maxNum) {

				m_list.resize(maxNum);

				for (size_t i = 0; i < m_list.size(); i++)

					m_inactive.push_back(&(m_list[i]));
			}

			ResourceType* create(const string& name = "") {

				if (m_inactive.size()) {

					m_active.push_back(m_inactive.back());

					m_inactive.pop_back();

					m_active.back()->setName(name);

					return m_active.back();
				}

				return NULL;
			}

			void destroy(const string& name) {

				destroy(getByName(name));
			}

			void destroy(ResourceType* resource) {

				m_active.remove(resource);

				m_inactive.push_back(resource);
			}

			ResourceType* getById(WORD id) {

				return &(m_list[id]);
			}

			ResourceType* getByName(const string& name) {

				for (list<ResourceType*>::iterator itr = m_active.begin(); itr != m_active.end(); itr++)

					if ((*itr)->getName() == name)

						return (*itr);

				return NULL;
			}

			WORD getCurNum() {

				return m_curNum;
			}

			WORD getMaxNum() {

				return (WORD)m_list.size();
			}

			inline ResourceType& operator [] (int i) {

				return m_list[i];
			}

	};

};

//------------------------------------------------------------------------------
