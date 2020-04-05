/// The declarations of the Lua state utilities
/// \file
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_LUA_STATE_H
#define ODE_LUA_STATE_H

#include "ode/lua/state_t.h"

namespace ode::lua
{
  ///
  /// Initializes a new Lua state.
  ///
  /// \return A pointer to the new \c lua_State.
  ///
  state_t make_state() noexcept;

  ///
  /// Resets the given Lua state.
  ///
  /// \param state the Lua state to reset.
  ///
  void clean(const state_ptr_t state) noexcept;

} // namespace ode::lua

#endif // !ODE_LUA_STATE_H
