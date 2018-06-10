//===----------------------------- set_up.cpp -------------------*- C++ -*-===//
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
/// \file set_up.cpp
/// \brief The definitions of the common set up functions of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/set_up.h"

#include <stdexcept>

#include "ode/config.h"
#include "ode/logger.h"
#include "ode/filesystem/path.h"
#include "ode/framework/platform_manager.h"
#include "ode/gl/gl_config.h"

#include "ode/common/window.h"

#include "ode/logging_config.h"

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <glad/glad.h>

#include <gtest/gtest.h>

#include <spdlog/sinks/null_sink.h>

namespace ode::test
{
  namespace detail
  {
    void create_window()
    {
      SDL_GL_SetAttribute(
          SDL_GL_CONTEXT_PROFILE_MASK,
          SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, opengl_version_major);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, opengl_version_minor);
      SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
      // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#if ODE_OPENGL_SDL_ACCELERATED_VISUAL
      SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
#endif // ODE_OPENGL_SDL_ACCELERATED_VISUAL

      // MacOS only supports forward-compatible core contexts.
      if constexpr (ode::platform::macos == ode::current_platform)
      {
        SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_FLAGS,
            SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
      }

      ODE_TRACE(
          "Set the OpenGL version hint for the window to {}.{}",
          opengl_version_major,
          opengl_version_minor);

#if ODE_MACOS
      Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI;
#else
      Uint32 flags = SDL_WINDOW_OPENGL;
#endif // !ODE_MACOS

      test_window = SDL_CreateWindow(
          "info.window_name.data()",
          SDL_WINDOWPOS_CENTERED,
          SDL_WINDOWPOS_CENTERED,
          200,
          200,
          flags);

      if (!test_window)
      {
        const std::string error = std::string{SDL_GetError()};
        throw std::runtime_error{
            std::string{
                "The Simple DirectMedia Layer window creation failed, '"}
            + error
            + "'"};
      }
    }

    void create_gl_context(SDL_Window* window)
    {
      test_gl_context = SDL_GL_CreateContext(window);
      SDL_GL_SwapWindow(window);
      gladLoadGLLoader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress));
      SDL_GL_SetSwapInterval(opengl_swap_interval);
    }
  } // namespace detail

  int set_up(int argc, char* argv[])
  {
    if constexpr (::ode::test_use_null_sink)
    {
      auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();

      ode::logger = ode::create_logger(
          "ode_test_logger",
          ode::logger_pattern,
          ode::logger_level,
          null_sink);
    }
    else
    {
      ode::logger = ode::create_logger(
          "ode_test_logger",
          ode::logger_pattern,
          ode::logger_level);
    }

    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
      const std::string error = std::string{SDL_GetError()};
      throw std::runtime_error{
          std::string{"The Simple DirectMedia Layer initialization failed, '"}
          + error
          + "'"};
    }

    detail::create_window();
    detail::create_gl_context(test_window);

    ::testing::InitGoogleTest(&argc, argv);

#if ODE_TEST_BENCHMARKING

    ::benchmark::Initialize(&argc, argv);

    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
    {
      return 5;
    }

#endif // ODE_TEST_BENCHMARKING

    return 0;
  }
} // namespace ode::test
