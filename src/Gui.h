
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Gui : public Ogre::Singleton<Gui> {

//------------------------------------------------------------------------------

		private:

			CEGUI::OgreCEGUIRenderer*	m_renderer;
			CEGUI::System*				m_system;

			bool mouseEnters(const CEGUI::EventArgs& e);
			bool mouseLeaves(const CEGUI::EventArgs& e);

		public:

			Gui() : m_renderer(NULL), m_system(NULL), m_mouseOverGui(false) { }

			~Gui() {

				if (m_system)	delete m_system;
				if (m_renderer)	delete m_renderer;
			}


			CEGUI::OgreCEGUIRenderer* getRenderer() {
				
				return m_renderer;
			}
			CEGUI::System* getSystem() {
				
				return m_system;
			}

			bool init();

//------------------------------------------------------------------------------

		private:

			bool m_mouseOverGui;

		public:

			bool isMouseOverGui() {

				return m_mouseOverGui;
			}

	};

};

//------------------------------------------------------------------------------
