/// The declarations of the Lua state types.
/// \file
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_LUA_STATE_T_H
#define ODE_LUA_STATE_T_H

#include <memory>

#include "gsl/view"

#include <lua.hpp>

namespace ode::lua
{
  ///
  /// The type of the Lua state objects.
  ///
  using state_t = std::unique_ptr<lua_State, decltype(&lua_close)>;

  ///
  /// The pointer type which is used as the parameter type for raw Lua states.
  ///
  using state_ptr_t = gsl::not_null<lua_State*>;

} // namespace ode::lua

#endif // !ODE_LUA_STATE_T_H
