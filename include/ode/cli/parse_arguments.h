//===------------------------- parse_arguments.h ----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2020 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file parse_arguments.h
/// \brief The declarations of the utility for parsing command line arguments.
/// \author Antti Kivi
/// \date 18 March 2020
/// \copyright Copyright (c) 2020 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_CLI_PARSE_ARGUMENTS_H
#define ODE_CLI_PARSE_ARGUMENTS_H

#include "ode/argv_t.h"

namespace ode::cli {

  ///
  /// \brief Returns an object of the type \c arguments which contains the
  /// values set when executing the program from the command line.
  ///
  /// TODO Return value.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return An object of the type \c arguments.
  ///
  void parse_arguments(const int argc, ode::argv_t argv[]) noexcept;

} // namespace ode::cli

#endif // !ODE_CLI_PARSE_ARGUMENTS_H
