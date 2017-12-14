//===--------------------------- types.h ------------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file types.h
/// \brief The declarations of various helper types.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_TYPES_H
#define ANTHEM_TYPES_H

namespace anthem
{
  ///
  /// \brief Type of values which represent some number of pixels.
  ///
  typedef int pixel_count;

} // namespace anthem

///
/// \brief A \c pixel value representing an integer of pixels.
///
/// \param i integer of pixels.
///
/// \return The \c pixel literal.
///
constexpr anthem::pixel_count
operator""_px(const unsigned long long i) noexcept
{
  return static_cast<anthem::pixel_count>(i);
}

#endif // !ANTHEM_TYPES_H
