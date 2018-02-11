//===---------------------------- clean_up.cpp ------------------*- C++ -*-===//
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
/// \file clean_up.cpp
/// \brief Definition of the common cleanup function of the tests.
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/clean_up.h"

#include "ode/common/lua_state.h"

namespace ode
{
  namespace test
  {
    void clean_up()
    {
      lua_close(lua_state_script);
      lua_close(lua_state_stack);
      lua_close(lua_state_push);
      lua_close(lua_state_vm);

      lua_state_script = nullptr;
      lua_state_stack = nullptr;
      lua_state_push = nullptr;
      lua_state_vm = nullptr;
    }
  } // namespace test
} // namespace ode
