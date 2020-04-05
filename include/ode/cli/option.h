/// The declaration of the type of objects that contain information about one
/// command line option.
/// \file
/// \author Antti Kivi
/// \date 19 March 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_OPTION_H
#define ODE_CLI_OPTION_H

#include <string>

namespace ode::cli {

  ///
  /// The type of the object which contains the required frameworks of the
  /// application.
  ///
  /// \tparam A the type of the type of the application implementation.
  ///
  template <typename T> class option {
  };

} // namespace ode::cli

#endif // !ODE_CLI_OPTION_H
