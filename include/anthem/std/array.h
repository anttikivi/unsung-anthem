//===--- array.h ------------------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file array.h
/// \brief Implementations of some standard C++ array-related declarations
/// which are not supported by older C++ standard versions or which are not
/// part of the C++ standard but are specified in technical specifications.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_STD_ARRAY_H
#define ANTHEM_STD_ARRAY_H

#include <array>
#include <utility>

#include "anthem/macro_config.h"

namespace anthem {

  //////////////////////////////////////////////////////////////////////////////
  // C++ Extensions for Library Fundamentals, Version 2 ////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // 9.2.2 array creation functions [container.array.creation] /////////////////
  //////////////////////////////////////////////////////////////////////////////

  namespace detail {

    template <class T, std::size_t N, std::size_t... I>
    constexpr const std::array<std::remove_cv_t<T>, N>
    to_array_impl(T (&a)[N], std::index_sequence<I...> seq) {
      return {{a[I]...}};
    }

  } // namespace detail

  ///
  /// \brief Returns object of class \c std::array, the contents of which are
  /// exact copies of the contents of passed array.
  ///
  /// \param a array, the contents of which are copied.
  /// \return Constant object of class \c std::array<std::remove_cv_t<T>, N>.
  ///
  template <class T, std::size_t N>
  constexpr const std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N]) {
    return detail::to_array_impl(a, std::make_index_sequence<N>{});
  }

} // namespace anthem

#endif // !ANTHEM_STD_ARRAY_H
