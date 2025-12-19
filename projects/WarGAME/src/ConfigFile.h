#pragma once

#include "Dependencies.h"

class ConfigFile : public Ogre::ConfigFile
{
public:
	ConfigFile(const std::string& name) : Ogre::ConfigFile()
	{
		load(name);
	}

	std::string getString(const std::string& key, const std::string& section,
		const std::string& defaultValue = Ogre::StringUtil::BLANK) const
	{
		return getSetting(key, section, defaultValue);
	}

	float getFloat(const std::string& key, const std::string& section,
		const std::string& defaultValue = Ogre::StringUtil::BLANK) const
	{
		return Ogre::StringConverter::parseReal(getSetting(key, section, defaultValue));
	}

	unsigned int getUnInt(const std::string& key, const std::string& section,
		const std::string& defaultValue = Ogre::StringUtil::BLANK) const
	{
		return Ogre::StringConverter::parseUnsignedInt(getSetting(key, section, defaultValue));
	}
};
