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

#include <type_traits>

#include "gsl/util"

#include "anthem/array.h"
#include "anthem/types.h"

namespace anthem {

  const arguments parse_arguments(const logging::logger_t& logger,
                                  const int argc,
                                  const char* argv[]) noexcept {

    logging::debug(logger, "Going to parse {} argument(s)", argc - 1);

    const auto str_args = [&] {
      std::vector<std::string> ret = {};
      // The loop is started from index 1 as the index 0 is the name of the
      // executable and that should not be parsed.
      for (int i = 1; i < argc; ++i) {
        ret.emplace_back(argv[i]);
      }
      return ret;
    }();

    for (const auto& arg : str_args) {
      logging::debug(logger, "Now parsing option {}", arg);
    }

    return arguments{};
  }
} // namespace anthem
