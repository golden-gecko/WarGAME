
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectManager.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ObjectViewer: public Ogre::Singleton<ObjectViewer> {

		protected:

			CEGUI::FrameWindow*		m_objectViewer;
			CEGUI::Listbox*			m_list;
			CEGUI::StaticText*		m_text;
			CEGUI::StaticImage*		m_image;
			CEGUI::Listbox*			m_orderList;
			CEGUI::ListboxTextItem* m_item;

			bool list_SelectionChanged(const CEGUI::EventArgs& e) {

				if (m_list->getSelectedCount() && m_list->getFirstSelectedItem()->getUserData()) {

					m_text->setText(((Object*)(m_list->getFirstSelectedItem()->getUserData()))->toString());

					m_orderList->resetList();

					if (((Object*)(m_list->getFirstSelectedItem()->getUserData()))->m_orderList.getCount()) {

						for (ObjectOrderList::Iterator itr = ((Object*)(m_list->getFirstSelectedItem()->getUserData()))->m_orderList.Begin(); itr != ((Object*)(m_list->getFirstSelectedItem()->getUserData()))->m_orderList.End(); itr++) {

							m_item = new CEGUI::ListboxTextItem(itr->toString());
							m_item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
							m_item->setUserData(&(*itr));
							m_orderList->addItem(m_item);
						}

					} else {

						m_item = new CEGUI::ListboxTextItem("no orders");
						m_item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
						m_orderList->addItem(m_item);
					}

				} else {

					m_text->setText("no object selected");

					m_item = new CEGUI::ListboxTextItem("no orders");
					m_item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
					m_orderList->addItem(m_item);
				}

				return true;
			}

		public:

			ObjectViewer(): m_objectViewer(NULL), m_list(NULL), m_text(NULL), m_item(NULL) { }

			void init() {

				m_objectViewer = (CEGUI::FrameWindow*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectViewer");
				m_list = (CEGUI::Listbox*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectViewer/List");
				m_text = (CEGUI::StaticText*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectViewer/Text");
				m_image = (CEGUI::StaticImage*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectViewer/Image");
				m_orderList = (CEGUI::Listbox*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("ObjectViewer/OrderList");

				m_list->subscribeEvent(
					CEGUI::Listbox::EventSelectionChanged,
					CEGUI::Event::Subscriber(&ObjectViewer::list_SelectionChanged, this));

				m_objectViewer->setCaptionColour(CEGUI::colour(1.0f, 1.0f, 1.0f));
			}

			void setVisible(bool visible) {

				if (visible) {

					m_list->resetList();

					for (ObjectManager::Iterator itr = ObjectManager::getSingletonPtr()->Begin(); itr != ObjectManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem((*itr)->getName());
						m_item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_objectViewer->activate();
				}

				m_objectViewer->setVisible(visible);
			}

			void changeVisible() {

				setVisible(!m_objectViewer->isVisible());
			}

	};

};

//------------------------------------------------------------------------------
