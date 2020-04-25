/// The definitions of the utilities related to parsing command line arguments.
/// \file
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/command_line_interface.h"

#include <iostream>
#include <type_traits>

#include <cxxopts.hpp>

#include "ode/framework/platform_manager.h"

#include "anthem/config.h"
#include "anthem/logger.h"

namespace anthem
{
  std::ostream& operator<<(std::ostream& os, const arguments& a)
  {
    return os << "{"
              << ", window_width:" << std::to_string(a.window_width)
              << ", window_height:" << std::to_string(a.window_height)
              << ", window_name:" << a.window_name << "}";
  }

  arguments parse_arguments(const int argc, ode::argv_t argv[]) noexcept
  {
    ANTHEM_DEBUG("Going to parse {} argument(s)", argc - 1);

    cxxopts::Options options{
        anthem_name, "A game that will receive its description later"};

    options.add_options()(
        "window-width",
        "The initial width of the window in pixels",
        cxxopts::value<int>())(
        "window-height",
        "The initial height of the window in pixels",
        cxxopts::value<int>())(
        "window-name",
        "The name of the game window",
        cxxopts::value<std::string>()->default_value(default_window_name));

    int argc_parsing{argc};

#if ODE_WINDOWS
    auto result = options.parse(argc_parsing, argv);
#else
    auto result = options.parse(argc_parsing, argv);
#endif

    return arguments{
        result["window-width"].as<int>(),
        result["window-height"].as<int>(),
        result["window-name"].as<std::string>()};
  }
} // namespace anthem
