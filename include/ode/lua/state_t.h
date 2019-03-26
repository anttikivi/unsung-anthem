//===----------------------------- state_t.h --------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file state_t.h
/// \brief The declarations of the Lua state types.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_STATE_T_H
#define ODE_LUA_STATE_T_H

#include <memory>

#include "gsl/view"

#include <lua.hpp>

namespace ode::lua
{
  ///
  /// \brief The type of the Lua state objects.
  ///
  using state_t = std::unique_ptr<lua_State, decltype(&lua_close)>;

  ///
  /// \brief The pointer type which is used as the parameter type for raw Lua
  /// states.
  ///
  using state_ptr_t = gsl::not_null<lua_State*>;

} // namespace ode::lua

#endif // !ODE_LUA_STATE_T_H
