//
// Created by Danny Jang on 2021/11/18.
//

#include "brain/function.h"

#include <cmath>

#include "brain/tensor.h"
#include "brain/body.h"
#include "brain/variable.h"
#include "detail/function.h"

namespace brain {

function::function()
        :handle()
{
}

function::function(body* ptr)
        :handle{ptr}
{
}

std::vector<variable> function::operator()(const std::vector<variable>& inputs)
{
    return body_cast<detail::function>(*this).forward(inputs);
}

std::vector<variable> function::forward(const std::vector<variable>& inputs)
{
    return body_cast<detail::function>(*this).forward(inputs);
}

std::vector<variable> function::backward(const std::vector<variable>& inputs)
{
    return body_cast<detail::function>(*this).backward(inputs);
}

std::vector<variable> function::inputs()
{
    return body_cast<detail::function>(*this)._inputs;
}

std::vector<variable> function::outputs()
{
    return body_cast<detail::function>(*this)._outputs;
}

std::string function::name()
{
    return body_cast<detail::function>(*this)._name;
}

square square::make()
{
    return square(new detail::square());
}

square::square(body* ptr)
        :function{ptr}
{
}

exp exp::make()
{
    return exp(new detail::exp());
}

exp::exp(body* ptr)
        :function{ptr}
{
}

} //brain
