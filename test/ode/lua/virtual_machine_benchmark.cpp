//===------------------- virtual_machine_benchmark.cpp ----------*- C++ -*-===//
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
/// \file virtual_machine_benchmark.cpp
/// \brief The benchmarks of the Lua virtual machine utilities.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/virtual_machine.h"

#include "ode/config.h"
#include "ode/filesystem/path.h"

#include <benchmark/benchmark.h>

static void ode_lua_get_str(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto s = ode::lua::get<std::string>(l, "str");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_str);

static void ode_lua_get_greeting(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto s = ode::lua::get<std::string>(l, "greeting");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_greeting);

static void ode_lua_get_int(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto i = ode::lua::get<int>(l, "int");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_int);

static void ode_lua_get_integer(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto i = ode::lua::get<int>(l, "integer");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_integer);

static void ode_lua_get_f(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto f = ode::lua::get<float>(l, "f");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_f);

static void ode_lua_get_float(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto f = ode::lua::get<float>(l, "float");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_float);

static void ode_lua_get_b(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto b = ode::lua::get<bool>(l, "b");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_b);

static void ode_lua_get_bool(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto b = ode::lua::get<bool>(l, "boolean");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_bool);

static void ode_lua_get_table_str(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto s = ode::lua::get<std::string>(l, "table.str");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_table_str);

static void ode_lua_get_table_greeting(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto s = ode::lua::get<std::string>(l, "table.greeting");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_table_greeting);

static void ode_lua_get_table_int(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto i = ode::lua::get<int>(l, "table.int");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_table_int);

static void ode_lua_get_table_integer(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto i = ode::lua::get<int>(l, "table.integer");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_table_integer);

static void ode_lua_get_table_f(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto f = ode::lua::get<float>(l, "table.f");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_table_f);

static void ode_lua_get_table_float(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto f = ode::lua::get<float>(l, "table.float");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_table_float);

static void ode_lua_get_table_b(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto b = ode::lua::get<bool>(l, "table.b");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_table_b);

static void ode_lua_get_table_bool(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto b = ode::lua::get<bool>(l, "table.bool");
  }

  lua_close(l);
}

BENCHMARK(ode_lua_get_table_bool);

static void ode_lua_call_add(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto i = ode::lua::call<int>(l, "add", 688, 12);
  }

  lua_close(l);
}

BENCHMARK(ode_lua_call_add);

static void ode_lua_call_pow(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine_benchmark.lua";

  lua_State* l = luaL_newstate();

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  for (auto _ : state)
  {
    const auto i = ode::lua::call<int>(l, "pow", 2, 7);
  }

  lua_close(l);
}

BENCHMARK(ode_lua_call_pow);
