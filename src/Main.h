
//------------------------------------------------------------------------------
// Main.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#define STRICT
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
	class EnergyShieldDesc;
	class EngineDesc;
	class PartDesc;
	class PowerReactorDesc;
	class TeleporterDesc;
	class WeaponDesc;

	class Armour;
	class Body;
	class Shield;
	class Engine;
	class Part;
	class Reactor;
	class Teleporter;
	class Weapon;

	class BuildingDesc;
	class FortificationDesc;
	class ObjectDesc;
	class PowerPlantDesc;
	class VehicleDesc;

	class Building;
	class Fortification;
	class Object;
	class Missile;
	class PowerPlant;
	class Vehicle;

};

using namespace WarGAME;

template <typename T> T* Singleton<T>::ms_Singleton = NULL;

//------------------------------------------------------------------------------
