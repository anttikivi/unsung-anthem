//===-------------------------- graphics_scene.h ----------------*- C++ -*-===//
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
/// \file graphics_scene.h
/// \brief The declaration of the type of graphics system scenes.
/// \author Antti Kivi
/// \date 8 May 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_GRAPHICS_SCENE_H
#define ODE_GRAPHICS_SCENE_H

#include "ode/scene.h"
#include "ode/system_type.h"

namespace ode
{
  ///
  /// \brief The type of graphics system scene objects.
  ///
  struct graphics_scene final : public scene
  {
    ///
    /// \brief The system type of this scene.
    ///
    static constexpr system_type type = system_type::graphics;

    ///
    /// \brief Destructs an object of type \c graphics_scene.
    ///
    ~graphics_scene() = default;
  };

} // namespace ode

#endif // !ODE_GRAPHICS_SCENE_H
