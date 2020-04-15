/// The declaration of the type of the scene configuration wrappers.
/// \file
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_SCENE_CONFIGURATION_T_H
#define ODE_SYSTEMS_SCENE_CONFIGURATION_T_H

#include <memory>
#include <utility>

#include "ode/systems/scene_configuration.h"

namespace ode
{
  ///
  /// The type of the objects which hold the scene configuration object
  /// implementations.
  ///
  class scene_configuration_t final
  {
  public:
    ///
    /// Constructs an object of the type \c scene_configuration_t.
    ///
    scene_configuration_t() = default;

    ///
    /// Constructs an object of the type \c scene_configuration_t.
    ///
    /// \tparam T the type of the configuration implementation.
    ///
    /// \param t the configuration implementation.
    ///
    template <typename T> scene_configuration_t(T t)
        : config_ptr{std::make_shared<T>(std::move(t))}
    {
    }

    ///
    /// Constructs an object of the type \c scene_configuration_t by copying
    /// the given object of the type \c scene_configuration_t.
    ///
    /// \param a a \c scene_configuration_t from which the new one is
    /// constructed.
    ///
    scene_configuration_t(const scene_configuration_t& a) = default;

    ///
    /// Constructs an object of the type \c scene_configuration_t by moving the
    /// given object of the type \c scene_configuration_t.
    ///
    /// \param a a \c scene_configuration_t from which the new one is
    /// constructed.
    ///
    scene_configuration_t(scene_configuration_t&& a) = default;

    ///
    /// Destructs an object of the type \c scene_configuration_t.
    ///
    ~scene_configuration_t() = default;

    ///
    /// Assigns the given object of the type \c scene_configuration_t to this
    /// one by copying.
    ///
    /// \param a a \c scene_configuration_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_configuration_t& operator=(const scene_configuration_t& a) = default;

    ///
    /// Assigns the given object of the type \c scene_configuration_t to this
    /// one by moving.
    ///
    /// \param a a \c scene_configuration_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_configuration_t& operator=(scene_configuration_t&& a) = default;

  private:
    ///
    /// A pointer to the contained configuration implementation.
    ///
    std::shared_ptr<const scene_configuration> config_ptr;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SCENE_CONFIGURATION_T_H
