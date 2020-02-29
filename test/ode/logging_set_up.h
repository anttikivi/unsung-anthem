//===-------------------------- logging_set_up.h ----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file logging_set_up.h
/// \brief The declarations of the set up functions for the tests and
/// benchmarks of the logging functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/logging.h"

ode::logger_t create_logging_test_logger();

inline auto test_log = create_logging_test_logger();

ode::logger_t create_logging_benchmark_logger();

inline auto benchmark_log = create_logging_benchmark_logger();
