/// The declaration of the main engine framework.
/// \file
/// \author Antti Kivi
/// \date 6 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_ENGINE_FRAMEWORK_H
#define ODE_ENGINE_FRAMEWORK_H

#include <algorithm>
#include <iterator>
#include <utility>

#include <SDL2/SDL.h>

#include "ode/application.h"
#include "ode/config.h"
#include "ode/framework/platform_manager.h"
#include "ode/framework/state_manager.h"
#include "ode/initialize.h"
#include "ode/sdl/initialize_sdl.h"
#include "ode/type_name.h"

namespace ode
{
  ///
  /// The type of the object which contains the required frameworks of the
  /// application.
  ///
  /// \tparam A the type of the type of the application implementation.
  ///
#if ODE_CONCEPTS
  template <application A> class engine_framework final
#else
  template <typename A> class engine_framework final
#endif // !ODE_CONCEPTS
  {
  public:
    ///
    /// Constructs an object of the type \c engine_framework.
    ///
    engine_framework() = delete;

    ///
    /// Constructs an object of the type \c engine_framework.
    ///
    /// \param a the application.
    /// \param i an object of the type \c execution_info which holds the
    /// startup data.
    ///
    engine_framework(A&& a, const execution_info& i)
        : app{std::forward<A>(a)}, w{nullptr, nullptr}
    {
#if !ODE_CONCEPTS

      static_assert(
          is_application_v<A>,
          "The template argument passed to the engine is not a valid "
          "application type");

#endif // !ODE_CONCEPTS

      ODE_DEBUG("Initializing the engine of the application");

      sdl::initialize();
      w = initialize_window(i);
      gl_context = initialize_graphics(w.get());

      ODE_TRACE("Initializing the system container", ode_name);
      systems = std::vector<system_t>{};

      ODE_TRACE("Initializing the graphics system");

      auto gs = app.make_system(system_type::graphics);
      system_t& gs_ref = add_system(std::move(gs));

      ODE_TRACE("Initializing the input system");

      auto is = app.make_system(system_type::input);
      system_t& is_ref = add_system(std::move(is));

      ODE_TRACE("Initializing the other systems");

      auto os = app.make_other_systems();

      if (!os.empty())
      {
        std::move(os.begin(), os.end(), std::back_inserter(systems));
      }

      pfm = {&is};
      envm = {};
      sm = {};

      ODE_DEBUG("The engine of the application is initialized");
    }

    ///
    /// Constructs an object of the type \c engine_framework by copying the
    /// given object of the type \c engine_framework.
    ///
    /// \param an \c engine_framework from which the new one is constructed.
    ///
    engine_framework(const engine_framework& a) = delete;

    ///
    /// Constructs an object of the type \c engine_framework by moving the
    /// given object of the type \c engine_framework.
    ///
    /// \param an \c engine_framework from which the new one is constructed.
    ///
    engine_framework(engine_framework&& a) = default;

    ///
    /// Destructs an object of the type \c engine_framework.
    ///
    ~engine_framework()
    {
      SDL_GL_DeleteContext(gl_context);

      w.reset(nullptr);

      SDL_Quit();
      ODE_DEBUG("Simple DirectMedia Layer is terminated");
    }

    ///
    /// Assigns the given object of the type \c engine_framework to this one by
    /// copying.
    ///
    /// \param a an \c engine_framework from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    engine_framework& operator=(const engine_framework& a) = delete;

    ///
    /// Assigns the given object of the type \c engine_framework to this one by
    /// moving.
    ///
    /// \param a an \c engine_framework from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    engine_framework& operator=(engine_framework&& a) = default;

    ///
    /// Adds a system to the engine container.
    ///
    /// \param sys the system object.
    ///
    /// \return A reference to the added system.
    ///
    system_t& add_system(system_t&& sys)
    {
      ODE_DEBUG("Adding a system");
      systems.push_back(std::forward<system_t>(sys));
      return systems.back();
    }

    ///
    /// Gives a reference to the application.
    ///
    /// Remarks: The reference returned by this function is not constant.
    ///
    /// \return A reference to the application.
    ///
    inline A& application()
    {
      return app;
    }

    ///
    /// Gives a pointer to the window of the application.
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
    /// Gives a reference to the platform manager of the application.
    ///
    /// Remarks: The reference returned by this function is not constant.
    ///
    /// \return A reference to the platform manager.
    ///
    inline platform_manager& platform()
    {
      return pfm;
    }

    ///
    /// Gives a reference to the environment manager of the application.
    ///
    /// Remarks: The reference returned by this function is not constant.
    ///
    /// \return A reference to the environment manager.
    ///
    inline environment_manager& environment()
    {
      return envm;
    }

    ///
    /// Gives a reference to the scene state manager of the application.
    ///
    /// Remarks: The reference returned by this function is not constant.
    ///
    /// \return A reference to the scene state manager.
    ///
    inline state_manager& state()
    {
      return sm;
    }

  private:
    ///
    /// The application implementation object.
    ///
    A app;

    ///
    /// A pointer to the main window of the application.
    ///
    window_t w;

    ///
    /// The object representing the OpenGL context.
    ///
    SDL_GLContext gl_context;

    ///
    /// The systems.
    ///
    std::vector<system_t> systems;

    ///
    /// The platform manager.
    ///
    platform_manager pfm;

    ///
    /// The environment manager.
    ///
    environment_manager envm;

    ///
    /// The state manager which distributes the state changes.
    ///
    state_manager sm;
  };

  ///
  /// Initializes the engine framework and the components related to it.
  ///
  /// \tparam A the type of the type of the application implementation.
  ///
  /// \param a the application.
  /// \param i an object of the type \c execution_info which holds the startup
  /// data.
  ///
  /// \return An object of the type \c engine_framework.
  ///
#if ODE_CONCEPTS
  template <application A> auto make_engine(A&& a, const execution_info& i)
#else
  template <typename A> auto make_engine(A&& a, const execution_info& i)
#endif // !ODE_CONCEPTS
  {
#if !ODE_CONCEPTS

    static_assert(
        is_application_v<A>,
        "The template argument passed to the engine creation is not a valid "
        "application type");

#endif // !ODE_CONCEPTS

    initialize_logging();
    return engine_framework{std::forward<A>(a), i};
  }

} // namespace ode

#endif // !ODE_FRAMEWORK_ENGINE_FRAMEWORK_H
