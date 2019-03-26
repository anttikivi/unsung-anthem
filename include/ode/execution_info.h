//===-------------------------- execution_info.h ----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file execution_info.h
/// \brief The declarations of the execution information types.
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_EXECUTION_INFO_H
#define ODE_EXECUTION_INFO_H

#include <string>

#include "ode/argv_t.h"
#include "ode/pixel_count.h"

namespace ode
{
  using namespace std::literals::string_literals;

  ///
  /// \struct execution_info
  /// \brief The type of the objects which are used to pass information
  /// according to which the execution of the engine is started.
  ///
  struct execution_info final
  {
    ///
    /// \brief The number of the command line arguments passed to the program.
    ///
    const int argc;

    ///
    /// The command line arguments passed to the program.
    ///
    const argv_t* argv;

    ///
    /// \brief The starting width of the window.
    ///
    const pixel_count window_width = 0_px;

    ///
    /// \brief The starting height of the window.
    ///
    const pixel_count window_height = 0_px;

    ///
    /// \brief The name of the window.
    ///
    const std::string window_name = "null"s;
  };
} // namespace ode

#endif // !ODE_EXECUTION_INFO_H
