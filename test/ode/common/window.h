//===------------------------------ window.h --------------------*- C++ -*-===//
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
/// \file window.h
/// \brief The declarations of the window for the tests.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_TEST_COMMON_WINDOW_H
#define ODE_TEST_COMMON_WINDOW_H

#include <SDL2/SDL.h>

namespace ode::test
{
  ///
  /// \brief The common window of the tests.
  ///
  inline SDL_Window* test_window = nullptr;

  ///
  /// \brief The common OpenGL context of the tests.
  ///
  inline SDL_GLContext test_gl_context = nullptr;

} // namespace ode::test

#endif // !ODE_TEST_COMMON_WINDOW_H
