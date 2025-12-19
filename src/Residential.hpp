#pragma once

#include "PCH.hpp"

#include "Structure.hpp"

class Residential : public Structure
{
public:
    Residential(const std::string& name, Scene* scene) : Structure(name, scene), residents(0)
    {
    }

    virtual void load();

    virtual void unload();

    unsigned int getResidents() const
    {
        return residents;
    }
protected:
    unsigned int residents;
};
