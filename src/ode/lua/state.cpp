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
/// \brief The definition of the Lua state.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/state.h"

namespace ode
{
  namespace lua
  {
    state_ptr make_state() noexcept
    {
      return state_ptr{luaL_newstate(), lua_close};
    }

    void clean(gsl::not_null<lua_State*> state) noexcept
    {
      lua_pop(state, lua_gettop(state));
    }
  } // namespace lua
} // namespace ode
