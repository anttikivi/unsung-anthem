/// The declaration of the manager which holds execution-related information
/// and utilities.
/// \file
/// \author Antti Kivi
/// \date 12 May 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_FRAMEWORK_ENVIRONMENT_MANAGER_H
#define ODE_FRAMEWORK_ENVIRONMENT_MANAGER_H

namespace ode
{
  ///
  /// The type of the object which holds execution-related information and
  /// utilities.
  ///
  class environment_manager final
  {
  public:
    ///
    /// Constructs an object of the type \c environment_manager.
    ///
    environment_manager();

    ///
    /// Constructs an object of the type \c environment_manager by copying the
    /// given object of the type \c environment_manager.
    ///
    /// \param a an \c environment_manager from which the new one is
    /// constructed.
    ///
    environment_manager(const environment_manager& a) = delete;

    ///
    /// Constructs an object of the type \c environment_manager by moving the
    /// given object of the type \c environment_manager.
    ///
    /// \param a an \c environment_manager from which the new one is
    /// constructed.
    ///
    environment_manager(environment_manager&& a) = default;

    ///
    /// Destructs an object of the type \c environment_manager.
    ///
    ~environment_manager() = default;

    ///
    /// Assigns the given object of the type \c environment_manager to this one
    /// by copying.
    ///
    /// \param a an \c environment_manager from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    environment_manager& operator=(const environment_manager& a) = delete;

    ///
    /// Assigns the given object of the type \c environment_manager to this one
    /// by moving.
    ///
    /// \param a an \c environment_manager from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    environment_manager& operator=(environment_manager&& a) = default;

    ///
    /// Marks the environment to quit execution.
    ///
    void schedule_termination();

    ///
    /// Tells whether or not the program should continue its execution.
    ///
    /// \return A \c bool.
    ///
    inline bool should_execute() const noexcept
    {
      return execute;
    }

  private:
    ///
    /// Whether or not the execution of the program should continue.
    ///
    bool execute;
  };

} // namespace ode

#endif // !ODE_FRAMEWORK_ENVIRONMENT_MANAGER_H
