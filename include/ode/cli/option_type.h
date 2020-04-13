/// The declarations of the command line option type utilities.
/// \file
/// \author Antti Kivi
/// \date 5 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_OPTION_TYPE_H
#define ODE_CLI_OPTION_TYPE_H

#include <iostream>

#include "ode/__config"

namespace ode::cli
{
  ///
  /// An enumeration type, the enumerators of which represent the possible
  /// command line option types.
  ///
  /// TODO: Add support for list options, i.e. options that take multiple
  /// values.
  ///
  enum class option_type : ODE_OPTION_TYPE_ENUM_TYPE
  {
    null,
    boolean,
    integer,
    floating_point,
    string
  };

  ///
  /// Inserts an enumerator of the type \c option_type to the \c std::ostream.
  ///
  /// \param os the stream to which the data is inserted.
  /// \param a the enumerator which is inserted.
  ///
  /// \return A reference of the \c std::ostream.
  ///
  std::ostream& operator<<(std::ostream& os, const option_type& a);
} // namespace ode::cli

#endif // !ODE_CLI_OPTION_TYPE_H
