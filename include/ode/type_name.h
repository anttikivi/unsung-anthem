/// The declaration of the type trait utility used to get a type as a string
/// view.
/// \file
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_TYPE_NAME_H
#define ODE_TYPE_NAME_H

#include <string_view>

namespace ode
{
  ///
  /// TODO
  ///
  template <typename T> constexpr std::string_view type_name()
  {
#ifdef __clang__
    std::string_view p = __PRETTY_FUNCTION__;
    return std::string_view{p.data() + 34, p.size() - 34 - 1};
#elif defined(__GNUC__)
    std::string_view p = __PRETTY_FUNCTION__;
#  if __cplusplus < 201402
    return std::string_view{p.data() + 36, p.size() - 36 - 1};
#  else
    return std::string_view{p.data() + 49, p.find(';', 49) - 49};
#  endif
#elif defined(_MSC_VER)
    std::string_view p = __FUNCSIG__;
    return std::string_view{p.data() + 84, p.size() - 84 - 7};
#endif
  }
} // namespace ode

#endif // !ODE_TYPE_NAME_H
