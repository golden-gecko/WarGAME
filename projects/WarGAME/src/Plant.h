#pragma once

#include "Dependencies.h"
#include "Object.h"

class Plant : public Object
{
public:
	Plant(unsigned int id, const std::string& mesh);

	void update(float time);

	void onCreate(unsigned int creator = 0);
	void onDestroy(unsigned int destroyer = 0);

	float getHideFactor() const { return mHideFactor; }
	const std::string& getSpecies() const { return mSpecies; }

	void setHideFactor(float factor) { mHideFactor = factor; }
	void setSpecies(const std::string& species) { mSpecies = species; }
	void setHideRadius(float radius) { mHideRadius = radius; }
protected:
	float							mHideFactor;
	float							mHideRadius;
	std::map<std::string, float>	mResources;
	std::string						mSpecies;
};
