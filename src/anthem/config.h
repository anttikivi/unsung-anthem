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
/// \brief The declarations and definitions of miscellaneous constants.
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

  ///
  /// \brief The root directory of the game scripts.
  ///
#ifdef ANTHEM_SCRIPT_ROOT
  constexpr auto script_root = ANTHEM_SCRIPT_ROOT;
#else
  constexpr auto script_root = "script/anthem";
#endif // !defined(ANTHEM_SCRIPT_ROOT)

  ///
  /// \brief The root directory of the test scripts.
  ///
#ifdef ANTHEM_TEST_SCRIPT_ROOT
  constexpr auto test_script_root = ANTHEM_TEST_SCRIPT_ROOT;
#else
  constexpr auto test_script_root = "script/test/anthem";
#endif // !defined(ANTHEM_TEST_SCRIPT_ROOT)

} // namespace anthem

#endif // !ANTHEM_CONFIG_H
