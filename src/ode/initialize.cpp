//===--------------------------- initialize.cpp -----------------*- C++ -*-===//
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
/// \file initialize.cpp
/// \brief The definitions of the initialization functions.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/initialize.h"

#include "ode/config.h"

#include "ode/logging_config.h"
#include "ode/sdl/window.h"

namespace ode
{
  void initialize_logging()
  {
    logger = create_logger(logger_name, logger_pattern, logger_level);

    ODE_INFO("The main logger of {} is created", ode_name);
    ODE_DEBUG(
        "The logger has the name '{}', the pattern '{}', and the level '{}'",
        logger_name,
        logger_pattern,
        logger_level);
  }

  window_t initialize_window(const execution_info& info)
  {
    window_t window = sdl::create_window({
        info.window_width,
        info.window_height,
        info.window_name});

    ODE_DEBUG("The main window of {} is created", ode_name);

    return window;
  }

} // namespace ode
