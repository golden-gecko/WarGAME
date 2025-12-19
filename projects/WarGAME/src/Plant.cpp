#include "Dependencies.h"
#include "ObjectManager.h"
#include "Plant.h"

Plant::Plant(unsigned int id, const std::string& mesh) : Object(id, OT_PLANT, mesh)
{
}

void Plant::update(float time)
{
}

void Plant::onCreate(unsigned int creator)
{
//	const ObjectVector& objects = ObjectManager::getSingleton().get(OT_UNIT, radius);

//	for each (std::pair<Object*> object in objects)
	{

	}
}

void Plant::onDestroy(unsigned int destroyer)
{
}
