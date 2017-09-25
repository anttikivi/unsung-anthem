//===-------------------------- glfw.cpp ------------------------*- C++ -*-===//
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
/// \file glfw.cpp
/// \brief The definition of the GLFW helper functions.
/// \author Antti Kivi
/// \date 20 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "glfw.h"

namespace anthem
{
  namespace glfw
  {
    void initialize(const logging::logger_t& logger)
    {
      if (!glfwInit())
      {
        logging::error(logger, "The GLFW initialization failed");
      }
      logging::debug(logger, "GLFW is initialized");
    }

    void quit(const logging::logger_t& logger)
    {
      glfwTerminate();
      logging::debug(logger, "GLFW is terminated");
    }

    GLFWwindow* create_window(
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

      GLFWwindow* window = glfwCreateWindow(
          args.window_width,
          args.window_height,
          args.window_name.c_str(),
          NULL,
          NULL);

      if (!window)
      {
        logging::error(logger, "The GLFW window creation failed");
        quit(logger);
      }

      glfwMakeContextCurrent(window);
      gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
      glfwSwapInterval(1);

      return window;
    }

    void destroy_window(const logging::logger_t& logger, GLFWwindow* window)
    {
      glfwDestroyWindow(window);
    }

  } // namespace glfw
} // namespace anthem
