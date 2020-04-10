/// The declarations of the utility for parsing command line arguments.
/// \file
/// \author Antti Kivi
/// \date 18 March 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_PARSE_ARGUMENTS_H
#define ODE_CLI_PARSE_ARGUMENTS_H

#include <vector>

#include "ode/argv_t.h"

namespace ode::cli
{
  struct arguments;
  class option_group_t;
}

namespace ode::cli
{
  ///
  /// Parses the given command line arguments and resolves the values for the
  /// command line options.
  ///
  /// Returns an object of the type \c arguments which contains the values set
  /// when executing the program from the command line.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  /// \param options a vector of command line option group objects holding the
  /// information of the possible command line option for parsing the
  /// arguments.
  ///
  /// \return An object of the type \c arguments.
  ///
  arguments parse_arguments(
      const int argc,
      ode::argv_t argv[],
      std::vector<option_group_t> option_groups);

} // namespace ode::cli

#endif // !ODE_CLI_PARSE_ARGUMENTS_H
