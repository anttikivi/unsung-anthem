/// The definitions of the common cleanup functions of the tests.
/// \file
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/common/clean_up.h"

#include "ode/common/window.h"

namespace ode::test
{
  void clean_up()
  {
    SDL_GL_DeleteContext(test_gl_context);
    SDL_DestroyWindow(test_window);
    SDL_Quit();
  }
} // namespace ode::test
