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

namespace anthem {
  namespace glfw {

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

  } // namespace glfw
} // namespace anthem

#endif // !ANTHEM_GLFW_H
