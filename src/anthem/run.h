//===------------------------------- run.h ----------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2018 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file run.h
/// \brief The declaration of the main execution function.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_RUN_H
#define ANTHEM_RUN_H

#include <cstdlib>

#include "ode/argv_t.h"

namespace anthem
{
  ///
  /// \brief Returns the end code of the program after executing it with the
  /// given arguments.
  ///
  /// This function is impure.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return A value which represents the end code of the program.
  ///
  auto run(int argc, ode::argv_t argv[]) -> decltype(EXIT_SUCCESS);

} // namespace anthem

#endif // !ANTHEM_RUN_H
