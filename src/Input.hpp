#pragma once

#include "PCH.hpp"

class Input : public OIS::KeyListener, public OIS::MouseListener
{
public:
    Input(Ogre::RenderWindow* renderWindow, Ogre::Camera* camera);

    virtual bool keyPressed(const OIS::KeyEvent& arg)
    {
        return true;
    }

    virtual bool keyReleased(const OIS::KeyEvent& arg)
    {
        return true;
    }

    virtual bool mouseMoved(const OIS::MouseEvent& arg);

    virtual bool mousePressed(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
    {
        return true;
    }

    virtual bool mouseReleased(const OIS::MouseEvent& arg, OIS::MouseButtonID id)
    {
        return true;
    }

    OIS::Keyboard* getKeyboard() const
    {
        return keyboard;
    }

    OIS::Mouse* getMouse() const
    {
        return mouse;
    }

    void capture()
    {
        keyboard->capture();
        mouse->capture();
    }

    virtual bool isKeyDown(OIS::KeyCode key) const
    {
        return keyboard->isKeyDown(key);
    }
protected:
    Ogre::RenderWindow* renderWindow;
    Ogre::Camera* camera;

    OIS::InputManager* inputManager;
    OIS::Keyboard* keyboard;
    OIS::Mouse* mouse;
};
