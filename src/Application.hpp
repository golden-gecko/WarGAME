#pragma once

#include "PCH.hpp"

#include "Input.hpp"

class Application : public Ogre::Root, public Ogre::FrameListener, public Ogre::WindowEventListener
{
public:
    Application(const Ogre::String& pluginFileName, const Ogre::String& configFileName, const Ogre::String& logFileName);

    virtual bool frameStarted(const Ogre::FrameEvent& evt)
    {
        return isRunning;
    }

    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    virtual bool frameEnded(const Ogre::FrameEvent& evt)
    {
        return isRunning;
    }

    virtual void windowMoved(Ogre::RenderWindow* rw)
    {
    }

    virtual void windowResized(Ogre::RenderWindow* rw)
    {
    }

    virtual bool windowClosing(Ogre::RenderWindow* rw)
    {
        return true;
    }

    virtual void windowClosed(Ogre::RenderWindow* rw)
    {
        isRunning = false;
    }

    virtual void windowFocusChange(Ogre::RenderWindow* rw)
    {
    }
protected:
    /**
     * If set to false, application will quit.
     */
    bool isRunning;

    Ogre::RenderWindow* renderWindow;
    Ogre::SceneManager* sceneManager;
    Ogre::Camera* camera;
    Ogre::Viewport* viewport;
    Ogre::TerrainGlobalOptions* terrainOptions;
    Ogre::TerrainGroup* terrainGroup;

    Input* input;
};
