//
// Created by Danny Jang on 2021/11/23.
//

#include "brain/tensor.h"

#include <numeric>
#include <utility>

#include "brain/body.h"

#include "BrainML/Device.h"
#include "BrainML/Buffer.h"

namespace brain {

namespace {

inline auto size(const std::vector<uint32_t>& shape)
{
    return std::accumulate(std::begin(shape), std::end(shape), 1, std::multiplies<>());
}

inline auto byte_size(const std::vector<uint32_t>& shape)
{
    return size(shape)*sizeof(float);
}

} //unnamed

tensor::tensor(float data)
        :_shape{1}, _data{data}
{
}

tensor::tensor(std::vector<uint32_t> shape, float* data)
        :_shape{std::move(shape)}, _data{*data}
{
}

float* tensor::map() const
{
    return &_data;
}

void tensor::unmap()
{
}

std::vector<uint32_t> tensor::shape() const
{
    return _shape;
}

tensor operator-(const tensor& lhs)
{
    auto result = -*lhs.map();
    return {lhs.shape(), &result};
}

tensor operator+(const tensor& lhs, float rhs)
{
    auto result = *lhs.map()+rhs;
    return {lhs.shape(), &result};
}

tensor operator+(float lhs, const tensor& rhs)
{
    auto result = lhs+*rhs.map();
    return {rhs.shape(), &result};
}

tensor operator-(const tensor& lhs, float rhs)
{
    auto result = *lhs.map()-rhs;
    return {lhs.shape(), &result};
}

tensor operator-(float lhs, const tensor& rhs)
{
    auto result = lhs-*rhs.map();
    return {rhs.shape(), &result};
}

tensor operator*(const tensor& lhs, const tensor& rhs)
{
    auto result = *lhs.map()**rhs.map();
    return tensor{result};
}

tensor operator*(const tensor& lhs, float rhs)
{
    auto result = *lhs.map()*rhs;
    return tensor{result};
}

tensor operator*(float lhs, const tensor& rhs)
{
    auto result = lhs**rhs.map();
    return tensor{result};
}

} //brain