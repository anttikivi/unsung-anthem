/// The definitions of the Lua state utilities.
/// \file
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/lua/state.h"

namespace ode::lua
{
  state_t make_state() noexcept
  {
    return state_t{luaL_newstate(), &lua_close};
  }

  void clean(const state_ptr_t state) noexcept
  {
    lua_pop(state, lua_gettop(state));
  }

} // namespace ode::lua
