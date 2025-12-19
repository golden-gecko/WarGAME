
//------------------------------------------------------------------------------
// Xml.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

//------------------------------------------------------------------------------
// XML
//------------------------------------------------------------------------------

namespace WarGAME {

	enum ResourceType {

		RT_EVENT,
		RT_MAP,
		RT_MODULE,
		RT_OBJECT,
		RT_SKY

	};

	class Xml {

		private:

			TiXmlDocument		m_document;

			vector<TiXmlNode*>	m_events;
			vector<TiXmlNode*>	m_maps;
			vector<TiXmlNode*>	m_modules;
			vector<TiXmlNode*>	m_objects;
			vector<TiXmlNode*>	m_skies;

			const char* getText(TiXmlNode* node, const char* name){

				for (TiXmlNode* i = node->FirstChild(); i != NULL; i = i->NextSibling())

					if ((i->Type() == TiXmlNode::ELEMENT) && (strcmp(i->Value(), name) == 0))

						return i->ToElement()->GetText();

				return "";

			}

		public:

			Xml(string fileName){

				m_document.SetValue(fileName.c_str());

			}

			bool load(){

				if (m_document.LoadFile() == false)

					return false;

				if (m_document.RootElement() == NULL)

					return false;

				if (strcmp(m_document.RootElement()->Value(), "WarGAME") != 0)

					return false;

				for (TiXmlNode* i = m_document.RootElement()->FirstChild(); i != NULL; i = i->NextSibling()) {

					if (strcmp(i->Value(), "Event") == 0)

						m_events.push_back(i);

					else if (strcmp(i->Value(), "map") == 0)

						m_maps.push_back(i);

					else if (strcmp(i->Value(), "descriptor") == 0)

						m_modules.push_back(i);

					else if (strcmp(i->Value(), "object") == 0)

						m_objects.push_back(i);

					else if (strcmp(i->Value(), "sky") == 0)

						m_skies.push_back(i);

				} // for (...)

				return true;

			}

			int getNumResources(ResourceType resourceType){

				switch (resourceType) {

					case RT_EVENT	: return (int)m_events.size();
					case RT_MAP		: return (int)m_maps.size();
					case RT_MODULE	: return (int)m_modules.size();
					case RT_OBJECT	: return (int)m_objects.size();
					case RT_SKY		: return (int)m_skies.size();

				}

				return 0;
			
			}

			const char* getParameterAsString(ResourceType resourceType, int resourceIndex, const char* name){

				switch (resourceType) {

					case RT_EVENT	: return getText(m_events[resourceIndex], name);
					case RT_MAP		: return getText(m_maps[resourceIndex], name);
					case RT_MODULE	: return getText(m_modules[resourceIndex], name);
					case RT_OBJECT	: return getText(m_objects[resourceIndex], name);
					case RT_SKY		: return getText(m_skies[resourceIndex], name);

				}

				return "";

			}

			double getParameterAsNumber(ResourceType resourceType, int resourceIndex, const char* name){

				return atof(getParameterAsString(resourceType, resourceIndex, name));

			}

			bool getParameterAsBool(ResourceType resourceType, int resourceIndex, const char* name){

				if (getParameterAsNumber(resourceType, resourceIndex, name))

					return true;

				return false;

			}

	};

};

//------------------------------------------------------------------------------
