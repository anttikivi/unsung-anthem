//===----------------------- environment_manager.h --------------*- C++ -*-===//
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
/// \file environment_manager.h
/// \brief The declaration of the manager which holds execution-related
/// information and utilities.
/// \author Antti Kivi
/// \date 12 May 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_ENVIRONMENT_MANAGER_H
#define ODE_FRAMEWORK_ENVIRONMENT_MANAGER_H

namespace ode
{
  ///
  /// \class environment_manager
  /// \brief The type of the object which holds execution-related information
  /// and utilities.
  ///
  class environment_manager final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c environment_manager.
    ///
    environment_manager();

    ///
    /// \brief Constructs an object of the type \c environment_manager by
    /// copying the given object of the type \c environment_manager.
    ///
    /// \param an \c environment_manager from which the new one is constructed.
    ///
    environment_manager(const environment_manager& a) = default;

    ///
    /// \brief Constructs an object of the type \c environment_manager by
    /// moving the given object of the type \c environment_manager.
    ///
    /// \param an \c environment_manager from which the new one is constructed.
    ///
    environment_manager(environment_manager&& a) = default;

    ///
    /// \brief Destructs an object of the type \c environment_manager.
    ///
    ~environment_manager() = default;

    ///
    /// \brief Assigns the given object of the type \c environment_manager to
    /// this one by copying.
    ///
    /// \param a an \c environment_manager from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    environment_manager& operator=(const environment_manager& a) = default;

    ///
    /// \brief Assigns the given object of the type \c environment_manager to
    /// this one by moving.
    ///
    /// \param a an \c environment_manager from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    environment_manager& operator=(environment_manager&& a) = default;

    ///
    /// \brief Marks the environment to quit execution.
    ///
    void schedule_termination();

    ///
    /// \brief Tells whether or not the program should continue its execution.
    ///
    /// \return A \c bool.
    ///
    inline bool should_execute() const noexcept
    {
      return execute;
    }

  private:
    ///
    /// \brief Whether or not the execution of the program should continue.
    ///
    bool execute;
  };

} // namespace ode

#endif // !ODE_FRAMEWORK_ENVIRONMENT_MANAGER_H
