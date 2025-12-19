#pragma once

#include "Dependencies.h"
#include "Object.h"

class Resource : public Object
{
public:
	Resource(unsigned int id, const std::string& mesh);

	virtual void update(float time);
protected:
	std::map<std::string, float> mMaximalResource;
	std::map<std::string, float> mCurrentResource;
	std::map<std::string, float> mProduceResource;
};
