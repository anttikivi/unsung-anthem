/// The declaration of the type of objects that contain information about
/// groups of command line options where none of the options are exclusive.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_INCLUSIVE_OPTION_GROUP_H
#define ODE_CLI_INCLUSIVE_OPTION_GROUP_H

#include "ode/cli/option_group.h"

namespace ode::cli
{
  ///
  /// The type of objects which contain information about a group of command
  /// line options where none of the options are exclusive.
  ///
  class inclusive_option_group : public option_group
  {
  public:
    ///
    /// Constructs an object of the type \c inclusive_option_group.
    ///
    /// Remarks: This constructor is the default constructor and the resulting
    /// object contains only empty values.
    ///
    inclusive_option_group();

    ///
    /// Constructs an object of the type \c inclusive_option_group.
    ///
    /// The constructed group object doesn’t contain a name nor a description.
    ///
    /// \param opts the options which will be contained by this group.
    ///
    inclusive_option_group(std::vector<option>&& opts);

    ///
    /// Constructs an object of the type \c inclusive_option_group.
    ///
    /// \param n the name of the group.
    /// \param opts the options which will be contained by this group.
    ///
    inclusive_option_group(const std::string& n, std::vector<option>&& opts);

    ///
    /// Constructs an object of the type \c inclusive_option_group.
    ///
    /// \param n the name of the group.
    /// \param d the description of the group.
    /// \param opts the options which will be contained by this group.
    ///
    inclusive_option_group(
        const std::string& n,
        const std::string& d,
        std::vector<option>&& opts);

    ///
    /// Constructs an object of the type \c inclusive_option_group by copying
    /// the given object of the type \c inclusive_option_group.
    ///
    /// \param a an \c inclusive_option_group from which the new one is
    /// constructed.
    ///
    inclusive_option_group(const inclusive_option_group& a) = default;

    ///
    /// Constructs an object of the type \c inclusive_option_group by moving
    /// the given object of the type \c inclusive_option_group.
    ///
    /// \param a an \c inclusive_option_group from which the new one is
    /// constructed.
    ///
    inclusive_option_group(inclusive_option_group&& a) = default;

    ///
    /// Destructs an object of the type \c inclusive_option_group.
    ///
    ~inclusive_option_group() = default;

    ///
    /// Assigns the given object of the type \c inclusive_option_group to this
    /// one by copying.
    ///
    /// \param a an \c inclusive_option_group from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    inclusive_option_group& operator=(const inclusive_option_group& a)
        = delete;

    ///
    /// Assigns the given object of the type \c inclusive_option_group to this
    /// one by moving.
    ///
    /// \param a an \c inclusive_option_group from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    inclusive_option_group& operator=(inclusive_option_group&& a) = delete;

    ///
    /// Parses the options of this group from the given command line arguments.
    ///
    /// \param argc the number of arguments passed in the execution.
    /// \param argv the array containing the arguments passed in the execution.
    ///
    /// \return An object of the type \c std::optional which contains an object
    /// of the type \c arguments if the parsing is successful.
    ///
    std::optional<arguments> parse_group(
        const int argc,
        ode::argv_t argv[]) const;
  };

} // namespace ode::cli

#endif // !ODE_CLI_INCLUSIVE_OPTION_GROUP_H
