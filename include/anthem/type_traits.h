//===------------------------ type_traits.h ---------------------*- C++ -*-===//
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
/// \file type_traits.h
/// \brief Declarations and definitions of the type-related standard utilities.
/// \author Antti Kivi
/// \date 13 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_TYPE_TRAITS_H
#define ANTHEM_TYPE_TRAITS_H

#include <type_traits>

namespace anthem {
  namespace util {

#if ANTHEM_CXX14
    template <bool B> using bool_constant = std::integral_constant<bool, B>;
#endif // ANTHEM_CXX14

#if ANTHEM_CXX14
    template<class B>
    struct negation : bool_constant<!bool(B::value)> {

    };
#endif // ANTHEM_CXX14

#if ANTHEM_CXX14
    template<class... T> struct conjunction : std::true_type {

    };
    template<class B1> struct conjunction<B1> : B1 {

    };
    template<class B1, class... Bn> struct conjunction<B1, Bn...> 
    : std::conditional_t<bool(B1::value), conjunction<Bn...>, B1> {

    };
#endif

  } // namespace util
} // namespace anthem

#endif // !ANTHEM_TYPE_TRAITS_H
