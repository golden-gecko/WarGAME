
//------------------------------------------------------------------------------
// Gui.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------
// Gui
//------------------------------------------------------------------------------

namespace WarGAME {

	class Gui : public Singleton<Gui> {

//------------------------------------------------------------------------------

		public:

			CEGUI::OgreCEGUIRenderer*	m_renderer;
			CEGUI::System*				m_system;

		public:

			Gui() : m_renderer(NULL), m_system(NULL), m_mouseOverGui(false) { }

			~Gui() {

				if (m_system)	delete m_system;
				if (m_renderer)	delete m_renderer;
			}

			bool init();

			CEGUI::OgreCEGUIRenderer*	getRenderer()	{ return m_renderer;	}
			CEGUI::System*				getSystem()		{ return m_system;		}

//------------------------------------------------------------------------------

		private:

			bool m_mouseOverGui;

		public:

			bool isMouseOverGui() {

				return m_mouseOverGui;
			}

//------------------------------------------------------------------------------

		public:

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
			CEGUI::MultiColumnList*		m_objectMultiList;
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

			bool objectDescList_MouseDoubleClick(const CEGUI::EventArgs& e);

			bool objectInfoText_MouseDoubleClick(const CEGUI::EventArgs& e);

		public:

			void setVisible(bool visible) {

				m_system->getGUISheet()->setVisible(visible);
			}

			void setViewerVisible(bool visible);
			void setObjectViewerVisible(bool visible);
			void setObjectDescViewerVisible(bool visible);
//			void setPartViewerVisible(bool visible);
			void setPartDescViewerVisible(bool visible);

			void changeViewerVisible();
			void changeObjectViewerVisible();
			void changeObjectDescViewerVisible();
			void changePartViewerVisible();
			void changePartDescViewerVisible();

			void updateViewer();
			void updateObjectViewer();
			void updateObjectDescViewer();
//			void updatePartViewer();
			void updatePartDescViewer();

			void updateGameInfo();
			void updateObjectInfo(ObjectTemp* object);

			ObjectDesc* getSelectedObjectDesc();

//------------------------------------------------------------------------------

	};

};

//------------------------------------------------------------------------------
