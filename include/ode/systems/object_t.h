/// The declaration of the type templates of the objects of the systems.
/// \file
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_OBJECT_T_H
#define ODE_SYSTEMS_OBJECT_T_H

#include <memory>
#include <utility>

#include "ode/systems/object.h"

namespace ode
{
  ///
  /// The type of the objects which are the functional objects of the systems.
  ///
  class object_t final
  {
  public:
    ///
    /// Constructs an object of the type \c object_t.
    ///
    object_t() = default;

    ///
    /// Constructs an object of the type \c object_t.
    ///
    /// \tparam T the type of the object implementation.
    ///
    /// \param t the object implementation.
    ///
    template <typename T>
    object_t(T t) : obj_ptr{std::make_unique<T>(std::move(t))}
    {

    }

    ///
    /// Constructs an object of the type \c object_t by copying the given
    /// object of the type \c object_t.
    ///
    /// \param an \c object_t from which the new one is constructed.
    ///
    object_t(const object_t& a) = delete;

    ///
    /// Constructs an object of the type \c object_t by moving the given object
    /// of the type \c object_t.
    ///
    /// \param an \c object_t from which the new one is constructed.
    ///
    object_t(object_t&& a) = default;

    ///
    /// Destructs an object of the type \c object_t.
    ///
    ~object_t() = default;

    ///
    /// Assigns the given object of the type \c object_t to this one by
    /// copying.
    ///
    /// \param an \c object_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    object_t& operator=(const object_t& a) = delete;

    ///
    /// Assigns the given object of the type \c object_t to this one by moving.
    ///
    /// \param an \c object_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    object_t& operator=(object_t&& a) = default;

  private:
    ///
    /// A pointer to the contained object implementation.
    ///
    std::unique_ptr<object> obj_ptr;
  };
} // namespace ode

#endif // !ODE_SYSTEMS_OBJECT_T_H
