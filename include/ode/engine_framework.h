//===------------------------- engine_framework.h ---------------*- C++ -*-===//
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
/// \file engine_framework.h
/// \brief The declaration of the main engine framework.
/// \author Antti Kivi
/// \date 6 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_ENGINE_FRAMEWORK_H
#define ODE_ENGINE_FRAMEWORK_H

#include <vector>

#include "ode/config.h"
#include "ode/initialize.h"
#include "ode/type_name.h"
#include "ode/framework/environment_manager.h"
#include "ode/framework/state_manager.h"
#include "ode/sdl/initialize_sdl.h"
#include "ode/systems/system_t.h"
#include "ode/systems/system_type.h"

#include <SDL2/SDL.h>

namespace ode
{
  ///
  /// \class engine_framework
  /// \brief The type of the object which contains the required frameworks of
  /// the application.
  ///
  /// \tparam A the type of the type of the application implementation.
  ///
  template <typename A> class engine_framework final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c engine_framework.
    ///
    engine_framework() = delete;

    ///
    /// \brief Constructs an object of the type \c engine_framework.
    ///
    /// \param i an object of the type \c execution_info which holds the
    /// startup data.
    ///
    engine_framework(const execution_info& i) : w{nullptr, nullptr}
    {
      ODE_DEBUG("Initializing the engine of the application");

      sdl::initialize();
      w = initialize_window(i);
      gl_context = initialize_graphics(w.get());
      env = {};
      scene_state = {};
      object_state = {};

      ODE_TRACE("Initializing the system container", ode_name);
      systems = std::vector<system_t>{};

      ODE_DEBUG("The engine of the application is initialized");
    }

    ///
    /// \brief Constructs an object of the type \c engine_framework by copying
    /// the given object of the type \c engine_framework.
    ///
    /// \param an \c engine_framework from which the new one is constructed.
    ///
    engine_framework(const engine_framework& a) = delete;

    ///
    /// \brief Constructs an object of the type \c engine_framework by moving
    /// the given object of the type \c engine_framework.
    ///
    /// \param an \c engine_framework from which the new one is constructed.
    ///
    engine_framework(engine_framework&& a) = default;

    ///
    /// \brief Destructs an object of the type \c engine_framework.
    ///
    ~engine_framework()
    {
      SDL_GL_DeleteContext(gl_context);

      w.reset(nullptr);

      SDL_Quit();
      ODE_DEBUG("Simple DirectMedia Layer is terminated");
    }

    ///
    /// \brief Assigns the given object of the type \c engine_framework to this
    /// one by copying.
    ///
    /// \param a an \c engine_framework from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    engine_framework& operator=(const engine_framework& a) = delete;

    ///
    /// \brief Assigns the given object of the type \c engine_framework to this
    /// one by moving.
    ///
    /// \param a an \c engine_framework from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    engine_framework& operator=(engine_framework&& a) = default;

    ///
    /// \brief Initializes a system.
    ///
    /// \tparam T the type of the system object.
    /// \tparam Args the types of arguments to be passed to the system in
    /// construction.
    ///
    /// \param args arguments to be passed to the system in construction.
    ///
    template <typename T, typename... Args>
    void initialize_system(Args&&... args)
    {
      ODE_DEBUG(
          "Initializing system of type {} with system type {}",
          type_name<T>(),
          T::type);
      systems.emplace_back(args...);
    }

    ///
    /// \brief Gives a pointer to the window of the application.
    ///
    /// Remarks: The pointer returned by this function is not constant.
    ///
    /// \return A pointer to the window.
    ///
    inline window_ptr_t window()
    {
      return w.get();
    }

    ///
    /// \brief Gives a reference to the environment manager of the application.
    ///
    /// Remarks: The reference returned by this function is not constant.
    ///
    /// \return A reference to the environment manager.
    ///
    inline environment_manager& environment()
    {
      return env;
    }

  private:
    ///
    /// \brief The application implementation object.
    ///
    A app;

    ///
    /// \brief A pointer to the main window of the application.
    ///
    window_t w;

    ///
    /// \brief The object representing the OpenGL context.
    ///
    SDL_GLContext gl_context;

    ///
    /// \brief The environment manager.
    ///
    environment_manager env;

    ///
    /// \brief The state manager which distributes the scene-level changes.
    ///
    state_manager scene_state;

    ///
    /// \brief The state manager which distributes the object-level changes.
    ///
    state_manager object_state;

    ///
    /// \brief The systems.
    ///
    std::vector<system_t> systems;
  };

  ///
  /// \brief Initializes the engine framework and the components related to it.
  ///
  /// \tparam A the type of the type of the application implementation.
  ///
  /// \param i an object of the type \c execution_info which holds the startup
  /// data.
  ///
  /// \return An object of the type \c engine_framework.
  ///
  template <typename A> auto create_engine(const execution_info& i)
  {
    initialize_logging();
    return engine_framework<A>{i};
  }

} // namespace ode

#endif // !ODE_FRAMEWORK_ENGINE_FRAMEWORK_H
