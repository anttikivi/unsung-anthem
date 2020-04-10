/// The declarations of the type templates of the command line option groups.
/// \file
/// \author Antti Kivi
/// \date 10 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CLI_OPTION_GROUP_T_H
#define ODE_CLI_OPTION_GROUP_T_H

#include <memory>

#include "ode/cli/option_group.h"

namespace ode::cli
{
  ///
  /// The type of the objects which hold the command line option groups.
  ///
  class option_group_t final
  {
  public:
    ///
    /// Constructs an object of the type \c option_group_t.
    ///
    option_group_t() = default;

    ///
    /// Constructs an object of the type \c option_group_t.
    ///
    /// \tparam T the type of the option_group implementation.
    ///
    /// \param t the option_group implementation.
    ///
    template <typename T>
    option_group_t(T t) : option_group_ptr{std::make_unique<T>(std::move(t))}
    {

    }

    ///
    /// Constructs an object of the type \c option_group_t by copying the given
    /// object of the type \c option_group_t.
    ///
    /// \param a \c option_group_t from which the new one is constructed.
    ///
    option_group_t(const option_group_t& a) = delete;

    ///
    /// Constructs an object of the type \c option_group_t by moving the given
    /// object of the type \c option_group_t.
    ///
    /// \param a \c option_group_t from which the new one is constructed.
    ///
    option_group_t(option_group_t&& a) = default;

    ///
    /// Destructs an object of the type \c option_group_t.
    ///
    ~option_group_t() = default;

    ///
    /// Assigns the given object of the type \c option_group_t to this one by
    /// copying.
    ///
    /// \param a \c option_group_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option_group_t& operator=(const option_group_t& a) = delete;

    ///
    /// Assigns the given object of the type \c option_group_t to this one by
    /// moving.
    ///
    /// \param a \c option_group_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    option_group_t& operator=(option_group_t&& a) = default;

  private:
    ///
    /// A pointer to the contained option_group implementation.
    ///
    std::unique_ptr<option_group> option_group_ptr;
  };
} // namespace ode::cli

#endif // !ODE_CLI_OPTION_GROUP_T_H
