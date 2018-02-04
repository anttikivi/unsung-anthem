//===--------------------- command_line_interface.cpp -----------*- C++ -*-===//
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
/// \file command_line_interface.cpp
/// \brief The definitions of the utilities related to parsing command line
/// arguments.
/// \author Antti Kivi
/// \date 2 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/command_line_interface.h"

#include <iostream>

#include "ode/logger.h"

#include <clara.hpp>

namespace ode
{
  std::ostream& operator<<(std::ostream& os, const arguments& a)
  {
    return os << "{"
        << "parsed:" << std::to_string(a.parsed)
        << ", window_width:" << std::to_string(a.window_width)
        << ", window_height:" << std::to_string(a.window_height)
        << ", window_name:" << a.window_name
        << "}";
  }

  arguments parse_arguments(const int argc, args_array argv[]) noexcept
  {
    ODE_DEBUG("Going to parse {} argument(s)", argc - 1);

    bool show_help_flag = false;
    auto window_width = default_window_width;
    auto window_height = default_window_width;
    auto window_name = std::string{default_window_name};

    auto cli
      = clara::Help(show_help_flag)
        | clara::Opt(window_width, "window-width")["--window-width"]
        ("The width of the window in pixels")
        | clara::Opt(window_height, "window-height")["--window-height"]
        ("The height of the window in pixels")
        | clara::Opt(window_name, "window-name")["--window-name"]
        ("The name of the game window");

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && \
    !defined(__CYGWIN__)
    auto result = cli.parse(clara::Args(argc, argv));
#else
    auto result = cli.parse(clara::Args(argc, const_cast<char**>(argv)));
#endif

    if(!result)
    {
      std::cerr << "Error in command line, '"
          << result.errorMessage()
          << "'"
          << std::endl;
      return arguments{false};
    }

    return arguments{
        true,
        show_help_flag,
        window_width,
        window_height,
        window_name};
  }
} // namespace ode