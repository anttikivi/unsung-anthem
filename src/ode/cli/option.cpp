/// The definition of the type of objects that contain information about one
/// command line option.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/option.h"

#include <algorithm>
#include <numeric>
#include <type_traits>

#include "gsl/assert"

#include "ode/logger.h"
#include "ode/string_utility.h"

namespace ode::cli
{
  option::option()
  : n{""},
  short_n{std::nullopt},
  t{option_type::null},
  default_v{nullptr},
  req{false}
  {
    // The default constructor initializes the option into an invalid state.
  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const option_type type,
      const value_t& default_v,
      const bool r)
  : n{name},
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
      const std::string& name,
      const std::string& default_v,
      const bool r)
  : option{name, option_type::string, default_v, r}
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
            std::get<parsed_indices_index>(value).size() > 1 ? std::accumulate(
                std::get<parsed_indices_index>(value).cbegin() + 1,
                std::get<parsed_indices_index>(value).cend(),
                std::to_string(std::get<parsed_indices_index>(value)[0]),
                [](const std::string& init, const int first)
                {
                  return init + ", " + std::to_string(first);
                }) : std::to_string(std::get<parsed_indices_index>(value)[0]));

        if (*std::get<parsed_option_index>(value) == *opt &&
            std::find(
                std::get<parsed_indices_index>(value).cbegin(),
                std::get<parsed_indices_index>(value).cend(), index)
            != std::get<parsed_indices_index>(value).cend())
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
    option::value_t parse_value(
        const option* opt,
        const std::string& raw_value)
    {
      switch (opt->type())
      {
      case option_type::boolean:
        if (is_boolean(raw_value))
        {
          // The Boolean value can be given with or without the separator so it
          // may be in the same index.
          return stob(raw_value);
        }
        else
        {
          return parse_without_value(opt);
        }
      case option_type::integer:
        if (is_integer(raw_value))
        {
          return std::stoi(raw_value);
        }
        else
        {
          return nullptr;
        }
      case option_type::floating_point:
        if (is_number(raw_value))
        {
          return std::stod(raw_value);
        }
        else
        {
          return nullptr;
        }
      case option_type::string:
        return raw_value;
      default:
        return nullptr;
      }
    }

  } // namespace detail

  option::parsed_value_t option::parse_option(
      const int argc,
      ode::argv_t argv[],
      const std::vector<option::parsed_value_t>& parsed_indices,
      const std::string_view prefix,
      const std::string_view short_prefix,
      const std::string_view separator,
      const bool allow_combining) const
  {
    ODE_TRACE("Beginning to parse the command line option '{}'", n);

    for (int i = 0; i < argc; ++i)
    {
      if (!detail::is_option_parsed(i, this, parsed_indices))
      {
        const std::string_view arg_view{argv[i]};

        // Start by checking for the longer name of the option as it’s
        // prioritized. The first check is to see whether the arguments starts
        // with the prefix of the long options. The second check is to see
        // whether the name of the option comes after the prefix.
        if (0 == arg_view.rfind(prefix, 0) &&
            n == arg_view.substr(prefix.size(), n.size()))
        {
          // See if the next character is the value separator.
          if (separator == arg_view.substr(
              prefix.size() + n.size(), separator.size()))
          {
            const std::size_t full_option_size
                = prefix.size() + n.size() + separator.size();

            // Copy the underlying string from the view only when needed.
            const std::string raw_value{arg_view.substr(
                full_option_size,
                arg_view.size() - full_option_size).data()};

            const auto value{detail::parse_value(this, raw_value)};

            return parsed_value_t{
                this,
                std::holds_alternative<std::nullptr_t>(value) ?
                    std::optional<value_t>{std::nullopt} :
                    std::optional<value_t>{value},
                std::vector<int>{i}};
          }
          else
          {
            // The next character isn’t the separator so before moving to the
            // next index, check that the argument in the current index doesn’t
            // continue after the character that are already checked, i.e. the
            // name of the found option actually matches the name of this
            // option.
            if (arg_view.size() == prefix.size() + n.size())
            {
              // Make sure the index isn’t out of bounds.
              if (i + 1 < argc)
              {
                // The raw value of the of the option is in the next argument.
                const std::string raw_value{argv[i + 1]};

                const auto value{detail::parse_value(this, raw_value)};

                return parsed_value_t{
                    this,
                    std::holds_alternative<std::nullptr_t>(value) ?
                        std::optional<value_t>{std::nullopt} :
                        std::optional<value_t>{value},
                    std::holds_alternative<std::nullptr_t>(value) ?
                        std::vector<int>{i} :
                        std::vector<int>{i, i + 1}};
              }
              else
              {
                // The raw value of the of the option is in the next argument.
                const std::string raw_value{""};

                const auto value{detail::parse_value(this, raw_value)};

                return parsed_value_t{
                    this,
                    std::holds_alternative<std::nullptr_t>(value) ?
                        std::optional<value_t>{std::nullopt} :
                        std::optional<value_t>{value},
                    std::vector<int>{i}};
              }
            }
          }
        }
        else if (short_n.has_value() && 0 == arg_view.rfind(short_prefix, 0))
        {
          // TODO Take into account that the prefix is the same for long and
          // short options on Windows.

          if (allow_combining)
          {
            // TODO Check lenght.
          }
          else
          {
            // If combining of the short options isn’t allowed, the size of the
            // argument must naturally be equal to the sum of the the size of
            // the prefix and the size of the short name of the option.
            if (arg_view.size() == short_prefix.size() + short_n->size())
            {
              // The raw value of the of the option is in the next argument.
              const std::string raw_value{argv[i + 1]};

              // TODO The parsing function should make sure the value isn’t
              // accidentally parsed from the name of the next option.

              // TODO Parse the value.
            }
          }
        }
      }
    } // for (int i = 0; i < argc; ++i)

    return parsed_value_t{this, std::nullopt, std::vector<int>{-1}};
  }

  std::string option::name() const
  {
    return n;
  }

  std::optional<std::string> option::short_name() const
  {
    return short_n;
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
    return lhs.n == rhs.n &&
        lhs.short_n == rhs.short_n &&
        lhs.t == rhs.t &&
        lhs.default_v == rhs.default_v &&
        lhs.req == rhs.req;
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
        return std::get<std::string>(a.default_value());;
      default:
        return "null";
      }
    }
  } // namespace detail

  std::ostream& operator<<(std::ostream& os, const option& a)
  {
    using namespace std::string_literals;

    return os << "{"
        << "option:" << a.name()
        << " ("
        << (a.short_name().has_value() ? *a.short_name() : "no short name"s)
        << ")"
        << ", type:" << a.type()
        << ", default value:" << detail::default_value_to_string(a)
        << ", required:" << std::to_string(a.required())
        << "}";
  }

} // namespace ode::cli
