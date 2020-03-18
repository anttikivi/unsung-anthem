//===------------------------------- task.h ---------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file task.h
/// \brief The declaration of the type of the objects which hold the executable
/// tasks of the systems.
/// \author Antti Kivi
/// \date 13 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_TASK_H
#define ODE_FRAMEWORK_TASK_H

namespace ode
{
  ///
  /// \class task
  /// \brief The type of the objects which hold single game task as changes
  /// made during a single frame.
  ///
  class task final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c task.
    ///
    task() = default;

    ///
    /// \brief Constructs an object of the type \c task by copying the given
    /// object of the type \c task.
    ///
    /// \param a a \c task from which the new one is constructed.
    ///
    task(const task& a) = default;

    ///
    /// \brief Constructs an object of the type \c task by moving the given
    /// object of the type \c task.
    ///
    /// \param a a \c task from which the new one is constructed.
    ///
    task(task&& a) = default;

    ///
    /// \brief Destructs an object of the type \c task.
    ///
    ~task() = default;

    ///
    /// \brief Assigns the given object of the type \c task to this one by
    /// copying.
    ///
    /// \param a a \c task from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    task& operator=(const task& a) = default;

    ///
    /// \brief Assigns the given object of the type \c task to this one by
    /// moving.
    ///
    /// \param a a \c task from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    task& operator=(task&& a) = default;
  };

} // namespace ode

#endif // !ODE_FRAMEWORK_TASK_H
