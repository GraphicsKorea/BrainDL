//
// Created by Danny Jang on 2021/11/29.
//

#ifndef BRAIN_DETAIL_FUNCTION_H
#define BRAIN_DETAIL_FUNCTION_H

#include <string>
#include <vector>
#include <functional>

#include "brain/body.h"

namespace brain {

class variable;

namespace detail {

class function : public body {
public:
    function();

    std::vector<brain::variable> forward(const std::vector<brain::variable>& inputs);

    // 변수 이름이 inputs 이 아니라 grads or gradients 로 변경
    std::vector<brain::variable> backward(const std::vector<brain::variable>& inputs);

protected:
    std::function<std::vector<brain::variable>(const std::vector<brain::variable>& inputs)> _forward;
    std::function<std::vector<brain::variable>(const std::vector<brain::variable>& inputs)> _backward;

protected:
public:
    std::string _name;
    std::vector<brain::variable> _inputs;
    std::vector<brain::variable> _outputs;
};

class square : public function {
public:
    square();
};

class exp : public function {
public:
    exp();
};

} //brain::detail

} //brain

#endif //BRAIN_DETAIL_FUNCTION_H
