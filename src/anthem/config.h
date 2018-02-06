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
/// \brief The declarations and the definitions of the Unsung Anthem
/// miscellaneous constants.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_CONFIG_H
#define ANTHEM_CONFIG_H

namespace anthem
{
  ///
  /// \brief The name of the product.
  ///
#ifdef ANTHEM_PRODUCT_NAME
  constexpr auto anthem_name = ANTHEM_PRODUCT_NAME;
#else
  constexpr auto anthem_name = "Unsung Anthem";
#endif // !defined(ANTHEM_PRODUCT_NAME)

} // namespace anthem

#endif // !ANTHEM_CONFIG_H
