//===------------------------------- path.h ---------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file path.h
/// \brief The declarations and the definitions of the file system path values.
/// \author Antti Kivi
/// \date 11 February 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FILESYSTEM_PATH_H
#define ODE_FILESYSTEM_PATH_H

namespace ode::filesystem::path
{
  ///
  /// \brief The character which should be used as the path separator on the
  /// current system.
  ///
#if _WIN32
  // constexpr char preferred_separator = '\\';
  constexpr char preferred_separator = '/';
#else
  constexpr char preferred_separator = '/';
#endif // !_WIN32

} // namespace ode::filesystem::path

#endif // !ODE_FILESYSTEM_PATH_H
