#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "ACL.h"
#include "resource.h"
#include "subject.h"

class ACLTest : public ::testing::Test {
protected:
    virtual void SetUp() override
    {
        res = Resource(1);
        res2 = Resource(2);
        sub = Subject("user");
    }
    virtual void TearDown() override
    {

    }
    Resource res;
    Resource res2;
    Subject sub;
};


TEST_F(ACLTest, AddTest)
{
    ACL::ACL<Subject, Resource> acl;
    EXPECT_THROW(acl.IsAllowed(sub, res), std::runtime_error);

    acl.Add(sub, res);
    EXPECT_TRUE(acl.IsAllowed(sub, res));
    acl.Add(sub, res2, ACL::forbid);
    EXPECT_FALSE(acl.IsAllowed(sub, res2));
}

TEST_F(ACLTest, DelTest)
{
    ACL::ACL<Subject, Resource> acl;
    acl.Add(sub, res);
    EXPECT_TRUE(acl.IsAllowed(sub, res));
    EXPECT_THROW(acl.Add(sub, res), std::runtime_error);
    acl.Del(sub, res);
    EXPECT_FALSE(acl.IsAllowed(sub, res));
    acl.Del(res);
    EXPECT_THROW(acl.IsAllowed(sub, res), std::runtime_error);
}

TEST_F(ACLTest, AllowAccessTest)
{
    ACL::ACL<Subject, Resource> acl;
    EXPECT_THROW(acl.AllowAccess(sub, res), std::runtime_error);
    acl.Add(sub, res, ACL::forbid);
    EXPECT_FALSE(acl.IsAllowed(sub, res));
    acl.AllowAccess(sub, res);
    EXPECT_TRUE(acl.IsAllowed(sub, res));
}

TEST_F(ACLTest, ForbidAccessTest)
{
    ACL::ACL<Subject, Resource> acl;
    EXPECT_THROW(acl.ForbidAccess(sub, res);, std::runtime_error);
    acl.Add(sub, res);
    EXPECT_TRUE(acl.IsAllowed(sub, res));
    acl.ForbidAccess(sub, res);
    EXPECT_FALSE(acl.IsAllowed(sub, res));
}

TEST_F(ACLTest, MultipleResourceTest)
{
    ACL::ACL<Subject, Resource> acl;
    for(int i = 0; i < 1000; i++) {
        acl.Add(sub, Resource(i));
    }
    for(int i = 0; i < 1000; i++) {
        EXPECT_TRUE(acl.IsAllowed(sub, Resource(i)));
    }
}
