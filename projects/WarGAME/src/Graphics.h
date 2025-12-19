#pragma once

#include "Dependencies.h"
#include "Debug.h"
#include "Input.h"
#include "Object.h"

class Graphics :
	public Ogre::Singleton<Graphics>,
	public Ogre::FrameListener,
	public Ogre::WindowEventListener
{
public:
	Input mInput;

	bool init();

	void mainLoop();

	void quit()
	{
		mRender = false;
	}

	void shutdown();

	Ogre::Camera* createCamera(const std::string& name) const
	{
		return mSceneManager->createCamera(name);
	}

	Ogre::Viewport* getViewport() const
	{
		return mViewport;
	}

	Ogre::RaySceneQuery* getRaySceneQuery() const
	{
		return mRaySceneQuery;
	}

	Ogre::Entity* createEntity(const std::string& name, const std::string& mesh) const;

	Ogre::ParticleSystem* createParticleSystem(const std::string& name, const std::string& script) const;

	Ogre::SceneNode* createSceneNode() const;

	void destroy(Ogre::Entity* entity) const;

	void destroy(Ogre::ParticleSystem* particleSystem) const;

	void destroy(Ogre::SceneNode* sceneNode) const;

	Object* Graphics::raycastObject(const Ogre::Ray& ray) const;

	Ogre::RenderWindow* getRenderWindow() const
	{
		return mRenderWindow;
	}

	Ogre::SceneManager* getSceneManager() const
	{
		return mSceneManager;
	}

	Ogre::Camera* getCamera() const
	{
		return mCamera;
	}

	Ogre::Ray getCameraToViewportRay(int x, int y, int width, int height) const
	{
		return mCamera->getCameraToViewportRay((float)x / (float)width, (float)y / (float)height);
	}

	void setSelectionVisible(bool visible)
	{
		mBoxSelectionNode->setVisible(visible);
	}

	/// Coordinates are unified.
	/// (0.0, 0.0) is the top-left corner of the screen.
	/// (1.0, 1.0) is the bottom-right corner of the screen.
	void setSelectionCorners(float left, float top, float right, float bottom)
	{
		mBoxSelectionRectangle->setCorners(left, top, right, bottom);
	}

	void destroy(Ogre::Material* material)
	{
		Ogre::MaterialManager::getSingleton().remove(material->getName());
	}

	const Ogre::SceneQueryResult& raycast(const Ogre::PlaneBoundedVolumeList& volumes) const
	{
		mPlaneQuery->setVolumes(volumes);
		return mPlaneQuery->execute();
	}

	void createStructureCursor(const std::string& name);
	void setStructureCursorPosition(const Ogre::Vector3& position);
	void setStructureCursorVisible(bool visible);

protected:

	bool					mRender;

	// Ogre
	Ogre::Root*								mRoot;
	Ogre::RenderWindow*						mRenderWindow;
	Ogre::SceneManager*						mSceneManager;
	Ogre::Camera*							mCamera;
	Ogre::Viewport*							mViewport;
	Ogre::RaySceneQuery*					mRaySceneQuery;
	Ogre::PlaneBoundedVolumeListSceneQuery* mPlaneQuery;
	Ogre::Rectangle2D*						mBoxSelectionRectangle;
	Ogre::SceneNode*						mBoxSelectionNode;

	Ogre::Entity*							mEntity;
	Ogre::Material*							mMaterial;
	Ogre::SceneNode*						mNode;

	// Ogre
	bool frameStarted(const Ogre::FrameEvent& evt);
	bool frameEnded(const Ogre::FrameEvent& evt);

	void windowMoved(Ogre::RenderWindow* rw);
	void windowResized(Ogre::RenderWindow* rw);
	void windowClosed(Ogre::RenderWindow* rw);
	void windowFocusChange(Ogre::RenderWindow* rw);
};
