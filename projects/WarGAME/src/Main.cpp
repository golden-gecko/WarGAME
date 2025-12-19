#include "Dependencies.h"
#include "Debug.h"
#include "Game.h"
#include "Graphics.h"
#include "GUI.h"
#include "Main.h"
#include "ObjectManager.h"
#include "PlayerManager.h"
#include "TemplateManager.h"
#include "Terrain.h"
#include "Water.h"
/*
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
*/
int main()
{
	//*
	Game game;
	Graphics graphics;
	GUI gui;
	ObjectManager ObjectManager;
	PlayerManager playerManager;
	TemplateManager templateManager;
	Terrain terrain;
	Water water;

	try
	{
		INIT("WarGAME.debug.log", false);
		LOG("Session starts");
		LOG("Walk Speed - 1.5");
		LOG("Run Speed - 3.5");

		if (Graphics::getSingleton().init())
		{
			TemplateManager::getSingleton().init();

			if (GUI::getSingleton().init())
			{
				Terrain::getSingleton().init(Graphics::getSingleton().getSceneManager(), Graphics::getSingleton().getRaySceneQuery());
				Terrain::getSingleton().load("terrain.cfg");

				Water::getSingleton().init(Graphics::getSingleton().getSceneManager());
				Water::getSingleton().load("Ocean2_Cg");

				if (Game::getSingleton().init())
				{
					Game::getSingleton().load("quick.save");
					Graphics::getSingleton().mainLoop();
					Game::getSingleton().save("quick.save");
				}
			}
		}

		LOG("Session ends");
		SHUTDOWN();
	}
	catch (CEGUI::Exception e)
	{
		Graphics::getSingleton().shutdown();

		MessageBox(NULL, e.getMessage().c_str(), "CEGUI", MB_ICONERROR | MB_OK);
	}
	catch (Ogre::Exception e)
	{
		Graphics::getSingleton().shutdown();

		MessageBox(NULL, e.getDescription().c_str(), "Ogre3D", MB_ICONERROR | MB_OK);
	}
	catch (OIS::Exception e)
	{
		Graphics::getSingleton().shutdown();

		MessageBox(NULL, e.eText, "OIS", MB_ICONERROR | MB_OK);
	}
	catch (...)
	{
		Graphics::getSingleton().shutdown();

		MessageBox(NULL, "Error!", "WarGAME", MB_ICONERROR | MB_OK);
	}
	//*/

	return 0;
}
/*
class Ability
{
public:
	Ability() :
		mEnergyConsumed(5.0f), mRadius(10.0f), mDamage(5.0f), mHeal(0.0f),
		mCastTime(0.0f), mMaxCastTime(1.0f), mDuration(0.0f), mMaxDuration(1.5f),
		mRechargeTime(15.0f), mMaxRechargeTime(15.0f),
		mTimesUsed(0), mMaxTimesUsed(500)
	{
	}

	void use(const Ogre::Vector3& position)
	{
	}

	void update(float time)
	{
	}
protected:
	std::string mName;

	float mEnergyConsumed;
	float mRadius;
	float mDamage;
	float mHeal;

	float mCastTime;
	float mMaxCastTime;

	float mDuration;
	float mMaxDuration;

	float mRechargeTime;
	float mMaxRechargeTime;

	unsigned int mTimesUsed;
	unsigned int mMaxTimesUsed;
};


	/*if (b)
	{
		Ogre::MaterialPtr m = (Ogre::MaterialPtr)
			Ogre::MaterialManager::getSingleton().getByName("terrain");
		
		using namespace Ogre;

		// Manually loads an image and puts the contents in a manually created texture
		tex = TextureManager::getSingleton().createManual(
			"dynamic",
			"General",
			TEX_TYPE_2D,
			size, size, 5, PF_X8R8G8B8);

		/// Lock the buffer so we can write to it
		tex->getBuffer(0,0)->lock(HardwareBuffer::HBL_DISCARD);
		const PixelBox &pb = tex->getBuffer(0,0)->getCurrentLock();

		/// Update the contents of pb here
		/// Image data starts at pb.data and has format pb.format
		/// Here we assume data.format is PF_X8R8G8B8 so we can address pixels as uint32.
		uint32 *data = static_cast<uint32*>(pb.data);
		size_t height = pb.getHeight();
		size_t width = pb.getWidth();
		size_t pitch = pb.rowPitch; // Skip between rows of image
		for(size_t y=0; y<height; ++y)
		{
			for(size_t x=0; x<width; ++x)
			{
					// 0xRRGGBB -> fill the buffer with green pixels
					data[pitch*y + x] = 0x00AA00;
			}
		}

		/// Unlock the buffer again (frees it for use by the GPU)
		tex->getBuffer(0,0)->unlock();

	//	Ogre::TextureUnitState* tus = m->getTechnique(0)->getPass(0)->createTextureUnitState("dynamic");
	//	tus->setTextureFiltering(Ogre::FO_NONE, Ogre::FO_NONE, Ogre::FO_NONE);

		b = false;
	}
	//*/

	//{
		//if (current >= 0.2f)
		//{
			/*tex = Ogre::TextureManager::getSingleton().getByName("dynamic");

			tex->getBuffer(0, 0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

			const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();

			Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);

			for(size_t i = 0; i < pb.getHeight() * pb.getWidth(); ++i)
			{
			//	data[i] = 0x00AA00;
			}

			const std::map<unsigned int, Object*>& objects = ObjectManager::getSingleton().get();

			Ogre::Vector3 min, max, pos;

			for (std::map<unsigned int, Object*>::const_iterator i = objects.begin(); i != objects.end(); i++)
			{
				const Ogre::AxisAlignedBox& box = i->second->getBoundingBox();

				pos = i->second->getPosition() * size / 2500.0f;

				data[pb.rowPitch * (size_t)pos.z + (size_t)pos.x] = 0xAAAA00;

				/*
				min = box.getMinimum() * size / 2500.0f;
				max = box.getMaximum() * size / 2500.0f;

				for(size_t z = min.z; z < max.z; ++z)
				{
					for(size_t x = min.x; x < max.x; ++x)
					{
						data[pb.rowPitch * z + x] = 0xAAAA00;
					}
				}
				//*/
			//}

			/*tex->getBuffer(0, 0)->unlock();*/


/*
Ogre::Rectangle2D* rect;
bool inits = true;
int start_x = 0, start_y = 0;

bool mSelectionButtonDown = false;

	if (inits)
	{
		rect = new Ogre::Rectangle2D();
		
		inits = false;

		Ogre::AxisAlignedBox box;
		box.setInfinite();
		rect->setBoundingBox(box);
		rect->setMaterial("box_selection");

		mSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(rect);
	}

	if (mSelectionButtonDown)
	{
		if (abs(start_x - arg.state.X.abs) > 4 &&  abs(start_y - arg.state.Y.abs) > 4)
		{
			rect->setCorners(
				start_x / (float)arg.state.width * 2.0f - 1.0f,
				(1.0f - start_y / (float)arg.state.height) * 2.0f - 1.0f,
				arg.state.X.abs / (float)arg.state.width * 2.0f - 1.0f,
				(1.0f - arg.state.Y.abs / (float)arg.state.height) * 2.0f - 1.0f);

			rect->setVisible(true);
		}
		else
		{
			rect->setVisible(false);
		}
	}
	else
	{
		rect->setVisible(false);
	}
	//*/


	/*
	if (GUI::getSingleton().isMouseOver() == false)
	{
		Ogre::Camera* mCamera = Graphics::getSingleton().getCamera();

		mViewport->setCamera(mCamera);

		switch (id)
		{
			case OIS::MB_Left:
			{
				Ogre::Ray ray = mCamera->getCameraToViewportRay(
					(float)arg.state.X.abs / (float)arg.state.width,
					(float)arg.state.Y.abs / (float)arg.state.height);

				Object* o = Input::getSingleton().raycastObject(ray);

				if (o && o->isAlly(Game::getSingleton().getActivePlayer()))
				{
				//	Game::getSingleton().select(o,
				//		Input::getSingleton().getKeyboard()->isKeyDown(
				//		OIS::KC_LSHIFT) || Input::getSingleton().getKeyboard()->isKeyDown(OIS::KC_RSHIFT));
				}
				else
				{
				//	Game::getSingleton().selectAll(false);
				}

				break;
			}

			case OIS::MB_Right:
			{
				if (Input::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Ctrl))
				{
					Order o(OT_ATTACK_POSITION);

					o = Terrain::getSingleton().getPosition(
						mCamera->getCameraToViewportRay(
						(float)arg.state.X.abs / (float)arg.state.width,
						(float)arg.state.Y.abs / (float)arg.state.height));

				//	Game::getSingleton().order(o,
				//		Input::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Shift));
				}
				else if (Input::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Alt))
				{
					Order o(OT_LOOK);

					o = Terrain::getSingleton().getPosition(mCamera->getCameraToViewportRay(
						(float)arg.state.X.abs / (float)arg.state.width,
						(float)arg.state.Y.abs / (float)arg.state.height));

				//	Game::getSingleton().order(o,
				//		Input::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Shift));
				}
				else
				{
					Ogre::Ray ray = mCamera->getCameraToViewportRay(
						(float)arg.state.X.abs / (float)arg.state.width,
						(float)arg.state.Y.abs / (float)arg.state.height);

					Object* obj = Input::getSingleton().raycastObject(ray);

					if (obj && obj->isEnemy(Game::getSingleton().getActivePlayer()))
					{
						Order o(OT_ATTACK_OBJECT);

						o = obj->getID();

					//	Game::getSingleton().order(o,
					//		Input::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Shift));
					}
					else
					{
						Order o(OT_MOVE);

						o = Terrain::getSingleton().getPosition(ray);

					//	Game::getSingleton().order(o,
					//		Input::getSingleton().getKeyboard()->isModifierDown(OIS::Keyboard::Shift));
					}
				}

				break;
			}
		}

		start_x = arg.state.X.abs;
		start_y = arg.state.Y.abs;

		if (id == OIS::MB_Left)
		{
			mSelectionButtonDown = true;
		}
	}
	//*/


	/*
	if (id == OIS::MB_Left)
	{
		mSelectionButtonDown = false;

		rect->setVisible(false);
	}

	//*
	Ogre::Camera* mCamera = Graphics::getSingleton().getCamera();

	mViewport->setCamera(mCamera);

	if (id == OIS::MB_Left)
	{
		if (abs(start_x - arg.state.X.abs) > 9 &&  abs(start_y - arg.state.Y.abs) > 9)
		{
			float top = 0.0f;
			float bottom = 0.0f;
			float right = 0.0f;
			float left = 0.0f;

			float mLeftButtonDownScreenX = start_x / (float)arg.state.width;
			float mLeftButtonDownScreenY = start_y / (float)arg.state.height;

			float mLastMouseScreenX = (float)arg.state.X.abs / (float)arg.state.width;
			float mLastMouseScreenY = (float)arg.state.Y.abs / (float)arg.state.height;

			if(mLeftButtonDownScreenX < mLastMouseScreenX)
			{
				left = mLeftButtonDownScreenX;
				right = mLastMouseScreenX;
			}
			else
			{
				left = mLastMouseScreenX;
				right = mLeftButtonDownScreenX;
			}
			if(mLeftButtonDownScreenY < mLastMouseScreenY)
			{
				top = mLeftButtonDownScreenY;
				bottom = mLastMouseScreenY;
			}
			else
			{
				top = mLastMouseScreenY;
				bottom = mLeftButtonDownScreenY;
			}

			// cast a ray into the screen for each of the four points
			// Convert screen positions into rays in world space
			Ogre::Ray topLeft = mCamera->getCameraToViewportRay(left, top);
			Ogre::Ray topRight = mCamera->getCameraToViewportRay(right, top);
			Ogre::Ray bottomLeft = mCamera->getCameraToViewportRay(left, bottom);
			Ogre::Ray bottomRight = mCamera->getCameraToViewportRay(right, bottom);

			Ogre::PlaneBoundedVolume vol;
			vol.planes.push_back(Ogre::Plane(topLeft.getOrigin(), topRight.getOrigin(), bottomLeft.getOrigin())); //front plane
			vol.planes.push_back(Ogre::Plane(topLeft.getPoint(1000), topLeft.getOrigin(), bottomLeft.getPoint(1000)));   // left plane
			vol.planes.push_back(Ogre::Plane(topRight.getPoint(1000), topLeft.getPoint(1000), bottomLeft.getPoint(1000)));   // back plane
			vol.planes.push_back(Ogre::Plane(topRight.getOrigin(), topRight.getPoint(1000), bottomRight.getPoint(1000)));   // right plane
			vol.planes.push_back(Ogre::Plane(topLeft.getPoint(1000), topRight.getPoint(1000), topLeft.getOrigin()));   // top plane
			vol.planes.push_back(Ogre::Plane(bottomLeft.getPoint(1000), bottomLeft.getOrigin(), bottomRight.getPoint(1000)));   // bottom plane

			Ogre::PlaneBoundedVolumeList volumes;
			volumes.push_back(vol); 

			Ogre::PlaneBoundedVolumeListSceneQuery* q = mSceneManager->createPlaneBoundedVolumeQuery(volumes);

			Ogre::SceneQueryResult& r = q->execute();

			//Game::getSingleton().selectAll(false);

			for (Ogre::SceneQueryResultMovableList::iterator i = r.movables.begin(); i != r.movables.end(); i++)
			{
				const Ogre::Any& a = (*i)->getUserAny();

				// TODO: make it better.

				if (a.isEmpty() == false)
				{
					if (a.getType() == typeid(Object*))
					{
						if ((Ogre::any_cast<Object*>(a))->getPlayer() == Game::getSingleton().getActivePlayer())
						{
						//	Game::getSingleton().select(Ogre::any_cast<Object*>(a), true);
						}
					}
				}
			}

			mSceneManager->destroyQuery(q);

			rect->setVisible(false);
		}
	}
	//*/


/*
class Object
{
public:
	Object(const std::string& name, const std::string& mesh,
		const Ogre::Vector3& position);

	virtual ~Object();

	void setName(const std::string& name)
	{
		mName = name;
	}

protected:

	std::string mName;

public:

	virtual void order(const Order& order, bool quene = true)
	{
		if (quene == false)
		{
			mOrders.clear();
		}

		mOrders.push_back(order);
	}

	// Heals object.
	// @sender Object which gives health.
	// @return Returs true if object is at full health, otherwise returns false.
	virtual bool onHealth(unsigned int sender, float health)
	{
		mHealth += health;
		mHealthTaken += health;

		if (mHealth < mMaxHealth)
		{
			return false;
		}

		mHealth = mMaxHealth;

		return true;
	}

	// Damages object.
	// @sender Object which gives damage.
	// @return Returs true if object was destroyed (health below or equal 0), otherwise returns false.
	virtual bool onDamage(unsigned int sender, float damage)
	{
		mHealth -= damage;
		mDamageTaken += damage;

		if (mHealth > 0.0f)
		{
			return false;
		}

		return true;
	}

	virtual void update(float time);

	virtual Ogre::Vector3 getDirection() const
	{
		return mSceneNode->getOrientation() * mDirectionVector;
	}

	unsigned int getID() const
	{
		return mID;
	}

	Player* getPlayer() const
	{
		return mPlayer;
	}

	virtual const Ogre::Vector3& getPosition() const
	{
		return mSceneNode->getPosition();
	}

	virtual bool getSelected() const
	{
		return mSceneNode->getShowBoundingBox();
	}

	unsigned int getType() const
	{
		return mType;
	}

	virtual void setDirection(const Ogre::Vector3& direction)
	{
		mSceneNode->setDirection(direction, Ogre::Node::TS_WORLD, mDirectionVector);
	}

	virtual void setPosition(const Ogre::Vector3& position)
	{
		mSceneNode->setPosition(position);
	}

	virtual Ogre::Vector3 getSize() const
	{
		return mEntity->getBoundingBox().getMaximum() - mEntity->getBoundingBox().getMinimum();
	//	return mEntity->getBoundingBox().getSize();	
	}

	virtual void setScale(const Ogre::Vector3& scale)
	{
		mSceneNode->setScale(scale);
	}

	virtual void setScale(float scale)
	{
		mSceneNode->setScale(scale, scale, scale);
	}

	virtual void setScale(float x, float y, float z)
	{
		mSceneNode->setScale(x, y, z);
	}

	virtual void setSelected(bool selected)
	{
		mSceneNode->showBoundingBox(selected);
	}

	virtual Ogre::Vector3 getCenter() const
	{
		return mEntity->getWorldBoundingBox().getCenter();
	}

	virtual void setHealth(float health)
	{
		mHealth = health;
	}

	float getHealth() const
	{
		return mHealth;
	}

	float getMaxHealth() const
	{
		return mMaxHealth;
	}

	const std::string& getName() const
	{
		return mEntity->getName();
	}

	virtual std::string toString() const
	{
		return
			"\nName     " + getName() +
			"\nHP       " + Ogre::StringConverter::toString(mHealth, 0, 0, ' ', std::ios::fixed) + "/" + Ogre::StringConverter::toString(mMaxHealth, 0, 0, ' ', std::ios::fixed) +
			"\nHits     " + Ogre::StringConverter::toString(mHits) +
			"\nTaken    " + Ogre::StringConverter::toString(mDamageTaken) +
			"\nOrders   " + Ogre::StringConverter::toString(mOrders.size()) +
			"\nPosition " + Ogre::StringConverter::toString(getPosition()) +
			"\nTile     " + Ogre::StringConverter::toString((unsigned int)getPosition().x * 512 / 2500) + " " + Ogre::StringConverter::toString((unsigned int)getPosition().z * 512 / 2500);

	}

	virtual void setDirectionVector(const Ogre::Vector3& vector)
	{
		mDirectionVector = vector;
	}

	virtual void setPlayer(Player* player)
	{
		mPlayer = player;
	}

	bool isEnemy(Player* player) const
	{
		return mPlayer != player;
	}

	bool isAlly(Player* player) const
	{
		return mPlayer == player;
	}

	virtual void onShoot(float damage, bool hit, bool destroyed)
	{
	}

	/// Returns true, if objects was destroyed with this hit.
	virtual bool onHit(float damage);

	virtual void onMove(const Ogre::Vector3& move, bool blocked = false)
	{
	}

	float getMaxRange() const
	{
		return mMaxRange;
	}

	virtual const Ogre::AxisAlignedBox& getBoundingBox() const
	{
		return mEntity->getWorldBoundingBox();
	}

protected:

	const unsigned int	mType;
	const unsigned int	mID;

	unsigned int		mState;
	std::list<Order>	mOrders;

	float				mHealth;
	float				mMaxHealth;
	float				mHealthTaken;
	float				mDamageTaken;
	unsigned int		mHits;
	float				mMaxRange;

	Ogre::Vector3		mDirectionVector;

	Player*				mPlayer;
	Ogre::Entity*		mEntity;
	Ogre::SceneNode*	mSceneNode;

	Object(unsigned int type, unsigned int id);

};
/*
class Object
{
public:
	Object();
	virtual ~Object() = 0;
	virtual void update(float time) = 0;
	virtual void toString() = 0;
protected:
	const unsigned int		mID;
	const unsigned int		mType;
	Ogre::SceneNode*		mSceneNode;
};

class Simple : public Object
{
public:
	Simple();
	~Simple();
	update(float time);
	void toString();
	virtual bool onHit();
protected:
	float					mHealth;
	Ogre::Entity*			mEntity;
};

class Complex : public Complex
{
public:
	Complex();
	~Complex();
	update(float time);
	void toString();
protected:
	unsigned int			mState;
	float					mMaxHealth;
	float					mRange;
	float					mMaxRange;
	Player*					mPlayer;
	std::vector<Orders>		mOrders;
};

class Structure : public Complex
{
public:
	Structute();
	~Structute();
	update(float time);
	void toString();
protected:

};

class Unit : public Complex
{
public:
	Unit();
	~Unit();
	update(float time);
	void toString();
	virtual void onShoot(unsigned int target, bool hit, bool kill);
protected:
	unsigned int		mMoveTarget;
	Ogre::Vector3		mMoveDestination;
	unsigned int		mAttackTarget;
	Ogre::Vector3		mAttackDestination;
};
*/
	/*
	Ogre::BillboardSet* trees = Graphics::getSingleton().getSceneManager()->createBillboardSet("trees", 10);
	trees->setMaterialName("palmtree_board");
	trees->setSortingEnabled(true);
	trees->setBillboardType(Ogre::BBT_ORIENTED_COMMON);
	trees->setCommonDirection(Ogre::Vector3::UNIT_Y);

	for (unsigned int z = 500; z < 1500; z += 10)
	{
		for (unsigned int x = 500; x < 1500; x += 10)
		{
			Ogre::Vector3 pos = Terrain::getSingleton().getPosition(
				x + Ogre::Math::RangeRandom(0, 10), z + Ogre::Math::RangeRandom(0, 10));

			float dim(Ogre::Math::RangeRandom(8, 12));

			pos.y += dim * 0.5f;

			trees->createBillboard(pos)->setDimensions(dim, dim);
		}
	}

	Graphics::getSingleton().getSceneManager()->getRootSceneNode()->attachObject(trees);
	*/

/*

		case OS_ATTACKING:
		{
			mAnimation->addTime(time);

			if (Object* object = ObjectManager::getSingleton().get(mAttackTarget))
			{
				if (getPosition().distance(object->getPosition()) > 3.0f)
				{
					Ogre::Vector3 direction = mMoveTarget - getPosition();

					direction.y = 0.0f;
					direction.normalise();

					setDirection(direction);

					Game::getSingleton().message(Message(MT_MOVE, mID, direction * mSpeed * time));
				}
				else
				{
					if (mCurrentAttackDuration < mAttackDuration)
					{
						mCurrentAttackDuration += time;
					}
					else
					{
						Game::getSingleton().message(Message(MT_ATTACK, mID, mAttackTarget, mDamage));
					}
				}
			}
		}
		*/
/*
	CreatureTemplate* c = new CreatureTemplate();
	c->name = "Deer";
	c->description = "Grass eater.";
	c->mesh = "Deer.mesh";
	c->mMaxHealth = 100.0f;
	c->mMaxEnergy = 0.0f;
	c->scale = Ogre::Vector3(0.02f);
	c->picture = "c_a_deer.tga";
	c->mSpeciesName = "Deer";
	c->mSpecies = 0x01;
	c->mDamage = 1.0f;
	c->mSightDistance = 40.0;
	c->mSpeed = 1.0f;
	c->mAnimationAttack = "ca1slashl";
	c->mAnimationIdle = "cpause1";
	c->mAnimationWalk = "cwalk";
	mTemplates.insert(std::make_pair(c->name, c));

	c = new CreatureTemplate();
	c->name = "Giant Spider";
	c->description = "Big green spider.";
	c->mesh = "Giant_Spider.mesh";
	c->scale = Ogre::Vector3(0.02f);
	c->picture = "c_spidgiant.tga";
	c->mMaxHealth = 150.0f;
	c->mMaxEnergy = 50.0f;
	c->mSpeciesName = "Spider";
	c->mSpecies = 0x02;
	c->mDamage = 5.0f;
	c->mSightDistance = 75.0;
	c->mSpeed = 1.0f;
	c->mAnimationAttack = "ca1slashl";
	c->mAnimationIdle = "cpause1";
	c->mAnimationWalk = "cwalk";
	mTemplates.insert(std::make_pair(c->name, c));

	c = new CreatureTemplate();
	c->name = "Ettercap";
	c->description = "Small and ugly insect.";
	c->mesh = "Ettercap.mesh";
	c->scale = Ogre::Vector3(0.02f);
	c->picture = "c_ettercap.tga";
	c->mMaxHealth = 200.0f;
	c->mMaxEnergy = 75.0f;
	c->mSpeciesName = "Spider";
	c->mSpecies = 0x03;
	c->mDamage = 5.0f;
	c->mSightDistance = 100.0;
	c->mSpeed = 1.0f;
	c->mAnimationAttack = "ca1slashl";
	c->mAnimationIdle = "cpause1";
	c->mAnimationWalk = "cwalk";
	mTemplates.insert(std::make_pair(c->name, c));

	c = new CreatureTemplate();
	c->name = "Jaguar";
	c->description = "Deer eater.";
	c->mesh = "Jaguar.mesh";
	c->scale = Ogre::Vector3(0.02f);
	c->picture = "c_cat_jag.tga";
	c->mMaxHealth = 60.0f;
	c->mMaxEnergy = 0.0f;
	c->mSpeciesName = "Jaguar";
	c->mSpecies = 0x03;
	c->mDamage = 8.0f;
	c->mSightDistance = 120.0;
	c->mSpeed = 1.5f;
	c->mAnimationAttack = "ca1slashl";
	c->mAnimationIdle = "cpause1";
	c->mAnimationWalk = "cwalk";
	mTemplates.insert(std::make_pair(c->name, c));

	c = new CreatureTemplate();
	c->name = "Green Goblin Wizard";
	c->description = "Small and ugly creature.";
	c->mesh = "c_gobwiza.mesh";
	c->scale = Ogre::Vector3(0.02f);
	c->picture = "c_goblina.tga";
	c->mMaxHealth = 60.0f;
	c->mMaxEnergy = 80.0f;
	c->mSpeciesName = "Goblin";
	c->mSpecies = 0x04;
	c->mDamage = 10.0f;
	c->mSightDistance = 150.0;
	c->mSpeed = 1.0f;
	c->mAnimationAttack = "1hslashl";
	c->mAnimationIdle = "pause1";
	c->mAnimationWalk = "cwalkf";
	mTemplates.insert(std::make_pair(c->name, c));

	c = new CreatureTemplate();
	c->name = "Red Goblin Soldier";
	c->description = "Small and ugly creature.";
	c->mesh = "c_goblinb.mesh";
	c->scale = Ogre::Vector3(0.02f);
	c->picture = "a_f01_fore.TGA";
	c->mMaxHealth = 60.0f;
	c->mMaxEnergy = 0.0f;
	c->mSpeciesName = "Goblin";
	c->mSpecies = 0x04;
	c->mDamage = 10.0f;
	c->mSightDistance = 150.0;
	c->mSpeed = 1.0f;
	c->mAnimationAttack = "1hslashl";
	c->mAnimationIdle = "pause1";
	c->mAnimationWalk = "cwalkf";
	mTemplates.insert(std::make_pair(c->name, c));

	ObjectTemplate* object = new ObjectTemplate();
	object->name = "Building #1";
	object->description = "City Building";
	object->mesh = "bldskyl1_01.mesh";
	object->scale = Ogre::Vector3(0.03f);
	object->picture = "skyscrp1.tga";
	mTemplates.insert(std::make_pair(object->name, object));

	object = new ObjectTemplate();
	object->name = "Building #2";
	object->description = "City Building";
	object->mesh = "bldskyl1_02.mesh";
	object->scale = Ogre::Vector3(0.03f);
	object->picture = "ss3roof.tga";
	mTemplates.insert(std::make_pair(object->name, object));

	object = new ObjectTemplate();
	object->name = "Building #3";
	object->description = "City Building";
	object->mesh = "bldskyl1_03.mesh";
	object->scale = Ogre::Vector3(0.03f);
	object->picture = "towtwin.tga";
	mTemplates.insert(std::make_pair(object->name, object));

	object = new ObjectTemplate();
	object->name = "Building #4";
	object->description = "City Building";
	object->mesh = "bldskyl1_04.mesh";
	object->scale = Ogre::Vector3(0.03f);
	object->picture = "tower2.tga";
	mTemplates.insert(std::make_pair(object->name, object));

	object = new ObjectTemplate();
	object->name = "Building #5";
	object->description = "City Building";
	object->mesh = "bldskyl1_05.mesh";
	object->scale = Ogre::Vector3(0.03f);
	object->picture = "tower1.tga";
	mTemplates.insert(std::make_pair(object->name, object));

	ResourceTemplate* resource = new ResourceTemplate();
	resource->name = "Energy";
	resource->description = "Required by all structures";
	resource->mesh = "sun.mesh";
	resource->maximal["Energy"] = 10000.0f;
	resource->produce["Energy"] = 10000.0f;
	resource->scale = Ogre::Vector3::UNIT_SCALE;
	resource->picture = "sun.jpg";
	resource->radius = 10000000.0f;
	mTemplates.insert(std::make_pair(resource->name, resource));

	resource = new ResourceTemplate();
	resource->name = "Metal";
	resource->description = "Required by all units";
	resource->mesh = "metal.mesh";
	resource->maximal["Metal"] = 500.0f;
	resource->produce["Metal"] = 0.4f;
	resource->scale = Ogre::Vector3(0.3f);
	resource->picture = "goblinmetal2.jpg";
	resource->radius = 1.0f;
	mTemplates.insert(std::make_pair(resource->name, resource));

	resource = new ResourceTemplate();
	resource->name = "Crystal";
	resource->description = "Very rare. Required by bigger units";
	resource->mesh = "crystal.mesh";
	resource->maximal["Crystal"] = 50.0f;
	resource->produce["Crystal"] = 0.01f;
	resource->scale = Ogre::Vector3(0.1f);
	resource->picture = "Marbl21l.JPG";
	resource->radius = 3.0f;
	mTemplates.insert(std::make_pair(resource->name, resource));

	FortificationTemplate* fortification = new FortificationTemplate();
	fortification->name = "Dragon's Teeth";
	fortification->description = "Perimeter Defense";
	fortification->mesh = "armdrag.mesh";
	fortification->cost["Energy"] = 250.0f;
	fortification->cost["Metal"] = 10.0f;
	fortification->mMaxHealth = 3500.0f;
	fortification->maxSightDistance = 100.0f;
	fortification->maxSlope = 32.0f;
	fortification->use["Energy"] = 0.0f;
	fortification->use["Metal"] = 0.0f;
	fortification->picture = "ArmDRAG.png";
	fortification->scale = Ogre::Vector3(0.3f);
	mTemplates.insert(std::make_pair(fortification->name, fortification));

	MineTemplate* mine = new MineTemplate();
	mine->name = "Metal Extractor";
	mine->description = "Extracts Metal";
	mine->mesh = "armmex.mesh";
	mine->cost["Energy"] = 521.0f;
	mine->cost["Metal"] = 50.0f;
	mine->mMaxHealth = 170.0f;
	mine->maxSightDistance = 210.0f;
	mine->maxSlope = 10.0f;
	mine->use["Energy"] = 3.0f;
	mine->use["Metal"] = 0.0f;
	mine->picture = "ArmMEX.png";
	mine->scale = Ogre::Vector3(0.03f);
	mTemplates.insert(std::make_pair(mine->name, mine));

	FactoryTemplate* factory = new FactoryTemplate();
	factory->name = "Vehicle Plant";
	factory->description = "Produces Vehicles";
	factory->mesh = "armlab.mesh";
	factory->cost["Energy"] = 1000.0f;
	factory->cost["Metal"] = 620.0f;
	factory->mMaxHealth = 2580.0f;
	factory->maxSightDistance = 210.0f;
	factory->maxSlope = 10.0f;
	factory->use["Energy"] = 5.0f;
	factory->use["Metal"] = 2.5f;
	factory->picture = "ArmLAB.png";
	factory->scale = Ogre::Vector3(0.05f, 0.09f, 0.05f);
	mTemplates.insert(std::make_pair(factory->name, factory));

	PlantTemplate* plant = new PlantTemplate();
	plant->name = "Palm Tree";
	plant->description = "Palm Tree";
	plant->mesh = "palmtree.mesh";
	plant->scale = Ogre::Vector3(0.05f);
	plant->mMaxHealth = 25.0f;
	plant->picture = "palmtree.tga";
	plant->sightHideFactor = 0.2f;
	plant->radarHideFactor = 0.1f;
	mTemplates.insert(std::make_pair(plant->name, plant));

	plant = new PlantTemplate();
	plant->name = "Pine Tree";
	plant->description = "Pine Tree";
	plant->mesh = "pinetree.mesh";
	plant->scale = Ogre::Vector3(0.06f);
	plant->mMaxHealth = 20.0f;
	plant->picture = "pinetree.tga";
	plant->sightHideFactor = 0.5f;
	plant->radarHideFactor = 0.3f;
	mTemplates.insert(std::make_pair(plant->name, plant));

	VehicleTemplate* vehicle = new VehicleTemplate();
	vehicle->name = "Jeffy";
	vehicle->description = "Fast Attack Vehicle";
	vehicle->cost["Energy"] = 564.0f;
	vehicle->cost["Metal"] = 37.0f;
	vehicle->mMaxHealth = 79.0f;
	vehicle->maxWaterDepth = 12.0f;
	vehicle->maxSightDistance = 18.0f;
	vehicle->maxSlope = 310.0f;
	vehicle->mesh = "armfav.mesh";
	vehicle->picture = "ArmFAV.png";
	vehicle->maxMoveSpeed = 3.0f;
	vehicle->maxBrakeRate = 0.06f;
	vehicle->maxAcceleration = 0.04f;
	vehicle->maxWeaponDamage = 3.0f;
	vehicle->weaponRange = 180.0f;
	vehicle->maxWeaponRechargeTime = 0.865f;
	vehicle->maxWeaponDamageRadius = 8.0f;
	vehicle->scale = Ogre::Vector3(0.03f);
	mTemplates.insert(std::make_pair(vehicle->name, vehicle));

	for (TemplateMap::const_iterator i = mTemplates.begin(); i != mTemplates.end(); ++i)
	{
		if (UnitTemplate* unit = dynamic_cast<UnitTemplate*>(i->second))
		{
			unit->maxSightDistance *= 10.0f;
		}

		if (VehicleTemplate* vehicle = dynamic_cast<VehicleTemplate*>(i->second))
		{
			vehicle->maxMoveSpeed *= 6.0f;
			vehicle->maxAcceleration *= 100.0f;
			vehicle->maxBrakeRate *= 200.0f;
			vehicle->weaponRange *= 0.5f;
		}
	}

	return true;
	*/

/*

struct structure_t
{
	struct health_t
	{
		float current;
		float maximal;
	};

	struct resource_t
	{
		char	name[512];
		float	value;
	};

	health_t	health;
	resource_t	consume[16];
	resource_t	cost[16];
	resource_t	produce[16];
};

struct vehicle_t
{
	struct move_t
	{
		float acceleration;
		float speed;
	};

	struct radar_t
	{
		float range;
	};

	struct weapon_t
	{
		float damage;
		float radius;
		float range;
	};

	move_t		move;
	radar_t		radar;
	weapon_t	weapon;
};
*/
