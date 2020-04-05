/// The declarations of the system type utilities.
/// \file
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_SYSTEM_TYPE_H
#define ODE_SYSTEMS_SYSTEM_TYPE_H

#include <array>
#include <iostream>

#include "ode/__config"

namespace ode
{
  ///
  /// An enumeration type, the enumerators of which represent the possible
  /// system types.
  ///
  /// The system types other than ‘other’ are used for the systems which have
  /// special, engine-defined responsibilities. For systems which are
  /// application-specific and should run in accord with the basic schedule,
  /// the system type ‘other’ should be used.
  ///
  enum class system_type : ODE_SYSTEM_TYPE_ENUM_TYPE
  {
    graphics,
    input,
    other
  };

  ///
  /// Inserts an enumerator of the type \c system_type to the \c std::ostream.
  ///
  /// \param os the stream to which the data is inserted.
  /// \param a the enumerator which is inserted.
  ///
  /// \return A reference of the \c std::ostream.
  ///
  std::ostream& operator<<(std::ostream& os, const system_type& a);

  ///
  /// Gives an array containing all of the systems types for iterating over
  /// them.
  ///
  /// \return An object of the type \c std::array.
  ///
  constexpr std::array<system_type, 3> system_types() noexcept
  {
    return {system_type::graphics, system_type::input, system_type::other};
  }

} // namespace ode

#endif // !ODE_SYSTEMS_SYSTEM_TYPE_H
