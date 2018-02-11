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
#include <tuple>

#include <cstddef>

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
      template <typename T> T get_default() {
        return 0;
      }

      template <> inline std::string get_default<std::string>() {
        return "null";
      }
    } // namespace detail

    ///
    /// \brief Reads a value on the Lua stack.
    ///
    /// \tparam T the type of the value on the stack.
    ///
    /// \param state pointer to the Lua state.
    /// \param index the index of the value.
    ///
    /// \return the value on the top of the stack.
    ///
    template <typename T> T read(gsl::not_null<lua_State*> state, const int index) noexcept
    {
      return 0;
    }

    ///
    /// \brief Reads the value on top of the Lua stack.
    ///
    /// \tparam T the type of the value on the stack.
    ///
    /// \param state pointer to the Lua state.
    ///
    /// \return the value on the top of the stack.
    ///
    template <typename T> T read(gsl::not_null<lua_State*> state) noexcept
    {
      return read<T>(state, stack_top);
    }

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
        ret = read<T>(state);
      }
      else
      {
        ret = detail::get_default<T>();
      }

      clean(state);

      return ret;
    }

    namespace detail
    {
      template <std::size_t, typename... Ts> struct pop
      {
        using type = std::tuple<Ts...>;

        template <typename T> static std::tuple<T> worker(
            gsl::not_null<lua_State*> state,
            const int index)
        {
          return std::make_tuple(read<T>(state, index));
        }

        template <typename T1, typename T2, typename... Rest>
        static std::tuple<T1, T2, Rest...> worker(
            gsl::not_null<lua_State*> state,
            const int index)
        {
          std::tuple<T1> head = std::make_tuple(read<T1>(state, index));
          return std::tuple_cat(head, worker<T2, Rest...>(state, index + 1));
        }

        static type apply(gsl::not_null<lua_State*> state)
        {
          auto ret = worker<Ts...>(state, 1);
          lua_pop(state, sizeof...(Ts));
          return ret;
        }
      };

      template <typename T> struct pop<1, T>
      {
        using type = T;

        static type apply(gsl::not_null<lua_State*> state)
        {
          T ret = read<T>(state);
          lua_pop(state, 1);
          return ret;
        }
      };

      template <typename... Ts> struct pop<0, Ts...>
      {
        using type = void;

        static type apply(gsl::not_null<lua_State*> state)
        {

        }
      };

      template <typename... Ts>
      using pop_t = typename pop<sizeof...(Ts), Ts...>::type;

      template <typename... Ts>
      pop_t<Ts...> pop_value(gsl::not_null<lua_State*> state)
      {
        return pop<sizeof...(Ts), Ts...>::apply(state);
      }
    } // namespace detail

    ///
    /// \brief Calls a Lua function.
    ///
    /// \tparam Ts the types of the return values.
    /// \tparam Args the types of the function parameters.
    ///
    /// \param state the Lua state.
    /// \param name the name of the Lua function.
    /// \param args the parameters of the Lua function.
    ///
    /// \return the return value of the Lua function.
    ///
    template <typename... Ts, typename... Args>
    detail::pop_t<Ts...> call(
        gsl::not_null<lua_State*> state,
        const std::string& name,
        Args&&... args)
    {
      to_stack(state, name);

      const int n_ret = sizeof...(Ts);
      const int n_args = sizeof...(Args);

      push(state, std::forward<Args>(args)...);

      lua_call(state, n_args, n_ret);

      return detail::pop_value<Ts...>(state);
    }
  } // namespace lua
} // namespace ode

template <> inline bool ode::lua::read<bool>(
    gsl::not_null<lua_State*> state,
    const int index) noexcept
{
  return static_cast<bool>(lua_toboolean(state, index));
}

template <> inline float ode::lua::read<float>(
    gsl::not_null<lua_State*> state,
    const int index) noexcept
{
  if (0 == lua_isnumber(state, index))
  {
    ODE_ERROR("The value on top of the Lua stack is not a number");
  }
  return static_cast<float>(lua_tonumber(state, index));
}

template <> inline int ode::lua::read<int>(
    gsl::not_null<lua_State*> state,
    const int index) noexcept
{
  if (0 == lua_isnumber(state, index))
  {
    ODE_ERROR("The value on top of the Lua stack is not a number");
  }
  return static_cast<int>(lua_tonumber(state, index));
}

template <> inline std::string ode::lua::read<std::string>(
    gsl::not_null<lua_State*> state,
    const int index) noexcept
{
  if (0 == lua_isstring(state, index))
  {
    ODE_ERROR("The value on top of the Lua stack is not a string");
  }
  return std::string{lua_tostring(state, index)};
}

#endif // !ODE_LUA_VIRTUAL_MACHINE_H
