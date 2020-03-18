//===-------------------------- initialize_sdl.h ----------------*- C++ -*-===//
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
/// \file initialize_sdl.h
/// \brief The declaration of the initialization utility function for Simple
/// DirectMedia Layer.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_INITIALIZE_SDL_H
#define ODE_SDL_INITIALIZE_SDL_H

namespace ode::sdl
{
  ///
  /// \brief Initializes Simple DirectMedia Layer.
  ///
  /// Remarks: This function is impure.
  ///
  void initialize();

} // namespace ode::sdl

#endif // !ODE_SDL_INITIALIZE_SDL_H
