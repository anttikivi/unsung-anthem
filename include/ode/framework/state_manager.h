//===-------------------------- state_manager.h -----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file state_manager.h
/// \brief The declaration of the managers which hold the game state.
/// \author Antti Kivi
/// \date 4 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_STATE_MANAGER_H
#define ODE_FRAMEWORK_STATE_MANAGER_H

#include "ode/framework/state.h"

namespace ode
{
  ///
  /// \class state_manager
  /// \brief The type of the objects which are responsible for distributing the
  /// changes in the state.
  ///
  class state_manager final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c state_manager.
    ///
    state_manager() = default;

    ///
    /// \brief Constructs an object of the type \c state_manager by copying the
    /// given object of the type \c state_manager.
    ///
    /// \param a a \c state_manager from which the new one is constructed.
    ///
    state_manager(const state_manager& a) = default;

    ///
    /// \brief Constructs an object of the type \c state_manager by moving the
    /// given object of the type \c state_manager.
    ///
    /// \param a a \c state_manager from which the new one is constructed.
    ///
    state_manager(state_manager&& a) = default;

    ///
    /// \brief Destructs an object of the type \c state_manager.
    ///
    ~state_manager() = default;

    ///
    /// \brief Assigns the given object of the type \c state_manager to this
    /// one by copying.
    ///
    /// \param a a \c state_manager from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    state_manager& operator=(const state_manager& a) = default;

    ///
    /// \brief Assigns the given object of the type \c state_manager to this
    /// one by moving.
    ///
    /// \param a a \c state_manager from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    state_manager& operator=(state_manager&& a) = default;

    ///
    /// \brief Distributes the changes contained in the given state to the
    /// objects of this state manager.
    ///
    /// \param s the state, the changes of which are distributed.
    ///
    void distribute_state(const state& s)
    {
      // TODO
    }
  };

} // namespace ode

#endif // !ODE_FRAMEWORK_STATE_MANAGER_H
