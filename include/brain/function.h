//
// Created by Danny Jang on 2021/11/18.
//

#ifndef BRAIN_FUNCTION_H
#define BRAIN_FUNCTION_H

#include <vector>

#include "brain/handle.h"

namespace brain {

class variable;

class function : public handle {
public:
    function();

    explicit function(body* ptr);

    std::vector<variable> operator()(const std::vector<variable>& inputs);

    std::vector<variable> forward(const std::vector<variable>& inputs);

    std::vector<variable> backward(const std::vector<variable>& inputs);

    std::vector<variable> inputs();

    std::vector<variable> outputs();

    std::string name();
};

class square final : public function {
public:
    static square make();

private:
    explicit square(body* ptr);
};

class exp final : public function {
public:
    static exp make();

private:
    explicit exp(body* ptr);
};

} //brain

#endif //BRAIN_FUNCTION_H
