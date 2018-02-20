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

#include "ode/filesystem/path.h"

#include "ode/config.h"

#include <catch.hpp>

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

TEST_CASE("Lua variable values are got right", "[ode::lua::make_state]")
{
  lua_State* state = luaL_newstate();

  luaL_openlibs(state);

  const std::string filename =
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine.lua";

  const auto load_error = luaL_loadfile(state, filename.data());

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

  REQUIRE(std::string{"Hello!"} == str);
  REQUIRE(3 == integer);
  REQUIRE(7.4f == floating);
  REQUIRE(true == boolean);

#if defined(GSL_UNENFORCED_ON_CONTRACT_VIOLATION) && \
    GSL_UNENFORCED_ON_CONTRACT_VIOLATION

  const auto made_up_str = ode::lua::get<std::string>(state, made_up_var);
  const auto made_up_int = ode::lua::get<int>(state, made_up_var);
  const auto made_up_float = ode::lua::get<float>(state, made_up_var);
  const auto made_up_bool = ode::lua::get<bool>(state, made_up_var);

  REQUIRE(std::string{"null"} == made_up_str);
  REQUIRE(0 == made_up_int);
  REQUIRE(0 == made_up_float);
  REQUIRE(0 == made_up_bool);

#elif defined(GSL_THROW_ON_CONTRACT_VIOLATION) && \
    GSL_THROW_ON_CONTRACT_VIOLATION

  REQUIRE_THROWS(ode::lua::get<std::string>(state, made_up_var));
  REQUIRE_THROWS(ode::lua::get<int>(state, made_up_var));
  REQUIRE_THROWS(ode::lua::get<float>(state, made_up_var));
  REQUIRE_THROWS(ode::lua::get<bool>(state, made_up_var));
  
#endif // defined(GSL_THROW_ON_CONTRACT_VIOLATION) && \
    GSL_THROW_ON_CONTRACT_VIOLATION

  lua_close(state);

  state = nullptr;
}

TEST_CASE("Lua functions are called", "[ode::lua::call]")
{
  lua_State* state = luaL_newstate();

  luaL_openlibs(state);

  const std::string filename =
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine.lua";

  const auto load_error = luaL_loadfile(state, filename.c_str());

  lua_pcall(state, 0, 0, 0);

  const std::string add_func = "add";
  const std::string pow_func = "pow";

  const auto add_ret = ode::lua::call<int>(state, add_func, 4, 6);
  const auto pow_ret = ode::lua::call<int>(state, pow_func, 2, 3);

  REQUIRE(10 == add_ret);
  REQUIRE(8 == pow_ret);

  lua_close(state);

  state = nullptr;
}

#if ODE_TEST_BENCHMARKING

static void ode_bm_lua_get_str(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto s = ode::lua::get<std::string>(l, "str");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_str);

static void ode_bm_lua_get_greeting(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto s = ode::lua::get<std::string>(l, "greeting");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_greeting);

static void ode_bm_lua_get_int(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto i = ode::lua::get<int>(l, "int");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_int);

static void ode_bm_lua_get_integer(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto i = ode::lua::get<int>(l, "integer");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_integer);

static void ode_bm_lua_get_f(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto f = ode::lua::get<float>(l, "f");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_f);

static void ode_bm_lua_get_float(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto f = ode::lua::get<float>(l, "float");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_float);

static void ode_bm_lua_get_b(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto b = ode::lua::get<bool>(l, "b");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_b);

static void ode_bm_lua_get_bool(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto b = ode::lua::get<bool>(l, "boolean");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_bool);

static void ode_bm_lua_get_table_str(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto s = ode::lua::get<std::string>(l, "table.str");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_table_str);

static void ode_bm_lua_get_table_greeting(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto s = ode::lua::get<std::string>(l, "table.greeting");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_table_greeting);

static void ode_bm_lua_get_table_int(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto i = ode::lua::get<int>(l, "table.int");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_table_int);

static void ode_bm_lua_get_table_integer(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto i = ode::lua::get<int>(l, "table.integer");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_table_integer);

static void ode_bm_lua_get_table_f(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto f = ode::lua::get<float>(l, "table.f");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_table_f);

static void ode_bm_lua_get_table_float(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto f = ode::lua::get<float>(l, "table.float");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_table_float);

static void ode_bm_lua_get_table_b(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto b = ode::lua::get<bool>(l, "table.b");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_table_b);

static void ode_bm_lua_get_table_bool(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto b = ode::lua::get<bool>(l, "table.bool");
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_get_table_bool);

static void ode_bm_lua_call_add(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto i = ode::lua::call<int>(l, "add", 688, 12);
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_call_add);

static void ode_bm_lua_call_pow(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    const auto i = ode::lua::call<int>(l, "pow", 2, 7);
  }

  lua_close(l);
}

BENCHMARK(ode_bm_lua_call_pow);

#endif // ODE_TEST_BENCHMARKING
