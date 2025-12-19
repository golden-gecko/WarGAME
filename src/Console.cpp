
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Console.h"

//------------------------------------------------------------------------------

void Console::init() {

	m_console = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("console");
	m_log = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("console/log");
	m_command = (CEGUI::Editbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("console/command");

	m_console->setCaptionColour(CEGUI::colour(1.0f, 1.0f, 1.0f));

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

Console::~Console() {

	if (m_hFile)

		CloseHandle(m_hFile);
}

//------------------------------------------------------------------------------

void Console::write(const CEGUI::String& msg) {

	CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(msg);

	item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");

	m_log->addItem(item);
	m_log->ensureItemIsVisible(item);

	if (m_hFile) {

		DWORD bytes = 0;

		WriteFile(m_hFile, msg.c_str(), msg.length(), &bytes, NULL);
		WriteFile(m_hFile, "\r\n", 2, &bytes, NULL);
	}
}

//------------------------------------------------------------------------------

void Console::enter() {

	if (m_command->isActive()) {

		write(m_command->getText());

		m_command->setText("");
	}
}

//------------------------------------------------------------------------------

void Console::setVisible(bool visible) {

	m_console->setVisible(visible);

	if (visible)

		m_command->activate();
}

//------------------------------------------------------------------------------

void Console::changeVisible() {

	setVisible(!m_console->isVisible());
}

//------------------------------------------------------------------------------
