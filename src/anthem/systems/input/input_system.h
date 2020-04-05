/// The declaration of the type of the input system.
/// \file
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ANTHEM_SYSTEMS_INPUT_INPUT_SYSTEM_H
#define ANTHEM_SYSTEMS_INPUT_INPUT_SYSTEM_H

#include "ode/systems/input/input_system.h"

namespace anthem
{
  ///
  /// The type of the input system.
  ///
  class input_system final : public ode::input_system
  {
  public:
    ///
    /// The system type of this system.
    ///
    static constexpr ode::system_type type = ode::system_type::input;

    ///
    /// Constructs an object of the type \c input_system.
    ///
    input_system() = default;

    ///
    /// Constructs an object of the type \c input_system by copying the given
    /// object of the type \c input_system.
    ///
    /// \param a a \c input_system from which the new one is constructed.
    ///
    input_system(const input_system& a) = delete;

    ///
    /// Constructs an object of the type \c input_system by moving the given
    /// object of the type \c input_system.
    ///
    /// \param a a \c input_system from which the new one is constructed.
    ///
    input_system(input_system&& a) = default;

    ///
    /// Destructs an object of the type \c input_system.
    ///
    ~input_system() = default;

    ///
    /// Assigns the given object of the type \c input_system to this one by
    /// copying.
    ///
    /// \param a a \c input_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    input_system& operator=(const input_system& a) = delete;

    ///
    /// Assigns the given object of the type \c input_system to this one by
    /// moving.
    ///
    /// \param a a \c input_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    input_system& operator=(input_system&& a) = default;

    ///
    /// Creates a scene containing the type \c input_scene.
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
