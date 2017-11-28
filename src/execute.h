//===-------------------------- execute.h -----------------------*- C++ -*-===//
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
/// \file execute.h
/// \brief The declaration of the main execution function of the game engine.
/// \author Antti Kivi
/// \date 29 June 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_EXECUTE_H
#define ANTHEM_EXECUTE_H

#include "gsl/util"

#include "anthem/logging.h"

#include <GLFW/glfw3.h>

namespace anthem
{
  ///
  /// \brief Returns the object of type \c game_state after executing the
  /// program with the given arguments.
  ///
  /// Remarks: This function is impure.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv array containing the arguments passed in the execution.
  ///
  /// \return Does not return anything and, thus, this function is impure.
  ///
  void execute(int argc, const char* argv[]);

  ///
  /// \brief Creates and initializes the managers for the framework.
  ///
  /// Remarks: This function is impure.
  ///
  /// \return Does not return anything and, thus, this function is impure.
  ///
  void create_managers();

  ///
  /// \brief The function which is called on GLFW errors.
  ///
  /// This function is impure.
  ///
  /// \param error the error code.
  /// \param description the string containing the error description.
  ///
  void glfw_error_callback(int error, const char* description);

  ///
  /// \brief Initializes the GLFW framework.
  ///
  /// \return An object of type \c gsl::final_action containing the function
  /// which terminates GLFW.
  ///
  inline auto initialize_glfw()
  {
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
    {
      logging::error("The GLFW initialization failed");
    }

    logging::debug("GLFW is initialized");

    return gsl::finally([&]()
    {
      glfwTerminate();
      logging::debug("GLFW is terminated");
    });
  }

} // namespace anthem

#endif // !ANTHEM_EXECUTE_H
