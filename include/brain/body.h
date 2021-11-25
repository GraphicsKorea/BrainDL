//
// Created by Danny Jang on 2021/11/23.
//

#ifndef BRAIN_OBJECT_H
#define BRAIN_OBJECT_H

#include <atomic>

namespace brain {

/// body is the base class for the managed body.
class body {
public:
    /// constructor.
    body();

    /// deleted copy constructor.
    /// \param rhs const reference to an body.
    body(const body& rhs) = delete;

    /// destructor.
    virtual ~body();

    /// deleted assign operator.
    /// \param rhs const reference to an body.
    /// \return reference to an body.
    body& operator=(const body& rhs) = delete;

    /// increase an body's use count.
    void reference();

    /// decrease an body's use count.
    void release();

    /// Retrieve the intrusive_ptr instance count managing an body.
    /// \return intrusive_ptr instance count.
    uint64_t use_count();

private:
    std::atomic_uint64_t _use_count;
};

///
/// \tparam T
/// \tparam U
/// \param handle
/// \return
template<typename T, typename U>
T& body_cast(U& handle)
{
    return static_cast<T&>(*handle.get());
}

///
/// \tparam T
/// \tparam U
/// \param handle
/// \return
template<typename T, typename U>
const T& body_cast(const U& handle)
{
    return static_cast<const T&>(*handle.get());
}

} //brain

#endif //BRAIN_OBJECT_H
