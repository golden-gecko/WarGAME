
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Game.h"

//------------------------------------------------------------------------------

bool Game::load(string fileName) {

	FILE* file = fopen((SAVE_FOLDER_NAME + fileName).c_str(), "rb");

	if (file == NULL)

		return false;

	fclose(file);

	return true;
}

//------------------------------------------------------------------------------

bool Game::save(string fileName, SaveMode saveMode) {

	FILE* file = fopen((SAVE_FOLDER_NAME + fileName).c_str(), "wb");

	if (file == NULL)

		return false;

	fwrite(&saveMode, sizeof(SaveMode), 1, file);

	switch (saveMode) {

		case SM_QUICK:

			break;

		case SM_FULL:

			break;

	}

	fclose(file);

	return true;
}

//------------------------------------------------------------------------------

bool Game::quickSave() {

	return save(QUICK_SAVE_FILE_NAME);
}

//------------------------------------------------------------------------------

bool Game::quickLoad() {

	return load(QUICK_SAVE_FILE_NAME);
}

//------------------------------------------------------------------------------
