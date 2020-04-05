/// The declarations of the type templates of the system scenes.
/// \file
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_SCENE_T_H
#define ODE_SYSTEMS_SCENE_T_H

#include <memory>
#include <utility>

#include "ode/systems/scene.h"

namespace ode
{
  ///
  /// The type of the objects which are the functional system scenes.
  ///
  class scene_t final
  {
  public:
    ///
    /// Constructs an object of the type \c scene_t.
    ///
    scene_t() = default;

    ///
    /// Constructs an object of the type \c scene_t.
    ///
    /// \tparam T the type of the scene implementation.
    ///
    /// \param t the scene implementation.
    ///
    template <typename T>
    scene_t(T t) : scene_ptr{std::make_unique<T>(std::move(t))}
    {

    }

    ///
    /// Constructs an object of the type \c scene_t by copying the given object
    /// of the type \c scene_t.
    ///
    /// \param a \c scene_t from which the new one is constructed.
    ///
    scene_t(const scene_t& a) = delete;

    ///
    /// Constructs an object of the type \c scene_t by moving the given object
    /// of the type \c scene_t.
    ///
    /// \param a \c scene_t from which the new one is constructed.
    ///
    scene_t(scene_t&& a) = default;

    ///
    /// Destructs an object of the type \c scene_t.
    ///
    ~scene_t() = default;

    ///
    /// Assigns the given object of the type \c scene_t to this one by copying.
    ///
    /// \param a \c scene_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_t& operator=(const scene_t& a) = delete;

    ///
    /// Assigns the given object of the type \c scene_t to this one by moving.
    ///
    /// \param a \c scene_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_t& operator=(scene_t&& a) = default;

  private:
    ///
    /// A pointer to the contained scene implementation.
    ///
    std::unique_ptr<scene> scene_ptr;
  };
} // namespace ode

#endif // !ODE_SCENE_T_H
