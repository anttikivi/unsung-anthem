//===------------------------- window.cpp ------------------------*- C++ -*-===//
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
/// \file window.cpp
/// \brief The definition of the window-related functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "window.h"

#include <type_traits>

#include "arguments.h"
#include "input.h"

#include <glad/glad.h>

namespace anthem
{
  window_ptr create_window(
      const logging::logger_t& logger,
      const arguments& args)
  {
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, ANTHEM_OPENGL_VERSION_MAJOR);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ANTHEM_OPENGL_VERSION_MINOR);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

      // MacOS only supports forward-compatible core contexts.
#if __APPLE__
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

      logging::trace(
          logger,
          "Set the OpenGL version hint for the window to {}.{}",
          ANTHEM_OPENGL_VERSION_MAJOR,
          ANTHEM_OPENGL_VERSION_MINOR);

      window_ptr window{
          glfwCreateWindow(
              args.window_width,
              args.window_height,
              args.window_name.c_str(),
              NULL,
              NULL),
          &glfwDestroyWindow};

      if (!window)
      {
        logging::error(logger, "The GLFW window creation failed");
        return {nullptr, nullptr};
      }

      glfwSetKeyCallback(window.get(), glfw_key_callback);

      glfwMakeContextCurrent(window.get());
      gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
      glfwSwapInterval(1);

      return std::move(window);
    }

} // namespace anthem
