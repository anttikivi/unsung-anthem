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
/// \brief The declarations of the type templates of the system scenes.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_SCENE_T_H
#define ODE_SYSTEMS_SCENE_T_H

#include <memory>
#include <utility>

#include "ode/systems/scene.h"

namespace ode
{
  ///
  /// \classs scene_t
  /// \brief The type of the objects which are the functional system scenes.
  ///
  class scene_t final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c scene_t.
    ///
    /// \tparam T the type of the system implementation.
    ///
    /// \param t the system implementation.
    ///
    template <typename T>
    scene_t(T t) : scene_ptr{std::make_shared<T>(std::move(t))}
    {

    }

    ///
    /// \brief Constructs an object of the type \c scene_t by copying the given
    /// object of the type \c scene_t.
    ///
    /// \param a \c scene_t from which the new one is constructed.
    ///
    scene_t(const scene_t& a) = default;

    ///
    /// \brief Constructs an object of the type \c scene_t by moving the given
    /// object of the type \c scene_t.
    ///
    /// \param a \c scene_t from which the new one is constructed.
    ///
    scene_t(scene_t&& a) = default;

    ///
    /// \brief Destructs an object of the type \c scene_t.
    ///
    ~scene_t() = default;

    ///
    /// \brief Assigns the given object of the type \c scene_t to this one by
    /// copying.
    ///
    /// \param a \c scene_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_t& operator=(const scene_t& a) = default;

    ///
    /// \brief Assigns the given object of the type \c scene_t to this one by
    /// moving.
    ///
    /// \param a \c scene_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_t& operator=(scene_t&& a) = default;

  private:
    ///
    /// \brief A pointer to the contained scene implementation.
    ///
    /// TODO Consider making this a gsl::owner so this type won’t limit the
    /// whole type.
    ///
    std::shared_ptr<const scene> scene_ptr;
  };
} // namespace ode

#endif // !ODE_SCENE_T_H
