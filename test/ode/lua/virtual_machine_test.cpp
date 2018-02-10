//===---------------------- virtual_machine_test.cpp ------------*- C++ -*-===//
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
/// \file virtual_machine_test.cpp
/// \brief Tests of the definitions of the Lua virtual machine utilities.
/// \author Antti Kivi
/// \date 10 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/virtual_machine.h"

#include "gsl/util"

#include "ode/config.h"

#include "ode/common/lua_state.h"

#include <catch.hpp>

#include <hayai/hayai.hpp>

TEST_CASE("Lua variable values are got right", "[ode::lua::make_state]")
{
  lua_State* state = luaL_newstate();

  luaL_openlibs(state);

  const std::string filename =
      std::string{ode::test_script_root} + "/virtual_machine.lua";

  const auto load_error = luaL_loadfile(state, filename.c_str());

  lua_pcall(state, 0, 0, 0);

  const std::string str_var = "table.str";
  const std::string int_var = "integer";
  const std::string float_var = "floating_point";
  const std::string bool_var = "boolean";
  const std::string made_up_var = "not.real";

  const auto str = ode::lua::get<std::string>(state, str_var);
  const auto integer = ode::lua::get<int>(state, int_var);
  const auto floating = ode::lua::get<float>(state, float_var);
  const auto boolean = ode::lua::get<bool>(state, bool_var);

  const auto made_up_str = ode::lua::get<std::string>(state, made_up_var);
  const auto made_up_int = ode::lua::get<int>(state, made_up_var);
  const auto made_up_float = ode::lua::get<float>(state, made_up_var);
  const auto made_up_bool = ode::lua::get<bool>(state, made_up_var);

  REQUIRE(std::string{"Hello!"} == str);
  REQUIRE(3 == integer);
  REQUIRE(7.4f == floating);
  REQUIRE(true == boolean);

  REQUIRE(std::string{"null"} == made_up_str);
  REQUIRE(0 == made_up_int);
  REQUIRE(0 == made_up_float);
  REQUIRE(0 == made_up_bool);

  lua_close(state);

  state = nullptr;
}

BENCHMARK(ode, lua_get_str, 100, 1000)
{
  const auto s = ode::lua::get<std::string>(ode::test::lua_state_vm, "str");
}

BENCHMARK(ode, lua_get_greeting, 100, 1000)
{
  const auto s = ode::lua::get<std::string>(
      ode::test::lua_state_vm,
      "greeting");
}

BENCHMARK(ode, lua_get_int, 100, 1000)
{
  const auto i = ode::lua::get<int>(ode::test::lua_state_vm, "int");
}

BENCHMARK(ode, lua_get_integer, 100, 1000)
{
  const auto i = ode::lua::get<int>(ode::test::lua_state_vm, "integer");
}

BENCHMARK(ode, lua_get_f, 100, 1000)
{
  const auto f = ode::lua::get<float>(ode::test::lua_state_vm, "f");
}

BENCHMARK(ode, lua_get_float, 100, 1000)
{
  const auto f = ode::lua::get<float>(
      ode::test::lua_state_vm,
      "floating_point");
}

BENCHMARK(ode, lua_get_b, 100, 1000)
{
  const auto b = ode::lua::get<bool>(ode::test::lua_state_vm, "b");
}

BENCHMARK(ode, lua_get_bool, 100, 1000)
{
  const auto b = ode::lua::get<bool>(ode::test::lua_state_vm, "boolean");
}

BENCHMARK(ode, lua_get_table_str, 100, 1000)
{
  const auto s = ode::lua::get<std::string>(
      ode::test::lua_state_vm,
      "table.str");
}

BENCHMARK(ode, lua_get_table_greeting, 100, 1000)
{
  const auto s = ode::lua::get<std::string>(
      ode::test::lua_state_vm,
      "table.greeting");
}

BENCHMARK(ode, lua_get_table_int, 100, 1000)
{
  const auto i = ode::lua::get<int>(ode::test::lua_state_vm, "table.int");
}

BENCHMARK(ode, lua_get_table_integer, 100, 1000)
{
  const auto i = ode::lua::get<int>(ode::test::lua_state_vm, "table.integer");
}

BENCHMARK(ode, lua_get_table_f, 100, 1000)
{
  const auto f = ode::lua::get<float>(ode::test::lua_state_vm, "table.f");
}

BENCHMARK(ode, lua_get_table_float, 100, 1000)
{
  const auto f = ode::lua::get<float>(
      ode::test::lua_state_vm,
      "table.floating_point");
}

BENCHMARK(ode, lua_get_table_b, 100, 1000)
{
  const auto b = ode::lua::get<bool>(ode::test::lua_state_vm, "table.b");
}

BENCHMARK(ode, lua_get_table_bool, 100, 1000)
{
  const auto b = ode::lua::get<bool>(ode::test::lua_state_vm, "table.boolean");
}
