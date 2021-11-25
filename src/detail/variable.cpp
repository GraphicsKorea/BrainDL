//
// Created by Danny Jang on 2021/11/29.
//

#include "variable.h"

#include <vector>
#include <string>

#include "brain/variable.h"

namespace brain::detail {

variable::variable(tensor data)
        :_data{std::move(data)}, _grad{0.0f}, creator{}
{
}

void variable::backward()
{
    auto f = creator;
    if (f) {
        auto n = f.name();
        auto x = f.inputs();
        x = f.backward({brain::variable(this)});
        x[0].backward();
    }
}

} //brain::detail