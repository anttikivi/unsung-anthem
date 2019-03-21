//===--------------------------- pixel_count.h ------------------*- C++ -*-===//
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
/// \file pixel_count.h
/// \brief The declaration of the pixel count type.
/// \author Antti Kivi
/// \date 4 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_PIXEL_COUNT_H
#define ODE_PIXEL_COUNT_H

namespace ode
{
  ///
  /// \brief The type of the values which represent some number of pixels.
  ///
  using pixel_count = int;

} // namespace ode

///
/// \brief A \c pixel_count value representing an integer of pixels.
///
/// \param i an integer of pixels.
///
/// \return The \c pixel_count literal.
///
constexpr ode::pixel_count operator""_px(const unsigned long long i) noexcept
{
  return static_cast<ode::pixel_count>(i);
}

#endif // !ODE_PIXEL_COUNT_H
