#include "resource.h"
#include <functional>

Resource::Resource(unsigned long id) : id(id)
{

}

Resource::Resource(const Resource &other)
{
    this->id = other.id;
}

unsigned long Resource::getID() const
{
    return id;
}

bool Resource::operator==(const Resource &other) const
{
    return this->id == other.id;
}

Resource &Resource::operator=(const Resource &other)
{
    if (this == &other) return *this;

    this->id = other.id;
    return *this;
}
