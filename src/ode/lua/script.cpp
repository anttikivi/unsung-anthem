//===----------------------------- script.cpp -------------------*- C++ -*-===//
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
/// \file script.cpp
/// \brief The definitions of the utilities for Lua scripts.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

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
