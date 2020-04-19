/// The declaration of the type of objects that contain information about
/// groups of command line options for parsing command line arguments.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_OPTION_GROUP_H
#define ODE_CLI_OPTION_GROUP_H

#include <optional>
#include <string>

#include "ode/argv_t.h"
#include "ode/cli/arguments.h"

namespace ode::cli
{
  ///
  /// The abstract base type of objects which contain information about a group
  /// of command line options for the command line parser.
  ///
  class option_group
  {
  public:
    ///
    /// Constructs an object of the type \c option_group.
    ///
    /// Remarks: This constructor is the default constructor and the resulting
    /// object contains only empty values.
    ///
    option_group() = default;

    ///
    /// Constructs an object of the type \c option_group by copying the given
    /// object of the type \c option_group.
    ///
    /// \param a an \c option_group from which the new one is constructed.
    ///
    option_group(const option_group& a) = default;

    ///
    /// Constructs an object of the type \c option_group by moving the given
    /// object of the type \c option_group.
    ///
    /// \param a an \c option_group from which the new one is constructed.
    ///
    option_group(option_group&& a) = default;

    ///
    /// Destructs an object of the type \c option_group.
    ///
    virtual ~option_group() = default;

    ///
    /// Assigns the given object of the type \c option_group to this one by
    /// copying.
    ///
    /// \param a an \c option_group from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option_group& operator=(const option_group& a) = delete;

    ///
    /// Assigns the given object of the type \c option_group to this one by
    /// moving.
    ///
    /// \param a an \c option_group from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option_group& operator=(option_group&& a) = delete;

    ///
    /// Parses the options of this group from the given command line arguments.
    ///
    /// \param argc the number of arguments passed in the execution.
    /// \param argv the array containing the arguments passed in the execution.
    ///
    /// \return An object of the type \c std::optional which contains an object
    /// of the type \c arguments if the parsing is successful.
    ///
    virtual arguments parse_group(const int argc, ode::argv_t argv[]) const = 0;

    ///
    /// Creates an object of the type \c std::string containing a formatted
    /// string of the name, description, and options of this group.
    ///
    /// \return An object of the type \c std::string.
    ///
    virtual std::string format_help() const = 0;
  };

} // namespace ode::cli

#endif // !ODE_CLI_OPTION_GROUP_H
