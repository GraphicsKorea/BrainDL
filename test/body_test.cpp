//
// Created by Danny Jang on 2021/11/23.
//

#include <catch.hpp>
#include <brain/body.h>

TEST_CASE("[body] constructor", "[body]")
{
    brain::body obj;
    REQUIRE(obj.use_count() == 0);
}

TEST_CASE("[body] destructor", "[body]")
{
    auto obj = new brain::body();
    delete obj;
}

TEST_CASE("[body] reference", "[body]")
{
    auto obj = new brain::body();
    REQUIRE(obj->use_count() == 0);

    obj->reference();
    REQUIRE(obj->use_count() == 1);

    obj->reference();
    REQUIRE(obj->use_count() == 2);

    obj->release();
    REQUIRE(obj->use_count() == 1);

    obj->release();
}

TEST_CASE("[body] release", "[body]")
{
    auto obj = new brain::body();
    REQUIRE(obj->use_count() == 0);

    obj->reference();
    REQUIRE(obj->use_count() == 1);

    obj->release();
}