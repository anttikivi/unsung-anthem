//===----------------------------- set_up.cpp -------------------*- C++ -*-===//
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
/// \file set_up.cpp
/// \brief Definition of the common set up function of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/set_up.h"

#include "ode/logger.h"

#include "ode/config.h"
#include "ode/logging_config.h"

#include "ode/common/lua_state.h"

#include <spdlog/sinks/null_sink.h>

namespace ode
{
  namespace test
  {
    void set_up()
    {
      auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();

      ode::logger = ode::create_logger(
          "ode_test_logger",
          ode::logger_pattern,
          ode::logger_level,
          null_sink);

      lua_state_script = luaL_newstate();
      lua_state_stack = luaL_newstate();

      const std::string filename_stack = 
          std::string{ode::test_script_root} + "/stack.lua";

      luaL_loadfile(lua_state_stack, filename_stack.c_str());
      lua_pcall(lua_state_stack, 0, 0, 0);
    }
  } // namespace test
} // namespace ode
