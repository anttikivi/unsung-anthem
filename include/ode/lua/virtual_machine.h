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

#include <cstddef>

#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>

#include "gsl/assert"

#include "ode/lua/config.h"
#include "ode/lua/stack.h"
#include "ode/lua/state.h"
#include "ode/logger.h"

namespace ode::lua
{
  namespace detail
  {
    template <typename T> constexpr T get_default() noexcept
    {
      return 0;
    }

    template <> inline std::string get_default<std::string>() noexcept
    {
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
  template <typename T> constexpr auto read(
      const state_ptr_t state,
      const int index) ODE_CONTRACT_NOEXCEPT
  {
    if constexpr (std::is_same_v<std::remove_cv_t<T>, bool>)
    {
      return static_cast<bool>(lua_toboolean(state, index));
    }
    else if constexpr (std::is_same_v<std::remove_cv_t<T>, float>)
    {
      Ensures(1 == lua_isnumber(state, index));
      return static_cast<float>(lua_tonumber(state, index));
    }
    else if constexpr (std::is_same_v<std::remove_cv_t<T>, int>)
    {
      Ensures(1 == lua_isnumber(state, index));
      return static_cast<int>(lua_tonumber(state, index)); 
    }
    else if constexpr (std::is_same_v<std::remove_cv_t<T>, std::string>)
    {
      Ensures(1 == lua_isstring(state, index));
      return std::string{lua_tostring(state, index)};
    }
    else
    {
      return 0;
    }
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
  constexpr T read(const state_ptr_t state) ODE_CONTRACT_NOEXCEPT
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
  template <typename T> inline T get(
      const state_ptr_t state,
      std::string_view var) ODE_CONTRACT_NOEXCEPT
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

      template <typename T> static constexpr std::tuple<T> worker(
          const state_ptr_t state,
          const int index) noexcept
      {
        return std::make_tuple(read<T>(state, index));
      }

      template <typename T1, typename T2, typename... Rest>
      static constexpr std::tuple<T1, T2, Rest...> worker(
          const state_ptr_t state,
          const int index) noexcept
      {
        std::tuple<T1> head = std::make_tuple(read<T1>(state, index));
        return std::tuple_cat(head, worker<T2, Rest...>(state, index + 1));
      }

      static constexpr type apply(const state_ptr_t state) noexcept
      {
        auto ret = worker<Types...>(state, 1);
        lua_pop(state, sizeof...(Types));
        return ret;
      }
    };

    template <typename T> struct pop<1, T>
    {
      using type = T;

      static constexpr type apply(
          const state_ptr_t state) ODE_CONTRACT_NOEXCEPT
      {
        T ret = read<T>(state);
        lua_pop(state, 1);
        return ret;
      }
    };

    template <typename... Types> struct pop<0, Types...>
    {
      using type = void;

      static constexpr type apply(const state_ptr_t state) noexcept
      {

      }
    };

    template <typename... Types>
    using pop_t = typename pop<sizeof...(Types), Types...>::type;

    template <typename... Types> constexpr pop_t<Types...> pop_value(
        const state_ptr_t state) ODE_CONTRACT_NOEXCEPT
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
  constexpr detail::pop_t<Types...> call(
      const state_ptr_t state,
      const std::string& name,
      Args&&... args) ODE_CONTRACT_NOEXCEPT
  {
    to_stack(state, name);

    const int n_ret = sizeof...(Types);
    const int n_args = sizeof...(Args);

    push(state, std::forward<Args>(args)...);

    lua_call(state, n_args, n_ret);

    return detail::pop_value<Types...>(state);
  }
} // namespace ode::lua

#endif // !ODE_LUA_VIRTUAL_MACHINE_H
