//===---------------------------- lua_config.h ------------------*- C++ -*-===//
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
/// \file lua_config.h
/// \brief The declarations and the definitions of the Lua constants.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_LUA_CONFIG_H
#define ODE_LUA_LUA_CONFIG_H

namespace ode::lua
{
  ///
  /// \brief The index which represents the top of the Lua stack.
  ///
  constexpr int stack_top = -1;

} // namespace ode::lua

#endif // !ODE_LUA_LUA_CONFIG_H
