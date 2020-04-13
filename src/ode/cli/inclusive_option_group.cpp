/// The definition of the type of objects that contain information about groups
/// of command line options where none of the options are exclusive.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/inclusive_option_group.h"

#include <utility>

namespace ode::cli
{
  inclusive_option_group::inclusive_option_group() : option_group{}
  {

  }

  inclusive_option_group::inclusive_option_group(std::vector<option>&& opts)
  : option_group{std::move(opts)}
  {

  }

  inclusive_option_group::inclusive_option_group(
      const std::string& n,
      std::vector<option>&& opts)
  : option_group{n, std::move(opts)}
  {

  }

  inclusive_option_group::inclusive_option_group(
      const std::string& n,
      const std::string& d,
      std::vector<option>&& opts)
  : option_group{n, d, std::move(opts)}
  {

  }

  std::optional<arguments> inclusive_option_group::parse_group(
      const int argc,
      ode::argv_t argv[]) const
  {
  }
} // namespace ode::cli
