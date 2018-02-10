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

#include "ode/lua/config.h"

#include "ode/config.h"

#include <catch.hpp>

#if ODE_TEST_BENCHMARKING
# include <hayai/hayai.hpp>
#endif // ODE_TEST_BENCHMARKING

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

  luaL_openlibs(state);

  const std::string filename =
      std::string{ode::test_script_root} + "/state.lua";

  const auto load_error = luaL_loadfile(state, filename.c_str());

  lua_pcall(state, 0, 0, 0);

  const std::string var = "test.level.another";

  gsl::index index = 0;
  std::string current = "";

  for (auto c : var)
  {
    if ('.' == c)
    {
      if (0 == index)
      {
        lua_getglobal(state, current.c_str());
      }
      else
      {
        lua_getfield(state, ode::lua::stack_top, current.c_str());
      }

      current = "";
      index += 1;
    }
    else
    {
      current += c;
    }
  }

  lua_getfield(state, ode::lua::stack_top, current.c_str());

  const auto top1 = lua_gettop(state);

  REQUIRE(top1 == ++index);

  ode::lua::clean(state);

  const auto top2 = lua_gettop(state);

  REQUIRE(top2 == 0);

  lua_close(state);

  state = nullptr;
}

#if ODE_TEST_BENCHMARKING

BENCHMARK(ode, lua_make_state, 10, 1000)
{
  {
    auto state = ode::lua::make_state();
  }
}

#endif // ODE_TEST_BENCHMARKING
