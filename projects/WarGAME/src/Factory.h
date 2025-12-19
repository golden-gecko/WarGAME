#pragma once

#include "Dependencies.h"
#include "Structure.h"

class Factory : public Structure
{
public:
	Factory(unsigned int id, const std::string& mesh);
	void onOrder(const Order& order, bool append = false);
	void update(float time);
	std::string toString();

	void onBeginContruction(unsigned int object);
protected:
	std::map<std::string, unsigned short>	mQuantities;
	std::vector<std::string>				mQuene;
	std::string								mTemplateName;
	unsigned int							mCurrentContructed;
	unsigned int							mUnitsConstructed;

	Ogre::Vector3 mStartPoint;
	Ogre::Vector3 mRallyPoint;
};
