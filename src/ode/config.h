//===------------------------------ config.h --------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2018 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file config.h
/// \brief The declarations and the definitions of the Obliging Ode
/// miscellaneous constants.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_CONFIG_H
#define ODE_CONFIG_H

namespace ode
{
  ///
  /// \brief The name of the product.
  ///
#ifdef ODE_PRODUCT_NAME
  constexpr auto ode_name = ODE_PRODUCT_NAME;
#else
  constexpr auto ode_name = "Obliging Ode";
#endif // !defined(ODE_PRODUCT_NAME)

} // namespace ode

#endif // !ODE_CONFIG_H
