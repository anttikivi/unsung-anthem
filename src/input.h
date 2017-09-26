//===--------------------------- input.h ------------------------*- C++ -*-===//
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
/// \file input.h
/// \brief The declarations of the input-related functions.
/// \author Antti Kivi
/// \date 26 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_INPUT_H
#define ANTHEM_INPUT_H

#include "anthem/logging.h"

struct GLFWwindow;

namespace anthem
{
  ///
  /// \brief The logger which is used to log the input handling events.
  ///
  extern logger_t input_logger;

  ///
  /// \brief Handles single key input event.
  ///
  /// This function is impure.
  ///
  /// \param window the window which received the event.
  /// \param key the keyboard key which was pressed.
  /// \param scancode the system-specific scancode of the key.
  /// \param action the performed action, either \c GLFW_PRESS, \c GLFW_RELEASE
  /// or \c GLFW_REPEAT
  /// \param mods a bit field describing which modifier keys were held down.
  ///
  void glfw_key_callback(
      GLFWwindow* window,
      int key,
      int scancode,
      int action,
      int mods);

} // namespace anthem

#endif // !ANTHEM_INPUT_H
