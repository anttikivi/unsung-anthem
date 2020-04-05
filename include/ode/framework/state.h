/// The declaration of the type of the objects representing a single state.
/// \file
/// \author Antti Kivi
/// \date 12 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_FRAMEWORK_STATE_H
#define ODE_FRAMEWORK_STATE_H

namespace ode
{
  ///
  /// The type of the objects which hold single game state as changes made
  /// during a single frame.
  ///
  class state final
  {
  public:
    ///
    /// Constructs an object of the type \c state.
    ///
    state() = default;

    ///
    /// Constructs an object of the type \c state by copying the given object
    /// of the type \c state.
    ///
    /// \param a a \c state from which the new one is constructed.
    ///
    state(const state& a) = default;

    ///
    /// Constructs an object of the type \c state by moving the given object of
    /// the type \c state.
    ///
    /// \param a a \c state from which the new one is constructed.
    ///
    state(state&& a) = default;

    ///
    /// Destructs an object of the type \c state.
    ///
    ~state() = default;

    ///
    /// Assigns the given object of the type \c state to this one by copying.
    ///
    /// \param a a \c state from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    state& operator=(const state& a) = default;

    ///
    /// Assigns the given object of the type \c state to this one by moving.
    ///
    /// \param a a \c state from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    state& operator=(state&& a) = default;
  };

} // namespace ode

#endif // !ODE_FRAMEWORK_STATE_H
