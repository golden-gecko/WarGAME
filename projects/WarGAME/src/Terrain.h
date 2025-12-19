#pragma once

#include "Dependencies.h"

class Terrain : public Ogre::Singleton<Terrain>
{
public:
	void init(Ogre::SceneManager* scene, Ogre::RaySceneQuery* query);
	void load(const std::string& name);
	void unload();

	float getHeight(float x, float z)
	{
		return getHeight(Ogre::Vector3(x, 0.0f, z));
	}

	float getHeight(float x, float y, float z)
	{
		return getHeight(Ogre::Vector3(x, y, z));
	}

	float getHeight(const Ogre::Vector3& position)
	{
		mQuery->setRay(Ogre::Ray(Ogre::Vector3(position.x, 1000.0f, position.z), Ogre::Vector3::NEGATIVE_UNIT_Y));

		if (mQuery->execute().size())
		{
			const Ogre::RaySceneQueryResult& result = mQuery->getLastResults();

			for (Ogre::RaySceneQueryResult::const_iterator i = result.begin(); i != result.end(); i++)
			{
				if (i->worldFragment)
				{
					return i->worldFragment->singleIntersection.y;
				}
			}
		}

		return 0.0f;
	}

	float getHeight(const Ogre::Ray& ray)
	{
		mQuery->setRay(ray);

		if (mQuery->execute().size())
		{
			const Ogre::RaySceneQueryResult& result = mQuery->getLastResults();

			for (Ogre::RaySceneQueryResult::const_iterator i = result.begin(); i != result.end(); i++)
			{
				if (i->worldFragment)
				{
					return i->worldFragment->singleIntersection.y;
				}
			}
		}

		return 0.0f;
	}

	Ogre::Vector3 getPosition(float x, float z)
	{
		return getPosition(Ogre::Vector3(x, 0.0f, z));
	}

	Ogre::Vector3 getPosition(float x, float y, float z)
	{
		return getPosition(Ogre::Vector3(x, y, z));
	}

	Ogre::Vector3 getPosition(const Ogre::Vector3& position)
	{
		mQuery->setRay(Ogre::Ray(Ogre::Vector3(position.x, 1000.0f, position.z), Ogre::Vector3::NEGATIVE_UNIT_Y));

		if (mQuery->execute().size())
		{
			const Ogre::RaySceneQueryResult& result = mQuery->getLastResults();

			for (Ogre::RaySceneQueryResult::const_iterator i = result.begin(); i != result.end(); i++)
			{
				if (i->worldFragment)
				{
					return i->worldFragment->singleIntersection;
				}
			}
		}

		return Ogre::Vector3(position.x, 0.0f, position.z);
	}

	Ogre::Vector3 getPosition(const Ogre::Ray& ray)
	{
		mQuery->setRay(ray);

		if (mQuery->execute().size())
		{
			const Ogre::RaySceneQueryResult& result = mQuery->getLastResults();

			for (Ogre::RaySceneQueryResult::const_iterator i = result.begin(); i != result.end(); i++)
			{
				if (i->worldFragment)
				{
					return i->worldFragment->singleIntersection;
				}
			}
		}

		return Ogre::Vector3(ray.getOrigin().x, 0.0f, ray.getOrigin().z);
	}

	Ogre::Vector3 getRandomPosition(const Ogre::Vector3& position, float range)
	{
		return getPosition(
			position.x + Ogre::Math::SymmetricRandom() * range,
			position.z + Ogre::Math::SymmetricRandom() * range);
	}

	const std::string& getName() const
	{
		return mName;
	}
protected:
	std::string				mName;
	Ogre::SceneManager*		mScene;
	Ogre::RaySceneQuery*	mQuery;
	Ogre::MaterialPtr		mMaterial;
	Ogre::TexturePtr		mDamage;
	Ogre::TexturePtr		mFootsteps;
};
