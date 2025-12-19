#pragma once

#include "PCH.hpp"

#include "Object.hpp"

class Citizen : public Object
{
public:
    Citizen(const std::string& name, Scene* scene) : Object(name, scene)
    {
    }
};
