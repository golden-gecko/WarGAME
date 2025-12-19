#pragma once

#include "Dependencies.h"
#include "Unit.h"

class Structure : public Unit
{
public:
	float getUse(const std::string& name) const
	{
		std::map<std::string, float>::const_iterator i = mUse.find(name);

		if (i != mUse.end())
		{
			return i->second;
		}

		return 0.0f;
	}

	void setPlayer(Player* player)
	{
		if (mPlayer)
		{
			for (std::map<std::string, float>::const_iterator i = mUse.begin();
				i != mUse.end(); ++i)
			{
				mPlayer->getResource(i->first).use -= i->second;
			}
		}

		if (mPlayer = player)
		{
			for (std::map<std::string, float>::const_iterator i = mUse.begin();
				i != mUse.end(); ++i)
			{
				mPlayer->getResource(i->first).use += i->second;
			}
		}
	}
	void setUse(const std::map<std::string, float>& use) { mUse = use; }

	void onCreate(unsigned int creator = 0);
	void onDestroy(unsigned int destroyer = 0);

	void update(float time);
protected:
	Structure(unsigned int id, unsigned int type, const std::string& mesh);

	std::map<std::string, float> mUse;
};
