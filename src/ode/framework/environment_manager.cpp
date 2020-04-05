/// The definition of the manager which holds execution-related information and
/// utilities.
/// \file
/// \author Antti Kivi
/// \date 17 May 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

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
