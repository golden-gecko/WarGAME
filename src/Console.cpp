
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Console.h"

//------------------------------------------------------------------------------

bool Console::command_KeyDown(const CEGUI::EventArgs& e) {

	const CEGUI::KeyEventArgs& m = static_cast<const CEGUI::KeyEventArgs&>(e);

	switch (m.scancode) {

		 case CEGUI::Key::Return:

			write(m_command->getText());

			m_command->setText("");

			break;

	}

	return true;
}

//------------------------------------------------------------------------------

Console::~Console() {

	if (m_hFile)

		CloseHandle(m_hFile);
}

//------------------------------------------------------------------------------

void Console::init() {

	m_console = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Console");
	m_log = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Console/Log");
	m_command = (CEGUI::Editbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("Console/Command");

	m_console->setCaptionColour(CEGUI::colour(1.0f, 1.0f, 1.0f));

	m_command->subscribeEvent(
		CEGUI::Editbox::EventKeyDown,
		CEGUI::Event::Subscriber(&Console::command_KeyDown, this));

	m_hFile = CreateFile(
		"WarGAME.log",
		GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (m_hFile == INVALID_HANDLE_VALUE)

		m_hFile = NULL;
}

//------------------------------------------------------------------------------

void Console::write(const CEGUI::String& msg) {

	CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(msg);

	item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");

	m_log->addItem(item);
	m_log->ensureItemIsVisible(item);

	if (m_hFile) {

		DWORD bytes = 0;

		WriteFile(m_hFile, msg.c_str(), (DWORD)msg.length(), &bytes, NULL);
		WriteFile(m_hFile, "\r\n", 2, &bytes, NULL);
	}
}

//------------------------------------------------------------------------------

void Console::setMode(ConsoleMode mode) {

	m_mode = mode;

	switch (m_mode) {

		case CM_FULL:	

			m_console->setVisible(true);
			m_command->activate();

			break;

		case CM_MINI:	

			break;

		case CM_HIDDEN:

			m_console->setVisible(false);

			break;
	}
}

//------------------------------------------------------------------------------

void Console::changeMode() {

	switch (m_mode) {

		case CM_FULL:	setMode(CM_MINI);	break;
		case CM_MINI:	setMode(CM_HIDDEN);	break;
		case CM_HIDDEN:	setMode(CM_FULL);	break;
	}
}

//------------------------------------------------------------------------------
