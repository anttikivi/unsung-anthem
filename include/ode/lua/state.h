//===------------------------------ state.h ---------------------*- C++ -*-===//
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
/// \file state.h
/// \brief The declaration of the Lua state.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_STATE_H
#define ODE_LUA_STATE_H

#include <memory>

#include "gsl/view"

#include <lua.hpp>

namespace ode
{
  namespace lua
  {
    ///
    /// \brief The type of a pointer to an object of Lua state.
    ///
    using state_ptr = std::unique_ptr<lua_State, decltype(&lua_close)>;

    ///
    /// \brief Makes a new Lua state.
    ///
    /// \return Pointer to the new \c lua_State.
    ///
    state_ptr make_state() noexcept;

    ///
    /// \brief Resets the Lua state.
    ///
    /// \param state the state to reset.
    ///
    void clean(gsl::not_null<lua_State*> state) noexcept;
  } // namespace lua
} // namespace ode

#endif // !ODE_LUA_STATE_H
