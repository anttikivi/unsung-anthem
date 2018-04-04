//===---------------------------- execute.cpp -------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
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

#include "ode/execution_info.h"
#include "ode/logger.h"

#include "ode/config.h"
#include "ode/framework/main_loop.h"
#include "ode/logging_config.h"
#include "ode/sdl/initialize.h"
#include "ode/sdl/opengl.h"
#include "ode/sdl/window.h"

namespace ode
{
  int execute(const execution_info& info)
  {
    logger = create_logger(logger_name, logger_pattern, logger_level);

    ODE_INFO("The main logger of {} is created", ode_name);
    ODE_DEBUG(
        "The logger has the name '{}', the pattern '{}', and the level '{}'",
        logger_name,
        logger_pattern,
        logger_level);
    
    const auto sdl_quit_action = ode::sdl::initialize();

    sdl::window_ptr window = sdl::create_window({
        info.window_width,
        info.window_height,
        info.window_name});
    
    ODE_DEBUG("The main window of {} is created", ode_name);

    // TODO Maybe return some value.
    // create_managers();

    auto context = sdl::create_gl_context(window.get());

    main_loop(std::move(window));

    SDL_GL_DeleteContext(context);

    return EXIT_SUCCESS;
  }

  void create_managers()
  {
    // TODO
  }
} // namespace ode
