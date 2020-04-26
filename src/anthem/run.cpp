/// The definition of the main execution function.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/run.h"

#include <utility>

#include "ode/framework/main_loop.h"

#include "anthem/application.h"
#include "anthem/command_line_interface.h"
#include "anthem/config.h"
#include "anthem/logger.h"
#include "anthem/logging_config.h"

namespace anthem
{
  int run(int argc, char* argv[])
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

    const auto [parsed, args] = parse_arguments(argc, argv);

    if (!parsed)
    {
      return EXIT_SUCCESS;
    }

    ANTHEM_TRACE("The following values are set to the arguments:\n{}", args);

    const auto info = ode::execution_info{
        args.window_width, args.window_height, args.window_name};

    auto app = application{};
    auto engine = ode::make_engine(std::move(app), info);

    ode::main_loop<application>(std::move(engine));

    return EXIT_SUCCESS;
  }
} // namespace anthem
