/// The declaration of the pixel number type.
/// \file
/// \author Antti Kivi
/// \date 4 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_PIXEL_T_H
#define ODE_PIXEL_T_H

namespace ode
{
  ///
  /// The type of the values which represent some number of pixels.
  ///
  using pixel_t = int;

  namespace literals
  {
    inline namespace number_literals
    {
      ///
      /// A \c pixel_t value representing an integer of pixels.
      ///
      /// \param i an integer of pixels.
      ///
      /// \return The \c pixel_t literal.
      ///
      constexpr ode::pixel_t operator""_px(const unsigned long long i) noexcept
      {
        return static_cast<ode::pixel_t>(i);
      }
    } // namespace number_literals
  } // namespace literals
} // namespace ode

#endif // !ODE_PIXEL_T_H
