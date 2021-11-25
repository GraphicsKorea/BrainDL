//
// Created by Danny Jang on 2021/11/29.
//

#ifndef BRAIN_DETAIL_VARIABLE_H
#define BRAIN_DETAIL_VARIABLE_H

#include "brain/body.h"
#include "brain/tensor.h"
#include "brain/function.h"

namespace brain::detail {

class variable final : public body {
public:
    explicit variable(tensor data);

    void backward();

    inline tensor* data()
    {
        return &_data;
    }

    inline void data(tensor data)
    {
        _data = std::move(data);
    }

    inline tensor* grad()
    {
        return &_grad;
    }

    inline void grad(tensor grad)
    {
        _grad = std::move(grad);
    }

private:
    brain::tensor _data;
    brain::tensor _grad;

public:
    brain::function creator;
};

} //brain::detail

#endif //BRAIN_DETAIL_VARIABLE_H
