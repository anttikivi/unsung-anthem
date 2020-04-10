/// The definitions of the utility for parsing command line arguments.
/// \file
/// \author Antti Kivi
/// \date 18 March 2020
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/parse_arguments.h"

#include "ode/cli/arguments.h"
#include "ode/cli/option_group_t.h"

namespace ode::cli
{
  arguments parse_arguments(
      const int argc,
      ode::argv_t argv[],
      std::vector<option_group_t> option_groups)
  {
    // TODO The implementation gets objects of the type arguments from the
    // option groups and combines them into the final object.
    return {};
  }

} // namespace ode::cli
