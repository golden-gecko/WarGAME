#include "Dependencies.h"
#include "Debug.h"
#include "Game.h"
#include "Graphics.h"
#include "GUI.h"
#include "ObjectManager.h"
#include "PlayerManager.h"
#include "Terrain.h"
#include "Unit.h"

Game* Ogre::Singleton<Game>::ms_Singleton = NULL;

Game::Game() : mGameSpeed(1)
{
}

bool Game::init()
{
	Player* p1 = PlayerManager::getSingleton().create(PT_HUMAN, "Human", Ogre::ColourValue(0.0f, 0.0f, 0.7f));
	Player* p2 = PlayerManager::getSingleton().create(PT_COMPUTER, "Computer", Ogre::ColourValue(0.7f, 0.0f, 0.0f));

	p1->getResource("Energy").current = 5000.0f;
	p1->getResource("Metal").current = 2500.0f;

	p1->getResource("Energy").maximal = 5000.0f;
	p1->getResource("Metal").maximal = 2500.0f;

	p2->getResource("Energy").current = 5000.0f;
	p2->getResource("Metal").current = 2500.0f;

	p2->getResource("Energy").maximal = 5000.0f;
	p2->getResource("Metal").maximal = 2500.0f;

	setActivePlayer(p1);

	/*
	ObjectManager::getSingleton().create("Shrub #1", Terrain::getSingleton().getPosition(1103, 1123));
	ObjectManager::getSingleton().create("Shrub #2", Terrain::getSingleton().getPosition(1104, 1130));
	ObjectManager::getSingleton().create("Shrub #3", Terrain::getSingleton().getPosition(1105, 1140));
	ObjectManager::getSingleton().create("Shrub #5", Terrain::getSingleton().getPosition(1110, 1128));
	ObjectManager::getSingleton().create("Shrub #2", Terrain::getSingleton().getPosition(1140, 1137));
	ObjectManager::getSingleton().create("Shrub #5", Terrain::getSingleton().getPosition(1115, 1146));
	ObjectManager::getSingleton().create("Shrub #6", Terrain::getSingleton().getPosition(1124, 1225));
	ObjectManager::getSingleton().create("Shrub #5", Terrain::getSingleton().getPosition(1123, 1233));
	ObjectManager::getSingleton().create("Shrub #7", Terrain::getSingleton().getPosition(1122, 1044));
	ObjectManager::getSingleton().create("Shrub #4", Terrain::getSingleton().getPosition(1130, 1035));
	ObjectManager::getSingleton().create("Shrub #3", Terrain::getSingleton().getPosition(1110, 1126));
	ObjectManager::getSingleton().create("Shrub #2", Terrain::getSingleton().getPosition(1120, 1236));

	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1100, 1120));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1100, 1130));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1100, 1140));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1110, 1120));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1110, 1130));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1110, 1140));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1120, 1225));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1120, 1233));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1120, 1040));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1120, 1030));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1130, 1123));
	ObjectManager::getSingleton().create("Pine Tree", Terrain::getSingleton().getPosition(1130, 1235));

	ObjectManager::getSingleton().create("Deer", Terrain::getSingleton().getPosition(1000, 1000));
	ObjectManager::getSingleton().create("Deer", Terrain::getSingleton().getPosition(1010, 1000));
	ObjectManager::getSingleton().create("Deer", Terrain::getSingleton().getPosition(1010, 1010));
	ObjectManager::getSingleton().create("Deer", Terrain::getSingleton().getPosition(1000, 1010));

	ObjectManager::getSingleton().create("Giant Spider", Terrain::getSingleton().getPosition(1100, 1000));
	ObjectManager::getSingleton().create("Giant Spider", Terrain::getSingleton().getPosition(1110, 1000));
	ObjectManager::getSingleton().create("Giant Spider", Terrain::getSingleton().getPosition(1110, 1010));
	ObjectManager::getSingleton().create("Giant Spider", Terrain::getSingleton().getPosition(1100, 1010));

	ObjectManager::getSingleton().create("Ettercap", Terrain::getSingleton().getPosition(1080, 1010));
	ObjectManager::getSingleton().create("Ettercap", Terrain::getSingleton().getPosition(1090, 1010));

	ObjectManager::getSingleton().create("Gray Wolf", Terrain::getSingleton().getPosition(1180, 1010));
	ObjectManager::getSingleton().create("Gray Wolf", Terrain::getSingleton().getPosition(1190, 1010));
	*/

	/*
	Object* o1 = ObjectManager::getSingleton().create("Energy", Ogre::Vector3::ZERO);
	Object* o2 = ObjectManager::getSingleton().create("Crystal", Terrain::getSingleton().getPosition(1250, 1250));
	Object* o3 = ObjectManager::getSingleton().create("Crystal", Terrain::getSingleton().getPosition(1250, 1270));
	Object* o4 = ObjectManager::getSingleton().create("Metal", Terrain::getSingleton().getPosition(1200, 1250));

	ASSERT(o1);
	ASSERT(o2);
	ASSERT(o3);
	ASSERT(o4);

	Object* o10 = ObjectManager::getSingleton().create("Building #1", Terrain::getSingleton().getPosition(1200, 1200));
	Object* o11 = ObjectManager::getSingleton().create("Building #2", Terrain::getSingleton().getPosition(1200, 1210));
	Object* o12 = ObjectManager::getSingleton().create("Building #3", Terrain::getSingleton().getPosition(1200, 1220));
	Object* o13 = ObjectManager::getSingleton().create("Building #4", Terrain::getSingleton().getPosition(1200, 1230));
	Object* o14 = ObjectManager::getSingleton().create("Building #5", Terrain::getSingleton().getPosition(1200, 1240));

	ASSERT(o10);
	ASSERT(o11);
	ASSERT(o12);
	ASSERT(o13);

	Object* o20 = ObjectManager::getSingleton().create("Metal Extractor", Terrain::getSingleton().getPosition(1210, 1200));
	Object* o21 = ObjectManager::getSingleton().create("Metal Extractor", Terrain::getSingleton().getPosition(1220, 1200));
	Object* o22 = ObjectManager::getSingleton().create("Metal Extractor", Terrain::getSingleton().getPosition(1230, 1200));
	Object* o23 = ObjectManager::getSingleton().create("Vehicle Plant", Terrain::getSingleton().getPosition(1230, 1210));
	Object* o24 = ObjectManager::getSingleton().create("Vehicle Plant", Terrain::getSingleton().getPosition(1230, 1220));

	(dynamic_cast<Unit*>(o20))->setPlayer(p1);
	(dynamic_cast<Unit*>(o21))->setPlayer(p1);
	(dynamic_cast<Unit*>(o22))->setPlayer(p1);
	(dynamic_cast<Unit*>(o23))->setPlayer(p1);
	(dynamic_cast<Unit*>(o24))->setPlayer(p1);

	Object* o25 = ObjectManager::getSingleton().create("Jeffy", Terrain::getSingleton().getPosition(1230, 1240));
	Object* o26 = ObjectManager::getSingleton().create("Jeffy", Terrain::getSingleton().getPosition(1230, 1250));
	Object* o27 = ObjectManager::getSingleton().create("Jeffy", Terrain::getSingleton().getPosition(1230, 1260));
	Object* o28 = ObjectManager::getSingleton().create("Jeffy", Terrain::getSingleton().getPosition(1230, 1270));
	Object* o29 = ObjectManager::getSingleton().create("Jeffy", Terrain::getSingleton().getPosition(1230, 1280));

	(dynamic_cast<Unit*>(o25))->setPlayer(p1);
	(dynamic_cast<Unit*>(o26))->setPlayer(p1);
	(dynamic_cast<Unit*>(o27))->setPlayer(p1);
	(dynamic_cast<Unit*>(o28))->setPlayer(p1);
	(dynamic_cast<Unit*>(o29))->setPlayer(p1);

	(dynamic_cast<Unit*>(o25))->onOrder(Order(OT_FOLLOW, o26->getID()));
	(dynamic_cast<Unit*>(o26))->onOrder(Order(OT_FOLLOW, o27->getID()));
	(dynamic_cast<Unit*>(o27))->onOrder(Order(OT_FOLLOW, o28->getID()));
	(dynamic_cast<Unit*>(o28))->onOrder(Order(OT_FOLLOW, o29->getID()));


	std::string names[4] = { "explosion", "smoke", "shoot", "water" };

	for (unsigned int i = 0; i < 4; ++i)
	{
		for (unsigned int j = 0; j < 5; ++j)
		{
			mEffects.insert(std::make_pair(names[i],
				new Effect(names[i] + Ogre::StringConverter::toString(j), names[i])));
		}
	}
	*/

	return true;
}

void Game::shutdown()
{
}

const unsigned int size = 512;

unsigned int START_X = 250;
unsigned int START_Z = 150;

unsigned int END_X = 15;
unsigned int END_Z = 12;

struct tile
{
	int x, z;
	float f, g, h;
	tile* previous;
	char value;
};

tile map[size * size];

const unsigned int INDICES_NUM = 8;

int indices[INDICES_NUM][2] =
{
	{ -1, -1 },
	{ -1,  0 },
	{ -1,  1 },
	{  0, -1 },
	{  0,  1 },
	{  1, -1 },
	{  1,  0 },
	{  1,  1 }
};

void astar(const Ogre::Vector3& start, const Ogre::Vector3& end, std::vector<Ogre::Vector3>& path)
{
//*
	START_X = start.x  * size / 2500.0f;
	START_Z = start.z  * size / 2500.0f;

	END_X = end.x  * size / 2500.0f;
	END_Z = end.z  * size / 2500.0f;
//*/
	if (START_X == END_X && START_Z == END_Z)
	{
		return;
	}

	static bool init = true;

	/*
	Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("dynamic");

	tex->getBuffer(0, 0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

	const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();

	Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);
	*/

//	data[pb.rowPitch * z + x] = 0xAAAA00;
//	data[pb.rowPitch * z + x] = 0x00AA00;

	if (init)
	{
		for (unsigned int z = 0; z < size; ++z)
		{
			for (unsigned int x = 0; x < size; ++x)
			{
				map[size * z + x].x = x;
				map[size * z + x].z = z;
				map[size * z + x].f = map[size * z + x].g = map[size * z + x].h = 0.0f;
				map[size * z + x].previous = NULL;
			}
		}

		init = false;
	}

	std::set<tile*> opened;
	std::set<tile*> active;
	std::set<tile*> closed;

	std::set<tile*>::iterator o;
	tile* e = &(map[size * END_Z + END_X]);
	tile* t = &(map[size * START_Z + START_X]);
	t->h = t->f = sqrt((float)(e->x - t->x) * (e->x - t->x) + (e->z - t->z) * (e->z - t->z));

	opened.insert(&(map[size * START_Z + START_X]));

	unsigned int counter = 0;

	do
	{
		++counter;

		if (counter > 100)
		{
			break;
		}

		o = opened.begin();

		for (std::set<tile*>::iterator i = opened.begin(); i != opened.end(); ++i)
		{
			if ((*i)->f < (*o)->f)
			{
				o = i;
			}
		}

		for (unsigned int i = 0; i < INDICES_NUM; ++i)
		{
			unsigned int x = (*o)->x + indices[i][0];
			unsigned int z = (*o)->z + indices[i][1];

			// Is new tile coordinates valid?
			if (x > 0 && z > 0 && x < size - 1 && z < size - 1)
			{
				// New tile.
				t = &(map[size * z + x]);

				// Is new tile closed?
				if (closed.find(t) == closed.end())
				{
					// Are we at end?
					if (t == &(map[size * END_Z + END_X]))
					{
						t->previous = *o;

						goto END;
					}

					// Is new tile blocked?
				//	if (data[pb.rowPitch * z + x] != 0xAAAA00)
					{
						//t->g = (*o)->g + 1;//sqrt((float)((*o)->x - t->x) * ((*o)->x - t->x) + ((*o)->z - t->z) * ((*o)->z - t->z));
						t->h = sqrt((float)(e->x - t->x) * (e->x - t->x) + (e->z - t->z) * (e->z - t->z));
						t->f = t->g + t->h;
						t->previous = *o;

						active.insert(t);
					}
				}
			}
		}

		// Close current tile.
		closed.insert(*o);
		opened.erase(o);

		// Open new tiles.
		for (std::set<tile*>::iterator o = active.begin(); o != active.end(); ++o)
		{
			opened.insert(*o);
		}

		active.clear();

		//

	//	draw();
	}
	while (opened.size());

	//

	o = closed.begin();

	for (std::set<tile*>::iterator i = closed.begin(); i != closed.end(); ++i)
	{
		if ((*i)->f < (*o)->f)
		{
			o = i;
		}
	}

	t = *o;
/*
	data[pb.rowPitch * START_Z + START_X] = 0xAA0000;
	data[pb.rowPitch * END_Z + END_X] = 0xAA0000;
*/
	while (t && t != &(map[size * START_Z + START_X]))
	{
		//data[pb.rowPitch * t->z + t->x] = 0x0000AA;

		path.push_back(Ogre::Vector3(
			(float)t->x * 2500.0f / size + 2.0f, 0.0f,
			(float)t->z * 2500.0f / size + 2.0f));

		t = t->previous;
	}

//	tex->getBuffer(0, 0)->unlock();

	return;

END:
/*
	data[pb.rowPitch * START_Z + START_X] = 0xAA0000;
	data[pb.rowPitch * END_Z + END_X] = 0xAA0000;
*/
	t = &(map[size * END_Z + END_X]);

	path.push_back(end);

	// "t->previous" (not "t"), because we want to skip end tile.
	while (t->previous && t->previous != &(map[size * START_Z + START_X]))
	{

	//	data[pb.rowPitch * t->previous->z + t->previous->x] = 0x0000AA;

		path.push_back(Ogre::Vector3(
			(float)t->previous->x * 2500.0f / size + 2.0f, 0.0f,
			(float)t->previous->z * 2500.0f / size + 2.0f));

		t = t->previous;
	}

//	tex->getBuffer(0, 0)->unlock();
}

int i = 0;
float power = 0.00f;

void Game::update(float time)
{
	for (unsigned int i = 0; i < mGameSpeed; ++i)
	{
		/*
		i++;

		if (i % 2)
		{
			if (i % 60 < 30 )
			{
				power += 0.01f;

				getActivePlayer()->getActiveCamera()->setPosition(
					getActivePlayer()->getActiveCamera()->getPosition() + Ogre::Vector3(
						Ogre::Math::RangeRandom(-power, power),
						Ogre::Math::RangeRandom(-power, power),
						Ogre::Math::RangeRandom(-power, power)));
			}
			else if (i % 60 < 60 )
			{
				power -= 0.01f;

				getActivePlayer()->getActiveCamera()->setPosition(
					getActivePlayer()->getActiveCamera()->getPosition() + Ogre::Vector3(
						Ogre::Math::RangeRandom(-power, power),
						Ogre::Math::RangeRandom(-power, power),
						Ogre::Math::RangeRandom(-power, power)));
			}
		}
		*/

		/*
		for (std::vector<Ogre::SceneNode*>::size_type i = 0; i < nodes.size(); i++)
		{
			if (angles[0] < 90.0f)
			{
				nodes[i]->rotate(dir[i], Ogre::Degree(0.2f), Ogre::Node::TS_WORLD);
			}
		}

		angles[0] += 0.2f;
		//*/

		ObjectManager::getSingleton().update(time);
		PlayerManager::getSingleton().update(time);

		// Find one path during each frame.
		if (mPathQuene.size())
		{
			const PathQueneItem& item = mPathQuene.front();

			while (ObjectManager::getSingleton().get(item.mObject) == NULL)
			{
				mPathQuene.erase(mPathQuene.begin());
			}

			switch (ObjectManager::getSingleton().get(item.mObject)->getType())
			{
				case OT_VEHICLE:
				{
					/*
					Unit* u = dynamic_cast<Unit*>(ObjectManager::getSingleton().get(item.mObject));

					astar(u->getPosition(),
						item.mTarget,
						u->mPath);		
					*/

					break;
				}
			}

			mPathQuene.erase(mPathQuene.begin());
		}

		// Process messages.
		for (MessageMap::const_iterator m = mMessages.begin(); m != mMessages.end(); m++)
		{
			Object* sender = ObjectManager::getSingleton().get(m->second.getSender());

			switch (m->first)
			{
				case MT_INCREASE_HEALTH:
				{
					if (ObjectManager::getSingleton().get(m->second.getInt()))
					{
						ObjectManager::getSingleton().get(m->second.getInt())->onHeal(
							m->second.getSender(), m->second.getFloat());
					}

					break;
				}

				case MT_CHANGE_RESOURCE:
				{
				//	getPlayer(sender->getPlayer())->changeResource(m->second.getInt(), m->second.getFloat());

					break;
				}

				case MT_CREATE_OBJECT:
				{
					if (Object* sender = ObjectManager::getSingleton().get(m->second.getSender()))
					{
						if (Object* object = ObjectManager::getSingleton().create(m->second.getString()))
						{
							sender->onBeginContruction(object->getID());
						}
					}

					break;
				}

				case MT_MOVE:
				{
					/*
					Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("dynamic");

					tex->getBuffer(0,0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

					const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();

					Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);

					const std::map<unsigned int, Object*>& objects = ObjectManager::getSingleton().get();

					size_t size = 512;
					Object* sender = getObject(m->second.getSender());
					const Ogre::AxisAlignedBox& box = sender->getBoundingBox();

					Ogre::Vector3 curPos = sender->getPosition() * size / 2500.0f;
					Ogre::Vector3 newPos = (sender->getPosition() + m->second.getVector()) * size / 2500.0f;

					if ((size_t)curPos.x != (size_t)newPos.x || (size_t)curPos.z != (size_t)newPos.z)
					{
						if (data[pb.rowPitch * (size_t)newPos.z + (size_t)newPos.x] != 0xAAAA00)
						{
							sender->onMove(m->second.getVector());

							data[pb.rowPitch * (size_t)curPos.z + (size_t)curPos.x] = 0x00AA00;
							data[pb.rowPitch * (size_t)newPos.z + (size_t)newPos.x] = 0xAAAA00;
						}
						else
						{
							// Problems with orders other than OT_MOVE.
							sender->onMove(Ogre::Vector3::ZERO, true);
						}
					}
					else
					{
						sender->onMove(m->second.getVector());
					}

					tex->getBuffer(0, 0)->unlock();
					*/

					sender->onMove(m->second.getVector());

					break;
				}

				case MT_SHOOT_OBJECT:
				{
					if (Object* sender = ObjectManager::getSingleton().get(m->second.getSender()))
					{
						if (Object* target = ObjectManager::getSingleton().get(m->second.getInt()))
						{
							bool killed = target->onHit(
								m->second.getSender(),
								m->second.getFloat(),
								Ogre::Vector3::ZERO);

							sender->onShoot(
								m->second.getInt(),
								m->second.getFloat(),
								true,
								killed);

						//	createEffect("smoke", sender->getCenter() + sender->getDirection());
							createEffect("shoot", target->getCenter());
						}
						else
						{
							sender->onShoot(0, 0.0f, false, false);
						}
					}

					break;
				}

				case MT_SHOOT_POSITION:
				{
					if (Object* sender = ObjectManager::getSingleton().get(m->second.getSender()))
					{
						sender->onShoot(0, 0.0f, false, false);

					//	createEffect("smoke", sender->getCenter() + sender->getDirection(), sender->getDirection() * 2.0f);
						
						if (m->second.getVector().y > 24.0f)
						{
							createEffect("shoot", m->second.getVector() + Ogre::Vector3::UNIT_Y);
						}
						else
						{
							createEffect("water", Ogre::Vector3(m->second.getVector().x, 25.0f, m->second.getVector().z));
						}

						/*
						Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("dynamic");

						tex->getBuffer(0,0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

						const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();

						Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);

						const std::map<unsigned int, Object*>& objects = ObjectManager::getSingleton().get();

						size_t size = 512;
						Ogre::Vector3 curPos = m->second.getVector() * size / 2500.0f;
		
						data[pb.rowPitch * (size_t)curPos.z + (size_t)curPos.x] = 0x333333;
		
						tex->getBuffer(0, 0)->unlock();
						*/
					}

					break;
				}

				case MT_DESTROY_OBJECT:
				{
					if (Object* target = ObjectManager::getSingleton().get(m->second.getInt()))
					{
						createEffect("explosion", target->getPosition());

						/*
						Ogre::TexturePtr tex = Ogre::TextureManager::getSingleton().getByName("dynamic");

						tex->getBuffer(0,0)->lock(Ogre::HardwareBuffer::HBL_DISCARD);

						const Ogre::PixelBox& pb = tex->getBuffer(0, 0)->getCurrentLock();

						Ogre::uint32* data = static_cast<Ogre::uint32*>(pb.data);

						const std::map<unsigned int, Object*>& objects = ObjectManager::getSingleton().get();

						size_t size = 512;
						Ogre::Vector3 curPos = m->second.getVector() * size / 2500.0f;
		
						data[pb.rowPitch * (size_t)curPos.z + (size_t)curPos.x] = 0x333333;
		
						tex->getBuffer(0, 0)->unlock();
						*/

						//
						getActivePlayer()->removeFromGroups(target->getID());
						getActivePlayer()->removeFromSelection(target->getID());

						ObjectManager::getSingleton().destroy(target->getID());
					}

					break;
				}
			}
		}

		mMessages.clear();
	}
}

void Game::setActivePlayer(Player *player)
{
	mActivePlayer = player;
}

//------------------------------------------------------------------------------
// Save / Load
//------------------------------------------------------------------------------

bool Game::save(const std::string& name)
{
	std::ofstream file(
		("..\\saves\\" + name).c_str(),
		std::ios_base::binary | std::ios_base::out | std::ios_base::trunc);

	if (file.is_open() == false)
	{
		return false;
	}

	/*
	Game::getSingleton().save(file);
	Terrain::getSingleton().save(file);
	Water::getSingleton().save(file);
	PlayerManager::getSingleton().save(file);
	ObjectManager::getSingleton().save(file);
	*/

	file.close();

	return true;
}

bool Game::load(const std::string& name)
{
	std::ifstream file(
		("..\\saves\\" + name).c_str(),
		std::ios_base::binary | std::ios_base::in);

	if (file.is_open() == false)
	{
		return false;
	}

	/*
	Game::getSingleton().load(file);
	Terrain::getSingleton().load(file);
	Water::getSingleton().load(file);
	PlayerManager::getSingleton().load(file);
	ObjectManager::getSingleton().load(file);
	*/

	file.close();

	return true;
}
