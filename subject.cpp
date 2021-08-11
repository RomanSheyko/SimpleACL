#include "subject.h"

Subject::Subject(const std::string name) : name(name)
{

}

Subject::Subject(const Subject &other)
{
    this->name = other.name;
}

const std::string &Subject::getName() const
{
    return name;
}

bool Subject::operator==(const Subject &other) const
{
    return this->name == other.name;
}

Subject &Subject::operator=(const Subject &other)
{
    if (this == &other) return *this;

    this->name = other.name;
    return *this;
}
