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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace anthem {
  namespace glfw {

    void initialize(const logging::logger_t& logger) {

      if (!glfwInit()) {
        logging::error(logger, "The GLFW initialization failed");
      }
      logging::debug(logger, "GLFW is initialized");
    }

    void quit(const logging::logger_t& logger) {
      glfwTerminate();
      logging::debug(logger, "GLFW is terminated");
    }

  } // namespace glfw
} // namespace anthem
