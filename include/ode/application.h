//===--------------------------- application.h ------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file application.h
/// \brief The declaration of the application concept.
/// \author Antti Kivi
/// \date 9 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

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
