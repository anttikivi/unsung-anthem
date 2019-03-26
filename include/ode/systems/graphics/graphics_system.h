//===------------------------- graphics_system.h ----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file graphics_system.h
/// \brief The declaration of the type of the graphics system.
/// \author Antti Kivi
/// \date 8 May 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_GRAPHICS_GRAPHICS_SYSTEM_H
#define ODE_SYSTEMS_GRAPHICS_GRAPHICS_SYSTEM_H

#include "ode/systems/system.h"
#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// \class graphics_system
  /// \brief The type of the graphics system.
  ///
  /// The graphics system controls only the viewport inside the program window.
  ///
  class graphics_system : public system
  {
  public:
    ///
    /// \brief The system type of this system.
    ///
    static constexpr system_type type = system_type::graphics;

    ///
    /// \brief Constructs an object of the type \c graphics_system.
    ///
    graphics_system() = default;

    ///
    /// \brief Constructs an object of the type \c graphics_system by copying
    /// the given object of the type \c graphics_system.
    ///
    /// \param a a \c graphics_system from which the new one is constructed.
    ///
    graphics_system(const graphics_system& a) = delete;

    ///
    /// \brief Constructs an object of the type \c graphics_system by moving
    /// the given object of the type \c graphics_system.
    ///
    /// \param a a \c graphics_system from which the new one is constructed.
    ///
    graphics_system(graphics_system&& a) = default;

    ///
    /// \brief Destructs an object of the type \c graphics_system.
    ///
    ~graphics_system() = default;

    ///
    /// \brief Assigns the given object of the type \c graphics_system to this
    /// one by copying.
    ///
    /// \param a a \c graphics_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_system& operator=(const graphics_system& a) = delete;

    ///
    /// \brief Assigns the given object of the type \c graphics_system to this
    /// one by moving.
    ///
    /// \param a a \c graphics_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_system& operator=(graphics_system&& a) = default;

    ///
    /// \brief Creates a scene object containing the type \c graphics_scene.
    ///
    /// \param cfg the scene configuration according to which the scene is
    /// constructed.
    ///
    /// \return An object of the type \c scene_t.
    ///
    scene_t make_scene(const scene_configuration_t& cfg) const;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_GRAPHICS_GRAPHICS_SYSTEM_H
