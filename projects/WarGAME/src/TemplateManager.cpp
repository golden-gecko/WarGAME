#include "Dependencies.h"
#include "ConfigFile.h"
#include "Debug.h"
#include "TemplateManager.h"

TemplateManager* Ogre::Singleton<TemplateManager>::ms_Singleton = NULL;

bool TemplateManager::init()
{
	// Load creatures.
	{
		ConfigFile config("..\\objects\\creatures.txt");

		Ogre::ConfigFile::SectionIterator sections = config.getSectionIterator();

		// Skip first empty section.
		if (sections.hasMoreElements())
		{
			sections.moveNext();
		}

		while (sections.hasMoreElements())
		{
			// Create template.
			CreatureTemplate* creature = new CreatureTemplate();

			// Read parameters.
			creature->name = sections.peekNextKey();
			creature->description = config.getString("Description", creature->name, "Unknown");
			creature->mesh = config.getString("Mesh", creature->name, "Unknown.mesh");
			creature->maxEnergy = config.getFloat("MaxEnergy", creature->name, "10.0");
			creature->maxHealth = config.getFloat("MaxHealth", creature->name, "100.0");
			creature->maxSlope = config.getFloat("MaxSlope", creature->name, "40.0");
			creature->maxWaterDepth = config.getFloat("MaxWaterDepth", creature->name, "0.25");
			creature->scale = config.getFloat("Scale", creature->name, "1.0");
			creature->species = config.getString("Species", creature->name, "Unknown");
			creature->speed = config.getFloat("Speed", creature->name, "1.0");

			// Add template to list.
			mTemplates.insert(std::make_pair(creature->name, creature));

			// Move to next template.
			sections.moveNext();
		}
	}

	// Load plants.
	{
		ConfigFile config("..\\objects\\plants.txt");

		Ogre::ConfigFile::SectionIterator sections = config.getSectionIterator();

		// Skip first empty section.
		if (sections.hasMoreElements())
		{
			sections.moveNext();
		}

		while (sections.hasMoreElements())
		{
			// Create template.
			PlantTemplate* plant = new PlantTemplate();

			// Read parameters.
			plant->name = sections.peekNextKey();
			plant->description = config.getString("Description", plant->name, "Unknown");
			plant->hideFactor = config.getFloat("HideFactor", plant->name, "0.7");
			plant->mesh = config.getString("Mesh", plant->name, "Unknown.mesh");
			plant->maxSlope = config.getFloat("MaxSlope", plant->name, "40");
			plant->maxWaterDepth = config.getFloat("MaxWaterDepth", plant->name, "0.5");
			plant->scale = config.getFloat("Scale", plant->name, "1.0");
			plant->species = config.getString("Species", plant->name, "Unknown");

			// Add template to list.
			mTemplates.insert(std::make_pair(plant->name, plant));

			// Move to next template.
			sections.moveNext();
		}
	}

	// Load resources.
	{
		ConfigFile config("..\\objects\\resources.txt");

		Ogre::ConfigFile::SectionIterator sections = config.getSectionIterator();

		// Skip first empty section.
		if (sections.hasMoreElements())
		{
			sections.moveNext();
		}

		while (sections.hasMoreElements())
		{
			// Create template.
			ResourceTemplate* resource = new ResourceTemplate();

			// Read parameters.
			resource->name = sections.peekNextKey();
			resource->description = config.getString("Description", resource->name, "Unknown");
			resource->mesh = config.getString("Mesh", resource->name, "Unknown.mesh");
			resource->maxSlope = config.getFloat("MaxSlope", resource->name, "40");
			resource->maxWaterDepth = config.getFloat("MaxWaterDepth", resource->name, "0.5");
			resource->scale = config.getFloat("Scale", resource->name, "1.0");

			// Add template to list.
			mTemplates.insert(std::make_pair(resource->name, resource));

			// Move to next template.
			sections.moveNext();
		}
	}

	// Load structures.
	{
		ConfigFile config("..\\objects\\structures.txt");

		Ogre::ConfigFile::SectionIterator sections = config.getSectionIterator();

		// Skip first empty section.
		if (sections.hasMoreElements())
		{
			sections.moveNext();
		}

		while (sections.hasMoreElements())
		{
			std::string type = config.getString("Type", sections.peekNextKey());

			StructureTemplate* structure = NULL;

			if (type == "Factory")
			{
				// Create template.
				FactoryTemplate* factory = new FactoryTemplate();
				structure = factory;

				// Read parameters.
			}
			else if (type == "Fortification")
			{
				// Create template.
				FortificationTemplate* fortification = new FortificationTemplate();
				structure = fortification;

				// Read parameters.
			}
			else if (type == "Laboratory")
			{
				// Create template.
				LaboratoryTemplate* laboratory = new LaboratoryTemplate();
				structure = laboratory;

				// Read parameters.
			}
			else if (type == "Mine")
			{
				// Create template.
				MineTemplate* mine = new MineTemplate();
				structure = mine;

				// Read parameters.
				mine->produce["Energy"] = config.getFloat("Produce.Energy", sections.peekNextKey(), "0.0");
				mine->produce["Metal"] = config.getFloat("Produce.Metal", sections.peekNextKey(), "0.0");
			}
			else if (type == "Radar")
			{
				// Create template.
				RadarTemplate* radar = new RadarTemplate();
				structure = radar;

				// Read parameters.
			}
			else if (type == "Turret")
			{
				// Create template.
				TurretTemplate* turret = new TurretTemplate();
				structure = turret;

				// Read parameters.
				turret->weaponDamage = config.getFloat("Weapon.Damage", sections.peekNextKey(), "15.0");
				turret->weaponDamageRadius = config.getFloat("Weapon.Radius", sections.peekNextKey(), "5.0");
				turret->weaponRange = config.getFloat("Weapon.Range", sections.peekNextKey(), "300.0");
				turret->weaponRechargeTime = config.getFloat("Weapon.Recharge", sections.peekNextKey(), "1.0");
			}

			if (structure)
			{
				// Read parameters.
				structure->name = sections.peekNextKey();
				structure->cost["Energy"] = config.getFloat("Cost.Energy", structure->name, "100.0");
				structure->cost["Metal"] = config.getFloat("Cost.Metal", structure->name, "25.0");
				structure->description = config.getString("Description", structure->name, "Unknown");
				structure->maxHealth = config.getFloat("MaxHealth", structure->name, "100.0");
				structure->mesh = config.getString("Mesh", structure->name, "Unknown.mesh");
				structure->maxSlope = config.getFloat("MaxSlope", structure->name, "40");
				structure->maxWaterDepth = config.getFloat("MaxWaterDepth", structure->name, "0.5");
				structure->scale = config.getFloat("Scale", structure->name, "1.0");
				structure->sightDistance = config.getFloat("SightDistance", structure->name, "100.0");
				structure->use["Energy"] = config.getFloat("Use.Energy", structure->name, "0.0");
				structure->use["Metal"] = config.getFloat("Use.Metal", structure->name, "0.0");

				// Add template to list.
				mTemplates.insert(std::make_pair(structure->name, structure));
			}

			// Move to next template.
			sections.moveNext();
		}
	}

	// Load vehicles.
	{
		ConfigFile config("..\\objects\\vehicles.txt");

		Ogre::ConfigFile::SectionIterator sections = config.getSectionIterator();

		// Skip first empty section.
		if (sections.hasMoreElements())
		{
			sections.moveNext();
		}

		while (sections.hasMoreElements())
		{
			// Create template.
			VehicleTemplate* vehicle = new VehicleTemplate();

			// Read parameters.
			vehicle->name = sections.peekNextKey();
			vehicle->cost["Energy"] = config.getFloat("Cost.Energy", vehicle->name, "100.0");
			vehicle->cost["Metal"] = config.getFloat("Cost.Metal", vehicle->name, "20.0");
			vehicle->description = config.getString("Description", vehicle->name, "Unknown");
			vehicle->mesh = config.getString("Mesh", vehicle->name, "Unknown.mesh");
			vehicle->maxHealth = config.getFloat("MaxHealth", vehicle->name, "100.0");
			vehicle->maxSlope = config.getFloat("MaxSlope", vehicle->name, "40");
			vehicle->maxWaterDepth = config.getFloat("MaxWaterDepth", vehicle->name, "0.5");
			vehicle->scale = config.getFloat("Scale", vehicle->name, "1.0");
			vehicle->sightDistance = config.getFloat("SightDistance", vehicle->name, "250.0");
			vehicle->speed = config.getFloat("Speed", vehicle->name, "3.0");
			vehicle->weaponDamage = config.getFloat("Weapon.Damage", vehicle->name, "15.0");
			vehicle->weaponDamageRadius = config.getFloat("Weapon.Radius", vehicle->name, "5.0");
			vehicle->weaponRange = config.getFloat("Weapon.Range", vehicle->name, "300.0");
			vehicle->weaponRechargeTime = config.getFloat("Weapon.Recharge", vehicle->name, "1.0");

			// Add template to list.
			mTemplates.insert(std::make_pair(vehicle->name, vehicle));

			// Move to next template.
			sections.moveNext();
		}
	}

	// Load meshes.
	for (TemplateMap::const_iterator i = mTemplates.begin(); i != mTemplates.end(); ++i)
	{
		Ogre::MeshManager::getSingleton().load(i->second->mesh, "General");
	}

	return true;
}

void TemplateManager::shutdown()
{
	for (TemplateMap::const_iterator i = mTemplates.begin(); i != mTemplates.end(); ++i)
	{
		delete i->second;
	}

	mTemplates.clear();
}

ObjectTemplate* TemplateManager::get(const std::string& name) const
{
	TemplateMap::const_iterator i = mTemplates.find(name);

	if (i != mTemplates.end())
	{
		return i->second;
	}

	return NULL;
}

void TemplateManager::destroy(const std::string& name)
{
	ASSERT(name.length() > 0);

	TemplateMap::iterator i = mTemplates.find(name);

	if (i != mTemplates.end())
	{
		delete i->second;

		mTemplates.erase(i);
	}
}

void TemplateManager::destroyAll()
{
	for (TemplateMap::const_iterator i = mTemplates.begin(); i != mTemplates.end(); ++i)
	{
		delete i->second;
	}

	mTemplates.clear();
}
