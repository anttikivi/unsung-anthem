//===----------------------------- script.cpp -------------------*- C++ -*-===//
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
/// \file script.cpp
/// \brief The definitions of the utilities for Lua scripts.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/script.h"

#include <iostream>

#include "gsl/assert"

#include "ode/logger.h"

#include <lua.hpp>

namespace ode::lua
{
  int load_script_file(
      const gsl::not_null<lua_State*> state,
      std::string_view filename) ODE_CONTRACT_NOEXCEPT
  {
    const auto load_error = luaL_loadfile(state, filename.data());

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
