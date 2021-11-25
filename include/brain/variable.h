//
// Created by Danny Jang on 2021/11/17.
//

#ifndef BRAIN_VARIABLE_H
#define BRAIN_VARIABLE_H

#include <memory>

#include "brain/handle.h"
#include "brain/function.h"

#include "brain/tensor.h"

namespace brain {

// class tensor;

class variable : public handle {
public:
    static variable make(tensor data);

    variable();

    explicit variable(body* ptr);

    void backward();

    [[nodiscard]]
    tensor& data();

    void data(tensor data);

    tensor& grad();

    void grad(tensor grad);

    function& creator();
};

} //brain

#endif //BRAIN_VARIABLE_H
