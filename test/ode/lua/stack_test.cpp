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

#include "ode/common/lua_state.h"

#include <catch.hpp>

#if ODE_TEST_BENCHMARKING
# include <hayai/hayai.hpp>
#endif // ODE_TEST_BENCHMARKING

TEST_CASE("Lua variable is set to stack", "[ode::lua::to_stack]")
{
  lua_State* state = luaL_newstate();

  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack.lua";

  luaL_openlibs(state);

  const auto error_code = luaL_loadfile(state, filename.c_str());

  lua_pcall(state, 0, 0, 0);

  const bool is_put = ode::lua::to_stack(state, "testing.lua.stack");

  REQUIRE(3 == lua_gettop(state));

  lua_pop(state, 3);

  lua_close(state);
}

TEST_CASE("Variables are pushed to Lua stack", "[ode::lua::push]")
{
  lua_State* state = luaL_newstate();

  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack.lua";

  luaL_openlibs(state);

  const auto error_code = luaL_loadfile(state, filename.c_str());

  lua_pcall(state, 0, 0, 0);

  ode::lua::push(state, 3, 2.5f, std::string{"Hello, world!"}, true);

  REQUIRE(4 == lua_gettop(state));

  lua_pop(state, 4);

  lua_close(state);
}

#if ODE_TEST_BENCHMARKING

BENCHMARK(ode, lua_to_stack, 10, 1000)
{
  ode::lua::to_stack(ode::test::lua_state_stack, "testing.lua.stack");
  lua_pop(ode::test::lua_state_stack, lua_gettop(ode::test::lua_state_stack));
}

BENCHMARK(ode, lua_to_stack_no_log, 10, 1000)
{
  ode::lua::test::to_stack_no_log(
      ode::test::lua_state_stack,
      "testing.lua.stack");
  lua_pop(ode::test::lua_state_stack, lua_gettop(ode::test::lua_state_stack));
}

BENCHMARK(ode, lua_push_bool, 10, 1000)
{
  ode::lua::push(ode::test::lua_state_push, true);
  lua_pop(ode::test::lua_state_push, lua_gettop(ode::test::lua_state_push));
}

BENCHMARK(ode, lua_push_float, 10, 1000)
{
  ode::lua::push(ode::test::lua_state_push, 15.4f);
  lua_pop(ode::test::lua_state_push, lua_gettop(ode::test::lua_state_push));
}

BENCHMARK(ode, lua_push_int, 10, 1000)
{
  ode::lua::push(ode::test::lua_state_push, 3997);
  lua_pop(ode::test::lua_state_push, lua_gettop(ode::test::lua_state_push));
}

BENCHMARK(ode, lua_push_string, 10, 1000)
{
  ode::lua::push(ode::test::lua_state_push, "A string");
  lua_pop(ode::test::lua_state_push, lua_gettop(ode::test::lua_state_push));
}

BENCHMARK(ode, lua_push_string_longer, 10, 1000)
{
  ode::lua::push(
    ode::test::lua_state_push,
    "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Sed posuere "
    "interdum sem. Quisque ligula eros ullamcorper quis, lacinia quis "
    "facilisis sed sapien. Mauris varius diam vitae arcu. Sed arcu lectus "
    "auctor vitae, consectetuer et venenatis eget velit. Sed augue orci, "
    "lacinia eu tincidunt et eleifend nec lacus. Donec ultricies nisl ut "
    "felis, suspendisse potenti. Lorem ipsum ligula ut hendrerit mollis, "
    "ipsum erat vehicula risus, eu suscipit sem libero nec erat. Aliquam erat "
    "volutpat. Sed congue augue vitae neque. Nulla consectetuer porttitor "
    "pede. Fusce purus morbi tortor magna condimentum vel, placerat id "
    "blandit sit amet tortor.");
  lua_pop(ode::test::lua_state_push, lua_gettop(ode::test::lua_state_push));
}

BENCHMARK(ode, lua_push, 10, 1000)
{
  ode::lua::push(ode::test::lua_state_push, "Hello, World!", true, 366, 4.6f);
  lua_pop(ode::test::lua_state_push, lua_gettop(ode::test::lua_state_push));
}

#endif // ODE_TEST_BENCHMARKING
