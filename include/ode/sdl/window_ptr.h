//===---------------------------- window_ptr.h ------------------*- C++ -*-===//
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
/// \file window_ptr.h
/// \brief Declarations of the window types for Simple DirectMedia Layer.
/// \author Antti Kivi
/// \date 3 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_WINDOW_PTR_H
#define ODE_SDL_WINDOW_PTR_H

#include <memory>

#include <SDL2/SDL.h>

namespace ode::sdl
{
  ///
  /// \brief The type of the pointer to the window object.
  ///
  using window_ptr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

} // namespace ode::sdl

#endif // !ODE_SDL_WINDOW_PTR_H
