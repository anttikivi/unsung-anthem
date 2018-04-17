//===----------------------------- system_t.h -------------------*- C++ -*-===//
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
/// \file system_t.h
/// \brief Declarations of type templates of system objects of Obliging Ode.
/// \author Antti Kivi
/// \date 17 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEM_T_H
#define ODE_SYSTEM_T_H

#include <memory>
#include <utility>

namespace ode
{
  struct system;
} // namespace ode

namespace ode
{
  ///
  /// \brief Type of objects which are functional systems of Obliging Ode.
  ///
  class system_t final
  {
  public:
    ///
    /// \brief Constructs an object of type \c system_t.
    ///
    /// \tparam T type of the system implementation.
    ///
    /// \param t system implementation.
    ///
    template <typename T>
    system_t(T t) : sys_ptr{std::make_shared<T>(std::move(t))}
    {

    }

    ///
    /// \brief Constructs an object of type \c system_t by copying the given
    /// object of type \c system_t.
    ///
    /// \param a \c system_t from which the new one is constructed.
    ///
    system_t(const system_t& a) = default;

    ///
    /// \brief Constructs an object of type \c system_t by moving the given
    /// object of type \c system_t.
    ///
    /// \param a \c system_t from which the new one is constructed.
    ///
    system_t(system_t&& a) = default;

    ///
    /// \brief Destructs an object of type \c system_t.
    ///
    ~system_t() = default;

    ///
    /// \brief Assigns the given object of type \c system_t to this one by
    /// copying.
    ///
    /// \param a \c system_t from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    system_t& operator=(const system_t& a) = default;

    ///
    /// \brief Assigns the given object of type \c system_t to this one by
    /// moving.
    ///
    /// \param a \c system_t from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    system_t& operator=(system_t&& a) = default;

  private:
    ///
    /// \brief Pointer to the contained system implementation.
    ///
    std::shared_ptr<const system> sys_ptr;
  };
} // namespace ode

#endif // !ODE_SYSTEM_T_H
