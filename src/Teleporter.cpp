
//------------------------------------------------------------------------------

#include "Main.h"

#include "Teleporter.h"

#include "Core.h"

//------------------------------------------------------------------------------

Teleporter::Teleporter(Object* parent): Part(parent), m_gateEnt(NULL), m_portalPS(NULL), m_connection(NULL) {

	m_name = "Teleporter #" + Core::getSingletonPtr()->getDataCounterStr();

	m_gateNode = Core::getSingletonPtr()->createSceneNode();
	m_portalNode = m_gateNode->createChildSceneNode(Vector3(0.1f, 0.0f, 0.0f));

	m_renderTexture =
		Core::getSingletonPtr()->getRoot()->getRenderSystem()->createRenderTexture(
			m_name, 512, 512, TEX_TYPE_2D, PF_R8G8B8);

	m_camera = Core::getSingletonPtr()->getSceneManager()->createCamera(m_name);
	m_camera->setNearClipDistance(0.5f);
	m_camera->setFarClipDistance(512.0f);
	m_camera->setDirection(Vector3::UNIT_X);

	m_viewport = m_renderTexture->addViewport(m_camera);
	m_viewport->setBackgroundColour(ColourValue(0.0f, 0.5f, 0.75f));
	m_viewport->setOverlaysEnabled(false);

	m_gateNode->attachObject(m_camera);

	m_connection = this;
}

//------------------------------------------------------------------------------

void Teleporter::setDesc(PartDesc* partDesc) {

	m_partDesc = partDesc;

	m_gateEnt = Core::getSingletonPtr()->createEntity(m_partDesc->isTeleporterDesc()->m_meshName);
	m_gateEnt->setCastShadows(m_partDesc->isTeleporterDesc()->m_castShadows);
	m_gateEnt->getSubEntity(1)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState(m_name);

	m_gateNode->attachObject(m_gateEnt);

	m_portalPS = Core::getSingletonPtr()->createParticleSystem(m_partDesc->isTeleporterDesc()->m_particleSystemName);

	m_portalNode->translate(0.0f, m_gateEnt->getBoundingBox().getCenter().y, m_gateEnt->getBoundingBox().getCenter().z);
	m_portalNode->attachObject(m_portalPS);

	m_camera->setPosition(m_gateEnt->getBoundingBox().getCenter());
}

//------------------------------------------------------------------------------
