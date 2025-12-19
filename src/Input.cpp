#include "PCH.hpp"

#include "Input.hpp"

Input::Input(Ogre::RenderWindow* renderWindow, Ogre::Camera* camera) : renderWindow(renderWindow), camera(camera), inputManager(NULL), keyboard(NULL), mouse(NULL)
{
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
 
    renderWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
 
    #if defined OIS_WIN32_PLATFORM
        pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
        pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE")));
        pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_FOREGROUND")));
        pl.insert(std::make_pair(std::string("w32_keyboard"), std::string("DISCL_NONEXCLUSIVE")));
    #elif defined OIS_LINUX_PLATFORM
        pl.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
        pl.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
        pl.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
        pl.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));
    #endif

    inputManager = OIS::InputManager::createInputSystem(pl);

    keyboard = static_cast<OIS::Keyboard*>(inputManager->createInputObject( OIS::OISKeyboard, true ));
    mouse = static_cast<OIS::Mouse*>(inputManager->createInputObject( OIS::OISMouse, true ));
 
    keyboard->setEventCallback(this);
    mouse->setEventCallback(this);

    // Set initial mouse clipping size.
    // windowResized(renderWindow);
}

bool Input::mouseMoved(const OIS::MouseEvent& arg)
{
    // Rotate camera.
    if (mouse->getMouseState().buttonDown(OIS::MouseButtonID::MB_Right))
    {
        camera->yaw(Ogre::Degree(-arg.state.X.rel * 0.1f));
        camera->pitch(Ogre::Degree(-arg.state.Y.rel * 0.1f));
    }

    return true;
}
