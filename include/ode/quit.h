//===------------------------------- quit.h ---------------------*- C++ -*-===//
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
/// \file quit.h
/// \brief Declarations of quitting functions of Obliging Ode.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_QUIT_H
#define ODE_QUIT_H

#include <SDL2/SDL.h>

namespace ode
{
  ///
  /// \brief Destructs the graphics context of Obliging Ode.
  ///
  /// \param context the graphics context.
  ///
  template <typename T> void quit_graphics(T context)
  {
    SDL_GL_DeleteContext(context);
  }

} // namespace ode

#endif // !ODE_QUIT_H
