
//------------------------------------------------------------------------------
// Core.h
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------

#include "Main.h"

//------------------------------------------------------------------------------
// Core
//------------------------------------------------------------------------------

namespace WarGAME {

	class Core :	public Singleton<Core>,
					public FrameListener,
					public KeyListener,
					public MouseListener,
					public MouseMotionListener {

		private:

			Root*			m_root;
			RenderWindow*	m_renderWindow;
			SceneManager*	m_sceneManager;
			Camera*			m_camera;
			Viewport*		m_viewport;
			EventProcessor*	m_eventProcessor;
			InputReader*	m_inputReader;

		public:

			RenderWindow* getRenderWindow() { return m_renderWindow; }
			SceneManager* getSceneManager() { return m_sceneManager; }

		private:

			bool	m_notQuit;
			float	m_elapsedTime;
			bool	m_mouseButton[3];
			bool	m_keys[0xEE];

		private:

			Vector2	m_mouse2DPos;
			Vector3	m_mouse3DPos;

		public:

			Vector2 getMouse2DPos() { return m_mouse2DPos; }
			Vector3 getMouse3DPos() { return m_mouse3DPos; }

		private:

			virtual bool frameStarted(const FrameEvent& evt);
			virtual void keyClicked(KeyEvent* e) { }
			virtual void keyPressed(KeyEvent* e);
			virtual void keyReleased(KeyEvent* e);
			virtual void mouseClicked(MouseEvent* e) { }
			virtual void mouseEntered(MouseEvent* e) { }
			virtual void mouseExited(MouseEvent* e) { }
			virtual void mousePressed(MouseEvent* e);
			virtual void mouseReleased(MouseEvent* e);
			virtual void mouseMoved(MouseEvent* e);
			virtual void mouseDragged(MouseEvent* e);

			CEGUI::MouseButton convertOgreButtonToCEGUI(int buttonID);

		public:

			Object* m_objectUnderMouse;
			Object* m_lastSelectedObject;

			Object* ogreAnyToObject(Ogre::Any ogreAny);

		public:

			Core();
			~Core();

			Camera* getCamera() { return m_camera; }
			float getElapsedTime() { return m_elapsedTime; }


			bool init();

			void run();

			void quit();

		private:

			DWORD	m_dataCounter;

		public:

			WORD getDataCounter(){

				return m_dataCounter++;

			}

			string getDataCounterStr(){

				char getDataCounterStr[8];

				sprintf(getDataCounterStr, "%i", m_dataCounter++);

				return getDataCounterStr;

			}

		public:

			Entity* createEntity(string meshName){

				return m_sceneManager->createEntity(getDataCounterStr(), meshName);

			}

			ManualObject*	createManualObject(){

				return m_sceneManager->createManualObject(getDataCounterStr());

			}

			ParticleSystem* createParticleSystem(string templateName){

				return m_sceneManager->createParticleSystem(getDataCounterStr(), templateName);

			}

			SceneNode* createSceneNode(){

				return m_sceneManager->getRootSceneNode()->createChildSceneNode(getDataCounterStr());

			}

			void destroyEntity(Entity* entity){

				if (entity) m_sceneManager->destroyEntity(entity);

			}

			void destroyManualObject(ManualObject* manualObject){

				if (manualObject) m_sceneManager->destroyManualObject(manualObject);

			}

			void destroyParticleSystem(ParticleSystem* particleSystem){

				if (particleSystem) m_sceneManager->destroyParticleSystem(particleSystem);

			}

			void destroySceneNode(SceneNode* sceneNode){

				if (sceneNode) m_sceneManager->destroySceneNode(sceneNode->getName());

			}


			RaySceneQueryResult whatWouldHit(Vector3 pos, Vector3 dir);

			float getTerrainHeight(float x, float z);

			Vector3 getTerrainHeightVec(float x, float z){

				return Vector3(x, getTerrainHeight(x, z), z);

			}

			Vector3 getTerrainHeightVec(Vector3 vector){

				return Vector3(
					vector.x,
					getTerrainHeight(vector.x, vector.z),
					vector.z);


			}

			string positionToStr(float x, float z);

			string positionToStr(Vector3 pos){

				return positionToStr(pos.x, pos.z);

			}

	};

};

//------------------------------------------------------------------------------
