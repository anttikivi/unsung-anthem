//===------------------------- virtual_machine.h ----------------*- C++ -*-===//
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
/// \file virtual_machine.h
/// \brief The declaration of the Lua virtual machine utilities.
/// \author Antti Kivi
/// \date 7 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_VIRTUAL_MACHINE_H
#define ODE_LUA_VIRTUAL_MACHINE_H

#include <string>

#include "ode/lua/config.h"
#include "ode/lua/stack.h"
#include "ode/lua/state.h"
#include "ode/logger.h"

#include "gsl/view"

#include <lua.hpp>

namespace ode
{
  namespace lua
  {
    namespace detail
    {
      template <typename T>
      T get(gsl::not_null<lua_State*> state, const std::string& var) noexcept
      {
        return 0;
      }

      template <> inline bool get<bool>(
          gsl::not_null<lua_State*> state,
          const std::string& var) noexcept
      {
        return static_cast<bool>(lua_toboolean(state, stack_top));
      }

      template <> inline float get<float>(
          gsl::not_null<lua_State*> state,
          const std::string& var) noexcept
      {
        if (0 == lua_isnumber(state, stack_top))
        {
          ODE_ERROR("The value on top of the Lua stack is not a number");
        }
        return static_cast<float>(lua_tonumber(state, stack_top));
      }

      template <> inline int get<int>(
          gsl::not_null<lua_State*> state,
          const std::string& var) noexcept
      {
        if (0 == lua_isnumber(state, stack_top))
        {
          ODE_ERROR("The value on top of the Lua stack is not a number");
        }
        return static_cast<int>(lua_tonumber(state, stack_top));
      }

      template <> inline std::string get<std::string>(
          gsl::not_null<lua_State*> state,
          const std::string& var) noexcept
      {
        if (0 == lua_isstring(state, stack_top))
        {
          ODE_ERROR("The value on top of the Lua stack is not a string");
        }
        return std::string{lua_tostring(state, stack_top)};
      }

      template <typename T> T get_default() {
        return 0;
      }

      template <> inline std::string get_default<std::string>() {
        return "null";
      }
    } // namespace detail

    ///
    /// \brief Gets a variable from Lua.
    ///
    /// \tparam T the type of the variable.
    ///
    /// \param state the Lua state.
    /// \param var the name of the variable.
    ///
    /// \return the value of the variable.
    ///
    template <typename T>
    T get(gsl::not_null<lua_State*> state, const std::string& var) noexcept
    {
      T ret;

      if (to_stack(state, var))
      {
        ret = detail::get<T>(state, var);
      }
      else
      {
        ret = detail::get_default<T>();
      }

      clean(state);

      return ret;
    }
  } // namespace lua
} // namespace ode

#endif // !ODE_LUA_VIRTUAL_MACHINE_H
