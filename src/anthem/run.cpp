//===------------------------------ run.cpp ---------------------*- C++ -*-===//
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
/// \file run.cpp
/// \brief The definition of the main execution function.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/run.h"

#include <cstdlib>

#include <type_traits>

#include "ode/execution_info.h"
#include "ode/initialize.h"
#include "ode/logging.h"
#include "ode/quit.h"
#include "ode/framework/main_loop.h"
#include "ode/framework/platform_manager.h"
#include "ode/systems/input_system.h"
#include "ode/systems/system_t.h"

#include "anthem/command_line_interface.h"
#include "anthem/logger.h"

#include "anthem/config.h"
#include "anthem/logging_config.h"

namespace anthem
{
  int run(int argc, ode::argv_t argv[])
  {
    logger = ode::create_logger(logger_name, logger_pattern, logger_level);

    ANTHEM_INFO("The main logger of {} is created", anthem_name);
    ANTHEM_DEBUG(
        "The logger has the name '{}', the pattern '{}', and the level '{}'",
        logger_name,
        logger_pattern,
        logger_level);
    
    if constexpr (ode::platform::windows == ode::current_platform)
    {
      ANTHEM_DEBUG("{} is built for Windows", anthem_name);
    }
    else if constexpr (ode::platform::macos == ode::current_platform)
    {
      ANTHEM_DEBUG("{} is built for macOS", anthem_name);
    }
    else if constexpr (ode::platform::linux == ode::current_platform)
    {
      ANTHEM_DEBUG("{} is built for Linux", anthem_name);
    }
    else
    {
      ANTHEM_ERROR("{} is built for an unknown platform", anthem_name);
    }
    
    const auto args = parse_arguments(argc, argv);

    ANTHEM_TRACE("The following values are set to the arguments:\n{}", args);

    const auto info = ode::execution_info{
        argc,
        argv,
        args.window_width,
        args.window_height,
        args.window_name};
    
    ode::initialize_logging();

    const auto sdl_quit_action = ode::initialize_sdl();
    auto window = ode::initialize_window(info);
    auto graphics_context = ode::initialize_graphics(window.get());

    ode::initialize_ode();

    ode::initialize_system<ode::input_system>();

    ode::main_loop(std::move(window));

    ode::quit_graphics(graphics_context);

    window.reset(nullptr);

    return EXIT_SUCCESS;
  }
} // namespace anthem
