#pragma once

#include "PCH.hpp"

#include "Structure.hpp"

class Industrial : public Structure
{
public:
    Industrial(const std::string& name, Scene* scene) : Structure(name, scene), workers(0)
    {
    }

    virtual void load();

    virtual void unload();

    unsigned int getWorkers() const
    {
        return workers;
    }
protected:
    unsigned int workers;
};
