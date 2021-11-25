//
// Created by Danny Jang on 2021/11/16.
//

#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>
#include <brain/tensor.h>
#include <brain/variable.h>

void print(const std::string& msg, brain::variable& v)
{
    auto data = v.data();
    std::cout << msg << data << std::endl;
}

TEST_CASE("[variable] make", "[variable][development]")
{
    // brain::variable v;
    {
        brain::tensor data(1.0);
        auto x = brain::variable::make(data);
        print("x is ", x);

        x.data(brain::tensor(2.0));
        print("x is ", x);
    }

    {
        auto x = brain::variable::make(brain::tensor(1));
        auto y = brain::variable::make(brain::tensor(1));
        if (x == y) {
            int k = 10;
        }

    }

    REQUIRE(true == true);
}