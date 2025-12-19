#include "Dependencies.h"
#include "Game.h"
#include "Graphics.h"
#include "GUI.h"
#include "ObjectManager.h"
#include "Terrain.h"
#include "Unit.h"

Graphics* Ogre::Singleton<Graphics>::ms_Singleton = NULL;

bool Graphics::init()
{
	mEntity = NULL;
	mMaterial = NULL;
	mNode = NULL;

	mRender = true;

	// Initialize Ogre.
	mRoot = new Ogre::Root("Plugins.cfg", "Ogre.cfg", "Ogre.log");

	// Load display configuration.
	if (mRoot->restoreConfig() == false)
	{
		if (mRoot->showConfigDialog() == false)
		{
			return false;
		}
	}

	mRoot->addFrameListener(this);

	// Initialize render system and create render window.
	mRenderWindow = mRoot->initialise(true, "WarGAME");

	Ogre::WindowEventUtilities::addWindowEventListener(mRenderWindow, this);

	// Initialize resources.
	Ogre::ConfigFile resources;
	resources.load("Resources.cfg");

	Ogre::ConfigFile::SectionIterator sections = resources.getSectionIterator();

	Ogre::String secName;
	Ogre::ConfigFile::SettingsMultiMap* settings;
	Ogre::ConfigFile::SettingsMultiMap::iterator i;

	while (sections.hasMoreElements())
	{
		secName = sections.peekNextKey();
		settings = sections.getNext();

		for (i = settings->begin(); i != settings->end(); i++)
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(i->second, i->first, secName);
		}
	}

	//*
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	// Create scene manager.
	mSceneManager = mRoot->createSceneManager(Ogre::ST_EXTERIOR_CLOSE);

//	mSceneManager->setSkyDome(true, "Examples/CloudySky", 5.0f, 2.0f, 500.0f);

	Ogre::Plane plane;
	
	plane.normal = Ogre::Vector3::NEGATIVE_UNIT_Y;
	plane.d = 100.0f;

	mSceneManager->setSkyPlane(
		true,
		plane,
		"Examples/CloudySky",
		1000.0f, 10.0f, true, 12.0f, 250, 250);

	//mSceneManager->setFog(
	//	Ogre::FOG_LINEAR,
	//	Ogre::ColourValue(137.0f / 255.0f, 158.0f / 255.0f, 251.0f / 255.0f),
	//	0.0f,
	//	400.0f,
	//	900.0f);

	mCamera = mSceneManager->createCamera("Camera");
	mCamera->setPosition(1220.0f, 100.0f, 1220.0f);
	mCamera->lookAt(550.0f, 20.0f, 540.0f);
	mCamera->setFarClipDistance(0.0f);
	mCamera->setNearClipDistance(10.0f);

	// Structure cursor.
	mNode = createSceneNode();

	mPlaneQuery = mSceneManager->createPlaneBoundedVolumeQuery(Ogre::PlaneBoundedVolumeList());

	Ogre::TextureManager::getSingleton().load("terrain_map.png", "General");

//	mSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
//	mSceneManager->setShadowColour(Ogre::ColourValue(0.75f, 0.75f, 0.75f, 0.25f));
//	mSceneManager->setShadowFarDistance(256);

//	Ogre::Light* sun = mSceneManager->createLight("sun");
//	sun->setType(Ogre::Light::LT_DIRECTIONAL);
//	sun->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());
//	sun->setDiffuseColour(0.5, 0.5, 0.5);

	// Create ray scene query.
	mRaySceneQuery = mSceneManager->createRayQuery(Ogre::Ray());
	mRaySceneQuery->setSortByDistance(true);

	// Create viewport.
	mViewport = mRenderWindow->addViewport(mCamera);
	mViewport->setBackgroundColour(Ogre::ColourValue(137.0f / 255.0f, 158.0f / 255.0f, 251.0f / 255.0f));

	// Create input system.
	mInput.init(mRenderWindow);

	// Resize window to tell OIS about it's size.
	windowResized(mRenderWindow);

	// Create box selection objects.
	Ogre::AxisAlignedBox box;
	box.setInfinite();

	mBoxSelectionRectangle = new Ogre::Rectangle2D();
	mBoxSelectionRectangle->setBoundingBox(box);
	mBoxSelectionRectangle->setMaterial("box_selection");

	mBoxSelectionNode = createSceneNode();
	mBoxSelectionNode->attachObject(mBoxSelectionRectangle);
	mBoxSelectionNode->setVisible(false);

	return true;
}

void Graphics::mainLoop()
{
	mRoot->startRendering();
}

void Graphics::shutdown()
{
	mInput.shutdown();

	mRenderWindow->destroy();

	delete mRoot;
}

Ogre::Entity* Graphics::createEntity(const std::string& name, const std::string& mesh) const
{
	return mSceneManager->createEntity(name, mesh);
}

Ogre::ParticleSystem* Graphics::createParticleSystem(const std::string& name, const std::string& script) const
{
	return mSceneManager->createParticleSystem(name, script);
}

Ogre::SceneNode* Graphics::createSceneNode() const
{
	return mSceneManager->getRootSceneNode()->createChildSceneNode();
}

void Graphics::destroy(Ogre::Entity* entity) const
{
	mSceneManager->destroyEntity(entity);
}

void Graphics::destroy(Ogre::ParticleSystem* particleSystem) const
{
	mSceneManager->destroyParticleSystem(particleSystem);
}

void Graphics::destroy(Ogre::SceneNode* sceneNode) const
{
	mSceneManager->destroySceneNode(sceneNode->getName());
}

Object* Graphics::raycastObject(const Ogre::Ray& ray) const
{
	mRaySceneQuery->setRay(ray);

	if (mRaySceneQuery->execute().size())
	{
		const Ogre::RaySceneQueryResult& result = mRaySceneQuery->getLastResults();

		for (Ogre::RaySceneQueryResult::const_iterator i = result.begin(); i != result.end(); i++)
		{
			if (i->movable)
			{
				const Ogre::Any& any = i->movable->getUserAny();

				if (any.isEmpty() == false)
				{
					if (any.getType() == typeid(Object*))
					{
						return Ogre::any_cast<Object*>(any);
					}
				}
			}
		}
	}

	return NULL;
}

bool Graphics::frameStarted(const Ogre::FrameEvent& evt)
{
	mInput.capture();

	// Calculate camera direction.
	static Ogre::Vector3 dir, pos;

	Ogre::Camera* mCamera = Graphics::getSingleton().getCamera();

	mViewport->setCamera(mCamera);

	dir = mCamera->getDirection();
	dir.y = 0.0f;
	dir.normalise();
	dir *= 50.0f * evt.timeSinceLastFrame;

	pos = Ogre::Vector3::ZERO;

	CEGUI::Point point = CEGUI::MouseCursor::getSingleton().getDisplayIndependantPosition();

	// Move camera forward or backward and left or right.
	if (mInput.isKeyDown(OIS::KC_UP) || mInput.isKeyDown(OIS::KC_W) || (point.d_y < 0.01f))
	{
		pos += dir;
	}
	else if (mInput.isKeyDown(OIS::KC_DOWN) || mInput.isKeyDown(OIS::KC_S) || (point.d_y > 0.99f))
	{
		pos -= dir;
	}

	if (mInput.isKeyDown(OIS::KC_LEFT) || mInput.isKeyDown(OIS::KC_A) || (point.d_x < 0.01f))
	{
		pos -= dir.crossProduct(Ogre::Vector3::UNIT_Y);
	}
	else if (mInput.isKeyDown(OIS::KC_RIGHT) || mInput.isKeyDown(OIS::KC_D) || (point.d_x > 0.99f))
	{
		pos += dir.crossProduct(Ogre::Vector3::UNIT_Y);
	}

	// Do not allow camera to move outside the terrain.
	pos = mCamera->getPosition() + pos;

	if (pos.x < 1.0f)
	{
		pos.x = 1.0f;
	}

	if (pos.z < 1.0f)
	{
		pos.z = 1.0f;
	}


	// Raise or lower camera.
	static float height = 50.0f;

	if (mInput.isKeyDown(OIS::KC_PGUP) || mInput.isKeyDown(OIS::KC_Q))
	{
		height += 135.0f * evt.timeSinceLastFrame;
	}
	else if (mInput.isKeyDown(OIS::KC_PGDOWN) || mInput.isKeyDown(OIS::KC_Z))
	{
		height -= 135.0f * evt.timeSinceLastFrame;
	}


	if (height < 2.0f)
	{
		height = 2.0f;
	}
	else if (height > 100.0f)
	{
//		height = 100.0f;
	}

	if (Terrain::getSingleton().getPosition(pos).y > 24.0f)
	{
		// Move camera to final position (on ground).
		mCamera->setPosition(Terrain::getSingleton().getPosition(pos) + Ogre::Vector3::UNIT_Y * height);
	}
	else
	{
		// Move camera to final position (on water).
		mCamera->setPosition(Terrain::getSingleton().getPosition(pos) + Ogre::Vector3::UNIT_Y * (24.0f - Terrain::getSingleton().getPosition(pos).y + height));
	}

	// Convert mouse position to ray.
	point = CEGUI::MouseCursor::getSingleton().getPosition();

	Ogre::Ray ray = mCamera->getCameraToViewportRay(
		point.d_x / (float)mRenderWindow->getWidth(),
		point.d_y / (float)mRenderWindow->getHeight());

	// Get nearest object under mouser cursor.
	if (GUI::getSingleton().isMouseOver() == false)
	{
		if (Object* o = raycastObject(ray))
		{
			if (Unit* u = dynamic_cast<Unit*>(o))
			{
				if (u->isAlly(Game::getSingleton().getActivePlayer()))
				{
					GUI::getSingleton().getSingleton().setStatusText(o->toString());
				}
				else
				{
					GUI::getSingleton().getSingleton().setStatusText(
						"Name: " + u->getName() + "\n" +
						"Position: " + Ogre::StringConverter::toString(o->getPosition()) + "\n" +
						"Player: " + u->getPlayer()->getName());
				}
			}
			else
			{
				GUI::getSingleton().getSingleton().setStatusText(o->toString());
			}
		}
		else if (Game::getSingleton().getActivePlayer()->getSelected().size())
		{
			const Player::ObjectContainer& objects = Game::getSingleton().getActivePlayer()->getSelected();

			GUI::getSingleton().getSingleton().setStatusText(ObjectManager::getSingleton().get(*(objects.begin()))->toString());
		}
		else
		{
			GUI::getSingleton().getSingleton().setStatusText(Game::getSingleton().toString());
		}
	}
	else
	{
		GUI::getSingleton().getSingleton().setStatusText(Game::getSingleton().toString());
	}

	// Update game state each frame gives less control.
	// Updating textures each frame would be too expensive.
	static float timeSinceGameUpdate = 0.0f;
	static float timeSinceTextureUpdate = 0.0f;

	static float gameUpdateInterval = 0.02f;	// 50 times per second.
	static float textureUpdateInterval = 0.5f;	// Twice per second.

	timeSinceGameUpdate += evt.timeSinceLastFrame;
	timeSinceTextureUpdate += evt.timeSinceLastFrame;

	if (Game::getSingleton().getGameSpeed())
	{
		// Update game state.
		if (timeSinceGameUpdate >= gameUpdateInterval)
		{
			Game::getSingleton().update(gameUpdateInterval);

			timeSinceGameUpdate = 0.0f;
		}

		if (GUI::getSingleton().getVisible() && (timeSinceTextureUpdate >= textureUpdateInterval))
		{
			// Update mimap.
			Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("minimap");
			tex->getBuffer(0, 0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

			const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();
			Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);
		
			{
				Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("terrain_texture.jpg");
				tex->getBuffer(0, 0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

				const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();
				Ogre::uint32* data_ = static_cast<Ogre::uint32*>(pb.data);
			
				// Reset texture.
				for(size_t z = 0; z < pb.getHeight() * pb.getWidth(); ++z)
				{
					data[z] = (0xFF << 24) + data_[z];
				}

				tex->getBuffer(0, 0)->unlock();
			}

			// Mark all objects on the texture.
			const ObjectMap& objects = ObjectManager::getSingleton().get();

			size_t posZ, posX, minZ, minX, maxZ, maxX, z, x, size = 4;

			for (ObjectMap::const_iterator i = objects.begin(); i != objects.end(); ++i)
			{
				posZ = (size_t)i->second->getPosition().z * 512.0f / 2500.0f;
				posX = (size_t)i->second->getPosition().x * 512.0f / 2500.0f;

				minZ = posZ - size < 0 ? 0 : posZ - size;
				maxZ = posZ + size > pb.getHeight() ? pb.getHeight() : posZ + size;

				minX = posX - size < 0 ? 0 : posX - size;
				maxX = posX + size > pb.getWidth() ? pb.getWidth() : posX + size;

				for(z = minZ; z < maxZ; ++z)
				{
					for(x = minX; x < maxX; ++x)
					{
						if (Unit* u = dynamic_cast<Unit*>(i->second))
						{
							data[pb.rowPitch * z + x] = u->getPlayer()->getColour().getAsABGR();
						}
					}
				}
			}

			tex->getBuffer(0, 0)->unlock();


			// Update GUI.
			GUI::getSingleton().update(textureUpdateInterval);


			// Reset time.
			textureUpdateInterval = 0.0f;
		}
	}

	static bool b = true;

	static const unsigned int numFishes = 400;

	static Ogre::Entity* e[numFishes];
	static Ogre::AnimationState* a[numFishes];
	static Ogre::SceneNode* s[numFishes];
	static Ogre::Vector3 d[numFishes];
	static float speed[numFishes];
	static float time[numFishes];
	static float interval[numFishes];

	if (b)
	{
		for (unsigned int i = 0; i < numFishes; ++i)
		{
			time[i] = 0.0f;
			interval[i] = Ogre::Math::RangeRandom(10.0f, 15.0f);

			e[i] = createEntity("fish" + Ogre::StringConverter::toString(i), "fish.mesh");
			e[i]->setRenderingDistance(128.0f);

			a[i] = e[i]->getAnimationState("swim");
			s[i] = createSceneNode();

			a[i]->setEnabled(true);

			s[i]->attachObject(e[i]);
			s[i]->setScale(Ogre::Vector3(Ogre::Math::RangeRandom(0.1, 0.3)));

			Ogre::Vector3 p;

			do
			{
				p.x = Ogre::Math::RangeRandom(100, 2400);
				p.z = Ogre::Math::RangeRandom(100, 2400);
			}
			while (Terrain::getSingleton().getPosition(p).y > 18.0f);

			p.y = 22;
			s[i]->setPosition(p);

			speed[i] = Ogre::Math::RangeRandom(3.0f, 5.0f);

			d[i].x = Ogre::Math::RangeRandom(-1.0f, 1.0f);
			d[i].y = 0.0f;
			d[i].z = Ogre::Math::RangeRandom(-1.0f, 1.0f);

			d[i].normalise();
		}

		b = false;
	}

	for (unsigned int i = 0; i < numFishes; ++i)
	{
		a[i]->addTime(evt.timeSinceLastFrame * speed[i] * 0.5f);

		Ogre::Vector3 next = Terrain::getSingleton().getPosition(s[i]->getPosition() + d[i] * speed[i]);

		time[i] += evt.timeSinceLastFrame;

		if (time[i] > interval[i])
		{
			do
			{
				d[i].x = Ogre::Math::RangeRandom(-1.0f, 1.0f);
				d[i].z = Ogre::Math::RangeRandom(-1.0f, 1.0f);

				d[i].normalise();

				next = Terrain::getSingleton().getPosition(s[i]->getPosition() + d[i] * speed[i]);
			}
			while(next.x < 1.0f || next.x > 2400.0f || next.y > 22.0f || next.z < 1.0f || next.z > 2400.0f);

			time[i] = 0.0f;
			interval[i] = Ogre::Math::RangeRandom(10.0f, 15.0f);
		}

		while(next.x < 1.0f || next.x > 2400.0f || next.y > 18.0f || next.z < 1.0f || next.z > 2400.0f)
		{
			d[i].x = Ogre::Math::RangeRandom(-1.0f, 1.0f);
			d[i].z = Ogre::Math::RangeRandom(-1.0f, 1.0f);

			d[i].normalise();

			next = Terrain::getSingleton().getPosition(s[i]->getPosition() + d[i] * speed[i]);
		}

		s[i]->translate(d[i] * speed[i] * evt.timeSinceLastFrame, Ogre::Node::TS_WORLD);
		s[i]->setDirection(d[i], Ogre::Node::TS_WORLD, Ogre::Vector3::NEGATIVE_UNIT_X);
	}

	// Displays player details (name and resources).
	// Gets and converts resources to strings.
	Player* player = Game::getSingleton().getActivePlayer();
	const ResourceMap& resources = player->getResources();
	std::string text("");

	for (ResourceMap::const_iterator i = resources.begin(); i != resources.end(); ++i)
	{
		text += i->first;
		text += ": ";
		text += Ogre::StringConverter::toString(i->second.current, 1, 0, ' ', std::ios::fixed);
		text += " / ";
		text += Ogre::StringConverter::toString(i->second.maximal, 1, 0, ' ', std::ios::fixed);
		text += "      ";
	}

	GUI::getSingleton().setPlayerText(text);

	return true;
}

bool Graphics::frameEnded(const Ogre::FrameEvent& evt)
{
	return mRender;
}

void Graphics::windowMoved(Ogre::RenderWindow* rw)
{
}

void Graphics::windowResized(Ogre::RenderWindow* rw)
{
	const OIS::MouseState& ms = mInput.getMouseState();

	ms.height = rw->getHeight();
	ms.width = rw->getWidth();
}

void Graphics::windowClosed(Ogre::RenderWindow* rw)
{
	mRender = false;
}

void Graphics::windowFocusChange(Ogre::RenderWindow* rw)
{
}

void Graphics::createStructureCursor(const std::string& name)
{
	// Destroy previous cursor.
	if (mEntity && mMaterial)
	{
		destroy(mEntity);
		destroy(mMaterial);
	}

	// Get template.
	ObjectTemplate* temp = TemplateManager::getSingleton().get(name);

	// Create cursor.
	mEntity = createEntity("StructureCursor", temp->mesh);
	mEntity->setCastShadows(false);

	// Clone and modify material.
	mMaterial = mEntity->getSubEntity(0)->getMaterial()->clone("StructureCursorMaterial").get();
	mMaterial->setAmbient(0.0f, 0.7f, 0.0f);
	
	// Attach cursor to node.
	mNode->attachObject(mEntity);
	mNode->setScale(Ogre::Vector3(temp->scale));
}

void Graphics::setStructureCursorPosition(const Ogre::Vector3& position)
{
	mNode->setPosition(position);
}

void Graphics::setStructureCursorVisible(bool visible)
{
	mNode->setVisible(visible);
}
