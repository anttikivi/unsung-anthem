/// The definitions of the command line option type utilities.
/// \file
/// \author Antti Kivi
/// \date 13 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/option_type.h"

namespace ode::cli
{
  std::ostream& operator<<(std::ostream& os, const option_type& a)
  {
    return os << static_cast<ODE_OPTION_TYPE_ENUM_TYPE>(a);
  }
} // namespace ode::cli
