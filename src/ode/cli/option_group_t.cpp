/// The definitions of the type templates of the command line option groups.
/// \file
/// \author Antti Kivi
/// \date 19 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/option_group_t.h"

namespace ode::cli
{
  arguments option_group_t::parse_group(
      const int argc, ode::argv_t argv[]) const
  {
    return group->parse_group(argc, argv);
  }

  std::string option_group_t::format_help() const
  {
    return group->format_help();
  }
} // namespace ode::cli
