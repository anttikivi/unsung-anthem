//===------------------------ stack_benchmark.cpp ---------------*- C++ -*-===//
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
/// \file stack_benchmark.cpp
/// \brief The benchmarks of the Lua stack utility functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/stack.h"

#include "ode/config.h"
#include "ode/filesystem/path.h"

#include <benchmark/benchmark.h>

static void ode_to_stack(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    ode::lua::to_stack(l, "testing.lua.stack");
    lua_pop(l, lua_gettop(l));
  }

  lua_close(l);
}

BENCHMARK(ode_to_stack);

static void ode_push_bool(benchmark::State& state)
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

BENCHMARK(ode_push_bool);

static void ode_push_float(benchmark::State& state)
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

BENCHMARK(ode_push_float);

static void ode_push_int(benchmark::State& state)
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

BENCHMARK(ode_push_int);

static void ode_push_string(benchmark::State& state)
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

BENCHMARK(ode_push_string);

static void ode_push_string_longer(benchmark::State& state)
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

BENCHMARK(ode_push_string_longer);

static void ode_push(benchmark::State& state)
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

BENCHMARK(ode_push);
