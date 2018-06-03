//===----------------------------- state.cpp --------------------*- C++ -*-===//
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
/// \file state.cpp
/// \brief The definitions of the Lua state utilities.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

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
