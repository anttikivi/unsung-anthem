//===------------------------- graphics_system.h ----------------*- C++ -*-===//
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
/// \file graphics_system.h
/// \brief The declaration of the type of the graphics system.
/// \author Antti Kivi
/// \date 8 May 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_GRAPHICS_SYSTEM_H
#define ODE_SYSTEMS_GRAPHICS_SYSTEM_H

#include "ode/system_type.h"
#include "ode/system.h"

namespace ode
{
  ///
  /// \struct graphics_system
  /// \brief The type of the graphics system.
  ///
  /// The graphics system controls only the viewport inside the program window.
  ///
  struct graphics_system final : public system
  {
    ///
    /// \brief The system type of this system.
    ///
    static constexpr system_type type = system_type::graphics;

    ///
    /// \brief Destructs an object of the type \c graphics_system.
    ///
    ~graphics_system() = default;

    ///
    /// \brief Creates a scene object containing the type \c graphics_scene.
    ///
    /// \return An object of the type \c scene_t.
    ///
    scene_t create_scene() const;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_GRAPHICS_SYSTEM_H
