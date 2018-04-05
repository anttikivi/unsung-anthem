//===----------------------------- window_t.h -------------------*- C++ -*-===//
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
/// \file window_t.h
/// \brief Declarations of window types for Simple DirectMedia Layer.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_WINDOW_T_H
#define ODE_SDL_WINDOW_T_H

#include <memory>

#include <SDL2/SDL.h>

namespace ode::sdl
{
  ///
  /// \brief Type of window objects.
  ///
  using window_t = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

  ///
  /// \brief Pointer type which is used as parameter for passing the raw window
  /// pointer.
  ///
  using window_ptr_t = SDL_Window*;

} // namespace ode::sdl

#endif // !ODE_SDL_WINDOW_T_H
