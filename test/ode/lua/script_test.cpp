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

#include "ode/lua/state.h"

#include "ode/config.h"

#include "ode/common/lua_state.h"

#include <catch.hpp>

#include <hayai/hayai.hpp>

TEST_CASE("Lua script file is loaded", "[ode::lua::load_script_file]")
{
  auto state = ode::lua::make_state();

  const std::string filename1 = 
      std::string{ode::test_script_root} + "/script.lua";

  auto error_code = ode::lua::load_script_file(state.get(), filename1.c_str());

  REQUIRE(0 == error_code);

  const std::string filename2 = 
      std::string{ode::test_script_root} + "/not_script.lua";

  error_code = ode::lua::load_script_file(state.get(), filename2.c_str());

  REQUIRE_FALSE(0 == error_code);
}

BENCHMARK(ode, lua_load_script_file, 10, 1000)
{
  const std::string filename = 
      std::string{ode::test_script_root} + "/script.lua";

  ode::lua::load_script_file(ode::test::lua_state_script, filename.c_str());
}
