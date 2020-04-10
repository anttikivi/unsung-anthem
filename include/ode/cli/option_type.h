/// The declarations of the command line option type utilities.
/// \file
/// \author Antti Kivi
/// \date 5 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_OPTION_TYPE_H
#define ODE_CLI_OPTION_TYPE_H

#include "ode/__config"

namespace ode::cli
{
  ///
  /// An enumeration type, the enumerators of which represent the possible
  /// command line option types.
  ///
  /// TODO: Add support for list options, i.e. options that take multiple
  /// values.
  ///
  enum class option_type : ODE_OPTION_TYPE_ENUM_TYPE
  {
    boolean,
    integer,
    floating_point,
    string
  };
} // namespace ode::cli

#endif // !ODE_CLI_OPTION_TYPE_H
