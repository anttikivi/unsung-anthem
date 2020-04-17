/// The definition of the type of objects that contain information about one
/// command line option.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/option.h"

#include <cctype>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <sstream>
#include <type_traits>

#include "gsl/assert"

#include "ode/logger.h"
#include "ode/string_utility.h"

namespace ode::cli
{
  option::option()
      : n{""},
        alt_n{""},
        short_n{std::nullopt},
        t{option_type::null},
        default_v{nullptr},
        req{false}
  {
    // The default constructor initializes the option into an invalid state.
  }

  namespace detail
  {
    std::string create_alternative_name(const std::string& str)
    {
      std::string working_str{str};
      bool convert_next = false;
      // First use the hyphens in the name to convert the characters to the
      // correct case.
      std::transform(
          working_str.begin(),
          working_str.end(),
          working_str.begin(),
          [&convert_next](unsigned char ch) -> unsigned char {
            if (std::isalpha(ch))
            {
              if (convert_next)
              {
                convert_next = false;
                return std::toupper(ch);
              }
              else
              {
                return std::tolower(ch);
              }
            }
            else if ('-' == ch)
            {
              convert_next = true;
            }

            return ch;
          });
      // Remove the hyphens.
      std::remove(working_str.begin(), working_str.end(), '-');
      return working_str;
    }
  } // namespace detail

  option::option(
      const std::string& name,
      const std::string& short_name,
      const option_type type,
      const value_t& default_v,
      const bool r)
      : n{name},
        alt_n{detail::create_alternative_name(name)},
        short_n{short_name},
        t{type},
        default_v{default_v},
        req{r}
  {
    if (option_type::boolean == type)
    {
      ODE_TRACE(
          "Checking whether the option '{}', '{}' holds a Boolean default "
          "value",
          name,
          short_name);
      Ensures(std::holds_alternative<bool>(default_v));
    }
    else if (option_type::integer == type)
    {
      ODE_TRACE(
          "Checking whether the option '{}', '{}' holds an integer default "
          "value",
          name,
          short_name);
      Ensures(std::holds_alternative<int>(default_v));
    }
    else if (option_type::floating_point == type)
    {
      ODE_TRACE(
          "Checking whether the option '{}', '{}' holds a floating point "
          "default value",
          name,
          short_name);
      Ensures(std::holds_alternative<double>(default_v));
    }
    else if (option_type::string == type)
    {
      ODE_TRACE(
          "Checking whether the option '{}', '{}' holds a string default "
          "value",
          name,
          short_name);
      Ensures(std::holds_alternative<std::string>(default_v));
    }
  }

  option::option(
      const std::string& name,
      const option_type type,
      const value_t& default_v,
      const bool r)
      : n{name},
        alt_n{detail::create_alternative_name(name)},
        short_n{std::nullopt},
        t{type},
        default_v{default_v},
        req{r}
  {
    if (option_type::boolean == type)
    {
      ODE_TRACE(
          "Checking whether the option '{}' holds a Boolean default value",
          name);
      Ensures(std::holds_alternative<bool>(default_v));
    }
    else if (option_type::integer == type)
    {
      ODE_TRACE(
          "Checking whether the option '{}' holds an integer default value",
          name);
      Ensures(std::holds_alternative<int>(default_v));
    }
    else if (option_type::floating_point == type)
    {
      ODE_TRACE(
          "Checking whether the option '{}' holds a floating point default "
          "value",
          name);
      Ensures(std::holds_alternative<double>(default_v));
    }
    else if (option_type::string == type)
    {
      ODE_TRACE(
          "Checking whether the option '{}' holds a string default value",
          name);
      Ensures(std::holds_alternative<std::string>(default_v));
    }
  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const bool default_v,
      const bool r)
      : option{name, short_name, option_type::boolean, default_v, r}
  {
    ODE_TRACE("Creating a command line option that accepts Boolean values");
  }

  option::option(const std::string& name, const bool default_v, const bool r)
      : option{name, option_type::boolean, default_v, r}
  {
    ODE_TRACE("Creating a command line option that accepts Boolean values");
  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const int default_v,
      const bool r)
      : option{name, short_name, option_type::integer, default_v, r}
  {
    ODE_TRACE("Creating a command line option that accepts integer values");
  }

  option::option(const std::string& name, const int default_v, const bool r)
      : option{name, option_type::integer, default_v, r}
  {
    ODE_TRACE("Creating a command line option that accepts integer values");
  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const double default_v,
      const bool r)
      : option{name, short_name, option_type::floating_point, default_v, r}
  {
    ODE_TRACE(
        "Creating a command line option that accepts floating point values");
  }

  option::option(const std::string& name, const double default_v, const bool r)
      : option{name, option_type::floating_point, default_v, r}
  {
    ODE_TRACE(
        "Creating a command line option that accepts floating point values");
  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const std::string& default_v,
      const bool r)
      : option{name, short_name, option_type::string, default_v, r}
  {
    ODE_TRACE("Creating a command line option that accepts string values");
  }

  option::option(
      const std::string& name, const std::string& default_v, const bool r)
      : option{name, option_type::string, default_v, r}
  {
    ODE_TRACE("Creating a command line option that accepts string values");
  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const char* default_v,
      const bool r)
      : option{name, short_name, std::string{default_v}, r}
  {
    ODE_TRACE("Creating a command line option that accepts string values");
  }

  option::option(const std::string& name, const char* default_v, const bool r)
      : option{name, std::string{default_v}, r}
  {
    ODE_TRACE("Creating a command line option that accepts string values");
  }

  namespace detail
  {
    ///
    /// Tells if the option in question is already parsed from the argument in
    /// the given index.
    ///
    /// This function is index-sensitive as some options can be specified
    /// multiple times and to determine whether an option is used correctly
    /// isn’t handled by the object of the type \c option itself but by the
    /// object of the type \c option_group.
    ///
    /// \param index the index which is checked for the parsed option.
    /// \param opt a pointer to the object of the type \c option which is
    /// checked.
    /// \param parsed_indices an object of the type \c std::vector containing
    /// the values and indices of the command line arguments which are already
    /// parsed and, thus, should be skipped when parsing this option.
    ///
    /// \return \c true if the option is already parsed from the given index,
    /// otherwise \c false.
    ///
    bool is_option_parsed(
        const int index,
        const option* opt,
        const std::vector<option::parsed_value_t>& parsed_indices)
    {
      ODE_TRACE(
          "Checking if the option '{}' is already parsed from the index {}",
          opt->name(),
          index);
      for (const option::parsed_value_t& value : parsed_indices)
      {
        // This logging is a mess, but it’s better to have the whole expression
        // inside the macro so it can be deleted by disabling the macro.
        ODE_TRACE(
            "Going through the parsed options, current the option '{}' which "
            "contains the following source indices: {}",
            std::get<parsed_option_index>(value)->name(),
            std::get<parsed_indices_index>(value).size() > 1
                ? std::accumulate(
                      std::get<parsed_indices_index>(value).cbegin() + 1,
                      std::get<parsed_indices_index>(value).cend(),
                      std::to_string(std::get<parsed_indices_index>(value)[0]),
                      [](const std::string& init, const int first) {
                        return init + ", " + std::to_string(first);
                      })
                : std::to_string(std::get<parsed_indices_index>(value)[0]));

        if (*std::get<parsed_option_index>(value) == *opt &&
            std::find(
                std::get<parsed_indices_index>(value).cbegin(),
                std::get<parsed_indices_index>(value).cend(),
                index) != std::get<parsed_indices_index>(value).cend())
        {
          return true;
        }
      }

      return false;
    }

    ///
    /// Parses the value of the command line option without given raw string
    /// value.
    ///
    /// \param opt a pointer to the \c option which is parsed.
    ///
    /// \return An object of the type \c option::value_t.
    ///
    option::value_t parse_without_value(const option* opt)
    {
      if (option_type::boolean == opt->type())
      {
        return !std::get<bool>(opt->default_value());
      }
      else
      {
        return nullptr;
      }
    }

    ///
    /// Parses the value of the command line option by using the possible value
    /// from the next index.
    ///
    /// \param opt a pointer to the \c option which is parsed.
    /// \param raw_value the raw string value from the next argument if there
    /// is one.
    ///
    /// \return An object of the type \c option::value_t.
    ///
    option::value_t parse_value(const option* opt, const std::string& raw_value)
    {
      switch (opt->type())
      {
      case option_type::boolean:
        if (is_boolean(raw_value))
        {
          ODE_TRACE(
              "Parsing the option {} from value {} as a Boolean",
              opt->name(),
              raw_value);

          // The Boolean value can be given with or without the separator so it
          // may be in the same index.
          return stob(raw_value);
        }
        else
        {
          ODE_TRACE("Parsing the option {} as a Boolean flag", opt->name());
          return parse_without_value(opt);
        }
      case option_type::integer:
        if (is_integer(raw_value))
        {
          ODE_TRACE(
              "Parsing the option {} from value {} as an integer",
              opt->name(),
              raw_value);
          return std::stoi(raw_value);
        }
        else
        {
          ODE_TRACE(
              "Parsing the option {} from value {} as an integer yielded no "
              "valid value",
              opt->name(),
              raw_value);
          return nullptr;
        }
      case option_type::floating_point:
        if (is_number(raw_value))
        {
          ODE_TRACE(
              "Parsing the option {} from value {} as a floating point number",
              opt->name(),
              raw_value);
          return std::stod(raw_value);
        }
        else
        {
          ODE_TRACE(
              "Parsing the option {} from value {} as a floating point number "
              "yielded no valid value",
              opt->name(),
              raw_value);
          return nullptr;
        }
      case option_type::string:
        ODE_TRACE(
            "Parsing the option {} from value {} as a string",
            opt->name(),
            raw_value);
        return raw_value;
      default:
        ODE_TRACE("Parsing the option {} yielded no valid value", opt->name());
        return nullptr;
      }
    }

    ///
    /// Parses a long option.
    ///
    /// \param opt a pointer to the object of the type \c option to be parsed.
    /// \param arg_view a \c std::string_view pointing to the argument in
    /// \c current_index.
    /// \param name_view a \c std::string_view pointing to the selected name of
    /// the option.
    /// \param argc the number of arguments passed in the execution.
    /// \param argv an array containing the arguments passed in the execution.
    /// \param current_index the index of the current command line argument.
    /// \param parsed_indices an object of the type \c std::vector containing
    /// the values and indices of the command line arguments which are already
    /// parsed and, thus, should be skipped when parsing this option.
    /// \param prefix a string which is prefixed to the name of the options.
    /// \param separator a string which is used to separate the option from its
    /// value if a space isn’t used to do so.
    ///
    /// \return An object of the type \c std::pair, the first element of which
    /// is an object of the type \c std::optional which contains an object of
    /// the type \c value_t if the parsing is successful, and the second
    /// element of which is an object of the type \c std::vector containing the
    /// indices of the command line arguments that were parsed.
    ///
    option::parsed_value_t parse_long_option(
        const option* opt,
        const std::string_view arg_view,
        const std::string_view name_view,
        const int argc,
        ode::argv_t argv[],
        const int current_index,
        const std::vector<option::parsed_value_t>& parsed_indices,
        const std::string_view prefix,
        const std::string_view separator)
    {
      // See if the argument contains the value separator.
      if (separator ==
          arg_view.substr(prefix.size() + name_view.size(), separator.size()))
      {
        const std::size_t full_option_size =
            prefix.size() + name_view.size() + separator.size();

        const std::string raw_value{
            arg_view
                .substr(full_option_size, arg_view.size() - full_option_size)
                .data()};

        const auto value{parse_value(opt, raw_value)};

        return {
            opt,
            std::holds_alternative<std::nullptr_t>(value)
                ? std::optional<option::value_t>{std::nullopt}
                : std::optional<option::value_t>{value},
            std::vector<int>{current_index}};
      }
      else
      {
        // The next character isn’t the separator so before moving to the
        // next index, check that the argument in the current index doesn’t
        // continue after the character that are already checked, i.e. the
        // name of the found option actually matches the name of this
        // option.
        if (arg_view.size() == prefix.size() + name_view.size())
        {
          // Make sure the index isn’t out of bounds.
          if (current_index + 1 < argc)
          {
            // The raw value of the of the option is in the next argument.
            const std::string raw_value{argv[current_index + 1]};

            const auto value{parse_value(opt, raw_value)};

            return {
                opt,
                std::holds_alternative<std::nullptr_t>(value)
                    ? std::optional<option::value_t>{std::nullopt}
                    : std::optional<option::value_t>{value},
                std::holds_alternative<std::nullptr_t>(value)
                    ? std::vector<int>{current_index}
                    : std::vector<int>{current_index, current_index + 1}};
          }
          else
          {
            // The next argument is out of bounds.
            const std::string raw_value{""};

            const auto value{parse_value(opt, raw_value)};

            return {
                opt,
                std::holds_alternative<std::nullptr_t>(value)
                    ? std::optional<option::value_t>{std::nullopt}
                    : std::optional<option::value_t>{value},
                std::vector<int>{current_index}};
          }
        }
      }

      return {opt, std::nullopt, {-1}};
    }

    ///
    /// Parses a single short option when it doesn’t reside in a combination of
    /// short options and doesn’t contain a separator.
    ///
    /// \param opt a pointer to the object of the type \c option to be parsed.
    /// \param arg_view a \c std::string_view pointing to the argument in
    /// \c current_index.
    /// \param name_view a \c std::string_view pointing to the short name of
    /// the option.
    /// \param argc the number of arguments passed in the execution.
    /// \param argv an array containing the arguments passed in the execution.
    /// \param current_index the index of the current command line argument.
    /// \param prefix a string which is prefixed to the name of the options.
    ///
    /// \return An object of the type \c std::pair, the first element of which
    /// is an object of the type \c std::optional which contains an object of
    /// the type \c value_t if the parsing is successful, and the second
    /// element of which is an object of the type \c std::vector containing the
    /// indices of the command line arguments that were parsed.
    ///
    option::parsed_value_t parse_single_short_option_without_separator(
        const option* opt,
        const std::string_view arg_view,
        const std::string_view name_view,
        const int argc,
        ode::argv_t argv[],
        const int current_index,
        const std::string_view prefix)
    {
      // If combining of the short options and separators isn’t allowed, the
      // size of the argument must naturally be equal to the sum of the size
      // of the prefix and the size of the short name of the option. The
      // argument must also be equal to this combination.
      if (arg_view.size() == prefix.size() + name_view.size() &&
          std::string{prefix.data()} + name_view.data() == arg_view)
      {
        // Make sure the index isn’t out of bounds.
        if (current_index + 1 < argc)
        {
          // The raw value of the of the option is in the next argument.
          const std::string raw_value{argv[current_index + 1]};

          const auto value{parse_value(opt, raw_value)};

          return {
              opt,
              std::holds_alternative<std::nullptr_t>(value)
                  ? std::optional<option::value_t>{std::nullopt}
                  : std::optional<option::value_t>{value},
              std::holds_alternative<std::nullptr_t>(value)
                  ? std::vector<int>{current_index}
                  : std::vector<int>{current_index, current_index + 1}};
        }
        else
        {
          // The next argument is out of bounds.
          const std::string raw_value{""};

          const auto value{parse_value(opt, raw_value)};

          return {
              opt,
              std::holds_alternative<std::nullptr_t>(value)
                  ? std::optional<option::value_t>{std::nullopt}
                  : std::optional<option::value_t>{value},
              std::vector<int>{current_index}};
        }
      }

      // If no value can be parsed, the function returns a value with null
      // optional, which indicates that the loop should continue.
      return {opt, std::nullopt, {-1}};
    }

    ///
    /// Parses a single short option when it doesn’t reside in a combination of
    /// short options.
    ///
    /// \param opt a pointer to the object of the type \c option to be parsed.
    /// \param arg_view a \c std::string_view pointing to the argument in
    /// \c current_index.
    /// \param name_view a \c std::string_view pointing to the short name of
    /// the option.
    /// \param argc the number of arguments passed in the execution.
    /// \param argv an array containing the arguments passed in the execution.
    /// \param current_index the index of the current command line argument.
    /// \param prefix a string which is prefixed to the name of the options.
    /// \param separator a string which is used to separate the option from its
    /// value if a space isn’t used to do so.
    /// \param allow_separator_for_short whether or not allow to use the
    /// separator to separate the short options from the values.
    ///
    /// \return An object of the type \c std::pair, the first element of which
    /// is an object of the type \c std::optional which contains an object of
    /// the type \c value_t if the parsing is successful, and the second
    /// element of which is an object of the type \c std::vector containing the
    /// indices of the command line arguments that were parsed.
    ///
    option::parsed_value_t parse_single_short_option(
        const option* opt,
        const std::string_view arg_view,
        const std::string_view name_view,
        const int argc,
        ode::argv_t argv[],
        const int current_index,
        const std::string_view prefix,
        const std::string_view separator,
        const bool allow_separator_for_short)
    {
      if (allow_separator_for_short)
      {
        if (arg_view.size() == prefix.size() + name_view.size())
        {
          return parse_single_short_option_without_separator(
              opt, arg_view, name_view, argc, argv, current_index, prefix);
        }
        else if (
            0 ==
            arg_view.rfind(
                std::string{prefix.data()} + name_view.data() +
                    separator.data(),
                0))
        {
          const std::size_t full_option_size =
              prefix.size() + name_view.size() + separator.size();

          const std::string raw_value{
              arg_view
                  .substr(full_option_size, arg_view.size() - full_option_size)
                  .data()};

          const auto value{parse_value(opt, raw_value)};

          return {
              opt,
              std::holds_alternative<std::nullptr_t>(value)
                  ? std::optional<option::value_t>{std::nullopt}
                  : std::optional<option::value_t>{value},
              std::vector<int>{current_index}};
        }
      }
      else
      {
        return parse_single_short_option_without_separator(
            opt, arg_view, name_view, argc, argv, current_index, prefix);
      } // !allow_separator_for_short

      // If no value can be parsed, the function returns a value with null
      // optional, which indicates that the loop should continue.
      return {opt, std::nullopt, {-1}};
    }

    ///
    /// Checks whether or not the given argument is a valid combination of one
    /// character options.
    ///
    /// \param opt a pointer to the object of the type \c option to be parsed.
    /// \param arg_view a \c std::string_view pointing to the argument in
    /// \c current_index.
    /// \param name_view a \c std::string_view pointing to the short name of
    /// the option.
    /// \param argc the number of arguments passed in the execution.
    /// \param argv an array containing the arguments passed in the execution.
    /// \param all_options an object of the type \c std::vector containing a
    /// simple list of pointers to all of the possible options.
    /// \param current_index the index of the current command line argument.
    /// \param prefix a string which is prefixed to the name of the options.
    /// \param separator a string which is used to separate the option from its
    /// value if a space isn’t used to do so.
    ///
    /// \return \c true if the option combination in the given argument can be
    /// parsed, otherwise \c false.
    ///
    bool is_valid_option_combination(
        const option* opt,
        const std::string_view arg_view,
        const std::string_view name_view,
        const int argc,
        ode::argv_t argv[],
        const std::vector<option*> all_options,
        const int current_index,
        const std::string_view prefix)
    {
      // Double-check the prefix.
      if (0 != arg_view.rfind(prefix, 0))
      {
        return false;
      }

      // Make sure the rest of the characters in the argument are alphabetic
      // characters.
      for (const char ch : arg_view.substr(prefix.size()))
      {
        if (!std::isalpha(static_cast<unsigned char>(ch)))
        {
          return false;
        }
      }

      // Check that the option doesn’t match the long name of some option.
      for (const option* o : all_options)
      {
        if (arg_view.substr(prefix.size()) == o->name() ||
            arg_view.substr(prefix.size()) == o->alternative_name())
        {
          return false;
        }
      }

      bool found_options = true;

      // Check each of the options in the combination and see if they match
      // ones that actually exist. Also check that all of the options in the
      // combination can be parsed into valid values.
      for (int i = prefix.size(); i < arg_view.size(); ++i)
      {
        bool valid_option = false;

        for (const option* o : all_options)
        {
          // Check if the current option matches the current option.
          if (o->short_name().has_value() &&
              *o->short_name() == std::string{arg_view[i]})
          {
            // If this option is the last one in the combination, it requires
            // different handling as its value can be in the next argument.
            const std::string raw_value{
                arg_view.size() - 1 == i && current_index + 1 < argc
                    ? argv[current_index + 1]
                    : ""};

            const auto value = parse_value(o, raw_value);

            // If the value returned from the value parsing function is a value
            // of the type nullptr_t, the parsing wasn’t successful.
            valid_option = !std::holds_alternative<std::nullptr_t>(value);
          }
        }

        if (!valid_option)
        {
          found_options = false;
        }
      }

      return found_options;
    }

    ///
    /// Parses a short option.
    ///
    /// \param opt a pointer to the object of the type \c option to be parsed.
    /// \param arg_view a \c std::string_view pointing to the argument in
    /// \c current_index.
    /// \param name_view a \c std::string_view pointing to the short name of
    /// the option.
    /// \param argc the number of arguments passed in the execution.
    /// \param argv an array containing the arguments passed in the execution.
    /// \param all_options an object of the type \c std::vector containing a
    /// simple list of pointers to all of the possible options.
    /// \param current_index the index of the current command line argument.
    /// \param prefix a string which is prefixed to the name of the options.
    /// \param separator a string which is used to separate the option from its
    /// value if a space isn’t used to do so.
    /// \param allow_separator_for_short whether or not allow to use the
    /// separator to separate the short options from the values.
    /// \param allow_combining whether or not it’s allowed to specify multiple
    /// short, one-character options together.
    ///
    /// \return An object of the type \c std::pair, the first element of which
    /// is an object of the type \c std::optional which contains an object of
    /// the type \c value_t if the parsing is successful, and the second
    /// element of which is an object of the type \c std::vector containing the
    /// indices of the command line arguments that were parsed.
    ///
    option::parsed_value_t parse_short_option(
        const option* opt,
        const std::string_view arg_view,
        const std::string_view name_view,
        const int argc,
        ode::argv_t argv[],
        const std::vector<option*> all_options,
        const int current_index,
        const std::string_view prefix,
        const std::string_view separator,
        const bool allow_separator_for_short,
        const bool allow_combining)
    {
      if (allow_combining)
      {
        if (arg_view.size() == prefix.size() + name_view.size() ||
            (allow_separator_for_short &&
             0 ==
                 arg_view.rfind(
                     std::string{prefix.data()} + name_view.data() +
                         separator.data(),
                     0)))
        {
          return parse_single_short_option(
              opt,
              arg_view,
              name_view,
              argc,
              argv,
              current_index,
              prefix,
              separator,
              allow_separator_for_short);
        }
        else
        {
          if (is_valid_option_combination(
                  opt,
                  arg_view,
                  name_view,
                  argc,
                  argv,
                  all_options,
                  current_index,
                  prefix))
          {
            const auto option_index = arg_view.find(name_view);

            if (std::string_view::npos == option_index)
            {
              return {opt, std::nullopt, {-1}};
            }
            else if (arg_view.size() - 1 == option_index)
            {
              // If this option is the last one in the combination, it requires
              // different handling as its value can be in the next argument.
              const std::string raw_value{
                  current_index + 1 < argc ? argv[current_index + 1] : ""};

              const auto value{parse_value(opt, raw_value)};

              return {
                  opt,
                  std::holds_alternative<std::nullptr_t>(value)
                      ? std::optional<option::value_t>{std::nullopt}
                      : std::optional<option::value_t>{value},
                  std::holds_alternative<std::nullptr_t>(value)
                      ? std::vector<int>{current_index}
                      : std::vector<int>{current_index, current_index + 1}};
            }
            else
            {
              const std::string raw_value{""};

              const auto value{parse_value(opt, raw_value)};

              return {
                  opt,
                  std::holds_alternative<std::nullptr_t>(value)
                      ? std::optional<option::value_t>{std::nullopt}
                      : std::optional<option::value_t>{value},
                  std::vector<int>{current_index}};
            }
          }
          else
          {
            return {opt, std::nullopt, {-1}};
          }
        }
      }
      else
      {
        return parse_single_short_option(
            opt,
            arg_view,
            name_view,
            argc,
            argv,
            current_index,
            prefix,
            separator,
            allow_separator_for_short);
      } // !allow_combining
    }

  } // namespace detail

  option::parsed_value_t option::parse_option(
      const int argc,
      ode::argv_t argv[],
      const std::vector<option*> all_options,
      const std::vector<option::parsed_value_t>& parsed_indices,
      const std::string_view prefix,
      const std::string_view short_prefix,
      const std::string_view alternative_prefix,
      const std::string_view separator,
      const bool use_alternative_name,
      const bool allow_separator_for_short,
      const bool allow_combining) const
  {
    ODE_TRACE("Beginning to parse the command line option '{}'", n);

    for (int i = 0; i < argc; ++i)
    {
      if (!detail::is_option_parsed(i, this, parsed_indices))
      {
        const std::string_view arg_view{argv[i]};

        const std::string working_n{use_alternative_name ? alt_n : n};

        // Start by checking for the longer name of the option as it’s
        // prioritized. The first check is to see whether the arguments starts
        // with the prefix of the long options. The second check is to see
        // whether the name of the option comes after the prefix.
        if (0 == arg_view.rfind(prefix, 0) &&
            working_n == arg_view.substr(prefix.size(), working_n.size()))
        {
          return detail::parse_long_option(
              this,
              arg_view,
              working_n,
              argc,
              argv,
              i,
              parsed_indices,
              prefix,
              separator);
        }
        else if (
            !alternative_prefix.empty() &&
            0 == arg_view.rfind(alternative_prefix, 0) &&
            working_n ==
                arg_view.substr(alternative_prefix.size(), working_n.size()))
        {
          return detail::parse_long_option(
              this,
              arg_view,
              working_n,
              argc,
              argv,
              i,
              parsed_indices,
              alternative_prefix,
              separator);
        }
        else if (short_n.has_value() && 0 == arg_view.rfind(short_prefix, 0))
        {
          const auto value = detail::parse_short_option(
              this,
              arg_view,
              *short_n,
              argc,
              argv,
              all_options,
              i,
              short_prefix,
              separator,
              allow_separator_for_short,
              allow_combining);

          // If the parsing yields no value, it’s probably due to the fact that
          // the short option doesn’t exist in the given index as the check
          // can’t be done before the parsing like with long option names.
          // Therefore, the function shouldn’t return but continue the loop. If
          // it yields no value but the current index is indicated as parsed,
          // it means that the option was given in an invalid manner, and the
          // function should return.
          if (std::get<parsed_value_index>(value).has_value() ||
              std::get<parsed_indices_index>(value)[0] == i)
          {
            return value;
          }
        }
        else if (
            !alternative_prefix.empty() && short_n.has_value() &&
            0 == arg_view.rfind(alternative_prefix, 0))
        {
          const auto value = detail::parse_short_option(
              this,
              arg_view,
              *short_n,
              argc,
              argv,
              all_options,
              i,
              alternative_prefix,
              separator,
              allow_separator_for_short,
              allow_combining);

          // If the parsing yields no value, it’s probably due to the fact that
          // the short option doesn’t exist in the given index as the check
          // can’t be done before the parsing like with long option names.
          // Therefore, the function shouldn’t return but continue the loop. If
          // it yields no value but the current index is indicated as parsed,
          // it means that the option was given in an invalid manner, and the
          // function should return.
          if (std::get<parsed_value_index>(value).has_value() ||
              std::get<parsed_indices_index>(value)[0] == i)
          {
            return value;
          }
        }
      }
    } // for (int i = 0; i < argc; ++i)

    return parsed_value_t{this, std::nullopt, std::vector<int>{-1}};
  }

  option::parsed_value_t option::parse_option(
      const int argc,
      ode::argv_t argv[],
      const std::vector<option*> all_options,
      const std::vector<option::parsed_value_t>& parsed_indices) const
  {
#if ODE_WINDOWS
    return parse_option(
        argc,
        argv,
        all_options,
        parsed_indices,
        "/",
        "/",
        "-",
        ":",
        true,
        true,
        false);
#else
    return parse_option(
        argc,
        argv,
        all_options,
        parsed_indices,
        "--",
        "-",
        "",
        "=",
        false,
        false,
        true);
#endif // !ODE_WINDOWS
  }

  std::string option::format_help() const
  {
    std::stringstream builder{};

#if ODE_WINDOWS
    const std::string prefix{"/"};
    const std::string short_prefix{"/"};
    const std::string platform_dependent_name{alt_n};
#else
    const std::string prefix{"--"};
    const std::string short_prefix{"-"};
    const std::string platform_dependent_name{n};
#endif // !ODE_WINDOWS

    builder << "  ";

    if (short_n.has_value())
    {
      if (option_type::boolean == t)
      {
        builder << short_prefix << short_n.value() << ", ";
      }
      else
      {
        builder << short_prefix << short_n.value() << " " << meta_v << ", ";
      }
    }

    if (option_type::boolean == t)
    {
      builder << prefix << platform_dependent_name;
    }
    else
    {
      builder << prefix << platform_dependent_name << " " << meta_v;
    }

    // The description must be formatted. It must contain two 24 before
    // each line of text. The code must also start a new line when it
    // reaches 80 characters. The start of the new line must be before the
    // word that reaches 80 characters.
    std::istringstream d_iss{desc};
    std::vector<std::string> d_words{
        std::istream_iterator<std::string>{d_iss},
        std::istream_iterator<std::string>{}};
    std::stringstream d_ss{};

    const std::string padding{24, ' '};

    if (24 <= builder.str().size() + 1)
    {
      builder << "\n";

      for (const auto w : d_words)
      {
        if (d_ss.str().empty())
        {
          d_ss << padding << w;
        }
        else
        {
          if (80 >= d_ss.str().size() + 1 + w.size())
          {
            d_ss << " " << w;
          }
          else
          {
            // If the next word doesn’t fit into the line, start a new one.
            builder << d_ss.str() << "\n";
            d_ss.str(std::string{});
            d_ss << padding << w;
          }
        }
      }
    }
    else
    {
      const std::string::size_type missing_length =
          24 - static_cast<int>(builder.str().size());
      const std::string missing_padding(missing_length, ' ');
      builder << missing_padding;

      for (const auto w : d_words)
      {
        // If the beginning of the stream contains something else than spaces,
        // it’s the first line with the name of the option.
        if (padding != d_ss.str().substr(0, 24))
        {
          if (80 >= 24 + d_ss.str().size() + 1 + w.size())
          {
            d_ss << " " << w;
          }
          else
          {
            // If the next word doesn’t fit into the line, start a new one.
            builder << d_ss.str() << "\n";
            d_ss.str(std::string{});
            d_ss << padding << w;
          }
        }
        else
        {
          if (80 >= d_ss.str().size() + 1 + w.size())
          {
            d_ss << " " << w;
          }
          else
          {
            // If the next word doesn’t fit into the line, start a new one.
            builder << d_ss.str() << "\n";
            d_ss.str(std::string{});
            d_ss << padding << w;
          }
        }
      }
    }

    builder << d_ss.str();

    return builder.str();
  }

  std::string option::name() const
  {
    return n;
  }

  std::string option::alternative_name() const
  {
    return alt_n;
  }

  std::optional<std::string> option::short_name() const
  {
    return short_n;
  }

  std::string option::description() const
  {
    return desc;
  }

  std::string option::meta_variable() const
  {
    return meta_v;
  }

  option_type option::type() const
  {
    return t;
  }

  option::value_t option::default_value() const
  {
    return default_v;
  }

  bool option::required() const
  {
    return req;
  }

  bool operator==(const option& lhs, const option& rhs) noexcept
  {
    return lhs.n == rhs.n && lhs.alt_n == rhs.alt_n &&
        lhs.short_n == rhs.short_n && lhs.t == rhs.t &&
        lhs.default_v == rhs.default_v && lhs.req == rhs.req;
  }

  bool operator!=(const option& lhs, const option& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  namespace detail
  {
    std::string default_value_to_string(const option& a)
    {
      switch (a.type())
      {
      case option_type::boolean:
        return std::to_string(std::get<bool>(a.default_value()));
      case option_type::integer:
        return std::to_string(std::get<int>(a.default_value()));
      case option_type::floating_point:
        return std::to_string(std::get<double>(a.default_value()));
      case option_type::string:
        return std::get<std::string>(a.default_value());
        ;
      default:
        return "null";
      }
    }
  } // namespace detail

  std::ostream& operator<<(std::ostream& os, const option& a)
  {
    using namespace std::string_literals;

    return os << "{"
              << "option:" << a.name() << " (" << a.alternative_name() << ","
              << (a.short_name().has_value() ? *a.short_name()
                                             : "no short name"s)
              << ")"
              << ", type:" << a.type()
              << ", default value:" << detail::default_value_to_string(a)
              << ", required:" << std::to_string(a.required()) << "}";
  }

} // namespace ode::cli
