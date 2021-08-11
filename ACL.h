#ifndef ACL_H
#define ACL_H
#include <list>
#include <unordered_map>

namespace ACL {
enum {
    allowed = true,
    forbid = false
};

/**
  * \brief Realization of Access Control List
  * \details This realization of ACL stores the relationship between Subject and Resource. It uses
  * a hash table in order to provide fastest access to information about this relationship. When do you use
  * custom class you must provide a hash function and an equality operator for the Resource.
*/
template <class Subject, class Resource, class Hash = std::hash<Resource>,
          class KeyEqual = std::equal_to<Resource>>
class ACL {
public:
    ACL() = default;

    /**
      * \brief Add new resource, subject and relationship between them
      * \param[in] subj New subject relatated to the resource
      * \param[in] resource New resource
      * \param[in] access Relationship between subject and resource
      * \throws std::runtime_error if resource already exists
    */
    void Add(Subject subj, Resource resource, bool access = allowed) {
        if(storage.find(resource) != storage.end()) throw std::runtime_error("Resource already exists");
        storage[resource] = std::list<Subject>();
        if(access) AllowAccess(subj, resource);
    }

    /**
      * \brief Allows access for subject to given resource
      * \param[in] subj Subject
      * \param[in] resource Resource
      * \throws std::runtime_error if no such resource found
    */
    void AllowAccess(Subject subj, Resource resource) {
        try {
            auto& el = storage.at(resource);
            auto result = std::find(el.begin(), el.end(), subj);
            if(result == el.end()) {
                el.push_back(subj);
            }
        } catch (std::out_of_range& e) {
            throw std::runtime_error("No such resource");
        }
    }

    /**
      * \brief Forbid access for subject to given resource
      * \param[in] subj Subject
      * \param[in] resource Resource
      * \throws std::runtime_error if no such resource found
    */
    void ForbidAccess(Subject subj, Resource resource) {
        try {
            auto& el = storage.at(resource);
            auto result = std::find(el.begin(), el.end(), subj);
            if(result != el.end()) {
                el.erase(result);
            }
        } catch (std::out_of_range& e) {
            throw std::runtime_error("No such resource");
        }
    }

    /**
      * \brief Returns relationship between given subject and resource
      * \param[in] subj Subject
      * \param[in] resource Resource
      * \return true if access allowed and false otherwise
      * \throws std::runtime_error if no such resource found
    */
    bool IsAllowed(Subject subj, Resource resource) {
        try {
            auto& el = storage.at(resource);
            auto result = std::find(el.begin(), el.end(), subj);
            return result != el.end();
        } catch (std::out_of_range& e) {
            throw std::runtime_error("No such resource");
        }
    }

    /**
      * \brief Removes subject from given resource and destroys all relationships. Basically the same as ForbidAccess
      * \param[in] subj Subject
      * \param[in] resource Resource
      * \throws std::runtime_error if no such resource found
    */
    void Del(Subject subj, Resource resource) {
        ForbidAccess(subj, resource);
    }

    /**
      * \brief Removes resource
      * \param[in] subj Subject
      * \param[in] resource Resource
      * \throws std::runtime_error if no such resource found
    */
    void Del(Resource resource) {
        auto el = storage.find(resource);
        if(el != storage.end()) storage.erase(el);
        else throw std::runtime_error("No such resource");
    }

private:
    std::unordered_map<Resource, std::list<Subject>, Hash, KeyEqual> storage;
};

}

#endif // ACL_H
