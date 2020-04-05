/// The declaration of the pixel count type.
/// \file
/// \author Antti Kivi
/// \date 4 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_PIXEL_COUNT_H
#define ODE_PIXEL_COUNT_H

namespace ode
{
  ///
  /// The type of the values which represent some number of pixels.
  ///
  using pixel_count = int;

} // namespace ode

///
/// A \c pixel_count value representing an integer of pixels.
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
