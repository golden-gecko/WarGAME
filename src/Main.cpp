
//------------------------------------------------------------------------------
// Main.cpp
//------------------------------------------------------------------------------

#include "Main.h"

#include "Core.h"
#include "Gui.h"

#include "EventManager.h"
#include "ObjectManager.h"
#include "ObjectDescManager.h"
#include "PartDescManager.h"
#include "PlayerManager.h"
#include "SoundManager.h"

//------------------------------------------------------------------------------

Core	core;
Gui		gui;

EventManager		eventManager;
ObjectManager		objectManager;
ObjectDescManager	objectDescManager;
PartDescManager		partDescManager;
PlayerManager		playerManager;
SoundManager		soundManager;

//------------------------------------------------------------------------------

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int){

	if (core.init() && gui.init() && soundManager.init())

		core.run();

	return 0;

}

//------------------------------------------------------------------------------
