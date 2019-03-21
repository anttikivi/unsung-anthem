//===------------------------------ state.h ---------------------*- C++ -*-===//
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
/// \file state.h
/// \brief The declaration of the type of the objects representing a single
/// state.
/// \author Antti Kivi
/// \date 12 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_STATE_H
#define ODE_FRAMEWORK_STATE_H

namespace ode
{
  ///
  /// \class state
  /// \brief The type of the objects which hold single game state as changes
  /// made during a single frame.
  ///
  class state final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c state.
    ///
    state() = default;

    ///
    /// \brief Constructs an object of the type \c state by copying the given
    /// object of the type \c state.
    ///
    /// \param a a \c state from which the new one is constructed.
    ///
    state(const state& a) = default;

    ///
    /// \brief Constructs an object of the type \c state by moving the given
    /// object of the type \c state.
    ///
    /// \param a a \c state from which the new one is constructed.
    ///
    state(state&& a) = default;

    ///
    /// \brief Destructs an object of the type \c state.
    ///
    ~state() = default;

    ///
    /// \brief Assigns the given object of the type \c state to this one by
    /// copying.
    ///
    /// \param a a \c state from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    state& operator=(const state& a) = default;

    ///
    /// \brief Assigns the given object of the type \c state to this one by
    /// moving.
    ///
    /// \param a a \c state from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    state& operator=(state&& a) = default;
  };

} // namespace ode

#endif // !ODE_FRAMEWORK_STATE_H
