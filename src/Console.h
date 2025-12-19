
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Console: public Singleton<Console> {

		private:

			CEGUI::FrameWindow*	m_console;
			CEGUI::Listbox*		m_log;
			CEGUI::Editbox*		m_command;

			HANDLE				m_hFile;

		public:

			Console(): m_console(NULL), m_log(NULL), m_command(NULL), m_hFile(NULL) { }

			~Console();

			void init();

			void write(const CEGUI::String& msg);

			void enter();

			void setVisible(bool visible);

			void changeVisible();

	};

};

//------------------------------------------------------------------------------
