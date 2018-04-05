//===---------------------------- initialize.h ------------------*- C++ -*-===//
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
/// \file initialize.h
/// \brief Declarations of initialization functions of the game engine.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_INITIALIZE_H
#define ODE_INITIALIZE_H

#include "ode/window_t.h"
#include "ode/sdl/initialize.h"
#include "ode/sdl/opengl.h"

namespace ode
{
  struct execution_info;
}

namespace ode
{
  ///
  /// \brief Initializes the logging capabilities of Obliging Ode.
  ///
  void initialize_logging();

  ///
  /// \brief Initializes the Simple DirectMedia Layer.
  ///
  /// Remarks: The logging capabilities of Obliging Ode must be initialized
  /// before this function may be called.
  ///
  /// \return An object of type \c gsl::finally which terminates Simple
  /// DirectMedia Layer.
  ///
  inline auto initialize_sdl()
  {
    return sdl::initialize();
  }

  ///
  /// \brief Initializes the main window of Obliging Ode.
  ///
  /// Remarks: The logging capabilities of Obliging Ode and Simple DirectMedia
  /// Layer must be initialized before this function may be called.
  ///
  /// \param info object containing the starting execution information.
  ///
  /// \return Pointer to created window object.
  ///
  window_t initialize_window(const execution_info& info);

  ///
  /// \brief Initializes the graphics context of Obliging Ode.
  ///
  /// Remarks: The logging capabilities of Obliging Ode and Simple DirectMedia
  /// Layer must be initialized before this function may be called.
  ///
  /// \param window Pointer to the main window object.
  ///
  /// \return An object representing the graphics context.
  ///
  inline auto initialize_graphics(window_ptr_t window)
  {
    return sdl::create_gl_context(window);
  }

} // namespace ode

#endif // !ODE_INITIALIZE_H
