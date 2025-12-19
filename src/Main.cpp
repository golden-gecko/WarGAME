#include "PCH.hpp"

#include "Application.hpp"

int main()
{
    std::auto_ptr<Application> application(new Application("Plugins.cfg", "Ogre.cfg", "Ogre.log"));

    application->startRendering();
    application->shutdown();

    return 0;
}
