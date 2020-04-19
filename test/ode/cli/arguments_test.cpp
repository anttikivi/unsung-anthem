/// The tests for the type of objects which contain parsed command line
/// arguments.
/// \file
/// \author Antti Kivi
/// \date 19 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/arguments.h"

#include <gtest/gtest.h>

TEST(ode_cli_arguments, merge)
{
  ode::cli::arguments args_0{
      {{"window-width", 256}, {"window-height", 100}, {"developer-mode", true}},
      {},
      {"this-was-required", "so-was-this"},
      {"--this-is-not-valid", "why-was-this-argument-given"}};
  ode::cli::arguments arg_1{
      {{"window-name", "Obliging Ode"}, {"developer-mode", false}},
      {},
      {"this-was-required", "this-was-needed"},
      {"--this-is-not-valid", "wrong_argument"}};
  ode::cli::arguments arg_result{
      {{"window-width", 256},
       {"window-height", 100},
       {"developer-mode", false},
       {"window-name", "Obliging Ode"}},
      {},
      {"this-was-required", "so-was-this", "this-was-needed"},
      {"--this-is-not-valid", "why-was-this-argument-given", "wrong_argument"}};
  ASSERT_EQ(ode::cli::merge(args_0, arg_1), arg_result);
}
