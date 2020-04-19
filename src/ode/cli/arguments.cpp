/// The definitions for the type of objects which contain parsed command line
/// arguments.
/// \file
/// \author Antti Kivi
/// \date 19 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/arguments.h"

namespace ode::cli
{
  arguments merge(const arguments& a, const arguments& b)
  {
    auto option_values = b.option_values;
    option_values.insert(a.option_values.cbegin(), a.option_values.cend());

    auto failed_options = b.failed_options;
    failed_options.insert(a.failed_options.cbegin(), a.failed_options.cend());

    auto missing = b.missing_options;
    missing.insert(a.missing_options.cbegin(), a.missing_options.cend());

    auto unknown = b.unknown_arguments;
    unknown.insert(a.unknown_arguments.cbegin(), a.unknown_arguments.cend());

    return {option_values, failed_options, missing, unknown};
  }
} // namespace ode::cli
