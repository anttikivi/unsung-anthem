//===---------------------------- lua_state.h -------------------*- C++ -*-===//
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
/// \file lua_state.h
/// \brief Declaration of the common Lua state for the tests.
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_TEST_COMMON_LUA_STATE_H
#define ODE_TEST_COMMON_LUA_STATE_H

#include <lua.hpp>

namespace ode
{
  namespace test
  {
    ///
    /// \brief Pointer to the common Lua state of the script tests.
    ///
    extern lua_State* lua_state_script;

    ///
    /// \brief Pointer to the common Lua state of the stack tests.
    ///
    extern lua_State* lua_state_stack;
    
    ///
    /// \brief Pointer to the common Lua state of the stack push tests.
    ///
    extern lua_State* lua_state_push;

    ///
    /// \brief Pointer to the common Lua state of the virtual machine tests.
    ///
    extern lua_State* lua_state_vm;
  } // namespace test
} // namespace ode

#endif // !ODE_TEST_COMMON_LUA_STATE_H
