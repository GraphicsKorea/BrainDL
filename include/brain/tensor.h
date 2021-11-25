//
// Created by Danny Jang on 2021/11/24.
//

#ifndef BRAIN_TENSOR_H
#define BRAIN_TENSOR_H

#include <vector>
#include <xtensor.hpp>

namespace brain {

using tensor = xt::xarray<float>;

#if 0

class tensor final {
public:
    explicit tensor(float data);

    tensor(std::vector<uint32_t> shape, float* data);

    float* map() const;

    void unmap();

    [[nodiscard]]
    std::vector<uint32_t> shape() const;

private:
    std::vector<uint32_t> _shape;
    mutable float _data;
};

tensor operator-(const tensor& lhs);

tensor operator+(const tensor& lhs, float rhs);

tensor operator+(float lhs, const tensor& rhs);

tensor operator-(const tensor& lhs, float rhs);

tensor operator-(float lhs, const tensor& rhs);

tensor operator*(const tensor& lhs, const tensor& rhs);

tensor operator*(const tensor& lhs, float rhs);

tensor operator*(float lhs, const tensor& rhs);

#endif

} //brain

#endif //BRAIN_TENSOR_H
