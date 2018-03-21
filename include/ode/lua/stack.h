//===------------------------------ stack.h ---------------------*- C++ -*-===//
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
/// \file stack.h
/// \brief The declaration of the Lua stack utility functions.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_STACK_H
#define ODE_LUA_STACK_H

#include <string>
#include <string_view>
#include <utility>

#include "gsl/view"

#include "ode/__config"

#include <lua.hpp>

struct lua_State;

namespace ode::lua
{
  ///
  /// \brief Puts a Lua variable to the top of the Lua stack.
  ///
  /// \param state pointer to the Lua state.
  /// \param var the name of the variable to put to the top of the stack.
  ///
  /// \return \c true if the variable was moved successfully, otherwise
  /// \c false.
  ///
  bool to_stack(
      const gsl::not_null<lua_State*> state,
      std::string_view var) ODE_CONTRACT_NOEXCEPT;

  namespace detail
  {
    inline void push(const gsl::not_null<lua_State*> state, bool b) noexcept
    {
      lua_pushboolean(state, b);
    }

    inline void push(const gsl::not_null<lua_State*> state, float f) noexcept
    {
      lua_pushnumber(state, f);
    }

    inline void push(const gsl::not_null<lua_State*> state, int i) noexcept
    {
      lua_pushinteger(state, i);
    }

    // TODO Consider making this constexpr
    inline void push(
        const gsl::not_null<lua_State*> state,
        const std::string& s) noexcept
    {
      // TODO Consider making the ‘const std::string&’ a ‘std::string_view’
      // TODO Consider storing the pointer returned by ‘lua_pushstring’
      lua_pushstring(state, s.c_str());
    }
  } // namespace detail

  ///
  /// \brief Pushes the given value to the stack of the Lua state.
  ///
  /// \tparam T the type of the first value to be pushed.
  ///
  /// \param state pointer to the Lua state.
  /// \param t the first value to be pushed.
  ///
  template <typename T>
  constexpr void push(const gsl::not_null<lua_State*> state, T&& t) noexcept
  {
    detail::push(state, std::forward<T>(t));
  }

  ///
  /// \brief Pushes the given values to the stack of the Lua state.
  ///
  /// \tparam T the type of the first value to be pushed.
  /// \tparam Types the types of the rest of the values to be pushed.
  ///
  /// \param state pointer to the Lua state.
  /// \param t the first value to be pushed.
  /// \param types the rest of the values to be pushed.
  ///
  template <typename T, typename... Types>
  constexpr void push(
      const gsl::not_null<lua_State*> state,
      T&& t,
      Types&&... types) noexcept
  {
    detail::push(state, std::forward<T>(t));
    push(state, std::forward<Types>(types)...);
  }
} // namespace ode::lua

#endif // !ODE_LUA_STACK_H
