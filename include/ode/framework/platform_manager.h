/// The declaration of the manager which holds platform-related utilities.
/// \file
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_FRAMEWORK_PLATFORM_MANAGER_H
#define ODE_FRAMEWORK_PLATFORM_MANAGER_H

#include "ode/__config"
#include "ode/framework/environment_manager.h"
#include "ode/systems/system_t.h"

namespace ode
{
  ///
  /// An enumeration type, the enumerators of which represent platforms on
  /// which the program can run.
  ///
  enum class platform
  {
    windows,
    macos,
    linux
  };

  ///
  /// The platform on which the program is currently running.
  ///
#if ODE_WINDOWS
  constexpr platform current_platform = platform::windows;
#elif ODE_MACOS
  constexpr platform current_platform = platform::macos;
#else
  constexpr platform current_platform = platform::linux;
#endif // !ODE_WINDOWS && !ODE_MACOS

  ///
  /// The type of the object which holds platform-related utilities.
  ///
  class platform_manager final
  {
  public:
    ///
    /// Constructs an object of the type \c platform_manager.
    ///
    platform_manager() = default;

    ///
    /// Constructs an object of the type \c platform_manager.
    ///
    /// \param is a pointer to the input system.
    ///
    platform_manager(system_t* is);

    ///
    /// Constructs an object of the type \c platform_manager by copying the
    /// given object of the type \c platform_manager.
    ///
    /// \param a a \c platform_manager from which the new one is constructed.
    ///
    platform_manager(const platform_manager& a) = default;

    ///
    /// Constructs an object of the type \c platform_manager by moving the
    /// given object of the type \c platform_manager.
    ///
    /// \param a a \c platform_manager from which the new one is constructed.
    ///
    platform_manager(platform_manager&& a) = default;

    ///
    /// Destructs an object of the type \c platform_manager.
    ///
    ~platform_manager() = default;

    ///
    /// Assigns the given object of the type \c platform_manager to this one by
    /// copying.
    ///
    /// \param a a \c platform_manager from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    platform_manager& operator=(const platform_manager& a) = default;

    ///
    /// Assigns the given object of the type \c platform_manager to this one by
    /// moving.
    ///
    /// \param a a \c platform_manager from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    platform_manager& operator=(platform_manager&& a) = default;

    ///
    /// Polls all of the current system events waiting and forwards them.
    ///
    /// Remarks: The reference to the environment manager which is passed to
    /// the function is not constant and, thus, modifies the original
    /// environment manager object.
    ///
    /// \param e a reference to the environment manager.
    ///
    void poll_events(environment_manager& env);

  private:
    ///
    /// A pointer to the input system.
    ///
    system_t* input_system;
  };

} // namespace ode

#endif // !ODE_FRAMEWORK_PLATFORM_MANAGER_H
