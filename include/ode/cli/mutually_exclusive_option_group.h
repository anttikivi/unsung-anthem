/// The declaration of the type of objects that contain information about
/// groups of command line options where the options are mutually exclusive.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_MUTUALLY_EXCLUSIVE_OPTION_GROUP_H
#define ODE_CLI_MUTUALLY_EXCLUSIVE_OPTION_GROUP_H

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
    mutually_exclusive_option_group();

    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group.
    ///
    /// The constructed group object doesn’t contain a name nor a description.
    ///
    /// \param opts the options which will be contained by this group.
    ///
    mutually_exclusive_option_group(std::vector<option>&& opts);

    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group.
    ///
    /// \param n the name of the group.
    /// \param opts the options which will be contained by this group.
    ///
    mutually_exclusive_option_group(
        const std::string& n, std::vector<option>&& opts);

    ///
    /// Constructs an object of the type \c mutually_exclusive_option_group.
    ///
    /// \param n the name of the group.
    /// \param d the description of the group.
    /// \param opts the options which will be contained by this group.
    ///
    mutually_exclusive_option_group(
        const std::string& n, const std::string& d, std::vector<option>&& opts);

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
  };

} // namespace ode::cli

#endif // !ODE_CLI_MUTUALLY_EXCLUSIVE_OPTION_GROUP_H
