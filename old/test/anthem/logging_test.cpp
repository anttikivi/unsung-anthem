//===----------------------- logging_test.cpp -------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file logging_test.cpp
/// \brief Tests of the logging-related utility functions.
/// \author Antti Kivi
/// \date 27 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "anthem/logger.h"

TEST_CASE("logging functions work", "[anthem::logging]")
{
  CHECK_NOTHROW(anthem::logging::trace("Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::debug("Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::info("Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::warn("Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::error("Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::critical("Hello, {}", "World"));

  CHECK_NOTHROW(anthem::logging::trace("Hello, World"));
  CHECK_NOTHROW(anthem::logging::debug("Hello, World"));
  CHECK_NOTHROW(anthem::logging::info("Hello, World"));
  CHECK_NOTHROW(anthem::logging::warn("Hello, World"));
  CHECK_NOTHROW(anthem::logging::error("Hello, World"));
  CHECK_NOTHROW(anthem::logging::critical("Hello, World"));

  const auto test_logger = anthem::create_logger("test_logger_2");

  CHECK_NOTHROW(anthem::logging::trace(test_logger, "Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::debug(test_logger, "Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::info(test_logger, "Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::warn(test_logger, "Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::error(test_logger, "Hello, {}", "World"));
  CHECK_NOTHROW(anthem::logging::critical(test_logger, "Hello, {}", "World"));

  CHECK_NOTHROW(anthem::logging::trace(test_logger, "Hello, World"));
  CHECK_NOTHROW(anthem::logging::debug(test_logger, "Hello, World"));
  CHECK_NOTHROW(anthem::logging::info(test_logger, "Hello, World"));
  CHECK_NOTHROW(anthem::logging::warn(test_logger, "Hello, World"));
  CHECK_NOTHROW(anthem::logging::error(test_logger, "Hello, World"));
  CHECK_NOTHROW(anthem::logging::critical(test_logger, "Hello, World"));
}
