/// The declarations of the window for the tests.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_TEST_COMMON_WINDOW_H
#define ODE_TEST_COMMON_WINDOW_H

#include <SDL2/SDL.h>

namespace ode::test
{
  ///
  /// The common window of the tests.
  ///
  inline SDL_Window* test_window = nullptr;

  ///
  /// The common OpenGL context of the tests.
  ///
  inline SDL_GLContext test_gl_context = nullptr;

} // namespace ode::test

#endif // !ODE_TEST_COMMON_WINDOW_H
