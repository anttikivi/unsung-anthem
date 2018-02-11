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
#include <utility>

#include "gsl/view"

struct lua_State;

namespace ode
{
  namespace lua
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
        const std::string& var) noexcept;

    namespace detail
    {
      void push(const gsl::not_null<lua_State*> state, bool b) noexcept;
      void push(const gsl::not_null<lua_State*> state, float f) noexcept;
      void push(const gsl::not_null<lua_State*> state, int i) noexcept;
      void push(
          const gsl::not_null<lua_State*> state,
          const std::string& s) noexcept;
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
    void push(const gsl::not_null<lua_State*> state, T&& t) noexcept
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
    void push(
        const gsl::not_null<lua_State*> state,
        T&& t,
        Types&&... types) noexcept
    {
      detail::push(state, std::forward<T>(t));
      push(state, std::forward<Types>(types)...);
    }

    namespace test
    {
      bool to_stack_no_log(
          const gsl::not_null<lua_State*> state,
          const std::string& var) noexcept;

    } // namespace test
  } // namespace lua
} // namespace ode

#endif // !ODE_LUA_STACK_H
