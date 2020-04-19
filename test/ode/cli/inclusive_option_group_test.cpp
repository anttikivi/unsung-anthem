/// The tests of the type of objects that contain information about groups of
// command line options where none of the options are exclusive.
/// \file
/// \author Antti Kivi
/// \date 16 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/inclusive_option_group.h"

#include <gtest/gtest.h>

TEST(ode_cli_inclusive_option_group, parse_group)
{
  ode::cli::inclusive_option_group group{
      {{"window-width",
        "w",
        "set the initial width of the window",
        1920,
        false},
       {"window-height",
        "h",
        "set the initial height of the window",
        1080,
        false},
       {"demo", "launch the game in demo mode", false, false},
       {"frame-rate", "force the given frame rate", 60, false},
       {"test-float",
        "f",
        "test the floating point number options with the specified value",
        13.0,
        true},
       {"window-name",
        "n",
        "use the given name for the game window",
        "no-name",
        false}}};
  ode::argv_t argv_0[] = {
      "exe",
      "-w",
      "300",
      "--test-float",
      "16.44",
      "--demo",
      "--frame-rate",
      "30",
      "--window-height",
      "800"};
  const auto args = group.parse_group(10, argv_0);
  ode::cli::arguments args_base{
      {{"window-width", 300},
       {"test-float", 16.44},
       {"demo", true},
       {"frame-rate", 30},
       {"window-height", 800},
       {"window-name", "no-name"}},
      {},
      {},
      {}};

  ASSERT_EQ(args, args_base);
}

TEST(ode_cli_inclusive_option_group, detect_if_required_not_given)
{
  ode::cli::inclusive_option_group group{
      {{"window-width",
        "w",
        "set the initial width of the window",
        1920,
        false},
       {"window-height",
        "h",
        "set the initial height of the window",
        1080,
        false},
       {"demo", "launch the game in demo mode", false, false},
       {"frame-rate", "force the given frame rate", 60, false},
       {"test-float",
        "f",
        "test the floating point number options with the specified value",
        13.0,
        true},
       {"window-name",
        "n",
        "use the given name for the game window",
        "no-name",
        false}}};
  ode::argv_t argv_0[] = {
      "exe",
      "-w",
      "300",
      "--demo",
      "--frame-rate",
      "30",
      "--window-height",
      "800"};
  const auto args = group.parse_group(8, argv_0);
  ode::cli::arguments args_base{
      {{"window-width", 300},
       {"demo", true},
       {"frame-rate", 30},
       {"window-height", 800},
       {"window-name", "no-name"}},
      {},
      {"test-float"},
      {}};

  ASSERT_EQ(args, args_base);
}

TEST(ode_cli_inclusive_option_group, disallow_doubles)
{
  ode::cli::inclusive_option_group group{
      {{"window-width",
        "w",
        "set the initial width of the window",
        1920,
        false},
       {"window-height",
        "h",
        "set the initial height of the window",
        1080,
        false},
       {"demo", "launch the game in demo mode", false, false},
       {"frame-rate", "force the given frame rate", 60, false},
       {"test-float",
        "f",
        "test the floating point number options with the specified value",
        13.0,
        true},
       {"window-name",
        "n",
        "use the given name for the game window",
        "no-name",
        false}}};
  ode::argv_t argv_0[] = {
      "exe",
      "-w",
      "300",
      "--test-float",
      "16.44",
      "--demo",
      "--frame-rate",
      "30",
      "--window-height",
      "800",
      "--window-width",
      "500"};
  const auto args = group.parse_group(12, argv_0);
  ode::cli::arguments args_base{
      {{"window-width", 300},
       {"test-float", 16.44},
       {"demo", true},
       {"frame-rate", 30},
       {"window-height", 800},
       {"window-name", "no-name"}},
      {},
      {},
      {}};

  ASSERT_EQ(args, args_base);
}
