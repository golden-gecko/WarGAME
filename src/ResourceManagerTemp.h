
//------------------------------------------------------------------------------
// ResourceManagerTemp.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	template <typename T, typename ResourceType> class ResourceManagerTemp: public Singleton <T> {

		protected:

			list<ResourceType*> m_list;

		public:

			virtual ~ResourceManagerTemp() {

				destroyAll();
			}

			virtual void destroy(ResourceType* resource) {

				delete resource;

				m_list.remove(resource);
			}

			virtual void destroyAll() {

				for (list<ResourceType*>::iterator itr = m_list.begin(); itr != m_list.end(); itr++)

					delete *itr;

				m_list.clear();
			}

			int getCount() {

				return (int)m_list.size();
			}

	};
};

//------------------------------------------------------------------------------
