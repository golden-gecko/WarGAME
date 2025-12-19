
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Console: public Ogre::Singleton<Console> {

		public:

			enum ConsoleMode {

				// Console is fully visible, we can type commands.
				CM_FULL		= 0x01,
				// Console is partially visible, only few last messages are shown.
				CM_MINI		= 0x02,
				// Console is not visible.
				CM_HIDDEN	= 0x04

			};

		private:

			ConsoleMode			m_mode;

			CEGUI::FrameWindow*	m_console;
			CEGUI::Listbox*		m_log;
			CEGUI::Editbox*		m_command;

			HANDLE				m_hFile;

			bool command_KeyDown(const CEGUI::EventArgs& e);

		public:

			Console(): m_mode(CM_MINI), m_console(NULL), m_log(NULL), m_command(NULL), m_hFile(NULL) { }

			~Console();

			void init();

			void write(const CEGUI::String& msg);

			void setMode(ConsoleMode mode);

			void changeMode();

	};

};

//------------------------------------------------------------------------------
