//===--------------------------- input_scene.h ------------------*- C++ -*-===//
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
/// \file input_scene.h
/// \brief Declaration of type of input system scene of Unsung Anthem.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_INPUT_SCENE_H
#define ANTHEM_INPUT_SCENE_H

#include "ode/scene.h"

namespace anthem
{
  ///
  /// \brief Type of input system scene objects.
  ///
  struct input_scene final : public ode::scene
  {
    ///
    /// \brief Destructs an object of type \c input_scene.
    ///
    ~input_scene() = default;
  };

} // namespace anthem

#endif // !ANTHEM_INPUT_SCENE_H
