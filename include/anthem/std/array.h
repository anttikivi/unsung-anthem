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

#ifndef ANTHEM_ARRAY_H
#define ANTHEM_ARRAY_H

#include <array>

#include "anthem/macro_config.h"

#if defined(CPP11)

# include "anthem/std/utility.h"
# include "anthem/std/type_traits.h"

#endif // defined(CPP11)

namespace anthem {

  //////////////////////////////////////////////////////////////////////////////
  // C++ Extensions for Library Fundamentals, Version 2 ////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // 9.2.2 array creation functions [container.array.creation] /////////////////
  //////////////////////////////////////////////////////////////////////////////

  namespace detail {

#if defined(CPP11)

    template <class T, std::size_t N, std::size_t... I>
    constexpr const std::array<remove_cv_t<T>, N>
    to_array_impl(T (&a)[N], index_sequence<I...>) {
      return {{a[I]...}};
    }

#else

    template <class T, std::size_t N, std::size_t... I>
    constexpr const std::array<std::remove_cv_t<T>, N>
    to_array_impl(T (&a)[N], std::index_sequence<I...>) {
      return {{a[I]...}};
    }

#endif // !defined(CPP11)

  } // namespace detail

#if defined(CPP11)

  template <class T, std::size_t N>
  constexpr const std::array<remove_cv_t<T>, N> to_array(T (&a)[N]) {
    return detail::to_array_impl(a, make_index_sequence<N>{});
  }

#else

  template <class T, std::size_t N>
  constexpr const std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N]) {
    return detail::to_array_impl(a, std::make_index_sequence<N>{});
  }

#endif // !defined(CPP11)

} // namespace anthem

#endif // !ANTHEM_ARRAY_H
