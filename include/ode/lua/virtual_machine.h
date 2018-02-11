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
      template <typename T> T get_default() noexcept {
        return 0;
      }

      template <> inline std::string get_default<std::string>() noexcept {
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
    template <typename T>
    T read(const gsl::not_null<lua_State*> state, const int index) noexcept
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
    template <typename T>
    T read(const gsl::not_null<lua_State*> state) noexcept
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
    template <typename T> T get(
        const gsl::not_null<lua_State*> state,
        const std::string& var) noexcept
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
      template <std::size_t, typename... Types> struct pop
      {
        using type = std::tuple<Types...>;

        template <typename T> static std::tuple<T> worker(
            const gsl::not_null<lua_State*> state,
            const int index) noexcept
        {
          return std::make_tuple(read<T>(state, index));
        }

        template <typename T1, typename T2, typename... Rest>
        static std::tuple<T1, T2, Rest...> worker(
            const gsl::not_null<lua_State*> state,
            const int index) noexcept
        {
          std::tuple<T1> head = std::make_tuple(read<T1>(state, index));
          return std::tuple_cat(head, worker<T2, Rest...>(state, index + 1));
        }

        static type apply(const gsl::not_null<lua_State*> state) noexcept
        {
          auto ret = worker<Types...>(state, 1);
          lua_pop(state, sizeof...(Types));
          return ret;
        }
      };

      template <typename T> struct pop<1, T>
      {
        using type = T;

        static type apply(const gsl::not_null<lua_State*> state) noexcept
        {
          T ret = read<T>(state);
          lua_pop(state, 1);
          return ret;
        }
      };

      template <typename... Types> struct pop<0, Types...>
      {
        using type = void;

        static type apply(const gsl::not_null<lua_State*> state) noexcept
        {

        }
      };

      template <typename... Types>
      using pop_t = typename pop<sizeof...(Types), Types...>::type;

      template <typename... Types>
      pop_t<Types...> pop_value(const gsl::not_null<lua_State*> state) noexcept
      {
        return pop<sizeof...(Types), Types...>::apply(state);
      }
    } // namespace detail

    ///
    /// \brief Calls a Lua function.
    ///
    /// \tparam Types the types of the return values.
    /// \tparam Args the types of the function parameters.
    ///
    /// \param state the Lua state.
    /// \param name the name of the Lua function.
    /// \param args the parameters of the Lua function.
    ///
    /// \return the return value of the Lua function.
    ///
    template <typename... Types, typename... Args>
    detail::pop_t<Types...> call(
        const gsl::not_null<lua_State*> state,
        const std::string& name,
        Args&&... args) noexcept
    {
      to_stack(state, name);

      const int n_ret = sizeof...(Types);
      const int n_args = sizeof...(Args);

      push(state, std::forward<Args>(args)...);

      lua_call(state, n_args, n_ret);

      return detail::pop_value<Types...>(state);
    }
  } // namespace lua
} // namespace ode

namespace ode
{
  namespace lua
  {
    template <> inline bool read<bool>(
        const gsl::not_null<lua_State*> state,
        const int index) noexcept
    {
      return static_cast<bool>(lua_toboolean(state, index));
    }

    template <> inline float read<float>(
        const gsl::not_null<lua_State*> state,
        const int index) noexcept
    {
      if (0 == lua_isnumber(state, index))
      {
        ODE_ERROR("The value on top of the Lua stack is not a number");
      }
      return static_cast<float>(lua_tonumber(state, index));
    }

    template <> inline int read<int>(
        const gsl::not_null<lua_State*> state,
        const int index) noexcept
    {
      if (0 == lua_isnumber(state, index))
      {
        ODE_ERROR("The value on top of the Lua stack is not a number");
      }
      return static_cast<int>(lua_tonumber(state, index));
    }

    template <> inline std::string read<std::string>(
        const gsl::not_null<lua_State*> state,
        const int index) noexcept
    {
      if (0 == lua_isstring(state, index))
      {
        ODE_ERROR("The value on top of the Lua stack is not a string");
      }
      return std::string{lua_tostring(state, index)};
    }
  } // namespace lua
} // namespace ode

#endif // !ODE_LUA_VIRTUAL_MACHINE_H
