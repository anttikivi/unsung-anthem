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
/// \brief The definition of the Lua stack utility functions.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/stack.h"

#include "ode/logger.h"
#include "ode/lua/config.h"

#include <lua.hpp>

namespace ode
{
  namespace lua
  {
    bool to_stack(
        gsl::not_null<lua_State*> state,
        const std::string& var) noexcept
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
          }
          else
          {
            lua_getfield(state, stack_top, current.c_str());
          }

          if (0 != lua_isnil(state, stack_top))
          {
            ODE_ERROR("The top of the Lua stack is null");
            return false;
          }
          else
          {
            current = "";
            ++index;
          }
        }
        else
        {
          current += c;
        }
      }

      if (0 == index)
      {
        lua_getglobal(state, current.c_str());
      }
      else
      {
        lua_getfield(state, stack_top, current.c_str());
      }

      if (0 != lua_isnil(state, stack_top))
      {
        ODE_ERROR("The top of the Lua stack is null");
        return false;
      }

      return true;
    }
  } // namespace lua
} // namespace ode
