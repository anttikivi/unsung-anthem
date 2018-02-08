//===----------------------------- script.cpp -------------------*- C++ -*-===//
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
/// \file script.cpp
/// \brief The definitions of the utilities for Lua scripts.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/script.h"

#include "ode/logger.h"

#include <lua.hpp>

namespace ode
{
  namespace lua
  {
    int load_script_file(
        gsl::not_null<lua_State*> state,
        const std::string& filename) noexcept
    {
      const auto load_error = luaL_loadfile(state, filename.c_str());

      if (0 != load_error)
      {
        ODE_ERROR(
            "Failed to load the Lua script: {}, error code: {}",
            filename,
            load_error);
      }

      ODE_TRACE(
          "The script '{}' is loaded with code {}",
          filename,
          load_error);

      const auto call_error = lua_pcall(state, 0, 0, 0);

      ODE_TRACE("The script '{}' is called with code {}",
          filename,
          call_error);

      return load_error;
    }

    namespace test
    {
      int load_script_file_no_log(
          gsl::not_null<lua_State*> state,
          const std::string& filename) noexcept
      {
        const auto load_error = luaL_loadfile(state, filename.c_str());

        if (0 != load_error)
        {
          ODE_ERROR(
              "Failed to load the Lua script: {}, error code: {}",
              filename,
              load_error);
        }

        const auto call_error = lua_pcall(state, 0, 0, 0);

        return load_error;
      }
    } // namespace test
  } // namespace lua
} // namespace ode
