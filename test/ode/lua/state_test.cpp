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

  luaL_openlibs(state);

  const std::string filename = "script/test/ode/state.lua";

  const auto load_error = luaL_loadfile(state, filename.c_str());

  if (0 != load_error)
  {
    FAIL(
        "Failed to load the Lua script: "
        << filename
        << ", error code: "
        << load_error);
  }

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

      if (0 != lua_isnil(state, ode::lua::stack_top))
      {
        WARN("The top of the Lua stack is null");
      }
      else
      {
        current = "";
        index += 1;
      }
    }
    else
    {
      current += c;
    }
  }

  if (0 == index)
  {
    lua_getglobal(state, current.c_str());
  }
  else
  {
    lua_getfield(state, ode::lua::stack_top, current.c_str());
  }

  if (0 != lua_isnil(state, ode::lua::stack_top))
  {
    WARN("The top of the Lua stack is null");
  }

  const auto top1 = lua_gettop(state);

  REQUIRE(top1 == ++index);

  ode::lua::clean(state);

  const auto top2 = lua_gettop(state);

  REQUIRE(top2 == 0);

  lua_close(state);

  state = nullptr;
}

BENCHMARK(ode, lua_make_state, 10, 1000)
{
  {
    auto state = ode::lua::make_state();
  }
}
