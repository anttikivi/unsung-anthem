//===----------------------------- object_t.h -------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file object_t.h
/// \brief The declaration of the type templates of the objects of the systems.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_OBJECT_T_H
#define ODE_SYSTEMS_OBJECT_T_H

#include <memory>
#include <utility>

#include "ode/systems/object.h"

namespace ode
{
  ///
  /// \class object_t
  /// \brief The type of the objects which are the functional objects of the
  /// systems.
  ///
  class object_t final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c object_t.
    ///
    object_t() = default;

    ///
    /// \brief Constructs an object of the type \c object_t.
    ///
    /// \tparam T the type of the object implementation.
    ///
    /// \param t the object implementation.
    ///
    template <typename T>
    object_t(T t) : obj_ptr{std::make_unique<T>(std::move(t))}
    {

    }

    ///
    /// \brief Constructs an object of the type \c object_t by copying the
    /// given object of the type \c object_t.
    ///
    /// \param an \c object_t from which the new one is constructed.
    ///
    object_t(const object_t& a) = delete;

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
    object_t& operator=(const object_t& a) = delete;

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
    std::unique_ptr<object> obj_ptr;
  };
} // namespace ode

#endif // !ODE_SYSTEMS_OBJECT_T_H
