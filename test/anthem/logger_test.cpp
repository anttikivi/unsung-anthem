/// The tests of the main logging functions.
/// \file
/// \author Antti Kivi
/// \date 8 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/logger.h"

#include <gtest/gtest.h>

TEST(anthem_logger_macro, trace)
{
  ASSERT_NO_THROW(
      ANTHEM_TRACE("This is a test {}-level message in a macro", "trace"));
  ASSERT_NO_THROW(ANTHEM_TRACE(1));
}

TEST(anthem_logger_macro, debug)
{
  ASSERT_NO_THROW(
      ANTHEM_DEBUG("This is a test {}-level message in a macro", "debug"));
  ASSERT_NO_THROW(ANTHEM_DEBUG(2));
}

TEST(anthem_logger_macro, info)
{
  ASSERT_NO_THROW(
      ANTHEM_INFO("This is a test {}-level message in a macro", "info"));
  ASSERT_NO_THROW(ANTHEM_INFO(3));
}

TEST(anthem_logger_macro, warn)
{
  ASSERT_NO_THROW(
      ANTHEM_WARN("This is a test {}-level message in a macro", "warning"));
  ASSERT_NO_THROW(ANTHEM_WARN(4));
}

TEST(anthem_logger_macro, error)
{
  ASSERT_NO_THROW(
      ANTHEM_ERROR("This is a test {}-level message in a macro", "warning"));
  ASSERT_NO_THROW(ANTHEM_ERROR(5));
}

TEST(anthem_logger_macro, critical)
{
  ASSERT_NO_THROW(ANTHEM_CRITICAL(
      "This is a test {}-level message in a macro", "critical"));
  ASSERT_NO_THROW(ANTHEM_CRITICAL(6));
}

TEST(anthem_logger, trace)
{
  ASSERT_NO_THROW(
      anthem::logging::trace("This is a test {}-level message", "trace"));
  ASSERT_NO_THROW(anthem::logging::trace(1));
}

TEST(anthem_logger, debug)
{
  ASSERT_NO_THROW(
      anthem::logging::debug("This is a test {}-level message", "debug"));
  ASSERT_NO_THROW(anthem::logging::debug(2));
}

TEST(anthem_logger, info)
{
  ASSERT_NO_THROW(
      anthem::logging::info("This is a test {}-level message", "info"));
  ASSERT_NO_THROW(anthem::logging::info(3));
}

TEST(anthem_logger, warn)
{
  ASSERT_NO_THROW(
      anthem::logging::warn("This is a test {}-level message", "warning"));
  ASSERT_NO_THROW(anthem::logging::warn(4));
}

TEST(anthem_logger, error)
{
  ASSERT_NO_THROW(
      anthem::logging::error("This is a test {}-level message", "warning"));
  ASSERT_NO_THROW(anthem::logging::error(5));
}

TEST(anthem_logger, critical)
{
  ASSERT_NO_THROW(
      anthem::logging::critical("This is a test {}-level message", "critical"));
  ASSERT_NO_THROW(anthem::logging::critical(6));
}
