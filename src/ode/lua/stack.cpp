//===----------------------------- stack.cpp --------------------*- C++ -*-===//
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
/// \file stack.cpp
/// \brief The definitions of the Lua stack utility functions.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/stack.h"

#include "gsl/assert"

#include "ode/logger.h"
#include "ode/lua/lua_config.h"

namespace ode::lua
{
  bool to_stack(
      const state_ptr_t state,
      std::string_view var) ODE_CONTRACT_NOEXCEPT
  {
    int index = 0;
    std::string current = "";

    for (auto c : var)
    {
      if ('.' == c)
      {
        if (0 == index)
        {
          lua_getglobal(state, current.c_str());
          ODE_TRACE("Got the global '{}' to the top of the stack", current);
        }
        else
        {
          lua_getfield(state, stack_top, current.c_str());
          ODE_TRACE("Got '{}' to the top of the stack", current);
        }

        Ensures(0 == lua_isnil(state.get(), stack_top));

        ODE_TRACE("Resetting the temporary variable '{}'", current);
        current = "";
        ++index;
      }
      else
      {
        ODE_TRACE("Adding '{}' to '{}'", c, current);
        current += c;
      }
    }

    if (0 == index)
    {
      lua_getglobal(state, current.c_str());
      ODE_TRACE("Got the global '{}' to the top of the stack", current);
    }
    else
    {
      lua_getfield(state, stack_top, current.c_str());
      ODE_TRACE("Got '{}' to the top of the stack", current);
    }

    Ensures(0 == lua_isnil(state, stack_top));

    return true;
  }
} // namespace ode::lua
