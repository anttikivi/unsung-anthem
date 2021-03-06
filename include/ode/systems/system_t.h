/// The declarations of the type templates of system objects.
/// \file
/// \author Antti Kivi
/// \date 17 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_SYSTEM_T_H
#define ODE_SYSTEMS_SYSTEM_T_H

#include <memory>
#include <utility>

#include "ode/systems/system.h"

namespace ode
{
  ///
  /// The type of the objects which are the functional systems.
  ///
  class system_t final
  {
  public:
    ///
    /// Constructs an object of the type \c system_t.
    ///
    system_t() = default;

    ///
    /// Constructs an object of the type \c system_t.
    ///
    /// \tparam T the type of the system implementation.
    ///
    /// \param t the system implementation.
    ///
    template <typename T> system_t(T t)
        : sys_ptr{std::make_unique<T>(std::move(t))}
    {
    }

    ///
    /// Constructs an object of the type \c system_t by copying the given
    /// object of the type \c system_t.
    ///
    /// \param a \c system_t from which the new one is constructed.
    ///
    system_t(const system_t& a) = delete;

    ///
    /// Constructs an object of the type \c system_t by moving the given object
    /// of the type \c system_t.
    ///
    /// \param a \c system_t from which the new one is constructed.
    ///
    system_t(system_t&& a) = default;

    ///
    /// Destructs an object of the type \c system_t.
    ///
    ~system_t() = default;

    ///
    /// Assigns the given object of the type \c system_t to this one by
    /// copying.
    ///
    /// \param a \c system_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    system_t& operator=(const system_t& a) = delete;

    ///
    /// Assigns the given object of the type \c system_t to this one by moving.
    ///
    /// \param a \c system_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    system_t& operator=(system_t&& a) = default;

    ///
    /// Creates a scene object implementing the functionalities of this system.
    ///
    /// \param cfg the scene configuration according to which the scene is
    /// constructed.
    ///
    /// \return An object of the type \c scene_t which has the functionality of
    /// this system.
    ///
    scene_t make_scene(const scene_configuration_t& cfg) const;

  private:
    ///
    /// A pointer to the contained system implementation.
    ///
    std::unique_ptr<system> sys_ptr;
  };
} // namespace ode

#endif // !ODE_SYSTEMS_SYSTEM_T_H
