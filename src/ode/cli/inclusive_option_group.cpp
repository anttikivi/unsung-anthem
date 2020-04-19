/// The definition of the type of objects that contain information about groups
/// of command line options where none of the options are exclusive.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/inclusive_option_group.h"

#include <sstream>
#include <utility>

namespace ode::cli
{
  inclusive_option_group::inclusive_option_group(
      const std::string& name,
      const std::string& description,
      std::unordered_set<option>&& options)
      : name{name}, description{description}, options{std::move(options)}
  {
  }

  inclusive_option_group::inclusive_option_group(
      const std::string& name, std::unordered_set<option>&& options)
      : name{name}, description{std::nullopt}, options{std::move(options)}
  {
  }

  inclusive_option_group::inclusive_option_group(
      std::unordered_set<option>&& options)
      : name{std::nullopt},
        description{std::nullopt},
        options{std::move(options)}
  {
  }

  arguments inclusive_option_group::parse_group(
      const int argc, ode::argv_t argv[]) const
  {
    std::unordered_map<std::string, option::value_t> parsed{};
    std::unordered_map<std::string, std::string> failed{};
    std::unordered_set<std::string> missing{};
    std::unordered_set<std::string> unknown{};

    option::parsed_options_t parsing_values{};

    for (const auto option : options)
    {
      const auto value =
          option.parse_option(argc, argv, options, parsing_values);

      parsing_values.push_back({option, value.first, value.second});
    }

    return {parsed, failed, missing, unknown};
  }

  std::string inclusive_option_group::format_help() const
  {
    // Using string stream is an easy way to build the output.
    std::stringstream builder{};

    if (name.has_value())
    {
      builder << "\n\n" << name.value() << "\n";

      if (description.has_value())
      {
        // The description must be formatted. It must contain two spaces before
        // each line of text. The code must also start a new line when it
        // reaches 80 characters. The start of the new line must be before the
        // word that reaches 80 characters.
        std::istringstream iss{description.value()};
        std::vector<std::string> words{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}};
        std::stringstream ss{};

        for (const auto w : words)
        {
          if (ss.str().empty())
          {
            ss << "  " << w;
          }
          else
          {
            if (80 >= ss.str().size() + 1 + w.size())
            {
              ss << " " << w;
            }
            else
            {
              ss << "\n"
                 << "  " << w;
            }
          }
        }

        ss << "\n\n";
      }
    }
    else
    {
      // Sort the options in the group to required and optional options and
      // print them accordingly.
      std::vector<option> required{};
      std::vector<option> optional{};

      // A loop is used as option is not CopyAssignable.
      for (const auto& o : options)
      {
        if (o.is_required())
        {
          required.push_back(o);
        }
        else
        {
          optional.push_back(o);
        }
      }

      if (!required.empty())
      {
        builder << "\n\n"
                << "required options:";

        for (const auto& o : required)
        {
          builder << "\n" << o.format_help();
        }
      }

      if (!optional.empty())
      {
        builder << "\n\n"
                << "optional options:";

        for (const auto& o : optional)
        {
          builder << "\n" << o.format_help();
        }
      }
    }

    return builder.str();
  }
} // namespace ode::cli
