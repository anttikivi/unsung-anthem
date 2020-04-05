/// The declarations of the execution information types.
/// \file
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_EXECUTION_INFO_H
#define ODE_EXECUTION_INFO_H

#include <string>

#include "ode/argv_t.h"
#include "ode/pixel_count.h"

namespace ode
{
  using namespace std::literals::string_literals;

  ///
  /// The type of the objects which are used to pass information according to
  /// which the execution of the engine is started.
  ///
  struct execution_info final
  {
    ///
    /// The number of the command line arguments passed to the program.
    ///
    const int argc;

    ///
    /// The command line arguments passed to the program.
    ///
    const argv_t* argv;

    ///
    /// The starting width of the window.
    ///
    const pixel_count window_width = 0_px;

    ///
    /// The starting height of the window.
    ///
    const pixel_count window_height = 0_px;

    ///
    /// The name of the window.
    ///
    const std::string window_name = "null"s;
  };
} // namespace ode

#endif // !ODE_EXECUTION_INFO_H
