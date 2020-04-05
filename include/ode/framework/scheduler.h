/// The declaration of the scheduler which executes the updates of the
/// application on each frame.
/// \file
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_FRAMEWORK_SCHEDULER_H
#define ODE_FRAMEWORK_SCHEDULER_H

#include "ode/engine_framework.h"
#include "ode/framework/state.h"

namespace ode
{
  ///
  /// Runs the next frame of the application and constructs the state from it.
  ///
  /// TODO
  ///
  template <typename A>
  state update_state(const state& previous, engine_framework<A>& engine)
  {
    return {};
  }

} // namespace ode

#endif // !ODE_FRAMEWORK_SCHEDULER_H
