/// The declaration of the framework object.
/// \file
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_FRAMEWORK_FRAMEWORK_OBJECT_H
#define ODE_FRAMEWORK_FRAMEWORK_OBJECT_H

#include <vector>

#include "ode/systems/object_t.h"

namespace ode
{
  ///
  /// The type of the objects which hold the functional system objects.
  ///
  class framework_object final
  {
  public:
    ///
    /// Constructs an object of the type \c framework_object.
    ///
    framework_object() = default;

    ///
    /// Constructs an object of the type \c framework_object by copying the
    /// given object of the type \c framework_object.
    ///
    /// \param a a \c framework_object from which the new one is constructed.
    ///
    framework_object(const framework_object& a) = default;

    ///
    /// Constructs an object of the type \c framework_object by moving the
    /// given object of the type \c framework_object.
    ///
    /// \param a a \c framework_object from which the new one is constructed.
    ///
    framework_object(framework_object&& a) = default;

    ///
    /// Destructs an object of the type \c framework_object.
    ///
    ~framework_object() = default;

    ///
    /// Assigns the given object of the type \c framework_object to this one by
    /// copying.
    ///
    /// \param a a \c framework_object from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    framework_object& operator=(const framework_object& a) = default;

    ///
    /// Assigns the given object of the type \c framework_object to this one by
    /// moving.
    ///
    /// \param a a \c framework_object from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    framework_object& operator=(framework_object&& a) = default;

  private:
    ///
    /// The objects which implement the different functionalities of the
    /// systems.
    ///
    std::vector<object_t> objects;
  };
} // namespace ode

#endif // !ODE_FRAMEWORK_FRAMEWORK_OBJECT_H
