
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "WarGAME.h"

#include "Object.h"
#include "PartWithMesh.h"
#include "Player.h"

//------------------------------------------------------------------------------

namespace WarGAME {

	class Core:	public Ogre::Singleton<Core>,
				public Ogre::FrameListener,
				public Ogre::KeyListener,
				public Ogre::MouseListener,
				public Ogre::MouseMotionListener {

		private:

			Ogre::Camera*			m_camera;
			Ogre::EventProcessor*	m_eventProcessor;
			Ogre::InputReader*		m_inputReader;
			Ogre::RenderWindow*		m_renderWindow;
			Ogre::Root*				m_root;
			Ogre::SceneManager*		m_sceneManager;
			Ogre::Viewport*			m_viewport;

		public:

			Ogre::Camera* getCamera() {
				
				return m_camera;
			}
			Ogre::Root* getRoot() {
				
				return m_root;
			}
			Ogre::RenderWindow* getRenderWindow() {
				
				return m_renderWindow;
			}
			Ogre::SceneManager* getSceneManager() {
				
				return m_sceneManager;
			}
			Ogre::Viewport* getViewport() {
				
				return m_viewport;
			}

		private:

			bool	m_notQuit;
			float	m_elapsedTime;
			bool	m_mouseButton[3];
			bool	m_keys[0xEE];

		private:

			Ogre::Vector2	m_mouse2DPos;
			Ogre::Vector3	m_mouse3DPos;

		public:

			Ogre::Vector2 getMouse2DPos() { return m_mouse2DPos; }
			Ogre::Vector3 getMouse3DPos() { return m_mouse3DPos; }

		private:

			virtual bool frameStarted(const Ogre::FrameEvent& evt);
			virtual void keyClicked(Ogre::KeyEvent* e) { }
			virtual void keyPressed(Ogre::KeyEvent* e);
			virtual void keyReleased(Ogre::KeyEvent* e);
			virtual void mouseClicked(Ogre::MouseEvent* e) { }
			virtual void mouseEntered(Ogre::MouseEvent* e) { }
			virtual void mouseExited(Ogre::MouseEvent* e) { }
			virtual void mousePressed(Ogre::MouseEvent* e);
			virtual void mouseReleased(Ogre::MouseEvent* e);
			virtual void mouseMoved(Ogre::MouseEvent* e);
			virtual void mouseDragged(Ogre::MouseEvent* e);

			CEGUI::MouseButton convertOgreButtonToCEGUI(int buttonID);

		public:

			list<Object*>	m_hovered;
			list<Object*>	m_selected;
			float			m_gameSpeed;
			Object*			m_activeObject;
			Player*			m_activePlayer;

			Object* ogreAnyToObject(Ogre::Any ogreAny) {

				if (ogreAny.getType() == typeid(PartWithMesh*))

					return Ogre::any_cast<PartWithMesh*>(ogreAny)->getParent();

				return NULL;
			}

			void select(Object* object) {

				object->setSelected(true);

				m_selected.push_back(object);
			}

			void deselect(Object* object) {

				object->setSelected(!object->getSelected());

				m_selected.remove(object);
			}

			void deselectAll() {

				for (list<Object*>::iterator itr = m_selected.begin(); itr != m_selected.end(); itr++)

					(*itr)->setSelected(false);

				m_selected.clear();
			}

		public:

			Core();
			~Core();

			float getElapsedTime() { return m_elapsedTime; }


			bool init();

			void run();

			void quit();

		private:

			DWORD m_dataCounter;

		public:

			WORD getDataCounter() {

				return m_dataCounter++;
			}

			string getDataCounterStr() {

				char getDataCounterStr[8];

				sprintf(getDataCounterStr, "%i", m_dataCounter++);

				return getDataCounterStr;
			}

		public:

			Ogre::Entity* createEntity(const string& meshName) {

				return m_sceneManager->createEntity(getDataCounterStr(), meshName);
			}

			Ogre::Entity* createEntity(const string& name, const string& meshName) {

				return m_sceneManager->createEntity(name, meshName);
			}

			Ogre::ManualObject* createManualObject() {

				return m_sceneManager->createManualObject(getDataCounterStr());
			}

			Ogre::ParticleSystem* createParticleSystem(string templateName) {

				return m_sceneManager->createParticleSystem(getDataCounterStr(), templateName);
			}

			Ogre::SceneNode* createSceneNode() {

				return m_sceneManager->getRootSceneNode()->createChildSceneNode(getDataCounterStr());
			}

			Ogre::SceneNode* createSceneNode(const string& name) {

				return m_sceneManager->getRootSceneNode()->createChildSceneNode(name);
			}

			void destroyEntity(Ogre::Entity* entity) {

				if (entity) m_sceneManager->destroyEntity(entity);
			}

			void destroyManualObject(Ogre::ManualObject* manualObject) {

				if (manualObject) m_sceneManager->destroyManualObject(manualObject);
			}

			void destroyParticleSystem(Ogre::ParticleSystem* particleSystem) {

				if (particleSystem) m_sceneManager->destroyParticleSystem(particleSystem);
			}

			void destroySceneNode(Ogre::SceneNode* sceneNode) {

				if (sceneNode) m_sceneManager->destroySceneNode(sceneNode->getName());
			}

			Ogre::RaySceneQueryResult whatWouldHit(const Ogre::Vector3& pos, const Ogre::Vector3& dir);

			Object* getNearestObjectAtDirection(Object* object, const Ogre::Vector3& dir) {

				/*
				Ogre::RaySceneQueryResult& result = whatWouldHit(object->getWorldCenter(), dir);

				Object* o = NULL;

				for (Ogre::RaySceneQueryResult::iterator itr = result.begin(); itr != result.end(); itr++)

					if ((itr->distance < 5.0f) && (itr->movable && itr->movable->getUserAny().isEmpty() == false))

						if (o = ogreAnyToObject(itr->movable->getUserAny()))
							
							if ((o != object) && (o->m_type != Object::OT_MISSILE))

								return o;
				*/

				return NULL;
			}

			float getTerrainHeight(float x, float z);

			Ogre::Vector3 getTerrainHeightVec(float x, float z) {

				return Ogre::Vector3(x, getTerrainHeight(x, z), z);
			}

			Ogre::Vector3 getTerrainHeightVec(const Ogre::Vector3& vector) {

				return Ogre::Vector3(
					vector.x,
					getTerrainHeight(vector.x, vector.z),
					vector.z);

			}

			string positionToStr(float x, float z);

			string positionToStr(const Ogre::Vector3& pos) {

				return positionToStr(pos.x, pos.z);
			}

	};
};

//------------------------------------------------------------------------------
