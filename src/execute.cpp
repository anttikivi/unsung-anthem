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

#include <cstdlib>

#include "arguments.h"
#include "framework/game_loop.h"
#include "logging_config.h"
#include "sdl.h"
#include "window.h"

namespace anthem
{
  int execute(int argc, const char* argv[])
  {
    logger = create_logger(logger_name, logger_pattern, logger_level);

    logging::info("The main logger of the program is created");
    logging::debug(
        "The logger has the name '{}', the pattern '{}', and the level '{}'",
        logger_name,
        logger_pattern,
        logger_level);

    auto args = parse_arguments(argc, argv);

    logging::trace("The following values are set to the arguments:\n{}", args);

    const auto sdl_quit_action = initialize_sdl();

    // TODO: Maybe return some value.
    create_managers();

    window_ptr window = create_window(args);
    auto context = create_gl_context(window.get());

    game_loop(std::move(args), std::move(window));

    SDL_GL_DeleteContext(context);

    return EXIT_SUCCESS;
  }

  void create_managers()
  {
    // TODO
  }
} // namespace anthem
