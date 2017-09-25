//===--------------------------- glfw.h -------------------------*- C++ -*-===//
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
/// \file glfw.h
/// \brief The declaration of the GLFW helper functions.
/// \author Antti Kivi
/// \date 20 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_GLFW_H
#define ANTHEM_GLFW_H

#include "anthem/logging.h"

#include "arguments.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace anthem
{
  namespace glfw
  {
    ///
    /// \brief Initializes the GLFW framework.
    ///
    /// This function is impure.
    ///
    /// \param logger the main logger.
    ///
    void initialize(const logging::logger_t& logger);

    ///
    /// \brief Terminates the GLFW framework.
    ///
    /// This function is impure.
    ///
    /// \param logger the main logger.
    ///
    void quit(const logging::logger_t& logger);

    ///
    /// \brief Initializes a new GLFW window with OpenGL context.
    ///
    /// \param logger the main logger.
    /// \param args the parsed command line arguments.
    ///
    /// \return Pointer to the created object of type \c GLFWwindow.
    ///
    GLFWwindow* create_window(
        const logging::logger_t& logger,
        const arguments& args);

    ///
    /// \brief Destroys a GLFW window.
    ///
    /// \param logger the main logger.
    /// \param window the window.
    ///
    void destroy_window(const logging::logger_t& logger, GLFWwindow* window);

  } // namespace glfw
} // namespace anthem

#endif // !ANTHEM_GLFW_H
