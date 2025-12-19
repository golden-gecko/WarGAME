
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDescManager.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PartDescViewer: public Ogre::Singleton<PartDescViewer> {

		protected:

			Ogre::SceneManager*		m_sceneManager;
			Ogre::Camera*			m_camera;
			Ogre::Viewport*			m_viewport;
			Ogre::Entity*			m_entity;
			Ogre::SceneNode*		m_sceneNode;

			CEGUI::FrameWindow*		m_partDescViewer;
			CEGUI::Listbox*			m_list;
			CEGUI::StaticText*		m_text;
			CEGUI::StaticImage*		m_image;
			CEGUI::ListboxTextItem*	m_item;

			bool list_SelectionChanged(const CEGUI::EventArgs& e);

		public:

			PartDescViewer()
				:	m_sceneManager(NULL),
					m_camera(NULL),
					m_viewport(NULL),
					m_entity(NULL),
					m_sceneNode(NULL),
					m_partDescViewer(NULL),
					m_list(NULL),
					m_text(NULL),
					m_item(NULL) { }

			void init();

			void setVisible(bool visible) {

				if (visible) {

					m_list->resetList();

					m_item = new CEGUI::ListboxTextItem("arm");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::ArmDescManager::Iterator itr = PartDescManager::ArmDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::ArmDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("armour");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::ArmourDescManager::Iterator itr = PartDescManager::ArmourDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::ArmourDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("body");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::BodyDescManager::Iterator itr = PartDescManager::BodyDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::BodyDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("engine");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::EngineDescManager::Iterator itr = PartDescManager::EngineDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::EngineDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("explosive");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::ExplosiveDescManager::Iterator itr = PartDescManager::ExplosiveDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::ExplosiveDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("reactor");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::ReactorDescManager::Iterator itr = PartDescManager::ReactorDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::ReactorDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("shield");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::ShieldDescManager::Iterator itr = PartDescManager::ShieldDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::ShieldDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("teleporter");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::TeleporterDescManager::Iterator itr = PartDescManager::TeleporterDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::TeleporterDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("weapon");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartDescManager::WeaponDescManager::Iterator itr = PartDescManager::WeaponDescManager::getSingletonPtr()->Begin(); itr != PartDescManager::WeaponDescManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					for (size_t i = 0; i < m_list->getItemCount(); i++)

						m_list->getListboxItemFromIndex(i)->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");

					m_partDescViewer->activate();
				}

				m_partDescViewer->setVisible(visible);
			}

			void changeVisible() {

				setVisible(!m_partDescViewer->isVisible());
			}

	};

};

//------------------------------------------------------------------------------
