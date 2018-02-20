//===--------------------------- stack_test.cpp -----------------*- C++ -*-===//
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
/// \file stack_test.cpp
/// \brief Tests of the definitions of the Lua stack utility functions.
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/stack.h"

#include "ode/filesystem/path.h"

#include "ode/config.h"

#include <catch.hpp>

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

TEST_CASE("Lua variable is set to stack", "[ode::lua::to_stack]")
{
  lua_State* l = luaL_newstate();

  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack.lua";

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  const bool is_put = ode::lua::to_stack(l, "testing.lua.stack");

  REQUIRE(3 == lua_gettop(l));

  lua_pop(l, 3);

  lua_close(l);
}

TEST_CASE("Variables are pushed to Lua stack", "[ode::lua::push]")
{
  lua_State* l = luaL_newstate();

  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack.lua";

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  ode::lua::push(l, 3, 2.5f, std::string{"Hello, world!"}, true);

  REQUIRE(4 == lua_gettop(l));

  lua_pop(l, 4);

  lua_close(l);
}

#if ODE_TEST_BENCHMARKING

static void ode_bm_to_stack(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::to_stack(l, "testing.lua.stack");
    lua_pop(l, lua_gettop(l));
  }

  lua_close(l);
}

BENCHMARK(ode_bm_to_stack);

static void ode_bm_push_bool(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack_push.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::push(l, true);
    lua_pop(l, lua_gettop(l));
  }

  lua_close(l);
}

BENCHMARK(ode_bm_push_bool);

static void ode_bm_push_float(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack_push.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::push(l, 15.4f);
    lua_pop(l, lua_gettop(l));
  }

  lua_close(l);
}

BENCHMARK(ode_bm_push_float);

static void ode_bm_push_int(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack_push.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::push(l, 3997);
    lua_pop(l, lua_gettop(l));
  }

  lua_close(l);
}

BENCHMARK(ode_bm_push_int);

static void ode_bm_push_string(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack_push.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::push(l, "A string");
    lua_pop(l, lua_gettop(l));
  }

  lua_close(l);
}

BENCHMARK(ode_bm_push_string);

static void ode_bm_push_string_longer(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack_push.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::push(
        l,
        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Sed "
        "posuere interdum sem. Quisque ligula eros ullamcorper quis, lacinia "
        "quis facilisis sed sapien. Mauris varius diam vitae arcu. Sed arcu "
        "lectus auctor vitae, consectetuer et venenatis eget velit. Sed augue "
        "orci, lacinia eu tincidunt et eleifend nec lacus. Donec ultricies "
        "nisl ut felis, suspendisse potenti. Lorem ipsum ligula ut hendrerit "
        "mollis, ipsum erat vehicula risus, eu suscipit sem libero nec erat. "
        "Aliquam erat volutpat. Sed congue augue vitae neque. Nulla "
        "consectetuer porttitor pede. Fusce purus morbi tortor magna "
        "condimentum vel, placerat id blandit sit amet tortor.");
    lua_pop(l, lua_gettop(l));
  }

  lua_close(l);
}

BENCHMARK(ode_bm_push_string_longer);

static void ode_bm_push(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack_push.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::push(l, "Hello, World!", true, 366, 4.6f);
    lua_pop(l, lua_gettop(l));
  }

  lua_close(l);
}

BENCHMARK(ode_bm_push);

#endif // ODE_TEST_BENCHMARKING
