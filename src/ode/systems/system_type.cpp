/// The definitions of the system type utilities.
/// \file
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/systems/system_type.h"

namespace ode
{
  std::ostream& operator<<(std::ostream& os, const system_type& a)
  {
    return os << static_cast<ODE_SYSTEM_TYPE_ENUM_TYPE>(a);
  }
} // namespace ode
