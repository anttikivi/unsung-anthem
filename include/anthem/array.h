//===--------------------------- array.h ------------------------*- C++ -*-===//
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
/// \file array.h
/// \brief Declarations and definitions of the array-related standard
/// utilities.
/// \author Antti Kivi
/// \date 11 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_ARRAY_H
#define ANTHEM_ARRAY_H

#include <array>
#include <utility>

namespace anthem {
  namespace array {
    namespace detail {
      template <class T, std::size_t N, std::size_t... I>
      constexpr std::array<std::remove_cv_t<T>, N>
      to_array_impl(T (&a)[N], std::index_sequence<I...>) {
        return {{a[I]...}};
      }
    } // namespace detail

    ///
    /// \brief Creates a \c std::array from the built-in array \c a. The
    /// elements of the \c std::array are copy-initialized from the
    /// corresponding element of \c a.
    ///
    /// \tparam T the type of the array.
    /// \tparam N the number of the elements in the array.
    ///
    /// \param a the built-in array.
    ///
    /// \return an \c std::array object whose elements are copy-initialized
    /// from the corresponding element of \c a.
    ///
    template <class T, std::size_t N>
    constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N]) {
      return detail::to_array_impl(a, std::make_index_sequence<N>{});
    }
  } // namespace array
} // namespace anthem

#endif // !ANTHEM_ARRAY_H
