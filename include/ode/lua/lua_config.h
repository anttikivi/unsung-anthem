//===---------------------------- lua_config.h ------------------*- C++ -*-===//
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
/// \file lua_config.h
/// \brief The declarations and the definitions of the Lua constants.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
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
