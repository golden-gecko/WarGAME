
//------------------------------------------------------------------------------
// ConstructionPanel.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class ConstructionPanel: public Singleton<ConstructionPanel> {

		private:

			Ogre::SceneManager*		m_sceneManager;
			Ogre::Camera*			m_camera;
			Ogre::Viewport*			m_viewport;
			Ogre::Entity*			m_bodyEnt;
			Ogre::Entity*			m_weaponEnt;
			Ogre::SceneNode*		m_bodyNode;
			Ogre::SceneNode*		m_weaponNode;

			CEGUI::FrameWindow*		m_constructionPanel;
			CEGUI::Editbox*			m_name;
			CEGUI::StaticImage*		m_viewer;
			CEGUI::Listbox*			m_objectDescList;
			CEGUI::Listbox*			m_armourList;
			CEGUI::Listbox*			m_bodyList;
			CEGUI::Listbox*			m_engineList;
			CEGUI::Listbox*			m_explosiveList;
			CEGUI::Listbox*			m_powerReactorList;
			CEGUI::Listbox*			m_weaponList;
			CEGUI::PushButton*		m_add;
			CEGUI::PushButton*		m_rot;
			CEGUI::PushButton*		m_remove;
			CEGUI::PushButton*		m_close;

			bool constructionPanel_Shown(const CEGUI::EventArgs& e);
			bool constructionPanel_Hidden(const CEGUI::EventArgs& e);
			bool objectDescList_SelectionChanged(const CEGUI::EventArgs& e);
			bool bodyList_SelectionChanged(const CEGUI::EventArgs& e);
			bool weaponList_SelectionChanged(const CEGUI::EventArgs& e);
			bool add_MouseClicked(const CEGUI::EventArgs& e);
			bool change_MouseClicked(const CEGUI::EventArgs& e);
			bool remove_MouseClicked(const CEGUI::EventArgs& e);
			bool close_MouseClicked(const CEGUI::EventArgs& e);

		public:

			ConstructionPanel()
				:	m_sceneManager(NULL),
					m_camera(NULL),
					m_viewport(NULL),
					m_bodyEnt(NULL),
					m_weaponEnt(NULL),
					m_bodyNode(NULL),
					m_weaponNode(NULL),
					m_constructionPanel(NULL),
					m_name(NULL),
					m_objectDescList(NULL),
					m_viewer(NULL),
					m_armourList(NULL),
					m_bodyList(NULL),
					m_engineList(NULL),
					m_explosiveList(NULL),
					m_powerReactorList(NULL),
					m_weaponList(NULL),
					m_add(NULL),
					m_rot(NULL),
					m_remove(NULL),
					m_close(NULL) { }

			void init();

			void changeVisible() {

				m_constructionPanel->setVisible(!m_constructionPanel->isVisible());
			}

			void setVisible(bool visible) {

				m_constructionPanel->setVisible(visible);
			}

	};
};

//------------------------------------------------------------------------------
