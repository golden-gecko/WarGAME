
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartDescViewer.h"

#include "Core.h"
#include "Gui.h"

//------------------------------------------------------------------------------

bool PartDescViewer::list_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_list->getSelectedCount() && m_list->getFirstSelectedItem()->getUserData()) {

		m_text->setText(((PartDesc*)(m_list->getFirstSelectedItem()->getUserData()))->toString());

		switch (((PartDesc*)m_list->getFirstSelectedItem()->getUserData())->getType()) {

			case PartDesc::PDT_BODY_DESC:
			case PartDesc::PDT_SHIELD_DESC:
			case PartDesc::PDT_WEAPON_DESC:

				if (m_entity)
					
					m_sceneManager->destroyEntity(m_entity);

				m_entity = m_sceneManager->createEntity(
					"PartDescViewer/Entity",
					((PartWithMeshDesc*)m_list->getFirstSelectedItem()->getUserData())->getMeshName());

				m_sceneNode->attachObject(m_entity);
				m_sceneNode->scale(
					10.0f / m_entity->getBoundingRadius(),
					10.0f / m_entity->getBoundingRadius(),
					10.0f / m_entity->getBoundingRadius());

				break;

			default:

				if (m_entity) {

					m_sceneManager->destroyEntity(m_entity);
					m_entity = NULL;
				}

				break;
		}

	} else

		m_text->setText("no part desc selected");

	return true;
}

//------------------------------------------------------------------------------

void PartDescViewer::init() {

	m_sceneManager = Core::getSingletonPtr()->getRoot()->createSceneManager(
		Ogre::ST_EXTERIOR_CLOSE, "PartDescViewer/SceneManager");

	m_camera = m_sceneManager->createCamera("PartDescViewer/Camera");
	m_camera->setPosition(32.0f, 16.0f, 32.0f);
	m_camera->lookAt(0.0f, 0.0f, 0.0f);
	m_camera->setNearClipDistance(0.5f);
	m_camera->setFarClipDistance(128.0f);

	Ogre::RenderTexture* ogreTexture =
		Core::getSingletonPtr()->getRoot()->getRenderSystem()->createRenderTexture(
			"PartDescViewer/RenderToTexure", 512, 512, Ogre::TEX_TYPE_2D, Ogre::PF_R8G8B8);

	m_viewport = ogreTexture->addViewport(m_camera);
	m_viewport->setClearEveryFrame(true);

	CEGUI::Texture* ceguiTexture =
		Gui::getSingletonPtr()->getRenderer()->createTexture(
			"PartDescViewer/RenderToTexure");

	CEGUI::Imageset* imageSet =
		CEGUI::ImagesetManager::getSingleton().createImageset(
			"PartDescViewer/Imageset", ceguiTexture);

	imageSet->defineImage("PartDescViewer/Image",
		CEGUI::Point(0.0f, 0.0f),
		CEGUI::Size(ceguiTexture->getWidth(), ceguiTexture->getHeight()),
		CEGUI::Point(0.0f, 0.0f));

	m_sceneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();

	//

	m_partDescViewer = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartDescViewer");
	m_list = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartDescViewer/List");
	m_text = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartDescViewer/Text");
	m_image = (CEGUI::StaticImage*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartDescViewer/Image");

	m_list->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&PartDescViewer::list_SelectionChanged, this));

	m_partDescViewer->setCaptionColour(CEGUI::colour(1.0f, 1.0f, 1.0f));
	m_image->setImage(&imageSet->getImage("PartDescViewer/Image"));
}

//------------------------------------------------------------------------------
