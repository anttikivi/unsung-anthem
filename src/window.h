//===-------------------------- window.h ------------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file window.h
/// \brief The declaration of the window-related functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_WINDOW_H
#define ANTHEM_WINDOW_H

#include <memory>

#include <SDL2/SDL.h>

namespace anthem
{
  struct arguments;
}

namespace anthem
{
  ///
  /// \brief The type of the pointer to the window object.
  ///
  using window_ptr = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

  ///
  /// \brief Initializes a new Simple DirectMedia Layer window with OpenGL
  /// context.
  ///
  /// \param args the parsed command line arguments.
  ///
  /// \return Pointer to the created object of type \c GLFWwindow.
  ///
  window_ptr create_window(const arguments& args);

} // namespace anthem

#endif // !ANTHEM_WINDOW_H
