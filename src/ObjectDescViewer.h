
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectDescManager.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectDescViewer: public Ogre::Singleton<ObjectDescViewer> {

		protected:

			CEGUI::FrameWindow*		m_objectDescViewer;
			CEGUI::Listbox*			m_list;
			CEGUI::StaticImage*		m_image;
			CEGUI::ListboxTextItem*	m_item;

		public:

			ObjectDescViewer(): m_objectDescViewer(NULL), m_list(NULL), m_image(NULL), m_item(NULL) { }

			void init() {

				m_objectDescViewer = (CEGUI::FrameWindow*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectDescViewer");
				m_list = (CEGUI::Listbox*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectDescViewer/List");
				m_image = (CEGUI::StaticImage*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectDescViewer/Image");

				m_objectDescViewer->setCaptionColour(CEGUI::colour(1.0f, 1.0f, 1.0f));
			}

			void setVisible(bool visible) {

				if (visible) {

					m_list->resetList();

					for (ObjectDescManager::Iterator itr = ObjectDescManager::getSingletonPtr()->Begin(); itr != ObjectDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem((*itr)->getName());

						m_item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
						m_item->setUserData(*itr);

						m_list->addItem(m_item);
					}

					m_objectDescViewer->activate();
				}

				m_objectDescViewer->setVisible(visible);
			}

			void changeVisible() {

				setVisible(!m_objectDescViewer->isVisible());
			}

	};

};

//------------------------------------------------------------------------------
