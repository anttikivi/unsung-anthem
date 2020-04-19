/// The declaration of the type of objects that contain information about
/// groups of command line options where the options are mutually exclusive.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_MUTUALLY_EXCLUSIVE_OPTION_GROUP_H
#define ODE_CLI_MUTUALLY_EXCLUSIVE_OPTION_GROUP_H

#include <unordered_set>

#include "ode/cli/option.h"
#include "ode/cli/option_group.h"

namespace ode::cli
{
  ///
  /// The type of objects which contain information about a group of command
  /// line options where the options are mutually exclusive.
  ///
  class mutually_exclusive_option_group : public option_group
  {
  public:
    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group.
    ///
    /// Remarks: This constructor is the default constructor and the resulting
    /// object contains only empty values.
    ///
    mutually_exclusive_option_group() = default;

    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group.
    ///
    /// \param name the name of the group.
    /// \param description the description of the group.
    /// \param options the options which will be contained by this group.
    ///
    mutually_exclusive_option_group(
        const std::string& name,
        const std::string& description,
        std::unordered_set<option>&& options);

    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group.
    ///
    /// \param name the name of the group.
    /// \param options the options which will be contained by this group.
    ///
    mutually_exclusive_option_group(
        const std::string& name, std::unordered_set<option>&& options);

    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group.
    ///
    /// The constructed group object doesn’t contain a name nor a description.
    ///
    /// \param options the options which will be contained by this group.
    ///
    mutually_exclusive_option_group(std::unordered_set<option>&& options);

    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group by
    /// copying the given object of the type \c mutually_exclusive_option_group.
    ///
    /// \param a a \c mutually_exclusive_option_group from which the new one is
    /// constructed.
    ///
    mutually_exclusive_option_group(const mutually_exclusive_option_group& a) =
        default;

    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group by
    /// moving the given object of the type \c mutually_exclusive_option_group.
    ///
    /// \param a a \c mutually_exclusive_option_group from which the new one is
    /// constructed.
    ///
    mutually_exclusive_option_group(mutually_exclusive_option_group&& a) =
        default;

    ///
    /// Destructs an object of the type \c mutually_exclusive_option_group.
    ///
    ~mutually_exclusive_option_group() = default;

    ///
    /// Assigns the given object of the type \c mutually_exclusive_option_group
    /// to this one by copying.
    ///
    /// \param a a \c mutually_exclusive_option_group from which this one is
    /// assigned.
    ///
    /// \return A reference to \c *this.
    ///
    mutually_exclusive_option_group& operator=(
        const mutually_exclusive_option_group& a) = delete;

    ///
    /// Assigns the given object of the type \c mutually_exclusive_option_group
    /// to this one by moving.
    ///
    /// \param a a \c mutually_exclusive_option_group from which this one is
    /// assigned.
    ///
    /// \return A reference to \c *this.
    ///
    mutually_exclusive_option_group& operator=(
        mutually_exclusive_option_group&& a) = delete;

    ///
    /// Parses the options of this group from the given command line arguments.
    ///
    /// \param argc the number of arguments passed in the execution.
    /// \param argv the array containing the arguments passed in the execution.
    ///
    /// \return An object of the type \c std::optional which contains an object
    /// of the type \c arguments if the parsing is successful.
    ///
    arguments parse_group(const int argc, ode::argv_t argv[]) const;

    ///
    /// Creates an object of the type \c std::string containing a formatted
    /// string of the name, description, and options of this group.
    ///
    /// \return An object of the type \c std::string.
    ///
    std::string format_help() const;

  private:
    ///
    /// The command line options of this group.
    ///
    const std::unordered_set<option> options;

    ///
    /// The name of the group.
    ///
    /// If no name is provided, the options in the group are added to the list
    /// of root-level options.
    ///
    const std::optional<std::string> name;

    ///
    /// The description of the group.
    ///
    const std::optional<std::string> description;
  };

} // namespace ode::cli

#endif // !ODE_CLI_MUTUALLY_EXCLUSIVE_OPTION_GROUP_H
