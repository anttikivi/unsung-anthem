//===------------------------- universal_scene.h ----------------*- C++ -*-===//
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
/// \file universal_scene.h
/// \brief Declaration of universal scene of Obliging Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_UNIVERSAL_SCENE_H
#define ODE_UNIVERSAL_SCENE_H

#include <vector>

namespace ode
{
  class scene_t;
  class system_t;
} // namespace ode

namespace ode
{
  ///
  /// \brief Type of objects which hold the functional system scenes of
  /// Obliging Ode.
  ///
  class universal_scene final
  {
  public:
    ///
    /// \brief The type of references to the scene objects.
    /// 
    using scene_reference = scene_t&;

    ///
    /// \brief Constructs an object of type \c universal_scene.
    ///
    universal_scene();

    ///
    /// \brief Constructs an object of type \c universal_scene by copying the
    /// given object of type \c universal_scene.
    ///
    /// \param a \c universal_scene from which the new one is constructed.
    ///
    universal_scene(const universal_scene& a) = default;

    ///
    /// \brief Constructs an object of type \c universal_scene by moving the
    /// given object of type \c universal_scene.
    ///
    /// \param a \c universal_scene from which the new one is constructed.
    ///
    universal_scene(universal_scene&& a) = default;

    ///
    /// \brief Destructs an object of type \c universal_scene.
    ///
    ~universal_scene() = default;

    ///
    /// \brief Assigns the given object of type \c universal_scene to this one
    /// by copying.
    ///
    /// \param a \c universal_scene from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    universal_scene& operator=(const universal_scene& a) = default;

    ///
    /// \brief Assigns the given object of type \c universal_scene to this one
    /// by moving.
    ///
    /// \param a \c universal_scene from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    universal_scene& operator=(universal_scene&& a) = default;

    ///
    /// \brief Extends the universal scene with the functionalities of the
    /// given system.
    ///
    /// \param sys system with which the universal scene is extended.
    ///
    /// \return reference to the created object of type \c scene_t.
    ///
    scene_reference extend(const system_t& sys);

  private:
    ///
    /// \brief Scenes which implement the different functionalities of systems.
    ///
    std::vector<scene_t> scenes;
  };
} // namespace ode

#endif // !ODE_UNIVERSAL_SCENE_H
