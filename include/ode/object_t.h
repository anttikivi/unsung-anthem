//===----------------------------- object_t.h -------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2018 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file object_t.h
/// \brief Declarations of type templates of system objects of Obliging Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_OBJECT_T_H
#define ODE_OBJECT_T_H

#include <memory>
#include <utility>

namespace ode
{
  struct object;
} // namespace ode

namespace ode
{
  ///
  /// \brief Type of objects which are functional system objects of Obliging
  /// Ode.
  ///
  class object_t final
  {
  public:
    ///
    /// \brief Constructs an object of type \c object_t.
    ///
    /// \tparam T type of the system implementation.
    ///
    /// \param t system implementation.
    ///
    template <typename T>
    object_t(T t) : sys_ptr{std::make_shared<T>(std::move(t))}
    {

    }

    ///
    /// \brief Constructs an object of type \c object_t by copying the given
    /// object of type \c object_t.
    ///
    /// \param a \c object_t from which the new one is constructed.
    ///
    object_t(const object_t& a) = default;

    ///
    /// \brief Constructs an object of type \c object_t by moving the given
    /// object of type \c object_t.
    ///
    /// \param a \c object_t from which the new one is constructed.
    ///
    object_t(object_t&& a) = default;

    ///
    /// \brief Destructs an object of type \c object_t.
    ///
    ~object_t() = default;

    ///
    /// \brief Assigns the given object of type \c object_t to this one by
    /// copying.
    ///
    /// \param a \c object_t from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    object_t& operator=(const object_t& a) = default;

    ///
    /// \brief Assigns the given object of type \c object_t to this one by
    /// moving.
    ///
    /// \param a \c object_t from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    object_t& operator=(object_t&& a) = default;

  private:
    ///
    /// \brief Pointer to the contained object implementation.
    ///
    std::shared_ptr<const object> obj_ptr;
  };
} // namespace ode

#endif // !ODE_OBJECT_T_H
