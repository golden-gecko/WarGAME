#pragma once

#include "Dependencies.h"
#include "Structure.h"

class Mine : public Structure
{
public:
	Mine(unsigned int id, const std::string& mesh);

	void setPlayer(Player* player)
	{
		if (mPlayer)
		{
			for (std::map<std::string, float>::const_iterator i = mProduce.begin();
				i != mProduce.end(); ++i)
			{
				mPlayer->getResource(i->first).produced -= i->second;
			}

			for (std::map<std::string, float>::const_iterator i = mUse.begin();
				i != mUse.end(); ++i)
			{
				mPlayer->getResource(i->first).use -= i->second;
			}
		}

		if (mPlayer = player)
		{
			for (std::map<std::string, float>::const_iterator i = mProduce.begin();
				i != mProduce.end(); ++i)
			{
				mPlayer->getResource(i->first).produced += i->second;
			}

			for (std::map<std::string, float>::const_iterator i = mUse.begin();
				i != mUse.end(); ++i)
			{
				mPlayer->getResource(i->first).use += i->second;
			}
		}
	}
	void setProduce(const std::map<std::string, float>& produce)
	{
		mProduce = produce;
	}
protected:
	std::map<std::string, float> mProduce;
};
