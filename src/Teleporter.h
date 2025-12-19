
//------------------------------------------------------------------------------
// Teleporter.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Part.h"
#include "TeleporterDesc.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Teleporter: public Part {

		protected:

			Entity*			m_gateEnt;
			SceneNode*		m_gateNode;

			ParticleSystem*	m_portalPS;
			SceneNode*		m_portalNode;

			RenderTexture*	m_renderTexture;
			Camera*			m_camera;
			Viewport*		m_viewport;

			Teleporter*		m_connection;

		public:

			Teleporter(ObjectTemp* parent): Part(parent), m_gateEnt(NULL), m_portalPS(NULL), m_connection(NULL) {

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

			virtual void on() {

				m_gateEnt->getSubEntity(1)->setVisible(true);
				m_portalPS->getEmitter(0)->setEnabled(true);
			}

			virtual void off() {

				m_gateEnt->getSubEntity(1)->setVisible(false);
				m_portalPS->getEmitter(0)->setEnabled(false);
			}

			void connectTo(Teleporter* connection = NULL) {

				m_connection = (connection ? connection : this);
			}

			virtual void setDesc(PartDesc* partDesc) {

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

			virtual void setPosition(const Vector3& position) {

				m_gateNode->setPosition(position);
			}

			virtual void setOrientation(const Quaternion& q) {

				m_gateNode->setOrientation(q);
			}

			virtual string toString() {

				return "";
			}

			virtual bool update(float deltaTime) {

				return true;
			}

	};

};

//------------------------------------------------------------------------------
