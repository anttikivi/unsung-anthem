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
/// \brief The declarations of the type templates of the system objects.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_OBJECT_T_H
#define ODE_SYSTEMS_OBJECT_T_H

#include <memory>

#include "ode/systems/object.h"

namespace ode
{
  ///
  /// \class object_t
  /// \brief The type of the objects which are the functional system objects.
  ///
  class object_t final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c object_t.
    ///
    /// \tparam T the type of the system implementation.
    ///
    /// \param t the system implementation.
    ///
    template <typename T>
    object_t(T t) : sys_ptr{std::make_shared<T>(std::move(t))}
    {

    }

    ///
    /// \brief Constructs an object of the type \c object_t by copying the
    /// given object of the type \c object_t.
    ///
    /// \param an \c object_t from which the new one is constructed.
    ///
    object_t(const object_t& a) = default;

    ///
    /// \brief Constructs an object of the type \c object_t by moving the given
    /// object of the type \c object_t.
    ///
    /// \param an \c object_t from which the new one is constructed.
    ///
    object_t(object_t&& a) = default;

    ///
    /// \brief Destructs an object of the type \c object_t.
    ///
    ~object_t() = default;

    ///
    /// \brief Assigns the given object of the type \c object_t to this one by
    /// copying.
    ///
    /// \param an \c object_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    object_t& operator=(const object_t& a) = default;

    ///
    /// \brief Assigns the given object of the type \c object_t to this one by
    /// moving.
    ///
    /// \param an \c object_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    object_t& operator=(object_t&& a) = default;

  private:
    ///
    /// \brief A pointer to the contained object implementation.
    ///
    std::shared_ptr<const object> obj_ptr;
  };
} // namespace ode

#endif // !ODE_SYSTEMS_OBJECT_T_H
