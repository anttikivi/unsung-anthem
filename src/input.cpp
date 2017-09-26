//===-------------------------- input.cpp -----------------------*- C++ -*-===//
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
/// \file input.cpp
/// \brief The definitions of the input-related functions.
/// \author Antti Kivi
/// \date 26 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "input.h"

namespace anthem
{
  logger_t input_logger = nullptr;

  void glfw_key_callback(
      GLFWwindow* window,
      int key,
      int scancode,
      int action,
      int mods)
  {
    logging::trace(input_logger, "Pressed key {}", key);
  }

} // namespace anthem
