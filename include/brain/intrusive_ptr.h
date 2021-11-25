//
// Created by Danny Jang on 2021/11/23.
//

#ifndef BRAIN_INTRUSIVE_PTR_H
#define BRAIN_INTRUSIVE_PTR_H

#include <algorithm>

namespace brain {

/// intrusive_ptr is smart pointer that retains ownership of an object.
/// \tparam T object type.
template<typename T>
class intrusive_ptr final {
public:
    /// default constructor.
    intrusive_ptr()
            :_ptr{nullptr}
    {
    }

    /// construct.
    /// \param ptr pointer to an object.
    explicit intrusive_ptr(T* ptr)
            :_ptr{ptr}
    {
        if (_ptr) {
            _ptr->reference();
        }
    }

    /// copy constructor.
    /// \param rhs const reference to an intrusive_ptr.
    intrusive_ptr(const intrusive_ptr& rhs)
            :_ptr{rhs._ptr}
    {
        if (_ptr) {
            _ptr->reference();
        }
    }

    /// copy constructor.
    /// \tparam U object type.
    /// \param rhs const reference to an intrusive_ptr.
    template<typename U>
    explicit intrusive_ptr(const intrusive_ptr<U>& rhs)
            :_ptr{rhs.get()}
    {
        if (_ptr) {
            _ptr->reference();
        }
    }

    /// move constructor.
    /// \param rhs reference to an intrusive_ptr.
    intrusive_ptr(intrusive_ptr&& rhs) noexcept
            :_ptr{rhs.detach()}
    {
    }

    /// move constructor
    /// \tparam U object type.
    /// \param rhs reference to an intrusive_ptr to be moved.
    template<typename U>
    explicit intrusive_ptr(intrusive_ptr<U>&& rhs)
            :_ptr{rhs.detach()}
    {
    }

    /// destructor.
    ~intrusive_ptr()
    {
        if (_ptr) {
            _ptr->release();
        }
    }

    /// assign operator.
    /// \param rhs const reference to an intrusive_ptr.
    /// \return reference to an intrusive_ptr.
    intrusive_ptr& operator=(const intrusive_ptr& rhs)
    {
        intrusive_ptr(rhs).swap(*this);
        return *this;
    }

    /// assign operator.
    /// \param ptr pointer to an object.
    /// \return reference to an intrusive_ptr.
    intrusive_ptr& operator=(T* ptr)
    {
        intrusive_ptr(ptr).swap(*this);
        return *this;
    }

    /// move assign operator.
    /// \param rhs reference to an intrusive_ptr to be moved.
    /// \return reference to an intrusive_ptr.
    intrusive_ptr& operator=(intrusive_ptr&& rhs) noexcept
    {
        intrusive_ptr(std::move(rhs)).swap(*this);
        return *this;
    }

    /// move assign operator.
    /// \tparam U object type.
    /// \param rhs reference to an intrusive_ptr to be moved.
    /// \return reference to an intrusive_ptr.
    template<class U>
    intrusive_ptr& operator=(intrusive_ptr<U>&& rhs) noexcept
    {
        intrusive_ptr(std::move(rhs)).swap(*this);
        return *this;
    }

    /// check if a stored pointer is not nullptr.
    /// \return true a stored pointer is not nullptr, false otherwise.
    explicit operator bool() const
    {
        return _ptr;
    }

    /// pointer operator.
    /// \return pointer to an object.
    T* operator->() const
    {
        return _ptr;
    }

    /// dereference operator.
    /// \return reference to an object.
    T& operator*() const
    {
        return *_ptr;
    }

    /// release the ownership of an object.
    void reset()
    {
        intrusive_ptr().swap(*this);
    }

    /// replace an object.
    /// \param ptr pointer to an object.
    void reset(T* ptr)
    {
        intrusive_ptr(ptr).swap(*this);
    }

    /// detach from an object.
    /// \return pointer to an object.
    auto detach()
    {
        auto ptr = _ptr;
        _ptr = nullptr;
        return ptr;
    }

    /// retrieve a pointer to an object.
    /// \return pointer to an object.
    auto get() const
    {
        return _ptr;
    }

private:
    /// swap a value with rhs.
    /// \param rhs reference to an intrusive_ptr.
    void swap(intrusive_ptr& rhs) noexcept
    {
        std::swap(_ptr, rhs._ptr);
    }

private:
    T* _ptr;
};

/// comparison operator.
/// \tparam T object type.
/// \tparam U object type.
/// \param lhs const reference to an intrusive_ptr to compare.
/// \param rhs const reference to an intrusive_ptr to compare.
/// \return true if objects are same, false otherwise.
template<typename T, typename U>
inline auto operator==(const intrusive_ptr<T>& lhs, const intrusive_ptr<U>& rhs)
{
    return lhs.get() == rhs.get();
}

/// comparison operator.
/// \tparam T object type.
/// \tparam U object type.
/// \param lhs const reference to an intrusive_ptr to compare.
/// \param rhs const reference to an intrusive_ptr to compare.
/// \return true if objects are different, false otherwise.
template<typename T, typename U>
inline auto operator!=(const intrusive_ptr<T>& lhs, const intrusive_ptr<U>& rhs)
{
    return lhs.get() != rhs.get();
}

/// comparison operator.
/// \tparam T object type.
/// \tparam U object type
/// \param lhs const reference to an intrusive_ptr to compare.
/// \param rhs pointer to compare.
/// \return true if objects are same, false otherwise.
template<typename T, typename U>
inline auto operator==(const intrusive_ptr<T>& lhs, U* rhs)
{
    return lhs.get() == rhs;
}

/// comparison operator.
/// \tparam T object type.
/// \tparam U object type
/// \param lhs const reference to an intrusive_ptr to compare.
/// \param rhs pointer to compare.
/// \return true if objects are different, false otherwise.
template<typename T, typename U>
inline auto operator!=(const intrusive_ptr<T>& lhs, U* rhs)
{
    return lhs.get() != rhs;
}

/// comparison operator.
/// \tparam T object type.
/// \tparam U object type
/// \param lhs pointer to compare.
/// \param rhs const reference to an intrusive_ptr to compare.
/// \return true if objects are same, false otherwise.
template<typename T, typename U>
inline auto operator==(T* lhs, const intrusive_ptr<U>& rhs)
{
    return lhs == rhs.get();
}

/// comparison operator.
/// \tparam T object type.
/// \tparam U object type
/// \param lhs pointer to compare.
/// \param rhs const reference to an intrusive_ptr to compare.
/// \return true if objects are different, false otherwise.
template<typename T, typename U>
inline auto operator!=(T* lhs, const intrusive_ptr<U>& rhs)
{
    return lhs != rhs.get();
}

} //brain

#endif //BRAIN_INTRUSIVE_PTR_H
