//===--------------------------- pixel_count.h ------------------*- C++ -*-===//
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
/// \file pixel_count.h
/// \brief Declaration of the pixel count type.
/// \author Antti Kivi
/// \date 4 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_PIXEL_COUNT_H
#define ODE_PIXEL_COUNT_H

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

#endif // !ODE_PIXEL_COUNT_H
