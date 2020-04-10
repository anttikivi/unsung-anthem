/// The declaration of the type of objects that contain information about one
/// command line option.
/// \file
/// \author Antti Kivi
/// \date 19 March 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_OPTION_H
#define ODE_CLI_OPTION_H

#include <string>
#include <variant>

#include "ode/cli/option_type.h"

namespace ode::cli
{
  ///
  /// The string which is prefixed to the long names of the options.
  ///
#if _WIN32
  constexpr auto option_prefix = "/";
#else
  constexpr auto option_prefix = "--";
#endif // !_WIN32

  ///
  /// The string which is prefixed to the short names of the options.
  ///
#if _WIN32
  constexpr auto short_option_prefix = "/";
#else
  constexpr auto short_option_prefix = "-";
#endif // !_WIN32

  ///
  /// The string which is used to separate the option from its value if a space
  /// isn’t used to do so.
  ///
#if _WIN32
  constexpr auto value_separator = ":";
#else
  constexpr auto value_separator = "=";
#endif // !_WIN32

  ///
  /// The type of objects which contain information about one command line
  /// option for the command line parser.
  ///
  class option final
  {
  public:
    ///
    /// The type of the command line option values.
    ///
    using value_t = std::variant<bool, int, float, std::string>;

    ///
    /// Constructs an object of the type \c option.
    ///
    option() = default;

    ///
    /// Constructs an object of the type \c option.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param type an enumerable value representing type of the values which
    /// this command line option accepts.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const option_type type,
        const value_t& default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a Boolean
    /// value.
    ///
    /// The command line options accepting Boolean values don’t necessarily
    /// need any explicit value. A useful rule of thumb of their functionality
    /// is that when they’re specifed, the value is the opposite of the default
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const bool default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts an integer
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const int default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a single
    /// precision floating point value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const float default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option which accepts a string
    /// value.
    ///
    /// \param name the long name of the command line option.
    /// \param short_name the short, one-character name of the command line
    /// option.
    /// \param default_v the default value of the command line option.
    /// \param r whether or not this option is required.
    ///
    option(
        const std::string& name,
        const std::string& short_name,
        const std::string& default_v,
        const bool r);

    ///
    /// Constructs an object of the type \c option by copying the given object
    /// of the type \c option.
    ///
    /// \param a an \c option from which the new one is constructed.
    ///
    option(const option& a) = default;

    ///
    /// Constructs an object of the type \c option by moving the given object
    /// of the type \c option.
    ///
    /// \param a an \c option from which the new one is constructed.
    ///
    option(option&& a) = default;

    ///
    /// Destructs an object of the type \c option.
    ///
    ~option() = default;

    ///
    /// Assigns the given object of the type \c option to this one by copying.
    ///
    /// \param a an \c option from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option& operator=(const option& a) = default;

    ///
    /// Assigns the given object of the type \c option to this one by moving.
    ///
    /// \param a an \c option from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option& operator=(option&& a) = default;

    ///
    /// Gives the long name of this command line option.
    ///
    /// \return An object of the type \c std::string.
    ///
    std::string name() const;

    ///
    /// Gives the short, one-character name of this command line option.
    ///
    /// \return An object of the type \c std::string.
    ///
    std::string short_name() const;

    ///
    /// Gives an enumerable value representing the type of the values this
    /// command line option accepts.
    ///
    /// \return A value of the enumerable type \c option_type.
    ///
    option_type type() const;

    ///
    /// Gives the default value of the command line option.
    ///
    /// \return An object of the type \c value_t.
    ///
    value_t default_value() const;

    ///
    /// Gives a Boolean value telling whether or not this command line option is required.
    ///
    /// An option group may ignore the value of this Boolean if the group is
    /// for example mutually exclusive.
    ///
    /// \return A value of the type \c bool.
    ///
    bool required() const;

  private:
    ///
    /// The long name of the command line option.
    ///
    const std::string n;

    ///
    /// The short, one-character name of the command line option.
    ///
    const std::string short_n;

    ///
    /// The enumerable value representing the type of the values this command
    /// line option accepts.
    ///
    const option_type t;

    ///
    /// The default value of the command line option.
    ///
    const value_t default_v;

    ///
    /// Whether or not this option is required.
    ///
    /// An option group may ignore the value of this Boolean if the group is
    /// for example mutually exclusive.
    ///
    const bool req;
  };

} // namespace ode::cli

#endif // !ODE_CLI_OPTION_H
