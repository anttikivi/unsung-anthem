/// The declarations and definitions of miscellaneous constants.
/// \file
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ANTHEM_CONFIG_H
#define ANTHEM_CONFIG_H

namespace anthem
{
  ///
  /// The name of the product.
  ///
#ifdef ANTHEM_PRODUCT_NAME
  constexpr auto anthem_name = ANTHEM_PRODUCT_NAME;
#else
  constexpr auto anthem_name = "anthem";
#endif // !defined(ANTHEM_PRODUCT_NAME)

  ///
  /// The version of the product.
  ///
#ifdef ANTHEM_VERSION
  constexpr auto anthem_version = ANTHEM_VERSION;
#else
  constexpr auto anthem_version = "invalid-version";
#endif // !defined(ANTHEM_VERSION)

  ///
  /// The root directory of the game scripts.
  ///
#ifdef ANTHEM_SCRIPT_ROOT
  constexpr auto script_root = ANTHEM_SCRIPT_ROOT;
#else
  constexpr auto script_root = "lib/anthem";
#endif // !defined(ANTHEM_SCRIPT_ROOT)

  ///
  /// The root directory of the test scripts.
  ///
#ifdef ANTHEM_TEST_SCRIPT_ROOT
  constexpr auto test_script_root = ANTHEM_TEST_SCRIPT_ROOT;
#else
  constexpr auto test_script_root = "lib/anthem";
#endif // !defined(ANTHEM_TEST_SCRIPT_ROOT)

} // namespace anthem

#endif // !ANTHEM_CONFIG_H
