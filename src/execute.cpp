//===------------------------- execute.cpp ----------------------*- C++ -*-===//
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
/// \file execute.cpp
/// \brief The definition of the main execution function of the game engine.
/// \author Antti Kivi
/// \date 29 June 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "execute.h"

#include "arguments.h"
#include "logging_config.h"
#include "window.h"

namespace anthem
{
  void execute(int argc, const char* argv[])
  {
    const auto console =
        create_logger(logger_name, logger_pattern, logger_level);

    logging::info(console, "The main logger of the program is created");
    logging::debug(
        console,
        "The logger has the name '{}', the pattern '{}', and the level '{}'",
        logger_name,
        logger_pattern,
        logger_level);

    const auto args = parse_arguments(console, argc, argv);

    logging::trace(
        console,
        "The following values are set to the arguments:\n{}",
        args);

    auto glfw_quit_action = initialize_glfw(console);

    {
      window_ptr window = create_window(console, args);
    }
  }
} // namespace anthem
