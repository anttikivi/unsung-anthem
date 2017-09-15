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
#include <functional>
#include <type_traits>
#include <utility>

#if ANTHEM_CXX14
# include "anthem/type_traits.h"
#endif // ANTHEM_CXX14

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
    constexpr std::array<std::remove_cv_t<T>, N> to_array(T (&a)[N]) noexcept {
      return detail::to_array_impl(a, std::make_index_sequence<N>{});
    }

    namespace detail {
      template<class T> struct is_ref_wrapper : std::false_type {

      };

      template<class T>
      struct is_ref_wrapper<std::reference_wrapper<T>> : std::true_type {

      };
     
#if !ANTHEM_CXX14

      template<class T>
      using not_ref_wrapper = std::negation<is_ref_wrapper<std::decay_t<T>>>;

#else

      template<class T>
      using not_ref_wrapper = util::negation<is_ref_wrapper<std::decay_t<T>>>;

#endif // ANTHEM_CXX14
     
      template <class D, class...> struct return_type_helper {
        typedef D type;
      };

      template <class... Types>
      struct return_type_helper<void, Types...> : std::common_type<Types...> {

#if !ANTHEM_CXX14
        static_assert(std::conjunction_v<not_ref_wrapper<Types>...>,
                      "Types cannot contain reference_wrappers when D is "
                      "void");
#else
        static_assert(util::conjunction<not_ref_wrapper<Types>...>::value,
                      "Types cannot contain reference_wrappers when D is "
                      "void");
#endif // ANTHEM_CXX14

      };
     
      template <class D, class... Types> using return_type = 
          std::array<typename return_type_helper<D, Types...>::type,
                     sizeof...(Types)>;
    } // namespace detail

    ///
    /// \brief Creates an \c std::array whose size is equal to the number of
    /// arguments and whose elements are initialized from the corresponding 
    /// arguments.
    ///
    /// Returns
    /// \code
    /// std::array<VT, sizeof...(Types)>{std::forward<Types>(t)...}
    /// \endcode
    ///
    /// If \c D is \c void, then the deduced type \c VT is
    /// \c std::common_type_t<Types...>. Otherwise, it is \c D.
    ///
    /// If \c D is void and any of \c std::decay_t<Types>... is a
    /// specialization of \c std::reference_wrapper, the program is ill-formed.
    ///
    /// \param t the elements of the array.
    ///
    /// \return \c std::array<VT, sizeof...(Types)>{std::forward<Types>(t)...}
    ///
    template <class D = void, class... Types>
    constexpr detail::return_type<D, Types...>
    make_array(Types&&... t) noexcept {
      return {std::forward<Types>(t)... };
    }
  } // namespace array
} // namespace anthem

#endif // !ANTHEM_ARRAY_H
