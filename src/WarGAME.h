
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN
#define NOMINMAX

#include <windows.h>

#include <string>
#include <list>
using namespace std;

//------------------------------------------------------------------------------
// CEGUI
//------------------------------------------------------------------------------

#include "CEGUI.h"

//------------------------------------------------------------------------------
// Ogre 3D
//------------------------------------------------------------------------------

#include "Ogre.h"
#include "OgreCEGUIRenderer.h"
#include "OgreEventListeners.h"
#include "OgreKeyEvent.h"
#include "OgreMouseEvent.h"

//------------------------------------------------------------------------------
// WarGAME
//------------------------------------------------------------------------------

namespace WarGAME {

	class ArmDesc;
	class ArmourDesc;
	class BodyDesc;
	class EngineDesc;
	class ExplosiveDesc;
	class PartDesc;
	class PartWithMeshDesc;
	class ReactorDesc;
	class ShieldDesc;
	class TeleporterDesc;
	class WeaponDesc;

	class Arm;
	class Armour;
	class Body;
	class Engine;
	class Explosive;
	class Part;
	class PartWithMesh;
	class Reactor;
	class Shield;
	class Teleporter;
	class Weapon;

	class Object;

	class ObjectOrder;

	class ObjectDesc;

	class Player;

};

using namespace WarGAME;

template <typename T> T* Ogre::Singleton<T>::ms_Singleton = NULL;

//------------------------------------------------------------------------------
