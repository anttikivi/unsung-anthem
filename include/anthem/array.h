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
/// \brief Declarations of array-related utilities which are not specified by
/// the C++ standard.
/// \author Antti Kivi
/// \date 15 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_ARRAY_H
#define ANTHEM_ARRAY_H

#include <array>

namespace anthem {
  namespace array {

    namespace details {

      template <typename T, typename O, std::size_t N>
      constexpr std::array<std::remove_cv_t<T>, N> change_type_impl(const std::array<O, N>& array) noexcept {

        std::array<std::remove_cv_t<T>, N> a{};

        for (int i = 0; i < N; ++i) {
          a[i] = T{array[i]};
        }

        return std::move(a);
      }
    } // namespace details

    template <typename T, typename O, std::size_t N>
    constexpr std::array<std::remove_cv_t<T>, N>
    change_type(const std::array<O, N>& array) noexcept {

      return detail::change_type_impl<T>(array);
    }

  } // namespace array
} // namespace anthem

#endif // !ANTHEM_ARRAY_H
