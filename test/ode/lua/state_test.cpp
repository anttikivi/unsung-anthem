//===--------------------------- state_test.cpp -----------------*- C++ -*-===//
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
/// \file state_test.cpp
/// \brief Tests of the definition of the Lua state.
/// \author Antti Kivi
/// \date 7 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/state.h"

#include "gsl/util"

#include <catch.hpp>

#include <hayai/hayai.hpp>

TEST_CASE("Lua state is created", "[ode::lua::make_state]")
{
  auto state = ode::lua::make_state();

  REQUIRE_FALSE(nullptr == state);

  state.reset(nullptr);

  REQUIRE(nullptr == state);
}

TEST_CASE("Lua state is cleaned", "[ode::lua::clean]")
{
  lua_State* state = luaL_newstate();

  ode::lua::clean(state);

  lua_close(state);

  state = nullptr;
}

BENCHMARK(ode, lua_make_state, 10, 1000)
{
  {
    auto state = ode::lua::make_state();
  }
}
