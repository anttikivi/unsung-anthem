/// The declaration of the type of the argument array passed into the main
/// function.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_ARGV_T_H
#define ODE_ARGV_T_H

#include "ode/__config"

namespace ode
{
  ///
  /// TODO
  ///
#if ODE_WINDOWS
  using argv_t = char*;
#else
  using argv_t = const char*;
#endif // !ODE_WINDOWS
} // namespace ode

#endif // !ODE_ARGV_T_H
