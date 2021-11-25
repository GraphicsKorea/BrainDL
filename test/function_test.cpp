//
// Created by Danny Jang on 2021/11/25.
//

#include <catch2/catch.hpp>
#include <spdlog/spdlog.h>
#include <brain/tensor.h>
#include <brain/variable.h>
#include <brain/function.h>

void println(brain::variable& v)
{
    auto data = v.data();
    std::cout << "value: " << v.data() << ", grad: " << v.grad() << std::endl;
}

void println(brain::tensor& t)
{
    std::cout << t << std::endl;
}

template<typename T>
float numeric_diff(T f, brain::variable x, float eps = 1.0e-2)
{
    auto x0 = brain::variable::make(x.data() - eps);
    auto x1 = brain::variable::make(x.data() + eps);
    auto y0 = f({x0})[0];
    auto y1 = f({x1})[0];
    return ((y1.data() - y0.data()) / (xt::xarray<float>(2.0) * eps))[0];
}

std::vector<brain::variable> func(const std::vector<brain::variable>& x)
{
    auto A = brain::square::make();
    auto B = brain::exp::make();
    auto C = brain::square::make();
    return C(B(A(x)));
}

TEST_CASE("[function] make", "[function][development]")
{
    {
        auto x = brain::variable::make(brain::tensor(10));
        brain::function f = brain::square::make();
        // auto y = f.forward({x});
        auto y = f({x});
        // println("y is ", y[0]);
    }

    {
        auto A = brain::square::make();
        auto B = brain::exp::make();
        auto C = brain::square::make();

        auto x = brain::variable::make(brain::tensor(0.5));
        auto a = A({x});
        auto b = B(a);
        auto y = C(b);
        // println("y is ", y[0]);

        y[0].grad(brain::tensor(1.0f));
        b = C.backward({y[0]});
        a = B.backward(b);
        x = A.backward(a)[0];
        println(x);

        y[0].grad(brain::tensor(1.0f));
        y[0].backward();
        println(x);
    }

    {
        auto f = brain::square::make();
        auto x = brain::variable::make(brain::tensor(2.0));
        auto dy = numeric_diff(f, x);
        // spdlog::info("dy: {}", dy);
    }

    {
        auto x = brain::variable::make(brain::tensor(0.5));
        auto dy = numeric_diff(func, x);
        // spdlog::info("dy: {}", dy);
    }
}