/// The declarations of the type of objects which contain parsed command line
/// arguments.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_ARGUMENTS_H
#define ODE_CLI_ARGUMENTS_H

#include <unordered_map>
#include <unordered_set>

#include "ode/cli/option.h"

namespace ode::cli
{
  ///
  /// The type of objects which contain the values of the parsed command line
  /// arguments.
  ///
  /// The objects of this type have separate containers for command line
  /// options and positional command line arguments.
  ///
  struct arguments final
  {
    ///
    /// An object of the type \c std::unordered_map containing key-value pairs
    /// where the key is the name of a command line option and the value is its
    /// parsed value.
    ///
    const std::unordered_map<std::string, option::value_t> option_values;

    ///
    /// An object of the type \c std::unordered_map containing key-value pairs
    /// where the key is the of a command line option that couldn’t be parsed
    /// and the value is a string describing why the parsing failed.
    ///
    const std::unordered_map<std::string, std::string> failed_options;

    ///
    /// An object of the type \c std::unordered_set containing the names of the
    /// options that were required but weren’t given.
    ///
    const std::unordered_set<std::string> missing_options;

    ///
    /// An object of the type \c std::unordered_set containing the names of the
    /// options that were given on the command line but weren’t specified as
    /// valid arguments or options.
    ///
    const std::unordered_set<std::string> unknown_arguments;
  };

  ///
  /// Compares two objects of the type \c arguments.
  ///
  /// \param lhs the left-hand side object of the operator.
  /// \param rhs the right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  inline bool operator==(const arguments& lhs, const arguments& rhs) noexcept
  {
    return lhs.option_values == rhs.option_values &&
        lhs.missing_options == rhs.missing_options &&
        lhs.unknown_arguments == rhs.unknown_arguments;
  }

  ///
  /// Compares two objects of the type \c arguments.
  ///
  /// \param lhs the left-hand side object of the operator.
  /// \param rhs the right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are not equal,
  /// otherwise \c false.
  ///
  inline bool operator!=(const arguments& lhs, const arguments& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  ///
  /// Merges the data in two objects of the type \c arguments and returns a new
  /// object of the same type containing the merged data.
  ///
  /// If the data in the two given object contain same keys, the value from the
  /// second one is used.
  ///
  /// \param a an object of the type \c argument to merge.
  /// \param b an object of the type \c argument to merge.
  ///
  /// \return A new object of the type \c arguments.
  ///
  arguments merge(const arguments& a, const arguments& b);

} // namespace ode::cli

#endif // !ODE_CLI_ARGUMENTS_H
