
//------------------------------------------------------------------------------
// Gui.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

//------------------------------------------------------------------------------
// Gui
//------------------------------------------------------------------------------

namespace WarGAME {

	class Gui : public Singleton<Gui> {

//------------------------------------------------------------------------------

		private:

			CEGUI::OgreCEGUIRenderer*	m_renderer;
			CEGUI::System*				m_system;

		public:

			Gui()

				:	m_renderer(NULL),
					m_system(NULL),
					m_mouseOverGui(false) { }

			~Gui(){

				if (m_system)	delete m_system;
				if (m_renderer)	delete m_renderer;

			}

			bool init();

//------------------------------------------------------------------------------

		private:

			bool m_mouseOverGui;

		public:

			bool isMouseOverGui(){

				return m_mouseOverGui;

			}

//------------------------------------------------------------------------------

		private:

			CEGUI::FrameWindow*			m_viewer;
			CEGUI::Listbox*				m_type;
			CEGUI::Listbox*				m_list;
			CEGUI::StaticText*			m_text;

			CEGUI::FrameWindow*			m_gameInfo;
			CEGUI::StaticText*			m_gameInfoText;

			CEGUI::FrameWindow*			m_objectInfo;
			CEGUI::StaticText*			m_objectInfoText;
			CEGUI::Listbox*				m_objectInfoOrderList;

			CEGUI::FrameWindow*			m_objectViewer;
			CEGUI::Listbox*				m_objectList;
			CEGUI::StaticText*			m_objectText;

			CEGUI::FrameWindow*			m_objectDescViewer;
			CEGUI::Listbox*				m_objectDescList;
			CEGUI::StaticText*			m_objectDescText;

			CEGUI::FrameWindow*			m_partDescViewer;
			CEGUI::Listbox*				m_partDescList;
			CEGUI::StaticText*			m_partDescText;

			bool mouseEntersLeaves(const CEGUI::EventArgs& e);

			bool list_SelectionChanged(const CEGUI::EventArgs& e);
			bool type_SelectionChanged(const CEGUI::EventArgs& e);

			bool objectList_SelectionChanged(const CEGUI::EventArgs& e);
			bool objectDescList_SelectionChanged(const CEGUI::EventArgs& e);
			bool partDescList_SelectionChanged(const CEGUI::EventArgs& e);

		public:

			void setObjectViewerVisible(bool visible);
			void setObjectDescViewerVisible(bool visible);
			void setPartDescViewerVisible(bool visible);

			void changeObjectViewerVisible();
			void changeObjectDescViewerVisible();
			void changePartDescViewerVisible();

			void updateGameInfo();
			void updateObjectInfo(Object* object);
			void updateViewer();

//------------------------------------------------------------------------------

	};

};

//------------------------------------------------------------------------------
