#include "PCH.hpp"

#include "Grid.hpp"

namespace Debug
{
	void Grid::load()
	{
		unload();

		manualObject = scene->createManualObject(name);
		manualObject->setCastShadows(false);
		manualObject->setUserAny(Ogre::Any(this));

        manualObject->begin("Debug", Ogre::RenderOperation::OT_LINE_STRIP);
    
        const int size = 101;

        for (int z = 0; z < size; ++z)
        {
            for (int x = 0; x < size; ++x)
            {
                manualObject->position(0.0f, 0.0f, 0.0f);
		        manualObject->position(0.0f, 0.0f, z);
		        manualObject->position(x, 0.0f, z);
		        manualObject->position(x, 0.0f, 0.0f);

                manualObject->index((z * size + x) * 4 + 0);
                manualObject->index((z * size + x) * 4 + 1);

                manualObject->index((z * size + x) * 4 + 1);
                manualObject->index((z * size + x) * 4 + 2);

                manualObject->index((z * size + x) * 4 + 2);
                manualObject->index((z * size + x) * 4 + 3);

                manualObject->index((z * size + x) * 4 + 3);
                manualObject->index((z * size + x) * 4 + 0);
            }
        }

		manualObject->end();
        manualObject->convertToMesh(name);

        entity = scene->createEntity(name, name);
        entity->setUserAny(Ogre::Any(this));

		sceneNode = scene->createSceneNode(name);
		sceneNode->setPosition(Ogre::Vector3::ZERO);
		sceneNode->setScale(Ogre::Vector3::UNIT_SCALE * 1.0f);
		sceneNode->attachObject(entity);
		sceneNode->setUserAny(Ogre::Any(this));
	}

	void Grid::unload()
	{
		if (manualObject)
		{
			scene->destroyManualObject(manualObject);
		}
    
        if (entity)
		{
			scene->destroyEntity(entity);
		}

		if (sceneNode)
		{
			scene->destroySceneNode(sceneNode);
		}

		manualObject = NULL;
        entity = NULL;
		sceneNode = NULL;
	}
}
