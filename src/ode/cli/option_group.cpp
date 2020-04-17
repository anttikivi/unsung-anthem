/// The definition of the type of objects that contain information about groups
/// of command line options for parsing command line arguments.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/option_group.h"

#include <algorithm>
#include <iterator>
#include <sstream>
#include <utility>

#include "gsl/assert"

namespace ode::cli
{
  option_group::option_group() : opts{}, n{std::nullopt}, desc{std::nullopt}
  {
  }

  option_group::option_group(std::vector<option>&& opts)
      : opts{std::move(opts)}, n{std::nullopt}, desc{std::nullopt}
  {
  }

  option_group::option_group(const std::string& n, std::vector<option>&& opts)
      : opts{std::move(opts)}, n{n}, desc{std::nullopt}
  {
  }

  option_group::option_group(
      const std::string& n, const std::string& d, std::vector<option>&& opts)
      : opts{std::move(opts)}, n{n}, desc{d}
  {
    if (!d.empty())
    {
      Ensures(!n.empty());
    }
  }

  std::string option_group::format_help() const
  {
    // Using string stream is an easy way to build the output.
    std::stringstream builder{};

    if (n.has_value())
    {
      builder << "\n\n" << n.value() << "\n";

      if (desc.has_value())
      {
        // The description must be formatted. It must contain two spaces before
        // each line of text. The code must also start a new line when it
        // reaches 80 characters. The start of the new line must be before the
        // word that reaches 80 characters.
        std::istringstream iss{desc.value()};
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
      for (const auto o : opts)
      {
        if (o.required())
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

        for (const auto o : required)
        {
          builder << "\n" << o.format_help();
        }
      }

      if (!optional.empty())
      {
        builder << "\n\n"
                << "optional options:";

        for (const auto o : optional)
        {
          builder << "\n" << o.format_help();
        }
      }
    }

    return builder.str();
  }

  std::vector<option> option_group::options() const
  {
    return opts;
  }

  std::optional<std::string> option_group::name() const
  {
    return n;
  }

  std::optional<std::string> option_group::description() const
  {
    return desc;
  }
} // namespace ode::cli
