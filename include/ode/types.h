//===------------------------------ types.h ---------------------*- C++ -*-===//
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
/// \file types.h
/// \brief The declarations of various helper types.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_TYPES_H
#define ODE_TYPES_H

namespace ode
{
  ///
  /// \brief Type of values which represent some number of pixels.
  ///
  using pixel_count = int;

} // namespace ode

///
/// \brief A \c pixel value representing an integer of pixels.
///
/// \param i integer of pixels.
///
/// \return The \c pixel literal.
///
constexpr ode::pixel_count operator""_px(const unsigned long long i) noexcept
{
  return static_cast<ode::pixel_count>(i);
}

#endif // !ODE_TYPES_H
