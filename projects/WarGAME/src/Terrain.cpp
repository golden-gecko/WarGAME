#include "Dependencies.h"
#include "Terrain.h"

Terrain* Ogre::Singleton<Terrain>::ms_Singleton = NULL;

void Terrain::init(Ogre::SceneManager* scene, Ogre::RaySceneQuery* query)
{
	mScene = scene;
	mQuery = query;
}

void Terrain::load(const std::string& name)
{
	mScene->setWorldGeometry(mName = name);

	mFootsteps = Ogre::TextureManager::getSingleton().createManual(
		"footsteps", "terrain", Ogre::TEX_TYPE_2D,
		512, 512, 1, Ogre::PF_A8R8G8B8);

	mDamage = Ogre::TextureManager::getSingleton().createManual(
		"damage", "terrain", Ogre::TEX_TYPE_2D,
		512, 512, 1, Ogre::PF_A8R8G8B8);

	mFootsteps = Ogre::TextureManager::getSingleton().createManual(
		"fog_of_war", "terrain", Ogre::TEX_TYPE_2D,
		512, 512, 1, Ogre::PF_A8R8G8B8);

	//

	mMaterial = (Ogre::MaterialPtr)
		Ogre::MaterialManager::getSingleton().getByName("terrain");

	mMaterial->getTechnique(0)->getPass(1)->createTextureUnitState("footsteps");
	mMaterial->getTechnique(0)->getPass(2)->createTextureUnitState("damage");
	mMaterial->getTechnique(0)->getPass(3)->createTextureUnitState("fog_of_war");

	{
		Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("footsteps");
		tex->getBuffer(0, 0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

		const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();
		Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);

		for(size_t i = 0; i < pb.getHeight() * pb.getWidth(); ++i)
		{
			data[i] = 0x00000000;
		}

		tex->getBuffer(0, 0)->unlock();
	}

	{
		Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("damage");
		tex->getBuffer(0, 0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

		const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();
		Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);

		for(size_t i = 0; i < pb.getHeight() * pb.getWidth(); ++i)
		{
			data[i] = 0x00000000;
		}

		tex->getBuffer(0, 0)->unlock();
	}

	{
		Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("fog_of_war");
		tex->getBuffer(0, 0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

		const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();
		Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);

		for(size_t i = 0; i < pb.getHeight() * pb.getWidth(); ++i)
		{
			data[i] = 0x00000000;
		}

		tex->getBuffer(0, 0)->unlock();
	}
}

void Terrain::unload()
{
	Ogre::TextureManager::getSingleton().remove(mDamage->getHandle());
	Ogre::TextureManager::getSingleton().remove(mFootsteps->getHandle());

	mDamage.setNull();
	mFootsteps.setNull();

	mScene->clearScene();
}
