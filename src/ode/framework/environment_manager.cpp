//===---------------------- environment_manager.cpp -------------*- C++ -*-===//
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
/// \file environment_manager.cpp
/// \brief The definition of the manager which holds execution-related
/// information and utilities.
/// \author Antti Kivi
/// \date 17 May 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/framework/environment_manager.h"

#include "ode/logger.h"

namespace ode
{
  environment_manager::environment_manager() : execute{true}
  {

  }

  void environment_manager::schedule_termination()
  {
    execute = false;
    ODE_DEBUG("The program was scheduled to quit");
  }

  environment_manager environment;

} // namespace ode
