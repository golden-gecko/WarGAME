#include "Dependencies.h"
#include "Factory.h"
#include "Game.h"
#include "Graphics.h"
#include "GUI.h"
#include "ObjectManager.h"
#include "PlayerManager.h"
#include "TemplateManager.h"

GUI* Ogre::Singleton<GUI>::ms_Singleton = NULL;

bool GUI::init()
{
	mLastOrder = OT_NONE;
	mMouseOver = false;
	mState = IS_SELECT_OBJECT;
	mStructure = NULL;

	// Init renderer.
	mRenderer = new CEGUI::OgreCEGUIRenderer(Graphics::getSingleton().getRenderWindow());
	mRenderer->setTargetSceneManager(Graphics::getSingleton().getSceneManager());

	// Init CEGUI system.
	mSystem = new CEGUI::System(mRenderer, 0, 0, 0, "WarGAME.config");
	mSystem->setDefaultMouseCursor("TaharezLook", "MouseArrow");
	mSystem->injectMousePosition(floor(mRenderer->getWidth() * 0.5f), floor(mRenderer->getHeight() * 0.5f));

	// Verify windows.
	try
	{
		mConsole = CEGUI::WindowManager::getSingleton().getWindow("Console");
		mMinimap = CEGUI::WindowManager::getSingleton().getWindow("Minimap");
		mResources = CEGUI::WindowManager::getSingleton().getWindow("Resources");
		mStatus = CEGUI::WindowManager::getSingleton().getWindow("Panel/Info/Text");
		mEditor = CEGUI::WindowManager::getSingleton().getWindow("Editor");

		mGroups = CEGUI::WindowManager::getSingleton().getWindow("Groups");	
		mGroupButtons[0] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/0");
		mGroupButtons[1] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/1");
		mGroupButtons[2] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/2");
		mGroupButtons[3] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/3");
		mGroupButtons[4] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/4");
		mGroupButtons[5] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/5");
		mGroupButtons[6] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/6");
		mGroupButtons[7] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/7");
		mGroupButtons[8] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/8");
		mGroupButtons[9] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Group/9");

		mSafe = (CEGUI::Checkbox*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Safe");

		mObjectList = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow("Editor/Objects/List");
		mObjectDetails = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow("Editor/Objects/Details");

		mPlayerList = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow("Editor/Players/List");
		mPlayerResources = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow("Editor/Players/Resources");
		mPlayerDetails = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow("Editor/Players/Details");

		mTemplateList = (CEGUI::Listbox*)CEGUI::WindowManager::getSingleton().getWindow("Editor/Templates/List");
		mTemplateDetails = CEGUI::WindowManager::getSingleton().getWindow("Editor/Templates/Details");
		mTemplatePicture = CEGUI::WindowManager::getSingleton().getWindow("Editor/Templates/Picture");

		mOrders["Attack"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Attack");
		mOrders["Capture"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Capture");
		mOrders["Destroy"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Destroy");
		mOrders["Disable"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Disable");
		mOrders["Enable"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Enable");
		mOrders["Follow"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Follow");
		mOrders["Guard"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Guard");
		mOrders["Look"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Look");
		mOrders["Move"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Move");
		mOrders["Patrol"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Patrol");
		mOrders["Stop"] = (CEGUI::PushButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Orders/Stop");

		for (unsigned int i = 0; i < 8; ++i)
		{
			mAbilities[i] = CEGUI::WindowManager::getSingleton().getWindow(
				"Panel/Orders/Abilities/" + Ogre::StringConverter::toString(i + 1));
		}

		mBehaviours["Attack/Fire"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Attack/Fire");
		mBehaviours["Attack/Return"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Attack/Return");
		mBehaviours["Attack/Hold"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Attack/Hold");
		mBehaviours["Target/Closest"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Target/Closest");
		mBehaviours["Target/Weakest"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Target/Weakest");
		mBehaviours["Target/Strongest"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Target/Strongest");
		mBehaviours["Move/Chase"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Move/Chase");
		mBehaviours["Move/Hold"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Move/Hold");
		mBehaviours["Range/Maximal"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Range/Maximal");
		mBehaviours["Range/Medeum"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Range/Medium");
		mBehaviours["Range/Close"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Range/Close");
		mBehaviours["Retreat/Never"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Retreat/Never");
		mBehaviours["Retreat/50"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Retreat/50");
		mBehaviours["Retreat/25"] = (CEGUI::RadioButton*)CEGUI::WindowManager::getSingleton().getWindow("Panel/Behaviour/Retreat/25");

		for (unsigned int i = 0; i < 8; ++i)
		{
			mStructures[i] = CEGUI::WindowManager::getSingleton().getWindow(
				"Panel/Structures/" + Ogre::StringConverter::toString(i + 1));

			mUnits[i] = CEGUI::WindowManager::getSingleton().getWindow
				("Panel/Units/" + Ogre::StringConverter::toString(i + 1));
		}
	}
	catch (...)
	{
		return false;
	}

	// Setup windows.
	mBehaviours["Attack/Fire"]->setSelected(true);
	mBehaviours["Move/Chase"]->setSelected(true);
	mBehaviours["Range/Maximal"]->setSelected(true);
	mBehaviours["Target/Closest"]->setSelected(true);
	mBehaviours["Retreat/Never"]->setSelected(true);

	mOrders["Attack"]->setID(OT_ATTACK);
	mOrders["Capture"]->setID(OT_CAPTURE);
	mOrders["Follow"]->setID(OT_FOLLOW);
	mOrders["Guard"]->setID(OT_GUARD);
	mOrders["Look"]->setID(OT_LOOK);
	mOrders["Move"]->setID(OT_MOVE);
	mOrders["Patrol"]->setID(OT_PATROL);

	// Subscribe mouse enters / leaves events.
	CEGUI::WindowManager::WindowIterator i = CEGUI::WindowManager::getSingleton().getIterator();

	while (i.isAtEnd() == false)
	{
		if (i.getCurrentValue() != mSystem->getGUISheet())
		{
			i.getCurrentValue()->subscribeEvent(
				CEGUI::Window::EventMouseEnters,
				CEGUI::Event::Subscriber(&GUI::mouseEnters, this));

			i.getCurrentValue()->subscribeEvent(
				CEGUI::Window::EventMouseLeaves,
				CEGUI::Event::Subscriber(&GUI::mouseLeaves, this));
		}

		++i;
	}

	// Subscribe events.
	mSystem->getGUISheet()->subscribeEvent(
		CEGUI::Window::EventMouseMove,
		CEGUI::Event::Subscriber(&GUI::mouseMove, this));
	mSystem->getGUISheet()->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&GUI::mouseClick, this));

	mPlayerList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&GUI::playerListSelectionChanged, this));
	mPlayerResources->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&GUI::playerResourcesSelectionChanged, this));
	mObjectList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&GUI::objectListSelectionChanged, this));
	mTemplateList->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&GUI::templateListSelectionChanged, this));

	mSafe->subscribeEvent(
		CEGUI::Checkbox::EventMouseClick,
		CEGUI::Event::Subscriber(&GUI::safeClick, this));

	mMinimap->subscribeEvent(
		CEGUI::Window::EventMouseClick,
		CEGUI::Event::Subscriber(&GUI::minimapClick, this));

	for (std::map<std::string, CEGUI::PushButton*>::const_iterator
		i = mOrders.begin(); i != mOrders.end(); ++i)
	{
		i->second->subscribeEvent(
			CEGUI::Window::EventMouseClick,
			CEGUI::Event::Subscriber(&GUI::orderClick, this));
	}

	for (std::map<std::string, CEGUI::RadioButton*>::const_iterator
		i = mBehaviours.begin(); i != mBehaviours.end(); ++i)
	{
		i->second->subscribeEvent(
			CEGUI::RadioButton::EventSelectStateChanged,
			CEGUI::Event::Subscriber(&GUI::behaviourClick, this));
	}

	for (unsigned int i = 0; i < 8; ++i)
	{
		mStructures[i]->subscribeEvent(
			CEGUI::Window::EventMouseClick,
			CEGUI::Event::Subscriber(&GUI::structureClick, this));

		mUnits[i]->subscribeEvent(
			CEGUI::Window::EventMouseClick,
			CEGUI::Event::Subscriber(&GUI::unitClick, this));
	}

	for (unsigned int i = 0; i < 10; i++)
	{
		mGroupButtons[i]->setID(i);
		mGroupButtons[i]->subscribeEvent(
			CEGUI::Window::EventMouseClick,
			CEGUI::Event::Subscriber(&GUI::groupButtonClick, this));
	}

	// Display minimap.
	Ogre::TexturePtr oTexture = Ogre::TextureManager::getSingleton().createManual(
		"minimap", "General", Ogre::TEX_TYPE_2D, 512, 512, 1, Ogre::PF_A8R8G8B8);

	CEGUI::Texture* cTexture = mRenderer->createTexture(oTexture);

	CEGUI::Imageset* imageset = CEGUI::ImagesetManager::getSingleton().createImageset("minimap.png", cTexture);
	imageset->defineImage("minimap.png", CEGUI::Point(0.0f, 0.0f),
		CEGUI::Size(cTexture->getWidth(), cTexture->getHeight()), CEGUI::Point(0.0f, 0.0f));

	CEGUI::Window* window = CEGUI::WindowManager::getSingleton().getWindow("Minimap");
	window->setProperty("Image", CEGUI::PropertyHelper::imageToString(&imageset->getImage("minimap.png")));

	// Load textures and create imagesets.
	const TemplateMap& templates = TemplateManager::getSingleton().get();
	unsigned int index = 0;

	//*
	for (TemplateMap::const_iterator i = templates.begin(); i != templates.end(); ++i)
	{
	//	Ogre::TexturePtr oTexture = Ogre::TextureManager::getSingleton().load(i->second->picture, "General");
	//	CEGUI::Texture* cTexture = GUI::getSingleton().getRenderer()->createTexture(oTexture);
	//	CEGUI::Imageset* imageset = CEGUI::ImagesetManager::getSingleton().createImageset(i->second->picture, cTexture);
	//	imageset->defineImage(i->second->picture, CEGUI::Point(0, 0), CEGUI::Size(cTexture->getWidth(), cTexture->getHeight()), CEGUI::Point(0, 0));

		switch (i->second->type)
		{
			case OT_FACTORY:
			case OT_FORTIFICATION:
			case OT_LABORATORY:
			case OT_MINE:
			case OT_RADAR:
			case OT_TURRET:

				ASSERT(index < 8);

				mStructures[index]->setUserData(i->second);
				mStructures[index]->setText(i->first);

			//	mStructures[index]->setProperty("Image",
			//		"set:" + i->second->picture + " image:" + i->second->picture);

				++index;

				break;
		}
	}
	//*/

	return true;
}

void GUI::shutdown()
{
	delete mSystem;
	delete mRenderer;
}

void GUI::update(float time)
{
	static CEGUI::ListboxTextItem* item;

	static const PlayerMap& players = PlayerManager::getSingleton().get();
	static const ObjectMap& objects = ObjectManager::getSingleton().get();
	static const TemplateMap& templates = TemplateManager::getSingleton().get();

	// Delete all items.
	mPlayerList->resetList();
	mObjectList->resetList();
	mTemplateList->resetList();

	// Add one item for each player.
	for (PlayerMap::const_iterator i = players.begin(); i != players.end(); ++i)
	{
		item = new CEGUI::ListboxTextItem(i->second->getName());
		item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		item->setUserData(i->second);
	//	item->setSelectionColours(CEGUI::colour(53.0f / 255.0f, 63.0f / 255.0f, 69.0f / 255.0f));

		mPlayerList->addItem(item);
	}

	for (ObjectMap::const_iterator i = objects.begin(); i != objects.end(); ++i)
	{
		item = new CEGUI::ListboxTextItem("   " + i->second->getName());
		item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		item->setUserData(i->second);
		
		mObjectList->addItem(item);
	}

	for (TemplateMap::const_iterator i = templates.begin(); i != templates.end(); ++i)
	{
		item = new CEGUI::ListboxTextItem("   " + i->second->name);
		item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		item->setUserData(i->second);

		mTemplateList->addItem(item);
	}

	// Add one item for each object.
	/*
	CEGUI::ListboxTextItem* plantsItem = new CEGUI::ListboxTextItem("Plants");
	CEGUI::ListboxTextItem* resourcesItem = new CEGUI::ListboxTextItem("Resources");
	CEGUI::ListboxTextItem* factoriesItem = new CEGUI::ListboxTextItem("Factories");
	CEGUI::ListboxTextItem* minesItem = new CEGUI::ListboxTextItem("Mines");
	CEGUI::ListboxTextItem* creaturesItem = new CEGUI::ListboxTextItem("Creatures");

	CEGUI::colour colour(193.0f / 255.0f, 213.0f / 255.0f, 1.0f);

	plantsItem->setTextColours(colour);
	resourcesItem->setTextColours(colour);
	factoriesItem->setTextColours(colour);
	minesItem->setTextColours(colour);
	creaturesItem->setTextColours(colour);

	mObjectList->addItem(plantsItem);

	for (ObjectMap::const_iterator i = objects.begin(); i != objects.end(); ++i)
	{
		if (i->second->getType() == OT_PLANT)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->getName());
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);
		
			mObjectList->addItem(item);
		}
	}

	mObjectList->addItem(resourcesItem);

	for (ObjectMap::const_iterator i = objects.begin(); i != objects.end(); ++i)
	{
		if (i->second->getType() == OT_RESOURCE)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->getName());
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);
		
			mObjectList->addItem(item);
		}
	}

	mObjectList->addItem(factoriesItem);

	for (ObjectMap::const_iterator i = objects.begin(); i != objects.end(); ++i)
	{
		if (i->second->getType() == OT_FACTORY)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->getName());
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);
		
			mObjectList->addItem(item);
		}
	}

	mObjectList->addItem(minesItem);

	for (ObjectMap::const_iterator i = objects.begin(); i != objects.end(); ++i)
	{
		if (i->second->getType() == OT_MINE)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->getName());
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);
		
			mObjectList->addItem(item);
		}
	}

	mObjectList->addItem(creaturesItem);

	for (ObjectMap::const_iterator i = objects.begin(); i != objects.end(); ++i)
	{
		if (i->second->getType() == OT_CREATURE)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->getName());
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);
		
			mObjectList->addItem(item);
		}
	}

	// Add one item for each template.
	plantsItem = new CEGUI::ListboxTextItem("Plants");
	resourcesItem = new CEGUI::ListboxTextItem("Resources");
	factoriesItem = new CEGUI::ListboxTextItem("Factories");
	minesItem = new CEGUI::ListboxTextItem("Mines");
	creaturesItem = new CEGUI::ListboxTextItem("Creatures");

	plantsItem->setTextColours(colour);
	resourcesItem->setTextColours(colour);
	factoriesItem->setTextColours(colour);
	minesItem->setTextColours(colour);
	creaturesItem->setTextColours(colour);

	mTemplateList->addItem(plantsItem);

	for (TemplateMap::const_iterator i = templates.begin(); i != templates.end(); ++i)
	{
		if (i->second->type == OT_PLANT)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->name);
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);

			mTemplateList->addItem(item);
		}
	}

	mTemplateList->addItem(resourcesItem);

	for (TemplateMap::const_iterator i = templates.begin(); i != templates.end(); ++i)
	{
		if (i->second->type == OT_RESOURCE)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->name);
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);

			mTemplateList->addItem(item);
		}
	}

	mTemplateList->addItem(minesItem);

	for (TemplateMap::const_iterator i = templates.begin(); i != templates.end(); ++i)
	{
		if (i->second->type == OT_MINE)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->name);
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);

			mTemplateList->addItem(item);
		}
	}

	mTemplateList->addItem(factoriesItem);

	for (TemplateMap::const_iterator i = templates.begin(); i != templates.end(); ++i)
	{
		if (i->second->type == OT_FACTORY)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->name);
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);

			mTemplateList->addItem(item);
		}
	}

	mTemplateList->addItem(creaturesItem);

	for (TemplateMap::const_iterator i = templates.begin(); i != templates.end(); ++i)
	{
		if (i->second->type == OT_CREATURE)
		{
			item = new CEGUI::ListboxTextItem("   " + i->second->name);
			item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
			item->setUserData(i->second);

			mTemplateList->addItem(item);
		}
	}
	*/

	// Object groups.
	for (unsigned int i = 0; i < 10; ++i)
	{
		if (Game::getSingleton().getActivePlayer()->getGroup(i).size())
		{
			mGroupButtons[i]->setVisible(true);
		}
		else
		{
			mGroupButtons[i]->setVisible(false);
		}
	}

	// Orders
	if (Game::getSingleton().getActivePlayer()->getSelected().size())
	{
		for (std::map<std::string, CEGUI::PushButton*>::const_iterator i = mOrders.begin();
			i != mOrders.end(); ++i)
		{
			if (i->first != "Destroy")
			{
				i->second->enable();
			}
			else
			{
				if (mSafe->isSelected())
				{
					i->second->enable();
				}
			}
		}
	}
	else
	{
		for (std::map<std::string, CEGUI::PushButton*>::const_iterator i = mOrders.begin();
			i != mOrders.end(); ++i)
		{
			i->second->disable();
		}
	}

	// Abilities
	if (Game::getSingleton().getActivePlayer()->getSelected().size())
	{
		for (unsigned int i = 0; i < 8; ++i)
		{
			mAbilities[i]->enable();
		}
	}
	else
	{
		for (unsigned int i = 0; i < 8; ++i)
		{
			mAbilities[i]->disable();
		}
	}

	// Units
	const Player::ObjectContainer& selected = Game::getSingleton().getActivePlayer()->getSelected();

	if (selected.size() == 1)
	{
		Object* object = ObjectManager::getSingleton().get(*(selected.begin()));

		if (object->getType() == OT_FACTORY)
		{
			unsigned int index = 0;

			const TemplateMap& templates = TemplateManager::getSingleton().get();

			for (TemplateMap::const_iterator i = templates.begin(); i != templates.end(); ++i)
			{
				if (i->second->type == OT_VEHICLE)
				{
				//	mUnits[index]->setProperty("Image", "set:" + i->second->picture + " image:" + i->second->picture);
					mUnits[index]->setUserData(i->second);
					mUnits[index]->setText(i->first);

					++index;
				}
			}
		}
		else
		{
			for (unsigned int i = 0; i < 8; ++i)
			{
			//	mUnits[i]->setProperty("Image", "");
				mUnits[i]->setText("");
			}
		}
	}
	else
	{
		for (unsigned int i = 0; i < 8; ++i)
		{
		//	mUnits[i]->setProperty("Image", "");
			mUnits[i]->setText("");
		}
	}

	// Cursor.
	if (isMouseOver() == false)
	{
		switch (mState)
		{
			case IS_PLACE_STRUCTURE:
			{
				CEGUI::Point mouse = CEGUI::MouseCursor::getSingleton().getPosition();

				Ogre::Ray ray = Graphics::getSingleton().getCamera()->getCameraToViewportRay(
					mouse.d_x / mRenderer->getWidth(), mouse.d_y / mRenderer->getHeight());

				Ogre::Vector3 position = Terrain::getSingleton().getPosition(ray);
				position = Terrain::getSingleton().getPosition(position);

				Graphics::getSingleton().setStructureCursorPosition(position);
				Graphics::getSingleton().setStructureCursorVisible(true);
				CEGUI::MouseCursor::getSingleton().setVisible(false);

				break;
			}

			case IS_SELECT_OBJECT:
			{
				CEGUI::MouseCursor::getSingleton().setVisible(true);

				break;
			}
		}
	}
	else
	{
		switch (mState)
		{
			case IS_PLACE_STRUCTURE:
			{
				Graphics::getSingleton().setStructureCursorVisible(false);
				CEGUI::MouseCursor::getSingleton().setVisible(true);

				break;
			}
		}
	}
}

bool GUI::minimapClick(const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& args =
		static_cast<const CEGUI::MouseEventArgs&>(e);

	std::cout << args.position.d_x << std::endl;
	std::cout << args.position.d_y << std::endl;

	return true;
}

bool GUI::groupButtonClick(const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& args =
		static_cast<const CEGUI::MouseEventArgs&>(e);

	Game::getSingleton().getActivePlayer()->selectGroup(
		args.window->getID());

	return true;
}

bool GUI::orderClick(const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& args =
		static_cast<const CEGUI::MouseEventArgs&>(e);

	ASSERT(args.window);
	
	if (args.window->getText() == "Destroy")
	{
		Game::getSingleton().getActivePlayer()->orderSelected(Order(OT_DESTROY));
	}
	else if (args.window->getText() == "Stop")
	{
		Game::getSingleton().getActivePlayer()->orderSelected(Order(OT_STOP));
	}
	else
	{
		mLastOrder = args.window->getID();
	}

	return true;
}

bool GUI::behaviourClick(const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& args =
		static_cast<const CEGUI::MouseEventArgs&>(e);

	ASSERT(args.window);
	ASSERT(args.window->getName().size());

	const CEGUI::String& name = args.window->getName();

	std::cout << args.window->getID() << std::endl;

	return true;
}

bool GUI::structureClick(const CEGUI::EventArgs& e)
{
	const CEGUI::MouseEventArgs& args =
		static_cast<const CEGUI::MouseEventArgs&>(e);

	if (args.window->getUserData())
	{
		mStructure = static_cast<StructureTemplate*>(args.window->getUserData());

		Graphics::getSingleton().createStructureCursor(mStructure->name);
		Graphics::getSingleton().setStructureCursorVisible(false);

		setState(IS_PLACE_STRUCTURE);
	}

	return true;
}

bool GUI::unitClick(const CEGUI::EventArgs& e)
{
	LOG("TODO");

	const CEGUI::MouseEventArgs& args =
		static_cast<const CEGUI::MouseEventArgs&>(e);



	// Units
	const Player::ObjectContainer& selected = Game::getSingleton().getActivePlayer()->getSelected();

	if (selected.size() == 1)
	{
		Object* object = ObjectManager::getSingleton().get(*(selected.begin()));

		if (Factory* factory = dynamic_cast<Factory*>(object))
		{
			ASSERT(args.window);
			ASSERT(args.window->getUserData());

			if (VehicleTemplate* vehicle = static_cast<VehicleTemplate*>(args.window->getUserData()))
			{
				factory->onOrder(Order(OT_CONSTRUCT, vehicle->name), true);
			}
		}
	}

	return true;
}

bool GUI::playerListSelectionChanged(const CEGUI::EventArgs& e)
{
	// Delete all items.
	mPlayerResources->resetList();

	// Get player.
	void* data = mPlayerList->getFirstSelectedItem()->getUserData();

	Player* player = static_cast<Player*>(data);

	// Add one item for each resource.
	const ResourceMap& resources = player->getResources();

	for (ResourceMap::const_iterator i = resources.begin(); i != resources.end(); ++i)
	{
		CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(i->first);

		item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
		item->setSelectionColours(CEGUI::colour(53.0f / 255.0f, 63.0f / 255.0f, 69.0f / 255.0f));

		mPlayerResources->addItem(item);
	}

	// Display player details.
	std::string s = "";

	for each (std::pair<std::string, ResourceDetails> p in player->getResources())
	{
		s += p.first + "\n";
		s += "   Current: " + Ogre::StringConverter::toString(p.second.current) + "\n";
		s += "   Maximal: " + Ogre::StringConverter::toString(p.second.maximal) + "\n";
		s += "   Produced: " + Ogre::StringConverter::toString(p.second.produced) + "\n";
		s += "   Use: " + Ogre::StringConverter::toString(p.second.use) + "\n";
	}

	mPlayerDetails->setText(player->toString() + "\n" + s);

	return true;
}

bool GUI::playerResourcesSelectionChanged(const CEGUI::EventArgs& e)
{
	return true;
}

bool GUI::objectListSelectionChanged(const CEGUI::EventArgs& e)
{
	if (void* data = mObjectList->getFirstSelectedItem()->getUserData())
	{
		// Get object.
		Object* object = static_cast<Object*>(data);

		// Display object details.
		mObjectDetails->setText(object->toString());
	}

	return true;
}

bool GUI::templateListSelectionChanged(const CEGUI::EventArgs& e)
{
	if (void* data = mTemplateList->getFirstSelectedItem()->getUserData())
	{
		// Get template.
		ObjectTemplate* objectTemplate = static_cast<ObjectTemplate*>(data);

		// Display template details.
		mTemplateDetails->setText(objectTemplate->toString());

		// Display picture.
	//	mTemplatePicture->setProperty("Image",
	//		"set: " + objectTemplate->picture + " image:" + objectTemplate->picture);
	}

	return true;
}

bool GUI::mouseClick(const CEGUI::EventArgs& e)
{
	if (isMouseOver() == false)
	{
		const CEGUI::MouseEventArgs& args =
			static_cast<const CEGUI::MouseEventArgs&>(e);

		switch (args.button)
		{
			case CEGUI::LeftButton:
				mouseLeftClick(args);
				break;

			case CEGUI::RightButton:
				mouseRightClick(args);
				break;
		}
	}

	return true;
}

bool GUI::mouseEnters(const CEGUI::EventArgs& e)
{
	mMouseOver = true;

	return true;
}

bool GUI::mouseLeaves(const CEGUI::EventArgs& e)
{
	mMouseOver = false;

	return true;
}

bool GUI::mouseMove(const CEGUI::EventArgs& e)
{
	return true;
}

void GUI::mouseLeftClick(const CEGUI::MouseEventArgs& args)
{
	switch (mState)
	{
		case IS_GIVE_ORDER:
		{
			break;
		}

		case IS_PLACE_STRUCTURE:
		{
			Player* player = Game::getSingleton().getActivePlayer();
			bool canBuild = true;

			// Has player enough resources?
			for (std::map<std::string, float>::iterator i = mStructure->cost.begin();
				i != mStructure->cost.end(); ++i)
			{
				if (player->getResource(i->first).current < i->second)
				{
					canBuild = false;
					
					break;
				}
			}

			// Player has enough resources.
			if (canBuild)
			{
				// Remove resources.
				for (std::map<std::string, float>::iterator i = mStructure->cost.begin();
					i != mStructure->cost.end(); ++i)
				{
					LOG(Ogre::StringConverter::toString(player->getResource(i->first).current));
					LOG(Ogre::StringConverter::toString(i->second));
					player->getResource(i->first).current -= i->second;
				}

				// Get position.
				CEGUI::Point cursor = 
					CEGUI::MouseCursor::getSingleton().getPosition();

				Ogre::Ray ray = Graphics::getSingleton().getCamera()->getCameraToViewportRay(
					cursor.d_x / mRenderer->getWidth(), cursor.d_y / mRenderer->getHeight());

				Ogre::Vector3 position = Terrain::getSingleton().getPosition(ray);
				position = Terrain::getSingleton().getPosition(position);

				// Build structure.
				Structure* structure = dynamic_cast<Structure*>
					(ObjectManager::getSingleton().create(mStructure->name, position));
				structure->setPlayer(player);
				structure->onCreate();
			}

			break;
		}

		case IS_SELECT_OBJECT:
		{
			break;
		}
	}
}

void GUI::mouseRightClick(const CEGUI::MouseEventArgs& args)
{
	switch (mState)
	{
		case IS_GIVE_ORDER:
		{
			break;
		}

		case IS_PLACE_STRUCTURE:
		{
			Graphics::getSingleton().setStructureCursorVisible(false);

			setState(IS_SELECT_OBJECT);

			break;
		}

		case IS_SELECT_OBJECT:
		{
			break;
		}
	}
}

bool GUI::safeClick(const CEGUI::EventArgs& e)
{
	if (mOrders["Enable"]->isDisabled() == false)
	{
		if (mSafe->isSelected())
		{
			mOrders["Destroy"]->enable();
		}
		else
		{
			mOrders["Destroy"]->disable();
		}
	}

	return true;
}
