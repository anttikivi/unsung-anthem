//===------------------------- execute.cpp ----------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2018 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file execute.cpp
/// \brief The definition of the main execution function of the game engine.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/execute.h"

#include <cstdlib>

namespace ode
{
  int execute(int argc, args_array argv[])
  {
    /*
    logger = create_logger(logger_name, logger_pattern, logger_level);

    ANTHEM_INFO("The main logger of the program is created");
    ANTHEM_DEBUG(
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
    */

    return EXIT_SUCCESS;
  }

  void create_managers()
  {
    // TODO
  }
} // namespace ode
