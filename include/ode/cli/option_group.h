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
#include <vector>

#include "ode/argv_t.h"
#include "ode/cli/option.h"

namespace ode::cli
{
  struct arguments;
}

namespace ode::cli
{
  ///
  /// The base type of objects which contain information about a group of
  /// command line options for the command line parser.
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
    option_group();

    ///
    /// Constructs an object of the type \c option_group.
    ///
    /// The constructed group object doesn’t contain a name nor a description.
    ///
    /// \param opts the options which will be contained by this group.
    ///
    option_group(std::vector<option>&& opts);

    ///
    /// Constructs an object of the type \c option_group.
    ///
    /// \param n the name of the group.
    /// \param opts the options which will be contained by this group.
    ///
    option_group(const std::string& n, std::vector<option>&& opts);

    ///
    /// Constructs an object of the type \c option_group.
    ///
    /// \param n the name of the group.
    /// \param d the description of the group.
    /// \param opts the options which will be contained by this group.
    ///
    option_group(
        const std::string& n,
        const std::string& d,
        std::vector<option>&& opts);

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
    option_group& operator=(const option_group& a) = default;

    ///
    /// Assigns the given object of the type \c option_group to this one by
    /// moving.
    ///
    /// \param a an \c option_group from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option_group& operator=(option_group&& a) = default;

    ///
    /// Parses the options of this group from the given command line arguments.
    ///
    /// \param argc the number of arguments passed in the execution.
    /// \param argv the array containing the arguments passed in the execution.
    ///
    /// \return An object of the type \c std::optional which contains an object
    /// of the type \c arguments if the parsing is successful.
    ///
    virtual std::optional<arguments> parse_group(
        const int argc,
        ode::argv_t argv[]) const = 0;

    ///
    /// Gives the options contained by this group.
    ///
    /// \return An object of the type \c std::vector which holds the contained
    /// \c option objects.
    ///
    virtual std::vector<option> options() const;

    ///
    /// Gives the name of this group.
    ///
    /// \return An object of the type \c std::optional which contains an object
    /// of the type \c std::string if the group has a name.
    ///
    virtual std::optional<std::string> name() const;

    ///
    /// Gives the description of this group.
    ///
    /// \return An object of the type \c std::optional which contains an object
    /// of the type \c std::string if the group has a description.
    ///
    virtual std::optional<std::string> description() const;

  private:
    ///
    /// The command line options of this group.
    ///
    const std::vector<option> opts;

    ///
    /// The name of the group.
    ///
    /// If no name is provided, the options in the group are added to the list
    /// of root-level options.
    ///
    const std::optional<std::string> n;

    ///
    /// The description of the group.
    ///
    const std::optional<std::string> desc;
  };

} // namespace ode::cli

#endif // !ODE_CLI_OPTION_GROUP_H
