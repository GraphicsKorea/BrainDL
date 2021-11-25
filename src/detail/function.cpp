//
// Created by Danny Jang on 2021/11/29.
//

#include "function.h"

#include "brain/variable.h"
#include "brain/function.h"

#include <cmath>
#include "brain/tensor.h"

namespace brain::detail {

function::function()
        :body()
{
}

std::vector<brain::variable> function::forward(const std::vector<brain::variable>& inputs)
{
    _inputs = inputs;
    _outputs = _forward(inputs);

    for (auto& output: _outputs) {
        output.creator() = brain::function(this);
    }

    return _outputs;
}

std::vector<brain::variable> function::backward(const std::vector<brain::variable>& inputs)
{
    return _backward(inputs);
}

square::square()
{
    _name = "square";
    _forward = [this](const std::vector<brain::variable>& inputs) {
      variable v = inputs[0];
      auto x = v.data();
      tensor y = x * x;
      _outputs.emplace_back(variable::make(y));

      _inputs = inputs;

      return _outputs;
    };

    _backward = [this](const std::vector<brain::variable>& inputs) {
      auto& x = _inputs[0].data();
      auto gy = inputs[0];
      auto gx = 2.0f * x * gy.grad();
      _inputs[0].grad(gx);
      std::vector<variable> result;
      result.push_back(_inputs[0]);
      return result;
    };
}

exp::exp()
        :function()
{
    _name = "exp";
    _forward = [this](const std::vector<brain::variable>& inputs) {
      brain::variable v = inputs[0];
      auto x = v.data();
      auto y = xt::exp(x);

      _inputs = inputs;
      _outputs.push_back(brain::variable::make(tensor(y)));
      return _outputs;
    };

    _backward = [this](const std::vector<brain::variable>& inputs) {
      auto res = brain::exp::make().forward(_inputs);
      auto gy = inputs[0];
      auto gx = res[0].data() * gy.grad();
      _inputs[0].grad(gx);

      std::vector<variable> result;
      result.push_back(_inputs[0]);
      return result;
    };
}

} //brain::detail

