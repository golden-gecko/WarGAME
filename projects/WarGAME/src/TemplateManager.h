#pragma once

#include "Dependencies.h"
#include "Object.h"

#pragma pack(1)

/// Base for all objects in game.
struct ObjectTemplate
{
	std::string		description;
	float			maxHealth;
	float			maxSlope;
	float			maxWaterDepth;
	std::string		mesh;
	std::string		name;
	float			scale;
	unsigned int	type;

	ObjectTemplate(unsigned type) : type(type)
	{
	}

	virtual std::string toString() const
	{
		return
			"\nName: " + name +
			"\nDescription: " + description;
	}
};

struct CreatureTemplate : public ObjectTemplate
{
	float			damage;
	float			energyRestore;
	float			healthRestore;
	float			maxEnergy;
	float			maxExperience;
	unsigned int	maxLevel;
	float			sightDistance;
	std::string		species;
	float			speed;

	CreatureTemplate() : ObjectTemplate(OT_CREATURE)
	{
	}
};

/// Required by structures and units.
struct ResourceTemplate : public ObjectTemplate
{
	float radius;

	std::map<std::string, float> maximal;
	std::map<std::string, float> produce;

	ResourceTemplate() : ObjectTemplate(OT_RESOURCE)
	{
	}
};

/// Plants can hide units.
struct PlantTemplate : public ObjectTemplate
{
	float		hideFactor;
	std::string	species;

	PlantTemplate() : ObjectTemplate(OT_PLANT)
	{
	}
};

/// Base for all structures and vehicles.
/// Units can "think" and execute orders.
struct UnitTemplate : public ObjectTemplate
{
	std::map<std::string, float>	cost;
	float							sightDistance;

	UnitTemplate(unsigned int type) : ObjectTemplate(type)
	{
	}

	std::string toString() const
	{
		std::string s =
			"\nSight Distance: " + Ogre::StringConverter::toString(sightDistance) +
			"\nMax Slope: " + Ogre::StringConverter::toString(maxSlope) +
			"\nCost";

		for (std::map<std::string, float>::const_iterator i = cost.begin();
			i != cost.end(); ++i)
		{
			s += "\n   " + i->first + ": " + Ogre::StringConverter::toString(
				i->second, 2, 0, 32, std::ios_base::fixed);
		}

		return ObjectTemplate::toString() + s;
	}
};

/// Base for all structures.
struct StructureTemplate : public UnitTemplate
{
	std::map<std::string, float> use;

	StructureTemplate(unsigned int type) : UnitTemplate(type)
	{
	}

	std::string toString() const
	{
		std::string s = "\nUse";

		for (std::map<std::string, float>::const_iterator i = use.begin();
			i != use.end(); ++i)
		{
			s += "\n   " + i->first + ": " + Ogre::StringConverter::toString(
				i->second, 2, 0, 32, std::ios_base::fixed);
		}

		return UnitTemplate::toString() + s;
	}
};

/// Moves around map and shoots at enemy.
struct VehicleTemplate : public UnitTemplate
{
	float acceleration;
	float brakeRate;
	float speed;
	float weaponDamage;
	float weaponDamageRadius;
	float weaponRange;
	float weaponRechargeTime;

	VehicleTemplate() : UnitTemplate(OT_VEHICLE)
	{
	}

	std::string toString() const
	{
		return UnitTemplate::toString() +
			"\nDamage: " + Ogre::StringConverter::toString(weaponDamage) +
			"\nMove Speed: " + Ogre::StringConverter::toString(speed) +
			"\nWeapon Range: " + Ogre::StringConverter::toString(weaponRange) +
			"\nWeapon Time: " + Ogre::StringConverter::toString(weaponRechargeTime);
	}
};

/// Constructs and repairs units.
struct FactoryTemplate : public StructureTemplate
{
	std::map<std::string, float>	use;
	std::vector<std::string>		vehicles;

	FactoryTemplate() : StructureTemplate(OT_FACTORY)
	{
	}
};

/// Defends base.
struct FortificationTemplate : public StructureTemplate
{
	float maxDefence;

	FortificationTemplate() : StructureTemplate(OT_FORTIFICATION)
	{
	}
};

/// Produces or exchange resources.
struct MineTemplate : public StructureTemplate
{
	std::map<std::string, float> produce;

	MineTemplate() : StructureTemplate(OT_MINE)
	{
	}

	std::string toString() const
	{
		std::string s = "\nProduce";

		for (std::map<std::string, float>::const_iterator i = produce.begin();
			i != produce.end(); ++i)
		{
			s += "\n   " + i->first + ": " + Ogre::StringConverter::toString(
				i->second, 2, 0, 32, std::ios_base::fixed);
		}

		return StructureTemplate::toString() + s;
	}
};

/// Gives access to new structures and units.
struct LaboratoryTemplate : public StructureTemplate
{
	std::vector<std::string> technologies;

	LaboratoryTemplate() : StructureTemplate(OT_LABORATORY)
	{
	}
};

/// Reveals distant units positions.
struct RadarTemplate : public StructureTemplate
{
	float maxRadarRange;

	RadarTemplate() : StructureTemplate(OT_RADAR)
	{
	}
};

/// Defends base and shoots at enemy.
struct TurretTemplate : public StructureTemplate
{
	float weaponDamage;
	float weaponDamageRadius;
	float weaponRange;
	float weaponRechargeTime;

	TurretTemplate() : StructureTemplate(OT_TURRET)
	{
	}
};

#pragma pack(4)

typedef std::map<std::string, ObjectTemplate*> TemplateMap;

/// Manages object templates.
class TemplateManager : public Ogre::Singleton<TemplateManager>
{
public:
	bool init();
	void shutdown();

	const TemplateMap& get() const
	{
		return mTemplates;
	}

	ObjectTemplate* get(const std::string& name) const;

	void destroy(const std::string& name);
	void destroyAll();
protected:
	TemplateMap mTemplates;
};
