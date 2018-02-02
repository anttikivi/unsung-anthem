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

#include <args.hxx>

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

    args::ArgumentParser parser{
        "TODO"s,
        "Some information which goes after the options should go here"s};
    args::HelpFlag help{
        parser,
        "help"s,
        "Display this help menu"s,
        {'h', "help"s}};
    args::ValueFlag<pixel_count> window_width{
        parser,
        "window-width"s,
        "The width of the window in pixels"s,
        {"window-width"s},
        default_window_width};
    args::ValueFlag<pixel_count> window_height{
        parser,
        "window-height"s,
        "The height of the window in pixels"s,
        {"window-height"s},
        default_window_height};
    args::ValueFlag<std::string> window_name{
        parser,
        "window-name"s,
        "The name of the game window"s,
        {"window-name"s},
        std::string{default_window_name}};

    try
    {
      parser.ParseCLI(argc, argv);
    }
    catch (const args::Help&)
    {
      std::cout << parser;
      return arguments{false};
    }
    catch (const args::ParseError& e)
    {
      std::cerr << e.what() << std::endl;
      std::cerr << parser;
      return arguments{false};
    }

    return arguments{
        true,
        args::get(window_width),
        args::get(window_height),
        args::get(window_name)};
  }
} // namespace ode
