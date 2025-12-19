
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "ObjectInfoBar.h"

#include "Core.h"
#include "Gui.h"
#include "ObjectManager.h"
#include "PartManager.h"

//------------------------------------------------------------------------------

void ObjectInfoBar::init() {

	m_hoveredImage = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingletonPtr()->createWindow("TaharezLook/StaticImage");
	m_hoveredImage->setBackgroundEnabled(false);
	m_hoveredImage->setFrameEnabled(false);
	m_hoveredImage->setSize(CEGUI::Size(0.07f, 0.02f));
	m_hoveredImage->setVisible(false);

	CEGUI::System::getSingletonPtr()->getGUISheet()->addChildWindow(m_hoveredImage);

	m_hoveredTexture = Ogre::TextureManager::getSingletonPtr()->createManual(
		"HoveredTexture",
		"General",
		Ogre::TEX_TYPE_2D,
		128,
		128,
		0,
		Ogre::PF_A8R8G8B8, 
		Ogre::TU_DYNAMIC_WRITE_ONLY);

	Ogre::HardwarePixelBufferSharedPtr m_buffer = m_hoveredTexture->getBuffer(0, 0);

	m_buffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);

	const Ogre::PixelBox& pb = m_buffer->getCurrentLock();

	for (unsigned int y = 0; y < 128; y++) {

		unsigned int* data = static_cast<unsigned int*>(pb.data) + y * pb.rowPitch;

		for (unsigned int x = 0; x < 128; x++)

			if (((y == 0 || y == 127) && ((x >= 0 && x <= 16) || (x >= 111 && x <= 127))) || ((x == 0 || x == 127) && ((y >= 0 && y <= 16) || (y >= 111 && y <= 127))))

				data[x] = 0xFF00FF00;

			else

				data[x] = 0x00000000;
	}

	m_buffer->unlock();

	CEGUI::Texture* ceguiTexture =
		Gui::getSingletonPtr()->getRenderer()->createTexture(
		"HoveredTexture");

	CEGUI::Imageset* imageSet =
		CEGUI::ImagesetManager::getSingleton().createImageset(
		"HoveredImageset", ceguiTexture);

	imageSet->defineImage(
		"HoveredImage",
		CEGUI::Point(0.0f, 0.0f),
		CEGUI::Size(ceguiTexture->getWidth(), ceguiTexture->getHeight()),
		CEGUI::Point(0.0f, 0.0f));

	m_hoveredImage->setImage(&imageSet->getImage("HoveredImage"));

	//

	m_images.resize(256);
	m_textures.resize(256);

	for (int i = 0; i < 256; i++) {

		//

		m_images[i] = (CEGUI::StaticImage*)CEGUI::WindowManager::getSingletonPtr()->createWindow("TaharezLook/StaticImage");
		m_images[i]->setBackgroundEnabled(false);
		m_images[i]->setFrameEnabled(false);
		m_images[i]->setSize(CEGUI::Size(0.07f, 0.02f));
		m_images[i]->setVisible(false);

		CEGUI::System::getSingletonPtr()->getGUISheet()->addChildWindow(m_images[i]);

		//

		char name[64];

		sprintf(name, "%i", i);

		//

		m_textures[i] = Ogre::TextureManager::getSingletonPtr()->createManual(
			string("OgreTexture") + name,
			"General",
			Ogre::TEX_TYPE_2D,
			128,
			128,
			0,
			Ogre::PF_A8R8G8B8, 
			Ogre::TU_DYNAMIC_WRITE_ONLY);

		//

		Ogre::HardwarePixelBufferSharedPtr m_buffer = m_textures[i]->getBuffer(0, 0);

		m_buffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);

		const Ogre::PixelBox& pb = m_buffer->getCurrentLock();

		for (unsigned int y = 0; y < 128; y++) {

			unsigned int* data = static_cast<unsigned int*>(pb.data) + y * pb.rowPitch;

			for (unsigned int x = 0; x < 128; x++)

				data[x] = 0x00000000;
		}

		m_buffer->unlock();

		//

		CEGUI::Texture* ceguiTexture =
			Gui::getSingletonPtr()->getRenderer()->createTexture(
			string("OgreTexture") + name);

		CEGUI::Imageset* imageSet =
			CEGUI::ImagesetManager::getSingleton().createImageset(
			string("Imageset") + name, ceguiTexture);

		imageSet->defineImage(
			string("Image") + name,
			CEGUI::Point(0.0f, 0.0f),
			CEGUI::Size(ceguiTexture->getWidth(), ceguiTexture->getHeight()),
			CEGUI::Point(0.0f, 0.0f));

		m_images[i]->setImage(&imageSet->getImage(string("Image") + name));
	}
}

//------------------------------------------------------------------------------

void ObjectInfoBar::update(float deltaTime) {

	if (Core::getSingletonPtr()->m_hovered.size()) {

		Ogre::Vector3 hcsPosition;
		Ogre::Vector2 corners[8];

		for (int i = 0; i < 8; i++) {

			hcsPosition =
				Core::getSingletonPtr()->getCamera()->getProjectionMatrix() *
				(Core::getSingletonPtr()->getCamera()->getViewMatrix() * Core::getSingletonPtr()->m_hovered.front()->getWorldBoundingBox().getAllCorners()[i]);

			corners[i].x = (hcsPosition.x * 0.5f) + 0.5f;
			corners[i].y = 1.0f - ((hcsPosition.y * 0.5f) + 0.5f);
		}

		float xMin = corners[0].x;
		float xMax = corners[0].x;
		float yMin = corners[0].y;
		float yMax = corners[0].y;

		for (int i = 1; i < 8; i++) {

			if (xMin > corners[i].x) xMin = corners[i].x;
			if (xMax < corners[i].x) xMax = corners[i].x;
			if (yMin > corners[i].y) yMin = corners[i].y;
			if (yMax < corners[i].y) yMax = corners[i].y;
		}

		m_hoveredImage->setPosition(CEGUI::Point(xMin, yMin));
		m_hoveredImage->setSize(CEGUI::Size(xMax - xMin, yMax - yMin));
		m_hoveredImage->setVisible(true);

	} else {

		m_hoveredImage->setVisible(false);
	}

	//

	int index = 0;

	for(ObjectManager::Iterator itr = ObjectManager::getSingletonPtr()->Begin(); itr != ObjectManager::getSingletonPtr()->End(); itr++) {

		Ogre::Vector3 hcsPosition;
		Ogre::Vector2 corners[8];

		for (int i = 0; i < 8; i++) {

			hcsPosition =
				Core::getSingletonPtr()->getCamera()->getProjectionMatrix() *
				(Core::getSingletonPtr()->getCamera()->getViewMatrix() * (*itr)->getWorldBoundingBox().getAllCorners()[i]);

			corners[i].x = (hcsPosition.x * 0.5f) + 0.5f;
			corners[i].y = 1.0f - ((hcsPosition.y * 0.5f) + 0.5f);
		}

		float xMin = corners[0].x;
		float xMax = corners[0].x;
		float yMin = corners[0].y;
		float yMax = corners[0].y;

		for (int i = 1; i < 8; i++) {

			if (xMin > corners[i].x) xMin = corners[i].x;
			if (xMax < corners[i].x) xMax = corners[i].x;
			if (yMin > corners[i].y) yMin = corners[i].y;
			if (yMax < corners[i].y) yMax = corners[i].y;
		}

		m_images[index]->setPosition(CEGUI::Point(xMin, yMin));
		m_images[index]->setSize(CEGUI::Size(xMax - xMin, 0.02f));
		m_images[index]->setVisible(true && m_visible);

		//

		Ogre::HardwarePixelBufferSharedPtr m_buffer = m_textures[index]->getBuffer(0, 0);

		m_buffer->lock(Ogre::HardwareBuffer::HBL_DISCARD);

		const Ogre::PixelBox& pb = m_buffer->getCurrentLock();

		for (unsigned int z = 0; z < 128; z++) {

			unsigned int* data = static_cast<unsigned int*>(pb.data) + z * pb.rowPitch;

			// Object hit points.

			if (z < 32)

				for (int x = 0; x < 128; x++)

					if (x < (int)((float)(*itr)->getHitPoints() / (float)(*itr)->getMaxHitPoints() * 128.0f))

						data[x] = 0xAA00DD00;

					else

						data[x] = 0x5500DD00;

			// Weapon ammunition level.

			else if ((*itr)->getWeapon() && z > 32 && z < 64)

				for (int x = 0; x < 128; x++)

					if (x < (int)((float)(*itr)->getWeapon()->getAmmunition() / (float)(*itr)->getWeapon()->getMaxAmmunition() * 128.0f))

						data[x] = 0xAADD3300;

					else

						data[x] = 0x55DD3300;

			// Weapon reload time.

			else if ((*itr)->getWeapon() && z > 64 && z < 96)

				for (int x = 0; x < 128; x++)

					if (x < (int)((*itr)->getWeapon()->getReloadTime() / (*itr)->getWeapon()->getMaxReloadTime() * 128))

						data[x] = 0xAADDDDDD;

					else

						data[x] = 0x55DDDDDD;

			// Engine fuel level.

			else if ((*itr)->getEngine() && z > 96 && z < 128)

				for (int x = 0; x < 128; x++)

					if (x < (int)((*itr)->getEngine()->getFuel() / (*itr)->getEngine()->getMaxFuel() * 128))

						data[x] = 0xAA3377DD;

					else

						data[x] = 0x553377DD;
		}

		m_buffer->unlock();

		//

		index++;
	}

	for (int i = index; i < 256; i++)

		m_images[i]->setVisible(false);
}

//------------------------------------------------------------------------------
