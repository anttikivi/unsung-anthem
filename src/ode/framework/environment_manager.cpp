//===---------------------- environment_manager.cpp -------------*- C++ -*-===//
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
/// \file environment_manager.cpp
/// \brief The definition of the manager which holds execution-related
/// information and utilities.
/// \author Antti Kivi
/// \date 17 May 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
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

} // namespace ode
