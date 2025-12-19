#include "Dependencies.h"
#include "Game.h"
#include "GUI.h"
#include "Input.h"
#include "Terrain.h"
#include "Unit.h"

Input::Input() : mInputManager(NULL), mKeyboard(NULL), mMouse(NULL),
	mSelectionButton(OIS::MB_Left), mOrderButton(OIS::MB_Right),
	mSelectionButtonDown(false), mDrag(false)
{
}

bool Input::init(Ogre::RenderWindow* window)
{
	// Get render window handle.
	size_t handle;
	window->getCustomAttribute("WINDOW", &handle);

	// Create input manager.
	OIS::ParamList params;
	params.insert(std::make_pair("WINDOW", Ogre::StringConverter::toString(handle)));
//	params.insert(std::make_pair("w32_mouse", "DISCL_FOREGROUND"));
//	params.insert(std::make_pair("w32_mouse", "DISCL_NONEXCLUSIVE"));

	mInputManager = OIS::InputManager::createInputSystem(params);

	ASSERT(mInputManager);

	// Create keyboard and mouse objects.
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject(OIS::OISKeyboard, true));
	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject(OIS::OISMouse, true));

	ASSERT(mKeyboard);
	ASSERT(mMouse);

	mKeyboard->setEventCallback(this);
	mMouse->setEventCallback(this);

	return true;
}

void Input::capture()
{
	ASSERT(mKeyboard);
	ASSERT(mMouse);

	mKeyboard->capture();
	mMouse->capture();
}

void Input::shutdown()
{
	// Destroy keyboard and mouse objects.
	mInputManager->destroyInputObject(mKeyboard);
	mInputManager->destroyInputObject(mMouse);

	// Destroy input manager.
	OIS::InputManager::destroyInputSystem(mInputManager);
}

bool Input::keyPressed(const OIS::KeyEvent& arg)
{
	CEGUI::System::getSingleton().injectKeyDown(arg.key);
	CEGUI::System::getSingleton().injectChar(arg.text);

	//* Temp
	enum Keys
	{
		K_PAUSE = 0,
		K_QUIT,
		K_MENU,
		K_MOVE_CAMERA_FORWARD,
		K_MOVE_CAMERA_BACKWARD,
		K_MOVE_CAMERA_LEFT,
		K_MOVE_CAMERA_RIGHT,
		K_ROTATE_CAMERA_UP,
		K_ROTATE_CAMERA_DOWN,
		K_ROTATE_CAMERA_LEFT,
		K_ROTATE_CAMERA_RIGHT,
		K_SELECT_GROUP_1,
		K_SELECT_GROUP_2,
		K_SELECT_GROUP_3,
		K_SELECT_GROUP_4,
		K_SELECT_GROUP_5,
		K_SELECT_GROUP_6,
		K_SELECT_GROUP_7,
		K_SELECT_GROUP_8,
		K_SELECT_GROUP_9,
		K_SELECT_GROUP_0,
		K_GAME_SPEED_DECREASE,
		K_GAME_SPEED_INCREASE,
		K_GAME_SCREENSHOOT
	};

	unsigned int mActionKeys[K_GAME_SCREENSHOOT][2] = { OIS::KC_UNASSIGNED };

	mActionKeys[K_PAUSE][0] = OIS::KC_SPACE;
	mActionKeys[K_PAUSE][1] = OIS::KC_PAUSE;
	mActionKeys[K_QUIT][0] = OIS::KC_ESCAPE;
	mActionKeys[K_SELECT_GROUP_1][0] = OIS::KC_1;
	mActionKeys[K_SELECT_GROUP_2][0] = OIS::KC_2;
	mActionKeys[K_SELECT_GROUP_3][0] = OIS::KC_3;
	mActionKeys[K_SELECT_GROUP_4][0] = OIS::KC_4;
	mActionKeys[K_SELECT_GROUP_0][0] = OIS::KC_0;
	mActionKeys[K_GAME_SPEED_DECREASE][0] = OIS::KC_SUBTRACT;
	mActionKeys[K_GAME_SPEED_INCREASE][0] = OIS::KC_ADD;
	//*// Temp

	std::string mActionNames[K_GAME_SCREENSHOOT] = { "" };

	mActionNames[K_PAUSE] = "Pause / Unpause";
	mActionNames[K_QUIT] = "Quit Game";
	mActionNames[K_SELECT_GROUP_1] = "Select Group 1";
	mActionNames[K_SELECT_GROUP_2] = "Select Group 2";
	mActionNames[K_SELECT_GROUP_3] = "Select Group 3";
	mActionNames[K_SELECT_GROUP_4] = "Select Group 4";
	mActionNames[K_SELECT_GROUP_0] = "Select Group 0";
	mActionNames[K_GAME_SPEED_DECREASE] = "Decrease Game Speed";
	mActionNames[K_GAME_SPEED_INCREASE] = "Increase Game Speed";

	if (arg.key == mActionKeys[K_PAUSE][0] || arg.key == mActionKeys[K_PAUSE][1])
	{
		Game::getSingleton().pause();
	}
	else if (arg.key == mActionKeys[K_QUIT][0] || arg.key == mActionKeys[K_QUIT][1])
	{
		Graphics::getSingleton().quit();
	}
	else if (arg.key == mActionKeys[K_GAME_SPEED_INCREASE][0] || arg.key == mActionKeys[K_GAME_SPEED_INCREASE][1])
	{
		Game::getSingleton().increaseGameSpeed();
	}
	else if (arg.key == mActionKeys[K_GAME_SPEED_DECREASE][0] || arg.key == mActionKeys[K_GAME_SPEED_DECREASE][1])
	{
		Game::getSingleton().decreaseGameSpeed();
	}
	else if (arg.key == mActionKeys[K_GAME_SPEED_DECREASE][0] || arg.key == mActionKeys[K_GAME_SPEED_DECREASE][1])
	{
	}

	switch (arg.key)
	{
		case OIS::KC_1:
			Game::getSingleton().getActivePlayer()->selectGroup(
				1, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_2:
			Game::getSingleton().getActivePlayer()->selectGroup(
				2, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_3:
			Game::getSingleton().getActivePlayer()->selectGroup(
				3, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_4:
			Game::getSingleton().getActivePlayer()->selectGroup(
				4, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_5:
			Game::getSingleton().getActivePlayer()->selectGroup(
				5, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_6:
			Game::getSingleton().getActivePlayer()->selectGroup(
				6, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_7:
			Game::getSingleton().getActivePlayer()->selectGroup(
				7, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_8:
			Game::getSingleton().getActivePlayer()->selectGroup(
				8, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_9:
			Game::getSingleton().getActivePlayer()->selectGroup(
				9, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_0:
			Game::getSingleton().getActivePlayer()->selectGroup(
				0, mKeyboard->isModifierDown(OIS::Keyboard::Ctrl));
			break;

		case OIS::KC_I:
			GUI::getSingleton().toggleVisible();
			break;

		case OIS::KC_GRAVE:
			GUI::getSingleton().toggleEditor();
			break;

	}

	return true;
}

bool Input::keyReleased(const OIS::KeyEvent& arg)
{
	CEGUI::System::getSingleton().injectKeyUp(arg.key);

	return true;
}

bool Input::mouseMoved(const OIS::MouseEvent& arg)
{
	CEGUI::System::getSingleton().injectMouseMove((float)arg.state.X.rel, (float)arg.state.Y.rel);

	if (isKeyDown(OIS::KC_F))
	{
		Graphics::getSingleton().getCamera()->yaw(
			Ogre::Degree(arg.state.X.rel * -0.2f));
		Graphics::getSingleton().getCamera()->pitch(
			Ogre::Degree(arg.state.Y.rel * -0.2f));
	}
	else
	{
		if (mSelectionButtonDown)
		{
			mDragEnd = CEGUI::MouseCursor::getSingleton().getPosition();
			CEGUI::Size size = CEGUI::System::getSingleton().getRenderer()->getSize();

			mDragEnd.d_x /= size.d_width;
			mDragEnd.d_y /= size.d_height;

			if (Ogre::Math::Abs(mDragStart.d_x - mDragEnd.d_x) > 0.01f &&  Ogre::Math::Abs(mDragStart.d_y - mDragEnd.d_y) > 0.01f)
			{
				mDrag = true;

				Graphics::getSingleton().setSelectionCorners(
					mDragStart.d_x * 2.0f - 1.0f, (1.0f - mDragStart.d_y) * 2.0f - 1.0f,
					mDragEnd.d_x * 2.0f - 1.0f, (1.0f - mDragEnd.d_y) * 2.0f - 1.0f);

				Graphics::getSingleton().setSelectionVisible(true);
			}
			else
			{
				Graphics::getSingleton().setSelectionVisible(false);
			}
		}
		else
		{
			Graphics::getSingleton().setSelectionVisible(false);
		}
	}

	return true;
}

bool Input::mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MouseButton(id));

	if (GUI::getSingleton().isMouseOver() == false)
	{
		if (id == mSelectionButton)
		{
			mSelectionButtonDown = true;

			mDragStart = CEGUI::MouseCursor::getSingleton().getPosition();
			CEGUI::Size size = CEGUI::System::getSingleton().getRenderer()->getSize();

			mDragStart.d_x /= size.d_width;
			mDragStart.d_y /= size.d_height;
		}
	}

	return true;
}

bool Input::mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
{
	CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MouseButton(id));

	if (id == mSelectionButton)
	{
		mSelectionButtonDown = false;

		if (mDrag)
		{
			mDrag = false;

			Graphics::getSingleton().setSelectionVisible(false);

			float top = 0.0f;
			float bottom = 0.0f;
			float right = 0.0f;
			float left = 0.0f;

			float mLeftButtonDownScreenX = mDragStart.d_x;
			float mLeftButtonDownScreenY = mDragStart.d_y;

			float mLastMouseScreenX = mDragEnd.d_x;
			float mLastMouseScreenY = mDragEnd.d_y;

			if(mLeftButtonDownScreenX < mLastMouseScreenX)
			{
				left = mLeftButtonDownScreenX;
				right = mLastMouseScreenX;
			}
			else
			{
				left = mLastMouseScreenX;
				right = mLeftButtonDownScreenX;
			}
			if(mLeftButtonDownScreenY < mLastMouseScreenY)
			{
				top = mLeftButtonDownScreenY;
				bottom = mLastMouseScreenY;
			}
			else
			{
				top = mLastMouseScreenY;
				bottom = mLeftButtonDownScreenY;
			}

			// cast a ray into the screen for each of the four points
			// Convert screen positions into rays in world space
			Ogre::Camera* mCamera = Graphics::getSingleton().getCamera();

			Ogre::Ray topLeft = mCamera->getCameraToViewportRay(left, top);
			Ogre::Ray topRight = mCamera->getCameraToViewportRay(right, top);
			Ogre::Ray bottomLeft = mCamera->getCameraToViewportRay(left, bottom);
			Ogre::Ray bottomRight = mCamera->getCameraToViewportRay(right, bottom);

			Ogre::PlaneBoundedVolume vol;
			vol.planes.push_back(Ogre::Plane(topLeft.getOrigin(), topRight.getOrigin(), bottomLeft.getOrigin())); //front plane
			vol.planes.push_back(Ogre::Plane(topLeft.getPoint(1000), topLeft.getOrigin(), bottomLeft.getPoint(1000)));   // left plane
			vol.planes.push_back(Ogre::Plane(topRight.getPoint(1000), topLeft.getPoint(1000), bottomLeft.getPoint(1000)));   // back plane
			vol.planes.push_back(Ogre::Plane(topRight.getOrigin(), topRight.getPoint(1000), bottomRight.getPoint(1000)));   // right plane
			vol.planes.push_back(Ogre::Plane(topLeft.getPoint(1000), topRight.getPoint(1000), topLeft.getOrigin()));   // top plane
			vol.planes.push_back(Ogre::Plane(bottomLeft.getPoint(1000), bottomLeft.getOrigin(), bottomRight.getPoint(1000)));   // bottom plane

			Ogre::PlaneBoundedVolumeList volumes;
			volumes.push_back(vol); 

			const Ogre::SceneQueryResult& r = Graphics::getSingleton().raycast(volumes);

		//	if (r.movables.size())
			{
				if (mKeyboard->isModifierDown(OIS::Keyboard::Shift) == false)
				{
					Game::getSingleton().getActivePlayer()->selectAll(false);
				}

				for (Ogre::SceneQueryResultMovableList::const_iterator i = r.movables.begin(); i != r.movables.end(); i++)
				{
					const Ogre::Any& a = (*i)->getUserAny();

					// TODO: make it better.
					if (a.isEmpty() == false)
					{
						if (a.getType() == typeid(Object*))
						{
							if (Object* object = Ogre::any_cast<Object*>(a))
							{
								if (Unit* unit = dynamic_cast<Unit*>(object))
								{
									Game::getSingleton().getActivePlayer()->selectObject(object, true);
								}
							}
						}
					}
				}
			}
		}
		else if (GUI::getSingleton().isMouseOver() == false)
		{
			Ogre::Ray ray = Graphics::getSingleton().getCamera()->getCameraToViewportRay(
				CEGUI::MouseCursor::getSingleton().getPosition().d_x / CEGUI::System::getSingleton().getRenderer()->getWidth(),
				CEGUI::MouseCursor::getSingleton().getPosition().d_y / CEGUI::System::getSingleton().getRenderer()->getHeight());

			Object* object = Graphics::getSingleton().raycastObject(ray);
			Unit* unit = dynamic_cast<Unit*>(object);
			Ogre::Vector3 pos = Terrain::getSingleton().getPosition(ray);

			switch (GUI::getSingleton().getLastOrder())
			{
				case OT_NONE:
				{
					Ogre::Ray ray = Graphics::getSingleton().getCamera()->getCameraToViewportRay(
					CEGUI::MouseCursor::getSingleton().getPosition().d_x / CEGUI::System::getSingleton().getRenderer()->getWidth(),
					CEGUI::MouseCursor::getSingleton().getPosition().d_y / CEGUI::System::getSingleton().getRenderer()->getHeight());

					if (Object* o = Graphics::getSingleton().raycastObject(ray))
					{
						if (Unit* u = dynamic_cast<Unit*>(o))
						{
							if (u->isAlly(Game::getSingleton().getActivePlayer()))
							{
								Game::getSingleton().getActivePlayer()->selectObject(
									o, mKeyboard->isModifierDown(OIS::Keyboard::Shift));
							}
						}
					}
					else if (mKeyboard->isModifierDown(OIS::Keyboard::Shift) == false)
					{
						Game::getSingleton().getActivePlayer()->selectAll(false);
					}

					break;
				}

				case OT_ATTACK:
				{
					if (object)
					{
						Game::getSingleton().getActivePlayer()->orderSelected(
							Order(OT_ATTACK_OBJECT, object->getID()));
					}
					else
					{
						Game::getSingleton().getActivePlayer()->orderSelected(
							Order(OT_ATTACK_POSITION, pos));
					}

					break;
				}

				case OT_CAPTURE:
					if (object)
						Game::getSingleton().getActivePlayer()->orderSelected(
							Order(OT_CAPTURE, object->getID()));
					break;

				case OT_FOLLOW:
					if (object)
						Game::getSingleton().getActivePlayer()->orderSelected(
							Order(OT_FOLLOW, object->getID()));
					break;

				case OT_GUARD:
				{
					if (object)
					{
						Game::getSingleton().getActivePlayer()->orderSelected(
							Order(OT_GUARD_OBJECT, object->getID()));
					}
					else
					{
						Game::getSingleton().getActivePlayer()->orderSelected(
							Order(OT_GUARD_POSITION, pos));
					}

					break;
				}

				case OT_MOVE:
				{
					Game::getSingleton().getActivePlayer()->orderSelected(
						Order(OT_MOVE, pos));

					break;
				}

				case OT_LOOK:
				{
					if (object)
					{
						Game::getSingleton().getActivePlayer()->orderSelected(
							Order(OT_LOOK_AT_OBJECT, object->getID()));
					}
					else
					{
						Game::getSingleton().getActivePlayer()->orderSelected(
							Order(OT_LOOK_AT_POSITION, pos));
					}

					break;
				}
			}

			GUI::getSingleton().clearLastOrder();
		}
	}
	else if (id == mOrderButton)
	{
		Ogre::Ray ray = Graphics::getSingleton().getCamera()->getCameraToViewportRay(
			CEGUI::MouseCursor::getSingleton().getPosition().d_x / CEGUI::System::getSingleton().getRenderer()->getWidth(),
			CEGUI::MouseCursor::getSingleton().getPosition().d_y / CEGUI::System::getSingleton().getRenderer()->getHeight());

		Object* object = Graphics::getSingleton().raycastObject(ray);
		Unit* unit = dynamic_cast<Unit*>(object);
		Ogre::Vector3 pos = Terrain::getSingleton().getPosition(ray);

		if (object && unit && unit->isEnemy(Game::getSingleton().getActivePlayer()))
		{
			Order order(OT_ATTACK_OBJECT);
			order.setInt(object->getID());

			Game::getSingleton().getActivePlayer()->orderSelected(
				order, mKeyboard->isModifierDown(OIS::Keyboard::Shift));
		}
		else
		{
			Order order(OT_MOVE);
			order.setVector(pos);

			Game::getSingleton().getActivePlayer()->orderSelected(
				order, mKeyboard->isModifierDown(OIS::Keyboard::Shift));
		}
	}

	return true;
}
