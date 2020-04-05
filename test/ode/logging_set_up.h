/// The declarations of the set up functions for the tests and benchmarks of
/// the logging functions.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/logging.h"

ode::logger_t create_logging_test_logger();

inline auto test_log = create_logging_test_logger();

ode::logger_t create_logging_benchmark_logger();

inline auto benchmark_log = create_logging_benchmark_logger();
