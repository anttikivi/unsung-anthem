//===--------------------------- input_system.h -----------------*- C++ -*-===//
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
/// \file input_system.h
/// \brief Declaration of type of input system object of Unsung Anthem.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_INPUT_SYSTEM_H
#define ANTHEM_INPUT_SYSTEM_H

#include "ode/system.h"

namespace anthem
{
  ///
  /// \brief Type of input system object of Unsung Anthem.
  ///
  struct input_system final : public ode::system
  {
    ///
    /// \brief Destructs an object of type \c input_system.
    ///
    ~input_system() = default;

    ///
    /// \brief Creates a scene object containing the type \c input_scene.
    ///
    /// \return An object of type \c ode::scene_t.
    ///
    ode::scene_t create_scene() const;
  };

} // namespace anthem

#endif // !ANTHEM_INPUT_SYSTEM_H
