#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <functional>

/**
  * \brief This class can be used as base class as a resource for the ACL
  * \details In this realization each resource is determined by its ID. Using this class as the base class for your
  * own resource can give you the ability to store any information in it and use it in ACL.
*/
class Resource
{
public:
    Resource() : id(0) {}
    Resource(unsigned long id);
    Resource(const Resource& other);
    virtual ~Resource() = default;
    unsigned long getID() const;
    bool operator==(const Resource &other) const;
    Resource& operator=(const Resource& other);
    unsigned long id;
};

namespace std {

  template <>
  struct hash<Resource>
  {
    std::size_t operator()(const Resource& res) const
    {
      return std::hash<unsigned long>()(res.getID());
    }
  };

}

#endif // RESOURCE_H
