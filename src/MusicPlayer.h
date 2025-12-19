
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class MusicPlayer: public Singleton<MusicPlayer> {

		private:

			CEGUI::StaticText*		m_title;
			CEGUI::MultiColumnList*	m_list;
			HANDLE					m_hThread;
			FSLsound*				m_music;

			__forceinline static DWORD WINAPI ThreadFunc(LPVOID) {

				MusicPlayer::getSingletonPtr()->getMusic() = fslLoadSound(
					("..\\music\\" + MusicPlayer::getSingletonPtr()->getList()->getFirstSelectedItem()->getText()).c_str());

				if (MusicPlayer::getSingletonPtr()->getMusic())

					MusicPlayer::getSingletonPtr()->getMusic()->Play();

				CloseHandle(MusicPlayer::getSingletonPtr()->getThread());

				return 0;
			}

			__forceinline const CEGUI::MultiColumnList* getList() {

				return m_list;
			}

			__forceinline FSLsound*& getMusic() {

				return m_music;
			}

			__forceinline HANDLE getThread() {

				return m_hThread;
			}

			bool list_MouseDoubleClick(const CEGUI::EventArgs& e);

		public:

			MusicPlayer(): m_title(NULL), m_list(NULL), m_hThread(NULL), m_music(NULL) { }

			~MusicPlayer() {

				if (m_music)

					fslKillSound(m_music);

				if (m_hThread)

					CloseHandle(m_hThread);

			}

			void init();

			void searchForMusicFiles();

			void previous();

			void pause() {

				if (m_music)

					m_music->Pause();

			}

			void play();

			void stop() {

				if (m_music)

					m_music->Stop();

			}

			void next();

	};

};

//------------------------------------------------------------------------------
