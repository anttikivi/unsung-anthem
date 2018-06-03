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
/// \brief The declarations of the type templates of system objects.
/// \author Antti Kivi
/// \date 17 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_SYSTEM_T_H
#define ODE_SYSTEMS_SYSTEM_T_H

#include <memory>
#include <utility>

#include "ode/systems/system.h"

// Forward declarations
namespace ode
{
  class scene_t;
} // namespace ode

namespace ode
{
  ///
  /// \class system_t
  /// \brief The type of the objects which are the functional systems.
  ///
  class system_t final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c system_t.
    ///
    /// \tparam T the type of the system implementation.
    ///
    /// \param t the system implementation.
    ///
    template <typename T>
    system_t(T t) : sys_ptr{std::make_shared<T>(std::move(t))}
    {

    }

    ///
    /// \brief Constructs an object of the type \c system_t by copying the
    /// given object of the type \c system_t.
    ///
    /// \param a \c system_t from which the new one is constructed.
    ///
    system_t(const system_t& a) = default;

    ///
    /// \brief Constructs an object of the type \c system_t by moving the given
    /// object of the type \c system_t.
    ///
    /// \param a \c system_t from which the new one is constructed.
    ///
    system_t(system_t&& a) = default;

    ///
    /// \brief Destructs an object of the type \c system_t.
    ///
    ~system_t() = default;

    ///
    /// \brief Assigns the given object of the type \c system_t to this one by
    /// copying.
    ///
    /// \param a \c system_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    system_t& operator=(const system_t& a) = default;

    ///
    /// \brief Assigns the given object of the type \c system_t to this one by
    /// moving.
    ///
    /// \param a \c system_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    system_t& operator=(system_t&& a) = default;
    
    ///
    /// \brief Creates a scene object implementing the functionalities of this
    /// system.
    ///
    /// \return An object of the type \c scene_t which has the functionality of
    /// this system.
    ///
    scene_t create_scene() const;

  private:
    ///
    /// \brief A pointer to the contained system implementation.
    ///
    std::shared_ptr<const system> sys_ptr;
  };
} // namespace ode

#endif // !ODE_SYSTEMS_SYSTEM_T_H
