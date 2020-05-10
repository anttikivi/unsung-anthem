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

  std::pair<bool, arguments> parse_arguments(const int argc, char* argv[])
  {
    ANTHEM_DEBUG("Going to parse {} argument(s)", argc - 1);

    cxxopts::Options options{
        anthem_name, "A game that will receive its description later"};

    options.add_options()("h,help", "Print the program usage and exit")(
        "version", "Print the program version and exit")(
        "window-width",
        "Set the initial width of the window in pixels",
        cxxopts::value<ode::pixel_t>()->default_value(
            default_window_width_value))(
        "window-height",
        "Set the initial height of the window in pixels",
        cxxopts::value<ode::pixel_t>()->default_value(
            default_window_height_value))(
        "window-name",
        "Set the name of the game window",
        cxxopts::value<std::string>()->default_value(
            default_window_name_value));

    try
    {
      int argc_parsing{argc};
      auto result = options.parse(argc_parsing, argv);

      if (result.count("help") > 0)
      {
        std::cout << options.help() << '\n';
        return {false, {}};
      }

      if (result.count("version") > 0)
      {
        std::cout << anthem_version << '\n';
        return {false, {}};
      }

      return {
          true,
          {result["window-width"].as<ode::pixel_t>(),
           result["window-height"].as<ode::pixel_t>(),
           result["window-name"].as<std::string>()}};
    }
    catch (const cxxopts::OptionParseException& e)
    {
      std::cerr << e.what() << '\n';
      return {false, {}};
    }
  }
} // namespace anthem
