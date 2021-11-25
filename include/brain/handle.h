//
// Created by Danny Jang on 2021/11/23.
//

#ifndef BRAIN_HANDLE_H
#define BRAIN_HANDLE_H

#include "brain/intrusive_ptr.h"

namespace brain {

class body;

/// handle is a handle to control an body.
class handle {
public:
    /// make a new body.
    /// \return a handle to a new body.
    static handle make();

    /// default constructor.
    handle();

    /// constructor.
    /// \param ptr pointer to an body.
    explicit handle(body* ptr);

    /// copy constructor.
    /// \param rhs const reference to a handle.
    handle(const handle& rhs);

    /// move constructor.
    /// \param rhs reference to a handle.
    handle(handle&& rhs) noexcept;

    /// destructor.
    ~handle();

    /// assign operator.
    /// \param rhs const reference to a handle.
    /// \return reference to a handle.
    handle& operator=(const handle& rhs);

    /// move assign operator.
    /// \param rhs reference to a handle.
    /// \return reference to a moved handle.
    handle& operator=(handle&& rhs) noexcept;

    /// check if a handle is valid.
    /// \return true handle is valid, false otherwise.
    explicit operator bool() const;

    /// reset a handle
    void reset();

    /// retrieved an pointer to body.
    /// \return pointer to body.
    [[nodiscard]]
    body* get() const;

protected:
    /// swap a value with rhs.
    /// \param rhs reference to a handle.
    void swap(handle& rhs) noexcept;

protected:
    intrusive_ptr<body> _ptr;
};

/// comparison operator.
/// \param lhs handle to compare.
/// \param rhs handle to compare.
/// \return true if handles point to a same body, false otherwise.
inline bool operator==(const handle& lhs, const handle& rhs)
{
    return lhs.get() == rhs.get();
}

/// comparison operator.
/// \param lhs handle to compare.
/// \param rhs handle to compare.
/// \return true if handles point to different body, false otherwise.
inline bool operator!=(const handle& lhs, const handle& rhs)
{
    return lhs.get() != rhs.get();
}

} //brain

#endif //BRAIN_HANDLE_H
