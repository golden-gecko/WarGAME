#pragma once

#include "Dependencies.h"
#include "Debug.h"

class Input : public OIS::KeyListener, public OIS::MouseListener
{
public:
	Input();

	bool init(Ogre::RenderWindow* window);
	void capture();
	void shutdown();

	const OIS::MouseState& getMouseState() const
	{
		ASSERT(mMouse);

		return mMouse->getMouseState();
	}

	bool isKeyDown(OIS::KeyCode key) const
	{
		ASSERT(mKeyboard);

		return mKeyboard->isKeyDown(key);
	}

	bool isModifierDown(OIS::Keyboard::Modifier mod) const
	{
		ASSERT(mKeyboard);

		return mKeyboard->isModifierDown(mod);
	}
protected:
	OIS::InputManager*	mInputManager;
	OIS::Keyboard*		mKeyboard;
	OIS::Mouse*			mMouse;

	OIS::MouseButtonID	mSelectionButton;
	OIS::MouseButtonID	mOrderButton;
	bool				mSelectionButtonDown;
	bool				mDrag;
	CEGUI::Point		mDragStart;
	CEGUI::Point		mDragEnd;

	bool keyPressed(const OIS::KeyEvent& arg);
	bool keyReleased(const OIS::KeyEvent& arg);

	bool mouseMoved(const OIS::MouseEvent& arg);
	bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id);
};
