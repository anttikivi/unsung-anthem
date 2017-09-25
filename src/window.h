//===-------------------------- window.h ------------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file window.h
/// \brief The declaration of the window-related functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_WINDOW_H
#define ANTHEM_WINDOW_H

#include <memory>

#include "anthem/logging.h"

#include <glfw/GLFW3.h>

namespace anthem
{
  struct arguments;
}

namespace anthem
{
  ///
  /// \brief The type of the pointer to the window object.
  ///
  typedef std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window_ptr;

  ///
  /// \brief Initializes a new GLFW window with OpenGL context.
  ///
  /// \param logger the main logger.
  /// \param args the parsed command line arguments.
  ///
  /// \return Pointer to the created object of type \c GLFWwindow.
  ///
  window_ptr create_window(
      const logging::logger_t& logger,
      const arguments& args);

  ///
  /// \brief Destroys a GLFW window.
  ///
  /// \param logger the main logger.
  /// \param window pointer to the window.
  ///
  void destroy_window(const logging::logger_t& logger, window_ptr&& window);

} // namespace anthem

#endif // !ANTHEM_WINDOW_H
