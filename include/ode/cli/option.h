//===------------------------------ option.h --------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2020 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file option.h
/// \brief The declaration of the type of objects that contain information
/// about one command line option.
/// \author Antti Kivi
/// \date 19 March 2020
/// \copyright Copyright (c) 2020 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_CLI_OPTION_H
#define ODE_CLI_OPTION_H

#include <string>

namespace ode::cli {

  ///
  /// \class option
  /// \brief The type of the object which contains the required frameworks of
  /// the application.
  ///
  /// \tparam A the type of the type of the application implementation.
  ///
  template <typename T> class option {
  };

} // namespace ode::cli

#endif // !ODE_CLI_OPTION_H
