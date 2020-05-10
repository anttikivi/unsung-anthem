/// The definitions of general string-related utilities.
/// \file
/// \author Antti Kivi
/// \date 12 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/string_utility.h"

#include <cctype>

#include <algorithm>
#include <ios>
#include <sstream>
#include <stdexcept>

#include "ode/logger.h"

namespace ode
{
  bool is_integer(const std::string& str)
  {
    if (!str.empty())
    {
      if (str.front() == '+' || str.front() == '-')
      {
        return std::find_if(
                   str.cbegin() + 1, str.cend(), [](unsigned char ch) -> bool {
                     return !std::isdigit(ch);
                   }) == str.cend();
      }
      else
      {
        return std::find_if(
                   str.cbegin(), str.cend(), [](unsigned char ch) -> bool {
                     return !std::isdigit(ch);
                   }) == str.cend();
      }
    }

    return false;
  }

  bool is_number(const std::string& str)
  {
    const int delimiter_index = str.find('.');

    if (std::string::npos == delimiter_index)
    {
      return is_integer(str);
    }
    else
    {
      return is_integer(str.substr(0, delimiter_index)) &&
          is_integer(str.substr(delimiter_index + 1)) &&
          std::isdigit(static_cast<unsigned char>(str[delimiter_index + 1]));
    }
  }

  std::string trim(const std::string& str)
  {
    // Explicitly copy the parameter to make it clear.
    std::string working_str = str;

    // Erase the whitespace characters from the beginning of the string.
    working_str.erase(
        working_str.begin(),
        std::find_if(
            working_str.begin(),
            working_str.end(),
            [](unsigned char ch) -> bool { return !std::isspace(ch); }));

    // Erase the whitespace characters from the end of the string.
    working_str.erase(
        std::find_if(
            working_str.rbegin(),
            working_str.rend(),
            [](unsigned char ch) -> bool { return !std::isspace(ch); })
            .base(),
        working_str.end());

    return working_str;
  }

  namespace detail
  {
    bool is_valid_bool(const std::string& str)
    {
      using namespace std::literals::string_literals;
      return is_integer(str) || "false"s == str || "true"s == str;
    }
  } // namespace detail

  bool is_boolean(const std::string& str)
  {
    std::string working_str{trim(str)};
    std::transform(
        working_str.begin(), working_str.end(), working_str.begin(), ::tolower);
    return detail::is_valid_bool(working_str);
  }

  bool stob(const std::string& str)
  {
    std::string working_str{trim(str)};
    std::transform(
        working_str.begin(), working_str.end(), working_str.begin(), ::tolower);

    if (!detail::is_valid_bool(working_str))
    {
      using namespace std::literals::string_literals;
      throw std::invalid_argument{
          "The value in the string "s + str +
          " cannot be converted to a Boolean"};
    }

    if (is_integer(working_str))
    {
      return std::stoi(working_str);
    }
    else
    {
      std::istringstream is{working_str};
      bool b{};
      is >> std::boolalpha >> b;
      return b;
    }
  }
} // namespace ode
