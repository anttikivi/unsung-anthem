/// The definition of the type of objects that contain information about groups
/// of command line options for parsing command line arguments.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/option_group.h"

#include <utility>

namespace ode::cli
{
  option_group::option_group() : opts{}, n{std::nullopt}, desc{std::nullopt}
  {

  }

  option_group::option_group(std::vector<option>&& opts)
  : opts{std::move(opts)},
  n{std::nullopt},
  desc{std::nullopt}
  {

  }

  option_group::option_group(
      const std::string& n,
      std::vector<option>&& opts)
  : opts{std::move(opts)},
  n{n},
  desc{std::nullopt}
  {

  }

  option_group::option_group(
      const std::string& n,
      const std::string& d,
      std::vector<option>&& opts)
  : opts{std::move(opts)},
  n{n},
  desc{d}
  {

  }

  std::vector<option> option_group::options() const
  {
    return opts;
  }

  std::optional<std::string> option_group::name() const
  {
    return n;
  }

  std::optional<std::string> option_group::description() const
  {
    return desc;
  }
} // namespace ode::cli
