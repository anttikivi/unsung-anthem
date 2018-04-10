//===-------------------------- logger_test.cpp -----------------*- C++ -*-===//
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
/// \file logger_test.cpp
/// \brief Tests of declarations of main logging functions of Obliging Ode.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/logger.h"

#include <gtest/gtest.h>

TEST(ode_logger_macro, trace)
{
  ASSERT_NO_THROW(
      ODE_TRACE("This is a test {}-level message in a macro", "trace"));
  ASSERT_NO_THROW(ODE_TRACE(1));
}

TEST(ode_logger_macro, debug)
{
  ASSERT_NO_THROW(
      ODE_DEBUG("This is a test {}-level message in a macro", "debug"));
  ASSERT_NO_THROW(ODE_DEBUG(2));
}

TEST(ode_logger_macro, info)
{
  ASSERT_NO_THROW(
      ODE_INFO("This is a test {}-level message in a macro", "info"));
  ASSERT_NO_THROW(ODE_INFO(3));
}

TEST(ode_logger_macro, warn)
{
  ASSERT_NO_THROW(
      ODE_WARN("This is a test {}-level message in a macro", "warning"));
  ASSERT_NO_THROW(ODE_WARN(4));
}

TEST(ode_logger_macro, error)
{
  ASSERT_NO_THROW(
      ODE_ERROR("This is a test {}-level message in a macro", "warning"));
  ASSERT_NO_THROW(ODE_ERROR(5));
}

TEST(ode_logger_macro, critical)
{
  ASSERT_NO_THROW(
      ODE_CRITICAL("This is a test {}-level message in a macro", "critical"));
  ASSERT_NO_THROW(ODE_CRITICAL(6));
}

TEST(ode_logger, trace)
{
  ASSERT_NO_THROW(
      ode::logging::trace("This is a test {}-level message", "trace"));
  ASSERT_NO_THROW(ode::logging::trace(1));
}

TEST(ode_logger, debug)
{
  ASSERT_NO_THROW(
      ode::logging::debug("This is a test {}-level message", "debug"));
  ASSERT_NO_THROW(ode::logging::debug(2));
}

TEST(ode_logger, info)
{
  ASSERT_NO_THROW(
      ode::logging::info("This is a test {}-level message", "info"));
  ASSERT_NO_THROW(ode::logging::info(3));
}

TEST(ode_logger, warn)
{
  ASSERT_NO_THROW(
      ode::logging::warn("This is a test {}-level message", "warning"));
  ASSERT_NO_THROW(ode::logging::warn(4));
}

TEST(ode_logger, error)
{
  ASSERT_NO_THROW(
      ode::logging::error("This is a test {}-level message", "warning"));
  ASSERT_NO_THROW(ode::logging::error(5));
}

TEST(ode_logger, critical)
{
  ASSERT_NO_THROW(
      ode::logging::critical("This is a test {}-level message", "critical"));
  ASSERT_NO_THROW(ode::logging::critical(6));
}
