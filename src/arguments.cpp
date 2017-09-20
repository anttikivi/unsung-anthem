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

namespace anthem {

  const arguments parse_arguments(const logging::logger_t& logger,
                                  const int argc,
                                  const char* argv[]) noexcept {

    logging::debug(logger, "Going to parse {} argument(s)", argc - 1);

    args::ArgumentParser parser{"TODO",
                                "Some information which goes after the "
                                "options should go here"};
    args::HelpFlag help{parser,
                        "help",
                        "Display this help menu",
                        {'h', "help"}};

    args::ValueFlag<pixel_count> window_width{parser, "window-width", "The width of the window", {"window-width"}, 0};
    args::ValueFlag<pixel_count> window_height{parser, "window-height", "The height of the window", {"window-height"}, 0};

    try {

      parser.ParseCLI(argc, argv);
    
    } catch (args::Help) {

      std::cout << parser;

#if defined(_MSC_VER) && _MSC_VER == 1900
      return arguments(false);
#else
      return arguments{false};
#endif // !(defined(_MSC_VER) && _MSC_VER == 1900)

    } catch (args::ParseError e) {

      std::cerr << e.what() << std::endl;
      std::cerr << parser;

#if defined(_MSC_VER) && _MSC_VER == 1900
      return arguments(false);
#else
      return arguments{false};
#endif // !(defined(_MSC_VER) && _MSC_VER == 1900)

    }

#if defined(_MSC_VER) && _MSC_VER == 1900
    return arguments(true, args::get(window_width), args::get(window_height));
#else
    return arguments{true, args::get(window_width), args::get(window_height)};
#endif // !(defined(_MSC_VER) && _MSC_VER == 1900)
  }
} // namespace anthem
