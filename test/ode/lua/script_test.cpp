//===-------------------------- script_test.cpp -----------------*- C++ -*-===//
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
/// \file script_test.cpp
/// \brief Tests of the definitions of the utilities for Lua scripts.
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/script.h"

#include "ode/filesystem/path.h"
#include "ode/lua/state.h"

#include "ode/config.h"

#include "ode/common/lua_state.h"

#include <catch.hpp>

#if ODE_TEST_BENCHMARKING

#endif // ODE_TEST_BENCHMARKING

TEST_CASE("Lua script file is loaded", "[ode::lua::load_script_file]")
{
  auto state = ode::lua::make_state();

  const std::string filename1 = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "script.lua";

  auto error_code = ode::lua::load_script_file(state.get(), filename1);

  REQUIRE_FALSE(LUA_ERRSYNTAX == error_code);
  REQUIRE_FALSE(LUA_ERRMEM == error_code);
  REQUIRE_FALSE(LUA_ERRGCMM == error_code);
  REQUIRE_FALSE(LUA_ERRFILE == error_code);
  REQUIRE(LUA_OK == error_code);

  const std::string filename2 = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "not_script.lua";

#if defined(GSL_UNENFORCED_ON_CONTRACT_VIOLATION) && \
    GSL_UNENFORCED_ON_CONTRACT_VIOLATION

  error_code = ode::lua::load_script_file(state.get(), filename2);

  REQUIRE_FALSE(LUA_ERRSYNTAX == error_code);
  REQUIRE_FALSE(LUA_ERRMEM == error_code);
  REQUIRE_FALSE(LUA_ERRGCMM == error_code);
  REQUIRE(LUA_ERRFILE == error_code);
  REQUIRE_FALSE(LUA_OK == error_code);

#elif defined(GSL_THROW_ON_CONTRACT_VIOLATION) && \
    GSL_THROW_ON_CONTRACT_VIOLATION

  REQUIRE_THROWS(ode::lua::load_script_file(state.get(), filename2));

#endif // defined(GSL_THROW_ON_CONTRACT_VIOLATION) && \
    GSL_THROW_ON_CONTRACT_VIOLATION
}

#if ODE_TEST_BENCHMARKING

BENCHMARK(ode, lua_load_script_file, 10, 1000)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "script.lua";

  ode::lua::load_script_file(ode::test::lua_state_script, filename.c_str());
}

BENCHMARK(ode, lua_load_script_file_no_log, 10, 1000)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "script.lua";

  ode::lua::test::load_script_file_no_log(
      ode::test::lua_state_script,
      filename.c_str());
}

#endif // ODE_TEST_BENCHMARKING
