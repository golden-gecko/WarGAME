
//------------------------------------------------------------------------------
// Main.cpp
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "EventManager.h"
#include "Game.h"
#include "Gui.h"
#include "ObjectManagerTemp.h"
#include "ObjectDescManagerTemp.h"
#include "PartDescManagerT.h"
#include "PlayerManager.h"
#include "SoundManagerTemp.h"

//------------------------------------------------------------------------------

Core					core;
//EventManager			eventManager;
Game					game;
Gui						gui;
ObjectManagerTemp		objectManager;
ObjectDescManagerTemp	objectDescManager;
PartDescManagerTemp			partDescManager;
PlayerManager			playerManager;
//SoundManagerTemp		soundManager;

//------------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	if (core.init() && gui.init() /*&& soundManager.init()*/)

		core.run();

	return 0;
}

//------------------------------------------------------------------------------
