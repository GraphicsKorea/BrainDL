//
// Created by Danny Jang on 2021/11/23.
//

#include <catch.hpp>
#include <brain/intrusive_ptr.h>
#include <brain/body.h>

namespace {

class base : public brain::body {
public:
    static std::atomic_uint64_t instance_count;

    base()
            :brain::body()
    {
        ++instance_count;
    }

    ~base() override
    {
        --instance_count;
    }
};

std::atomic_uint64_t base::instance_count{0};

class x : public base { };
class y : public x { };

} //unnamed

TEST_CASE("[intrusive_ptr] constructor", "[intrusive_ptr]")
{
    {
        brain::intrusive_ptr<x> ptr;
        REQUIRE_FALSE(ptr.get());
    }

    {
        brain::intrusive_ptr<x> ptr(nullptr);
        REQUIRE_FALSE(ptr.get());
    }

    {
        auto* obj = new x();
        REQUIRE(obj->use_count() == 0);

        brain::intrusive_ptr<x> ptr(obj);
        REQUIRE(ptr->use_count() == 1);
    }

    {
        REQUIRE(base::instance_count == 0);
        x* obj = new x();
        REQUIRE(obj->use_count() == 0);
        REQUIRE(base::instance_count == 1);

        brain::intrusive_ptr<x> ptr(obj);
        REQUIRE(ptr->use_count() == 1);
    }

    {
        brain::intrusive_ptr<x> ptr1;
        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    {
        brain::intrusive_ptr<y> ptr1;
        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    {
        brain::intrusive_ptr<x> ptr1(nullptr);
        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    {
        brain::intrusive_ptr<y> ptr1(nullptr);
        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    {
        REQUIRE(base::instance_count == 0);
        brain::intrusive_ptr<x> ptr1(new x());
        REQUIRE(base::instance_count == 1);

        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    {
        REQUIRE(base::instance_count == 0);
        brain::intrusive_ptr<y> ptr1(new y());
        REQUIRE(base::instance_count == 1);

        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    {
        brain::intrusive_ptr<x> ptr1(new x());
        REQUIRE(ptr1);

        brain::intrusive_ptr<x> ptr2(std::move(ptr1));
        REQUIRE_FALSE(ptr1);
        REQUIRE(ptr2);
    }

    {
        brain::intrusive_ptr<y> ptr1(new y());
        REQUIRE(ptr1);

        brain::intrusive_ptr<x> ptr2(std::move(ptr1));
        REQUIRE_FALSE(ptr1);
        REQUIRE(ptr2);
    }
}

TEST_CASE("[intrusive_ptr] destructor", "[intrusive_ptr]")
{
    REQUIRE(base::instance_count == 0);
    brain::intrusive_ptr<x> ptr1(new x());
    REQUIRE(ptr1->use_count() == 1);
    REQUIRE(base::instance_count == 1);

    {
        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1->use_count() == 2);
    }

    REQUIRE(ptr1->use_count() == 1);
    REQUIRE(base::instance_count == 1);
}

TEST_CASE("[intrusive_ptr] assign", "[intrusive_ptr]")
{
    {
        brain::intrusive_ptr<x> ptr1(new x());
        REQUIRE(ptr1);

        brain::intrusive_ptr<x> ptr2 = ptr1;
        REQUIRE(ptr1 == ptr2);
    }

    {
        brain::intrusive_ptr<x> ptr1(new x());
        REQUIRE(ptr1);

        brain::intrusive_ptr<x> ptr2 = std::move(ptr1);
        REQUIRE_FALSE(ptr1);
        REQUIRE(ptr2);
    }

    {
        brain::intrusive_ptr<x> ptr1(new x());
        REQUIRE(ptr1);

        brain::intrusive_ptr<x> ptr2;
        REQUIRE_FALSE(ptr2);

        std::swap(ptr1, ptr2);
        REQUIRE_FALSE(ptr1);
        REQUIRE(ptr2);
    }

    {
        brain::intrusive_ptr<x> ptr1(new x());
        REQUIRE(ptr1);

        brain::intrusive_ptr<x> ptr2(new x());
        REQUIRE(ptr1);

        ptr2 = std::move(ptr1);
        REQUIRE_FALSE(ptr1);
        REQUIRE(ptr2);
    }
}

TEST_CASE("[intrusive_ptr] conversion", "[intrusive_ptr]")
{
    {
        brain::intrusive_ptr<x> ptr;
        REQUIRE_FALSE(ptr);
    }

    {
        brain::intrusive_ptr<x> ptr(new x());
        REQUIRE(ptr);
    }
}

TEST_CASE("[intrusive_ptr] reset", "[intrusive_ptr]")
{
    {
        brain::intrusive_ptr<x> ptr;
        REQUIRE_FALSE(ptr.get());

        ptr.reset();
        REQUIRE_FALSE(ptr.get());

        REQUIRE(base::instance_count == 0);
        auto* obj = new x;
        REQUIRE(obj->use_count() == 0);
        REQUIRE(base::instance_count == 1);

        ptr.reset(obj);
        REQUIRE(ptr->use_count() == 1);

        ptr.reset();
        REQUIRE_FALSE(ptr.get());
        REQUIRE(base::instance_count == 0);
    }

    {
        REQUIRE(base::instance_count == 0);
        brain::intrusive_ptr<x> ptr(new x());
        REQUIRE(ptr.get());
        REQUIRE(ptr->use_count() == 1);
        REQUIRE(base::instance_count == 1);

        ptr.reset(nullptr);
        REQUIRE_FALSE(ptr.get());
        REQUIRE(base::instance_count == 0);
    }

    {
        REQUIRE(base::instance_count == 0);
        brain::intrusive_ptr<x> ptr(new x());
        REQUIRE(ptr.get());
        REQUIRE(ptr->use_count() == 1);
        REQUIRE(base::instance_count == 1);

        ptr.reset();
        REQUIRE_FALSE(ptr.get());
        REQUIRE(base::instance_count == 0);
    }
}

TEST_CASE("[intrusive_ptr] detach", "[intrusive_ptr]")
{
    {
        brain::intrusive_ptr<x> ptr;
        REQUIRE_FALSE(ptr.get());

        auto* obj = ptr.detach();
        REQUIRE_FALSE(obj);
    }

    {
        REQUIRE(base::instance_count == 0);
        auto* obj = new x();
        REQUIRE(obj->use_count() == 0);
        REQUIRE(base::instance_count == 1);

        brain::intrusive_ptr<x> ptr(obj);
        REQUIRE(ptr.get() == obj);
        REQUIRE(ptr->use_count() == 1);

        auto* detached = ptr.detach();
        REQUIRE_FALSE(ptr.get());
        REQUIRE(detached == obj);
        REQUIRE(detached->use_count() == 1);

        detached->release();
        REQUIRE(base::instance_count == 0);
    }
}

TEST_CASE("[intrusive_ptr] get", "[intrusive_ptr]")
{
    {
        brain::intrusive_ptr<x> ptr;
        REQUIRE_FALSE(ptr.get());
    }

    {
        REQUIRE(base::instance_count == 0);
        auto* obj = new x();
        REQUIRE(base::instance_count == 1);

        brain::intrusive_ptr<x> ptr(obj);
        REQUIRE(ptr);
        REQUIRE(ptr.get() == obj);
    }
}

TEST_CASE("[intrusive_ptr] comparison", "[intrusive_ptr]")
{
    {
        REQUIRE(base::instance_count == 0);
        auto* obj = new x();
        REQUIRE(base::instance_count == 1);

        brain::intrusive_ptr<x> ptr(obj);
        REQUIRE(ptr.get());

        REQUIRE(ptr == ptr);
        REQUIRE(ptr.get() == ptr.get());
    }

    {
        REQUIRE(base::instance_count == 0);
        brain::intrusive_ptr<x> ptr1(new x());
        REQUIRE(ptr1.get());
        REQUIRE(base::instance_count == 1);

        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1->use_count() == 2);

        REQUIRE(ptr1 == ptr2);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    {
        REQUIRE(base::instance_count == 0);
        brain::intrusive_ptr<y> ptr1(new y());
        REQUIRE(ptr1.get());
        REQUIRE(base::instance_count == 1);

        brain::intrusive_ptr<x> ptr2(ptr1);
        REQUIRE(ptr1->use_count() == 2);

        REQUIRE(ptr1 == ptr2);
        REQUIRE(ptr1.get() == ptr2.get());
    }

    {
        REQUIRE(base::instance_count == 0);
        brain::intrusive_ptr<x> ptr1(new x());
        REQUIRE(ptr1.get());
        brain::intrusive_ptr<x> ptr2(new x());
        REQUIRE(ptr2.get());
        REQUIRE(base::instance_count == 2);

        REQUIRE(ptr1 != ptr2);
        REQUIRE(ptr1.get() != ptr2.get());
    }
}
