//===---------------------------- clean_up.cpp ------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file clean_up.cpp
/// \brief The definitions of the common cleanup functions of the tests.
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

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
