/// The definition of the type of objects that contain information about groups
/// of command line options where the options are mutually exclusive.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/mutually_exclusive_option_group.h"

#include <utility>

namespace ode::cli
{
  mutually_exclusive_option_group::mutually_exclusive_option_group()
  : option_group{}
  {

  }

  mutually_exclusive_option_group::mutually_exclusive_option_group(
      std::vector<option>&& opts)
  : option_group{std::move(opts)}
  {

  }

  mutually_exclusive_option_group::mutually_exclusive_option_group(
      const std::string& n,
      std::vector<option>&& opts)
  : option_group{n, std::move(opts)}
  {

  }

  mutually_exclusive_option_group::mutually_exclusive_option_group(
      const std::string& n,
      const std::string& d,
      std::vector<option>&& opts)
  : option_group{n, d, std::move(opts)}
  {

  }
} // namespace ode::cli
