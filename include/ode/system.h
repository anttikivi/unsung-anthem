//===------------------------------ system.h --------------------*- C++ -*-===//
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
/// \file system.h
/// \brief Declaration of base type of system objects of Obliging Ode.
/// \author Antti Kivi
/// \date 17 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEM_H
#define ODE_SYSTEM_H

// Forward declarations
namespace ode
{
  class scene_t;
} // namespace ode

namespace ode
{
  ///
  /// \brief Base type of objects which implement functionalities of different
  /// the systems.
  ///
  struct system
  {
    ///
    /// \brief Destructs an object of type \c system.
    ///
    virtual ~system() = default;

    ///
    /// \brief Creates a scene object implementing functionalities of this
    /// system.
    ///
    /// \return An object of type \c scene_t.
    ///
    virtual scene_t create_scene() const = 0;
  };

} // namespace ode

#endif // !ODE_SYSTEM_H
