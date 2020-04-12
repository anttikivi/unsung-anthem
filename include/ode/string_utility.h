/// The declarations of general string-related utilities.
/// \file
/// \author Antti Kivi
/// \date 12 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_STRING_UTILITY_H
#define ODE_STRING_UTILITY_H

#include <string>

namespace ode
{
  ///
  /// Checks if the given object of the type \c std::string contains only
  /// characters that are decimal digits.
  ///
  /// Currently only decimal integers are supported.
  ///
  /// \param str the string to classify.
  ///
  /// \return \c true if the string contains a valid integer, otherwise
  /// \c false.
  ///
  bool is_integer(const std::string& str);

  ///
  /// Removes the leading and trailing whitespace characters from a string.
  ///
  /// The whitespace characters are identified by calling \c std::isspace.
  ///
  /// \param str the object of the type \c std::string to process.
  ///
  /// \return A copy of the string with whitespace characters removed.
  ///
  std::string trim(const std::string& str);

  ///
  /// Interprets a Boolean value in an object of the type \c std::string.
  ///
  /// Discards any whitespace characters as identified by calling
  /// \c std::isspace.
  ///
  /// \param str the object of the type \c std::string to convert.
  ///
  /// \return A \c bool value corresponding to the content of the string.
  ///
  /// \exception std::invalid_argument if no conversion could be performed.
  ///
  bool stob(const std::string& str);

} // namespace ode

#endif // !ODE_STRING_UTILITY_H
