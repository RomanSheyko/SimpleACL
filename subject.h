#ifndef SUBJECT_H
#define SUBJECT_H
#include <string>

/**
  * \brief Simple subject class for ACL
  * \details In this realization every subject is defined by its name.
*/
class Subject
{
public:
    Subject() : name("") {}
    Subject(const std::string name);
    Subject(const Subject& other);
    const std::string& getName() const;
    bool operator==(const Subject &other) const;
    Subject& operator=(const Subject& other);
private:
    std::string name;
};

#endif // SUBJECT_H
