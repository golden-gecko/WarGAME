
//------------------------------------------------------------------------------

#include "Main.h"

#include "MusicPlayer.h"

//------------------------------------------------------------------------------

bool MusicPlayer::list_MouseDoubleClick(const CEGUI::EventArgs& e) {

	if (m_list->getSelectedCount())

		play();

	return true;
}

//------------------------------------------------------------------------------

void MusicPlayer::init() {

	// Find CEGUI controls.

	m_title = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("MusicPlayer/Title");

	m_list = (CEGUI::MultiColumnList*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("MusicPlayer/List");

	m_list->setSelectionMode(CEGUI::MultiColumnList::RowSingle);
	m_list->addColumn("Name", 0, 0.3f);

	// Scan for music files.

	searchForMusicFiles();
}

//------------------------------------------------------------------------------

void MusicPlayer::searchForMusicFiles() {

	// Clear play list.

	m_list->resetList();

	// Search for *.ogg and *.lnk files.

	WIN32_FIND_DATA wfd;

	HANDLE hFind = FindFirstFile("..\\music\\*.*", &wfd);

	if (hFind)

		do

			if (wfd.cFileName[strlen(wfd.cFileName) - 1] == 'g') {

				CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(wfd.cFileName);

				item->setSelectionBrushImage("TaharezLook", "ListboxSelectionBrush");

				m_list->addRow(item, 0);
			}

		while (FindNextFile(hFind, &wfd));

}

//------------------------------------------------------------------------------

void MusicPlayer::previous() {

}

//------------------------------------------------------------------------------

void MusicPlayer::play() {

	if (m_list->getSelectedCount()) {

		if (m_music)

			fslKillSound(m_music);

				MusicPlayer::getSingletonPtr()->getMusic() = fslLoadSound(
					("..\\music\\" + MusicPlayer::getSingletonPtr()->getList()->getFirstSelectedItem()->getText()).c_str());

				if (MusicPlayer::getSingletonPtr()->getMusic())

					MusicPlayer::getSingletonPtr()->getMusic()->Play();

				//CloseHandle(MusicPlayer::getSingletonPtr()->getThread());

				//return 0;

		/*m_hThread = CreateThread(
			NULL,
			0,
			ThreadFunc,
			NULL,
			0,
			NULL);*/

	}
}

//------------------------------------------------------------------------------

void MusicPlayer::next() {

}

//------------------------------------------------------------------------------
