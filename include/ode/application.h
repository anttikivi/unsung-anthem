/// The declaration of the application concept.
/// \file
/// \author Antti Kivi
/// \date 9 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_APPLICATION_H
#define ODE_APPLICATION_H

#include "ode/__config"
#include "ode/application_type_traits.h"

namespace ode
{

#if ODE_CONCEPTS

  template <typename T> concept Application = is_application_v<T>;

#endif // ODE_CONCEPTS

} // namespace ode

#endif // !ODE_APPLICATION_H
