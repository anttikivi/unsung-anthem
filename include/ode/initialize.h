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
/// \brief Declarations of initialization functions of Obliging Ode.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_INITIALIZE_H
#define ODE_INITIALIZE_H

#include "ode/systems.h"
#include "ode/type_name.h"
#include "ode/window_t.h"
#include "ode/gl/data.h"
#include "ode/sdl/initialize.h"
#include "ode/sdl/opengl.h"

#include <glad/glad.h>

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
    ODE_TRACE("Initializing Simple DirectMedia Layer");
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
    auto context = sdl::create_gl_context(window);

    ODE_DEBUG("OpenGL is loaded");
    ODE_DEBUG("The OpenGL vendor is {}", gl::vendor());
    ODE_DEBUG("The OpenGL renderer is {}", gl::renderer());
    ODE_DEBUG("The OpenGL version is {}", gl::version());
    ODE_DEBUG(
        "The OpenGL shading language version is {}",
        gl::shading_language_version());

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    ODE_TRACE("Set the OpenGL clear colour");

    return context;
  }

  ///
  /// \brief Initializes miscellaneous capabilities of Obliging Ode.
  ///
  void initialize_ode();

  ///
  /// \brief Initializes a system of Obliging Ode.
  ///
  /// \tparam T type of the system object.
  /// \tparam Args types of arguments to be passed to the system in
  /// construction.
  ///
  /// \param args arguments to be passed to the system in construction.
  ///
  template <typename T, typename... Args>
  void initialize_system(Args&&... args)
  {
    ODE_DEBUG(
        "Initializing system of type {} with system type {}",
        type_name<T>(),
        T::type);
    systems.emplace(T::type, T{args...});
  }

} // namespace ode

#endif // !ODE_INITIALIZE_H
