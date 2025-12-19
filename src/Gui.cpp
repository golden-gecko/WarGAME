
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Core.h"
#include "Game.h"
#include "Gui.h"

//------------------------------------------------------------------------------

bool Gui::mouseEnters(const CEGUI::EventArgs& e) {

	m_mouseOverGui = true;

	return true;
}

//------------------------------------------------------------------------------

bool Gui::mouseLeaves(const CEGUI::EventArgs& e) {

	m_mouseOverGui = false;

	return true;
}

//------------------------------------------------------------------------------

bool Gui::init() {

	// Setup Ogre CEGUI Renderer and CEGUI system.

	m_renderer = new CEGUI::OgreCEGUIRenderer(
		Core::getSingletonPtr()->getRenderWindow(),
		Ogre::RENDER_QUEUE_OVERLAY,
		false,
		3000,
		Core::getSingletonPtr()->getSceneManager());

	m_system = new CEGUI::System(m_renderer);


	// Load scheme and setup defaults.

	CEGUI::SchemeManager::getSingletonPtr()->loadScheme("TaharezLook.scheme");

	m_system->setDefaultMouseCursor("TaharezLook", "MouseArrow");
	m_system->setDefaultFont("BankGothicMediumBT");


	// Load layout and setup defaults.

	m_system->setGUISheet(
		CEGUI::WindowManager::getSingletonPtr()->loadWindowLayout("gui.xml"));


	// Subscribe events.

	CEGUI::WindowManager::WindowIterator itr = CEGUI::WindowManager::getSingletonPtr()->getIterator();

	itr.toStart();

	while (itr.isAtEnd() == false) {

		if (itr.getCurrentValue() != m_system->getGUISheet()) {

			itr.getCurrentValue()->subscribeEvent(
				CEGUI::Window::EventMouseEnters,
				CEGUI::Event::Subscriber(&Gui::mouseEnters, this));

			itr.getCurrentValue()->subscribeEvent(
				CEGUI::Window::EventMouseLeaves,
				CEGUI::Event::Subscriber(&Gui::mouseLeaves, this));
		}

		itr++;
	}

	return true;
}

//------------------------------------------------------------------------------
