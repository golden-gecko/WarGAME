
//------------------------------------------------------------------------------
// Main.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#define NOMINMAX

#include <windows.h>
#include <math.h>

#include <vector>
#include <string>
#include <list>
#include <fstream>

using namespace std;

//------------------------------------------------------------------------------
// CEGUI
//------------------------------------------------------------------------------

#include "CEGUI.h"

//------------------------------------------------------------------------------
// FreeSL
//------------------------------------------------------------------------------

#include "FreeSL.h"

using namespace FreeSL;

//------------------------------------------------------------------------------
// Ogre 3D
//------------------------------------------------------------------------------

#include "Ogre.h"
#include "OgreCEGUIRenderer.h"
#include "OgreEventListeners.h"
#include "OgreKeyEvent.h"
#include "OgreMouseEvent.h"

using namespace Ogre;

//------------------------------------------------------------------------------
// TinyXml
//------------------------------------------------------------------------------

#include "tinyxml.h"

//------------------------------------------------------------------------------
// WarGAME
//------------------------------------------------------------------------------

namespace WarGAME {

	class ArmourDesc;
	class BodyDesc;
	class EngineDesc;
	class PartDesc;
	class PowerReactorDesc;
	class WeaponDesc;

	class Armour;
	class Body;
	class Engine;
	class Part;
	class PowerReactor;
	class Weapon;

	class ObjectDesc;

	class Building;
	class Fortification;
	class Object;
	class PowerPlant;
	class Vehicle;

};

using namespace WarGAME;

template <typename T> T* Singleton<T>::ms_Singleton = NULL;

//------------------------------------------------------------------------------
