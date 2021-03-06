/// The declarations of the initialization functions.
/// \file
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_INITIALIZE_H
#define ODE_INITIALIZE_H

#include "ode/execution_info.h"
#include "ode/gl/data.h"
#include "ode/logger.h"
#include "ode/sdl/opengl.h"
#include "ode/window_t.h"

namespace ode
{
  ///
  /// Initializes the logging capabilities.
  ///
  void initialize_logging();

  ///
  /// Initializes the main window.
  ///
  /// Remarks: The logging capabilities and Simple DirectMedia Layer must be
  /// initialized before this function may be called.
  ///
  /// \param info an object containing the initial execution information.
  ///
  /// \return A pointer to the created window object.
  ///
  window_t initialize_window(const execution_info& info);

  ///
  /// Initializes the graphics context.
  ///
  /// Remarks: The logging capabilities and Simple DirectMedia Layer must be
  /// initialized before this function may be called.
  ///
  /// \param window a pointer to the main window object.
  ///
  /// \return An object representing the graphics context.
  ///
  inline auto initialize_graphics(window_ptr_t window)
  {
    auto context = sdl::create_gl_context(window);

    ODE_DEBUG("OpenGL is loaded");
    ODE_DEBUG("The OpenGL vendor is {}", gl::get_vendor());
    ODE_DEBUG("The OpenGL renderer is {}", gl::get_renderer());
    ODE_DEBUG("The OpenGL version is {}", gl::get_version());
    ODE_DEBUG(
        "The OpenGL shading language version is {}",
        gl::get_shading_language_version());

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    ODE_TRACE("Set the OpenGL clear colour");

    return context;
  }

} // namespace ode

#endif // !ODE_INITIALIZE_H
