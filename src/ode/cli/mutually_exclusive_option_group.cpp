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
  mutually_exclusive_option_group::mutually_exclusive_option_group(
      const std::string& name,
      const std::string& description,
      std::unordered_set<option>&& options)
      : name{name}, description{description}, options{std::move(options)}
  {
  }

  mutually_exclusive_option_group::mutually_exclusive_option_group(
      const std::string& name, std::unordered_set<option>&& options)
      : name{name}, description{std::nullopt}, options{std::move(options)}
  {
  }

  mutually_exclusive_option_group::mutually_exclusive_option_group(
      std::unordered_set<option>&& options)
      : name{std::nullopt},
        description{std::nullopt},
        options{std::move(options)}
  {
  }

  arguments mutually_exclusive_option_group::parse_group(const int argc, ode::argv_t argv[]) const
  {
    std::unordered_map<std::string, option::value_t> parsed{};
    std::unordered_map<std::string, std::string> failed{};
    std::unordered_set<std::string> missing{};
    std::unordered_set<std::string> unknown{};

    option::parsed_options_t parsing_values{};

    return {parsed, failed, missing, unknown};
  }

  std::string mutually_exclusive_option_group::format_help() const
  {
    return "builder.str()";
  }
} // namespace ode::cli
