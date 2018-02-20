//===------------------------------- path.h ---------------------*- C++ -*-===//
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
/// \file path.h
/// \brief The declarations and the definitions of the file system path values.
/// \author Antti Kivi
/// \date 11 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FILESYSTEM_PATH_H
#define ODE_FILESYSTEM_PATH_H

namespace ode::filesystem::path
{
  ///
  /// \brief The character which should be used as path separator on the
  /// current system.
  ///
#if _WIN32
  constexpr char preferred_separator = '\\';
#else
  constexpr char preferred_separator = '/';
#endif // !_WIN32

  ///
  /// \brief Creates a path for the current system.
  ///
  /// \param source the path with 
  // std::string path(const std::string& source);

} // namespace ode::filesystem::path

#endif // !ODE_FILESYSTEM_PATH_H
