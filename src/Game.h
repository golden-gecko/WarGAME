
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	static const char QUICK_SAVE_FILE_NAME	[] = "QuickSave.WarGAME";
	static const char SAVE_FOLDER_NAME		[] = "\\..\\save\\";

	class Game: public Ogre::Singleton<Game> {

		public:

			enum SaveMode {

				SM_QUICK	= 0x01,
				SM_FULL		= 0x02

			};

		public:

			bool load(string fileName);

			bool save(string fileName, SaveMode saveMode = SM_QUICK);

			bool quickSave();

			bool quickLoad();

	};
};

//------------------------------------------------------------------------------
