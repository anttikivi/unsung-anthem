//===-------------------------- optional.h ----------------------*- C++ -*-===//
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
/// \file optional.h
/// \brief Declaration of an alias for the type \c std::optional.
/// \author Antti Kivi
/// \date 30 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_STD_OPTIONAL_H
#define ANTHEM_STD_OPTIONAL_H

#include "anthem/__config.h"

#if CXX17
# include <optional>
#elif CXX14
# include <experimental/optional>
#endif

namespace anthem {

  ///
  /// \brief Alias of class template of optional objects.
  ///
  /// The alias should be used for compatibility between different C++ standard
  /// versions.
  ///
#if CXX17
  template <typename T> using optional = std::optional<T>;
#elif CXX14
  template <typename T> using optional = std::experimental::optional<T>;
#endif

} // namespace anthem

#endif // !ANTHEM_STD_OPTIONAL_H
