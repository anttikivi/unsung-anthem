/// The declarations and the definitions of the file system path values.
/// \file
/// \author Antti Kivi
/// \date 11 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_FILESYSTEM_PATH_H
#define ODE_FILESYSTEM_PATH_H

namespace ode::filesystem::path
{
  ///
  /// The character which should be used as the path separator on the current
  /// system.
  ///
#if _WIN32
  constexpr char preferred_separator = '\\';
#else
  constexpr char preferred_separator = '/';
#endif // !_WIN32

} // namespace ode::filesystem::path

#endif // !ODE_FILESYSTEM_PATH_H
