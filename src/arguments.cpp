//===------------------------ arguments.cpp ---------------------*- C++ -*-===//
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
/// \file arguments.cpp
/// \brief The definitions of the utilities related to parsing command line
/// arguments.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "arguments.h"

#include <iostream>

#include <args.hxx>

namespace anthem
{
  std::ostream& operator<<(std::ostream& os, const arguments& a)
  {
    return os << "{"
        << "parsed:" << std::to_string(a.parsed)
        << ", window_width:" << std::to_string(a.window_width)
        << ", window_height:" << std::to_string(a.window_height)
        << "}";
  }

  const arguments parse_arguments(
      const logging::logger_t& logger,
      const int argc,
      const char* argv[]) noexcept
  {
    logging::debug(logger, "Going to parse {} argument(s)", argc - 1);

    args::ArgumentParser parser{
        "TODO",
        "Some information which goes after the options should go here"};
    args::HelpFlag help{
        parser,
        "help",
        "Display this help menu",
        {'h', "help"}};
    args::ValueFlag<pixel_count> window_width{
        parser,
        "window-width",
        "The width of the window in pixels",
        {"window-width"},
        0};
    args::ValueFlag<pixel_count> window_height{
        parser,
        "window-height",
        "The height of the window in pixels",
        {"window-height"},
        0};

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

    return arguments{true, args::get(window_width), args::get(window_height)};
  }
} // namespace anthem
