/// The declaration of the main execution function.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ANTHEM_RUN_H
#define ANTHEM_RUN_H

#include <cstdlib>

#include "ode/argv_t.h"

namespace anthem
{
  ///
  /// Returns the end code of the program after executing it with the given
  /// arguments.
  ///
  /// This function is impure.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return A value which represents the end code of the program.
  ///
  int run(int argc, ode::argv_t argv[]);

} // namespace anthem

#endif // !ANTHEM_RUN_H
