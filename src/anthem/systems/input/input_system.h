//===--------------------------- input_system.h -----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file input_system.h
/// \brief The declaration of the type of the input system.
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_SYSTEMS_INPUT_INPUT_SYSTEM_H
#define ANTHEM_SYSTEMS_INPUT_INPUT_SYSTEM_H

#include "ode/systems/input/input_system.h"

namespace anthem
{
  ///
  /// \class input_system
  /// \brief The type of the input system.
  ///
  class input_system final : public ode::input_system
  {
  public:
    ///
    /// \brief The system type of this system.
    ///
    static constexpr ode::system_type type = ode::system_type::input;

    ///
    /// \brief Constructs an object of the type \c input_system.
    ///
    input_system() = default;

    ///
    /// \brief Constructs an object of the type \c input_system by copying the
    /// given object of the type \c input_system.
    ///
    /// \param a a \c input_system from which the new one is constructed.
    ///
    input_system(const input_system& a) = delete;

    ///
    /// \brief Constructs an object of the type \c input_system by moving the
    /// given object of the type \c input_system.
    ///
    /// \param a a \c input_system from which the new one is constructed.
    ///
    input_system(input_system&& a) = default;

    ///
    /// \brief Destructs an object of the type \c input_system.
    ///
    ~input_system() = default;

    ///
    /// \brief Assigns the given object of the type \c input_system to this one
    /// by copying.
    ///
    /// \param a a \c input_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    input_system& operator=(const input_system& a) = delete;

    ///
    /// \brief Assigns the given object of the type \c input_system to this one
    /// by moving.
    ///
    /// \param a a \c input_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    input_system& operator=(input_system&& a) = default;

    ///
    /// \brief Creates a scene containing the type \c input_scene.
    ///
    /// \param cfg the scene configuration according to which the scene is
    /// constructed.
    ///
    /// \return An object of the type \c scene_t.
    ///
    ode::scene_t make_scene(const ode::scene_configuration_t& cfg) const;
  };

} // namespace anthem

#endif // !ANTHEM_SYSTEMS_INPUT_INPUT_SYSTEM_H
