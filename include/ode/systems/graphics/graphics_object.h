/// The declaration of the type of the graphics system objects.
/// \file
/// \author Antti Kivi
/// \date 8 May 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_GRAPHICS_GRAPHICS_OBJECT_H
#define ODE_SYSTEMS_GRAPHICS_GRAPHICS_OBJECT_H

#include "ode/systems/object.h"
#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// The type of the graphics system objects.
  ///
  class graphics_object final : public object
  {
  public:
    ///
    /// The system type of this object.
    ///
    static constexpr system_type type = system_type::graphics;

    ///
    /// Constructs an object of the type \c graphics_object.
    ///
    graphics_object() = default;

    ///
    /// Constructs an object of the type \c graphics_object by copying the
    /// given object of the type \c graphics_object.
    ///
    /// \param a a \c graphics_object from which the new one is constructed.
    ///
    graphics_object(const graphics_object& a) = default;

    ///
    /// Constructs an object of the type \c graphics_object by moving the given
    /// object of the type \c graphics_object.
    ///
    /// \param a a \c graphics_object from which the new one is constructed.
    ///
    graphics_object(graphics_object&& a) = default;

    ///
    /// Destructs an object of the type \c graphics_object.
    ///
    ~graphics_object() = default;

    ///
    /// Assigns the given object of the type \c graphics_object to this one by
    /// copying.
    ///
    /// \param a a \c graphics_object from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_object& operator=(const graphics_object& a) = default;

    ///
    /// Assigns the given object of the type \c graphics_object to this one by
    /// moving.
    ///
    /// \param a a \c graphics_object from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_object& operator=(graphics_object&& a) = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_GRAPHICS_GRAPHICS_OBJECT_H
