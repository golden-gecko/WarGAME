
//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "PartViewer.h"

#include "Core.h"
#include "Gui.h"

//------------------------------------------------------------------------------

bool PartViewer::list_SelectionChanged(const CEGUI::EventArgs& e) {

	if (m_list->getSelectedCount() && m_list->getFirstSelectedItem()->getUserData()) {

		m_text->setText(((Part*)(m_list->getFirstSelectedItem()->getUserData()))->toString());

		switch (((Part*)m_list->getFirstSelectedItem()->getUserData())->getType()) {

			case Part::PT_BODY:
			case Part::PT_SHIELD:
			case Part::PT_WEAPON:

				if (m_entity)
					
					m_sceneManager->destroyEntity(m_entity);

				m_entity = m_sceneManager->createEntity(
					"PartViewer/Entity",
					((PartWithMesh*)m_list->getFirstSelectedItem()->getUserData())->getPartWithMeshDesc()->getMeshName());

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

void PartViewer::init() {

	m_sceneManager = Core::getSingletonPtr()->getRoot()->createSceneManager(
		Ogre::ST_EXTERIOR_CLOSE, "PartViewer/SceneManager");

	m_camera = m_sceneManager->createCamera("PartViewer/Camera");
	m_camera->setPosition(32.0f, 16.0f, 32.0f);
	m_camera->lookAt(0.0f, 0.0f, 0.0f);
	m_camera->setNearClipDistance(0.5f);
	m_camera->setFarClipDistance(128.0f);

	Ogre::RenderTexture* ogreTexture =
		Core::getSingletonPtr()->getRoot()->getRenderSystem()->createRenderTexture(
			"PartViewer/RenderToTexure", 512, 512, Ogre::TEX_TYPE_2D, Ogre::PF_R8G8B8);

	m_viewport = ogreTexture->addViewport(m_camera);
	m_viewport->setClearEveryFrame(true);

	CEGUI::Texture* ceguiTexture =
		Gui::getSingletonPtr()->getRenderer()->createTexture(
			"PartViewer/RenderToTexure");

	CEGUI::Imageset* imageSet =
		CEGUI::ImagesetManager::getSingleton().createImageset(
			"PartViewer/Imageset", ceguiTexture);

	imageSet->defineImage("PartViewer/Image",
		CEGUI::Point(0.0f, 0.0f),
		CEGUI::Size(ceguiTexture->getWidth(), ceguiTexture->getHeight()),
		CEGUI::Point(0.0f, 0.0f));

	m_sceneNode = m_sceneManager->getRootSceneNode()->createChildSceneNode();

	//

	m_partViewer = (CEGUI::FrameWindow*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartViewer");
	m_list = (CEGUI::Listbox*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartViewer/List");
	m_text = (CEGUI::StaticText*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartViewer/Text");
	m_image = (CEGUI::StaticImage*)
		CEGUI::WindowManager::getSingletonPtr()->getWindow("PartViewer/Image");

	m_list->subscribeEvent(
		CEGUI::Listbox::EventSelectionChanged,
		CEGUI::Event::Subscriber(&PartViewer::list_SelectionChanged, this));

	m_partViewer->setCaptionColour(CEGUI::colour(1.0f, 1.0f, 1.0f));
	m_image->setImage(&imageSet->getImage("PartViewer/Image"));
}

//------------------------------------------------------------------------------
