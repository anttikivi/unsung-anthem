//===----------------------------- scene_t.h --------------------*- C++ -*-===//
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
/// \file scene_t.h
/// \brief Declarations of type templates of system scenes of Obliging Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SCENE_T_H
#define ODE_SCENE_T_H

#include <memory>
#include <utility>

namespace ode
{
  struct scene;
} // namespace ode

namespace ode
{
  ///
  /// \brief Type of objects which are functional system scenes of Obliging
  /// Ode.
  ///
  class scene_t final
  {
  public:
    ///
    /// \brief Constructs an object of type \c scene_t.
    ///
    /// \tparam T type of the system implementation.
    ///
    /// \param t system implementation.
    ///
    template <typename T>
    scene_t(T t) : sys_ptr{std::make_shared<T>(std::move(t))}
    {

    }

    ///
    /// \brief Constructs an object of type \c scene_t by copying the given
    /// object of type \c scene_t.
    ///
    /// \param a \c scene_t from which the new one is constructed.
    ///
    scene_t(const scene_t& a) = default;

    ///
    /// \brief Constructs an object of type \c scene_t by moving the given
    /// object of type \c scene_t.
    ///
    /// \param a \c scene_t from which the new one is constructed.
    ///
    scene_t(scene_t&& a) = default;

    ///
    /// \brief Destructs an object of type \c scene_t.
    ///
    ~scene_t() = default;

    ///
    /// \brief Assigns the given object of type \c scene_t to this one by
    /// copying.
    ///
    /// \param a \c scene_t from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    scene_t& operator=(const scene_t& a) = default;

    ///
    /// \brief Assigns the given object of type \c scene_t to this one by
    /// moving.
    ///
    /// \param a \c scene_t from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    scene_t& operator=(scene_t&& a) = default;

  private:
    ///
    /// \brief Pointer to the contained scene implementation.
    ///
    std::shared_ptr<const scene> scene_ptr;
  };
} // namespace ode

#endif // !ODE_SCENE_T_H
