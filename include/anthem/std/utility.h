//===--- utility.h ----------------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file integer_sequence.h
/// \brief Implementations of some standard C++ utility declarations which are
/// not supported by older C++ standard versions or which are not part of the
/// C++ standard but are specified in technical specifications.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_INTEGER_SEQUENCE_H
#define ANTHEM_INTEGER_SEQUENCE_H

#include <utility>
#include <type_traits>

namespace anthem {

  //////////////////////////////////////////////////////////////////////////////
  // 23.3 compile-time integer sequences [intseq] //////////////////////////////
  //////////////////////////////////////////////////////////////////////////////

  ///
  /// \brief Type of compile-time integer sequence objects.
  ///
  /// \tparam T an integer type to use for the elements of the sequence.
  /// \tparam I a non-type parameter pack representing the sequence.
  ///
  template <class T, T... I> struct integer_sequence {

    ///
    /// \brief The integer type used for the elements of the sequence.
    ///
    using value_type = T;

    static_assert(std::is_integral<T>::value,
                  "integer_sequence can only be instantiated with an integral "
                      "type");

    ///
    /// \brief Returns the number of elements in \c I. Equivalent to
    /// \c sizeof...(Ints).
    ///
    /// \return The number of elements in \c I.
    ///
    static constexpr std::size_t size() noexcept {
      return sizeof...(I);
    }
  };

  ///
  /// \brief Type of compile-time integer sequence objects in which the type of
  /// elements is \c std::size_t.
  ///
  template <std::size_t... I>
  using index_sequence = integer_sequence<std::size_t, I...>;

  namespace detail {

    template <std::size_t... I> struct index_tuple {

      typedef index_tuple<I..., sizeof...(I)> next;
    };

    template <std::size_t N> struct build_index_tuple {
      typedef typename build_index_tuple<N - 1>::type::next type;
    };

    template <> struct build_index_tuple<0> {
      typedef index_tuple<> type;
    };

    template <typename T, T N,
              typename ISeq = typename build_index_tuple<N>::type>
    struct make_integer_sequence_impl;

    template <typename T, T N, std::size_t... I>
    struct make_integer_sequence_impl<T, N, index_tuple<I...>> {
      static_assert(N >= 0, "Cannot make integer sequence of negative length");

      typedef integer_sequence<T, static_cast<T>(I)...> type;
    };

  } // namespace detail

  ///
  /// \brief Type of \c integer_sequence constructed from elements
  /// 0, 1, 2, ..., N-1.
  ///
  template <typename T, T N> using make_integer_sequence
  = typename detail::make_integer_sequence_impl<T, N>::type;

  ///
  /// \brief Type of \c index_sequence constructed from elements
  /// 0, 1, 2, ..., N-1.
  ///
  template <std::size_t N>
  using make_index_sequence = make_integer_sequence<std::size_t, N>;

} // namespace anthem

#endif // !ANTHEM_INTEGER_SEQUENCE_H
