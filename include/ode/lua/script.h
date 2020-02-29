//===------------------------------ script.h --------------------*- C++ -*-===//
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
/// \file script.h
/// \brief The declarations of the utilities for Lua scripts.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LUA_SCRIPT_H
#define ODE_LUA_SCRIPT_H

#include <string_view>

#include "ode/__config"
#include "ode/lua/state_t.h"

namespace ode::lua
{
  ///
  /// \brief Loads a Lua script from the given file.
  ///
  /// \param state the Lua state.
  /// \param filename the name of the file.
  ///
  /// \return The error code which the Lua API gives.
  ///
  int load_script_file(
      const state_ptr_t state,
      std::string_view filename) ODE_CONTRACT_NOEXCEPT;

} // namespace ode::lua

#endif // !ODE_LUA_SCRIPT_H
