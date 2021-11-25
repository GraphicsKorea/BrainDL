//
// Created by Danny Jang on 2021/11/23.
//

#include "brain/handle.h"

#include "brain/body.h"

namespace brain {

handle handle::make()
{
    return handle(new body());
}

handle::handle()
        :_ptr{}
{
}

handle::handle(body* ptr)
        :_ptr{ptr}
{
}

handle::handle(const handle& rhs)
        :_ptr{rhs._ptr}
{
}

handle::handle(handle&& rhs) noexcept
        :_ptr{std::move(rhs._ptr)}
{
}

handle::~handle()
{
}

handle& handle::operator=(const handle& rhs)
{
    handle(rhs).swap(*this);
    return *this;
}

handle& handle::operator=(handle&& rhs) noexcept
{
    handle(std::move(rhs)).swap(*this);
    return *this;
}

handle::operator bool() const
{
    return static_cast<bool>(_ptr);
}

void handle::reset()
{
    _ptr.reset();
}

body* handle::get() const
{
    return _ptr.get();
}

void handle::swap(handle& rhs) noexcept
{
    std::swap(_ptr, rhs._ptr);
}

} //brain
