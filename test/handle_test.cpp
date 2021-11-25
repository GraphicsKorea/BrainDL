//
// Created by Danny Jang on 2021/11/23.
//

#include <catch.hpp>
#include <brain/handle.h>

TEST_CASE("[handle] make", "[handle]")
{
    auto hnd = brain::handle::make();
    REQUIRE(hnd);
}

TEST_CASE("[handle] constructor", "[handle]")
{
    {
        brain::handle hnd;
        REQUIRE_FALSE(hnd);
    }

    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        brain::handle hnd2(hnd1);
        REQUIRE(hnd2);
    }

    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        brain::handle hnd2(std::move(hnd1));
        REQUIRE_FALSE(hnd1);
        REQUIRE(hnd2);
    }
}

TEST_CASE("[handle] destructor", "handle")
{
    brain::handle hnd1;
    REQUIRE_FALSE(hnd1);

    {
        auto hnd2 = brain::handle::make();
        REQUIRE(hnd2);

        hnd1 = hnd2;
        REQUIRE(hnd1 == hnd2);
    }

    REQUIRE(hnd1);
}

TEST_CASE("[handle] assign", "[handle]")
{
    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        auto hnd2 = hnd1;
        REQUIRE(hnd2);
    }

    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        auto hnd2 = std::move(hnd1);
        REQUIRE_FALSE(hnd1);
        REQUIRE(hnd2);
    }

    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        brain::handle hnd2;
        REQUIRE_FALSE(hnd2);

        std::swap(hnd1, hnd2);
        REQUIRE_FALSE(hnd1);
        REQUIRE(hnd2);
    }
}

TEST_CASE("[handle] comparison", "[handle]")
{
    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        auto hnd2 = hnd1;
        REQUIRE(hnd1 == hnd2);
    }

    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        brain::handle hnd2(hnd1);
        REQUIRE(hnd2);
        REQUIRE(hnd1 == hnd2);
    }

    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        brain::handle hnd2;
        REQUIRE(hnd1 != hnd2);
    }

    {
        auto hnd1 = brain::handle::make();
        REQUIRE(hnd1);

        auto hnd2 = brain::handle::make();
        REQUIRE(hnd2);
        REQUIRE(hnd1 != hnd2);
    }
}

TEST_CASE("[handle] conversion", "[handle]")
{
    {
        brain::handle hnd;
        REQUIRE_FALSE(hnd);
    }

    {
        auto hnd = brain::handle::make();
        REQUIRE(hnd);
    }
}

TEST_CASE("[handle] reset", "[handle]")
{
    auto hnd = brain::handle::make();
    REQUIRE(hnd);

    hnd.reset();
    REQUIRE_FALSE(hnd);
}

TEST_CASE("[handle] get", "[handle]")
{
    {
        brain::handle hnd;
        REQUIRE_FALSE(hnd);
    }

    {
        auto hnd = brain::handle::make();
        REQUIRE(hnd);
    }
}