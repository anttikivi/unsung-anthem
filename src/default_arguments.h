//===--------------------- default_arguments.h ------------------*- C++ -*-===//
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
/// \file default_arguments.h
/// \brief The declarations of the default values of the command line
/// arguments.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/types.h"

namespace anthem
{
  ///
  /// \brief The default width of the window in pixels.
  ///
  constexpr pixel_count default_window_width = 120_px;

  ///
  /// \brief The default height of the window in pixels.
  ///
  constexpr pixel_count default_window_height = 120_px;

  ///
  /// \brief The default name of the window.
  ///
  constexpr auto default_window_name = ANTHEM_WINDOW_NAME;
} // namespace anthem
