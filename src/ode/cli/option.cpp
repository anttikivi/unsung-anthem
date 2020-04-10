/// The definition of the type of objects that contain information about one
/// command line option.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/option.h"

#include <type_traits>

#include "gsl/assert"

namespace ode::cli
{
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
      Ensures(std::holds_alternative<bool>(default_v));
    }
    else if (option_type::integer == type)
    {
      Ensures(std::holds_alternative<int>(default_v));
    }
    else if (option_type::floating_point == type)
    {
      Ensures(std::holds_alternative<float>(default_v));
    }
    else if (option_type::string == type)
    {
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

  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const int default_v,
      const bool r)
  : option{name, short_name, option_type::integer, default_v, r}
  {

  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const float default_v,
      const bool r)
  : option{name, short_name, option_type::floating_point, default_v, r}
  {

  }

  option::option(
      const std::string& name,
      const std::string& short_name,
      const std::string& default_v,
      const bool r)
  : option{name, short_name, option_type::string, default_v, r}
  {

  }

  std::string option::name() const
  {
    return n;
  }

  std::string option::short_name() const
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

} // namespace ode::cli
