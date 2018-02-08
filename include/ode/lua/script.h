//===------------------------------ script.h --------------------*- C++ -*-===//
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
/// \file script.h
/// \brief The declarations of the utilities for Lua scripts.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_SCRIPT_H
#define ODE_LUA_SCRIPT_H

#include <string>

#include "gsl/view"

struct lua_State;

namespace ode
{
  namespace lua
  {
    ///
    /// \brief Loads a Lua script from the given file.
    ///
    /// \param state pointer to the Lua state.
    /// \param filename the name of the file.
    ///
    /// \return The error code which the Lua API gives.
    ///
    int load_script_file(
        gsl::not_null<lua_State*> state,
        const std::string& filename) noexcept;

    namespace test
    {
      int load_script_file_no_log(
          gsl::not_null<lua_State*> state,
          const std::string& filename) noexcept;
    } // namespace test
  } // namespace lua
} // namespace ode

#endif // !ODE_LUA_SCRIPT_H
