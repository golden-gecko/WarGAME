
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PlayerManager.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PlayerViewer: public Ogre::Singleton<PlayerViewer> {

		protected:

			CEGUI::FrameWindow*		m_playerViewer;
			CEGUI::Listbox*			m_list;
			CEGUI::StaticText*		m_text;
			CEGUI::ListboxTextItem* m_item;

			bool list_SelectionChanged(const CEGUI::EventArgs& e) {

				if (m_list->getSelectedCount() && m_list->getFirstSelectedItem()->getUserData())

					m_text->setText(((Player*)(m_list->getFirstSelectedItem()->getUserData()))->toString());

				else

					m_text->setText("No Player Selected");

				return true;
			}

		public:

			PlayerViewer(): m_playerViewer(NULL), m_list(NULL), m_text(NULL), m_item(NULL) { }

			void init() {

				m_playerViewer = (CEGUI::FrameWindow*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("PlayerViewer");
				m_list = (CEGUI::Listbox*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("PlayerViewer/List");
				m_text = (CEGUI::StaticText*)
					CEGUI::WindowManager::getSingletonPtr()->getWindow("PlayerViewer/Text");

				m_list->subscribeEvent(
					CEGUI::Listbox::EventSelectionChanged,
					CEGUI::Event::Subscriber(&PlayerViewer::list_SelectionChanged, this));

				m_playerViewer->setCaptionColour(CEGUI::colour(1.0f, 1.0f, 1.0f));
			}

			void setVisible(bool visible) {

				if (visible) {

					m_list->resetList();

					for (PlayerManager::Iterator itr = PlayerManager::getSingletonPtr()->Begin(); itr != PlayerManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem((*itr)->getName());

						m_item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");
						m_item->setUserData(*itr);

						m_list->addItem(m_item);
					}

					m_playerViewer->activate();
				}

				m_playerViewer->setVisible(visible);
			}

			void changeVisible() {

				setVisible(!m_playerViewer->isVisible());
			}

	};

};

//------------------------------------------------------------------------------
