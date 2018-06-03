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
/// \brief The declaration of the base type of the system objects.
/// \author Antti Kivi
/// \date 17 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_SYSTEM_H
#define ODE_SYSTEMS_SYSTEM_H

// Forward declarations
namespace ode
{
  class scene_t;
} // namespace ode

namespace ode
{
  ///
  /// \struct system
  /// \brief The base type of the objects which implement the functionalities
  /// of the different systems.
  ///
  struct system
  {
    ///
    /// \brief Destructs an object of the type \c system.
    ///
    virtual ~system() = default;

    ///
    /// \brief Creates a scene object implementing the functionalities of this
    /// system.
    ///
    /// \return An object of the type \c scene_t.
    ///
    virtual scene_t create_scene() const = 0;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SYSTEM_H
