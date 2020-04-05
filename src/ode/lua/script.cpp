/// The definitions of the utilities for Lua scripts.
/// \file
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/lua/script.h"

#include "gsl/assert"

#include "ode/logger.h"

namespace ode::lua
{
  int load_script_file(
      const state_ptr_t state,
      std::string_view filename) ODE_CONTRACT_NOEXCEPT
  {
    ODE_TRACE("Trying to load a Lua script from '{}'", filename.data());

    const auto load_error = luaL_loadfile(state, filename.data());

    ODE_TRACE("The load returned: {}", load_error);

    Ensures(LUA_OK == load_error);

    ODE_TRACE(
        "The script '{}' is loaded with code {}",
        filename.data(),
        load_error);

    const auto call_error = lua_pcall(state, 0, 0, 0);

    Ensures(LUA_OK == call_error);

    ODE_TRACE("The script '{}' is called with code {}",
        filename.data(),
        call_error);

    return load_error;
  }
} // namespace ode::lua
