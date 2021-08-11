#include <iostream>
#include "ACL.h"
#include "resource.h"
#include "subject.h"

int main()
{
    Resource res(1), res2(2), res3(3);
    Subject sub1("user1");
    Subject sub2("user2");
    Subject sub3("user3");
    ACL::ACL<Subject, Resource> acl;
    acl.Add(sub1, res);
    std::cout << (acl.IsAllowed(sub1, res) ? "true" : "false") << std::endl;
    acl.ForbidAccess(sub2, res);
    std::cout << (acl.IsAllowed(sub2, res) ? "true" : "false") << std::endl;
    acl.Add(sub3, res3, ACL::forbid);
    std::cout << (acl.IsAllowed(sub3, res3) ? "true" : "false") << std::endl;
    acl.AllowAccess(sub2, res3);
    std::cout << (acl.IsAllowed(sub2, res3) ? "true" : "false") << std::endl;
    return 0;
}
