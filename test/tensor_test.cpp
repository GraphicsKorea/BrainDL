//
// Created by Danny Jang on 2021/11/24.
//

#include <catch.hpp>
#include <brain/tensor.h>

TEST_CASE("[tensor] constructor", "[tensor][development]")
{

    {
        float data = 1.0;
        brain::tensor x({1}, &data);
    }

    {
//        auto x = brain::tensor::make({1}, {1.0f});
//        REQUIRE(x);
//
//        brain::tensor y(std::move(x));
//        REQUIRE(y);
//        REQUIRE_FALSE(x);
    }
}

TEST_CASE("[tensor] destructor", "[tensor][development]")
{

}

TEST_CASE("[tensor] add", "[tensor][development]")
{
    {
        float data = 1.0;
        brain::tensor x({1}, &data);
        auto y = x + 1.0f;
        int k = 10;
    }

    {
        float data = 1.0;
        brain::tensor x({1}, &data);
        auto y = 1.0f + x;
    }
}
