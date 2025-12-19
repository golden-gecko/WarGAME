#include "Dependencies.h"
#include "Graphics.h"
#include "Resource.h"

Resource::Resource(unsigned int id, const std::string& mesh) : Object(id, OT_RESOURCE, mesh)
{
}

void Resource::update(float time)
{
}
