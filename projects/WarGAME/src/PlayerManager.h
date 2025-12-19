#pragma once

#include "Dependencies.h"
#include "Debug.h"
#include "Player.h"

typedef std::map<std::string, Player*> PlayerMap;

/// Manages players.
class PlayerManager : public Ogre::Singleton<PlayerManager>
{
public:
	Player* create(unsigned int type, const std::string& name, const Ogre::ColourValue& colour)
	{
		if (mPlayers.find(name) == mPlayers.end())
		{
			Player* player = new Player(type, name, colour);

			mPlayers.insert(std::make_pair(name, player));

			return player;
		}

		return NULL;	
	}

	Player* get(const std::string& name)
	{
		PlayerMap::const_iterator i = mPlayers.find(name);

		if (mPlayers.find(name) != mPlayers.end())
		{
			return i->second;
		}

		return NULL;
	}

	const PlayerMap& get() const
	{
		return mPlayers;
	}

	void destroy(const std::string& name)
	{
		ASSERT(name.length() > 0);

		PlayerMap::iterator i = mPlayers.find(name);

		if (i != mPlayers.end())
		{
			delete i->second;

			mPlayers.erase(i);
		}
	}

	void destroyAll()
	{
		for (PlayerMap::const_iterator i = mPlayers.begin(); i != mPlayers.end(); ++i)
		{
			delete i->second;
		}

		mPlayers.clear();
	}

	void update(float time)
	{
		for (PlayerMap::const_iterator i = mPlayers.begin(); i != mPlayers.end(); ++i)
		{
			i->second->update(time);
		}
	}
protected:
	PlayerMap mPlayers;
};
