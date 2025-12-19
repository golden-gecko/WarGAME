
//------------------------------------------------------------------------------
// Main.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "BattleFieldCamera.h"
#include "ConstructionPanel.h"
#include "Core.h"
#include "Game.h"
#include "Gui.h"
#include "ObjectManager.h"
#include "ObjectDescManager.h"
#include "PartDescManager.h"
#include "PlayerManager.h"
#include "SoundManager.h"

//------------------------------------------------------------------------------

BattleFieldCamera	battleFieldCamera;
ConstructionPanel	constructionPanel;
Core				core;
Game				game;
Gui					gui;
ObjectManager		objectManager;
ObjectDescManager	objectDescManager;
PartDescManager		partDescManager;
PlayerManager		playerManager;
SoundManager		soundManager;

//------------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//if ( &&  /*&& soundManager.init()*/) {

		core.init();
		gui.init();
		battleFieldCamera.init();
		constructionPanel.init();
		objectManager.init();

		core.run();
	//}

	return 0;
}

//------------------------------------------------------------------------------
