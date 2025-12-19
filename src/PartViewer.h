
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartManager.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class PartViewer: public Ogre::Singleton<PartViewer> {

		protected:

			Ogre::SceneManager*		m_sceneManager;
			Ogre::Camera*			m_camera;
			Ogre::Viewport*			m_viewport;
			Ogre::Entity*			m_entity;
			Ogre::SceneNode*		m_sceneNode;

			CEGUI::FrameWindow*		m_partViewer;
			CEGUI::Listbox*			m_list;
			CEGUI::StaticText*		m_text;
			CEGUI::StaticImage*		m_image;
			CEGUI::ListboxTextItem*	m_item;

			bool list_SelectionChanged(const CEGUI::EventArgs& e);

		public:

			PartViewer()
				:	m_sceneManager(NULL),
					m_camera(NULL),
					m_viewport(NULL),
					m_entity(NULL),
					m_sceneNode(NULL),
					m_partViewer(NULL),
					m_list(NULL),
					m_text(NULL),
					m_image(NULL),
					m_item(NULL) { }

			void init();

			void setVisible(bool visible) {

				if (visible) {

					m_list->resetList();

					m_item = new CEGUI::ListboxTextItem("arm");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::ArmManager::Iterator itr = PartManager::ArmManager::getSingletonPtr()->Begin(); itr != PartManager::ArmManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("armour");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::ArmourManager::Iterator itr = PartManager::ArmourManager::getSingletonPtr()->Begin(); itr != PartManager::ArmourManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("body");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::BodyManager::Iterator itr = PartManager::BodyManager::getSingletonPtr()->Begin(); itr != PartManager::BodyManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("engine");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::EngineManager::Iterator itr = PartManager::EngineManager::getSingletonPtr()->Begin(); itr != PartManager::EngineManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("explosive");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::ExplosiveManager::Iterator itr = PartManager::ExplosiveManager::getSingletonPtr()->Begin(); itr != PartManager::ExplosiveManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("reactor");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::ReactorManager::Iterator itr = PartManager::ReactorManager::getSingletonPtr()->Begin(); itr != PartManager::ReactorManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("shield");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::ShieldManager::Iterator itr = PartManager::ShieldManager::getSingletonPtr()->Begin(); itr != PartManager::ShieldManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("teleporter");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::TeleporterManager::Iterator itr = PartManager::TeleporterManager::getSingletonPtr()->Begin(); itr != PartManager::TeleporterManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					m_item = new CEGUI::ListboxTextItem("weapon");
					m_item->setTextColours(CEGUI::colour(0.55f, 0.66f, 0.77));
					m_item->setSelectionColours(CEGUI::colour(0.0f, 0.0f, 0.0f));
					m_list->addItem(m_item);

					for (PartManager::WeaponManager::Iterator itr = PartManager::WeaponManager::getSingletonPtr()->Begin(); itr != PartManager::WeaponManager::getSingletonPtr()->End(); itr++) {

						m_item = new CEGUI::ListboxTextItem("  " + (*itr)->getName());
						m_item->setUserData(*itr);
						m_list->addItem(m_item);
					}

					for (size_t i = 0; i < m_list->getItemCount(); i++)

						m_list->getListboxItemFromIndex(i)->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");

					m_partViewer->activate();
				}

				m_partViewer->setVisible(visible);
			}

			void changeVisible() {

				setVisible(!m_partViewer->isVisible());
			}

	};

};

//------------------------------------------------------------------------------
