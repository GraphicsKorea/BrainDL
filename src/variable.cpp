//
// Created by Danny Jang on 2021/11/17.
//

#include "brain/variable.h"

#include "detail/variable.h"

namespace brain {

variable variable::make(tensor data)
{
    return variable(new detail::variable(std::move(data)));
}

variable::variable()
        :handle()
{
}

variable::variable(body* ptr)
        :handle{ptr}
{
}

void variable::backward()
{
    body_cast<detail::variable>(*this).backward();
}

tensor& variable::data()
{
    return *body_cast<detail::variable>(*this).data();
}

void variable::data(tensor data)
{
    return body_cast<detail::variable>(*this).data(std::move(data));
}

tensor& variable::grad()
{
    return *body_cast<detail::variable>(*this).grad();
};

void variable::grad(tensor grad)
{
    return body_cast<detail::variable>(*this).grad(std::move(grad));
}

function& variable::creator()
{
    return body_cast<detail::variable>(*this).creator;
}

} //brain
