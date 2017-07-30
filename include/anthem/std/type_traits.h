//===--- type_traits.h ------------------------------------------*- C++ -*-===//
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
/// \brief Support declarations for C++ standard library template
/// metaprogramming and type traits and definitions of object-like support
/// macros relating to C++ standard library template metaprogramming and type
/// traits.
/// \author Antti Kivi
/// \date 30 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_STD_TYPE_TRAITS_H
#define ANTHEM_STD_TYPE_TRAITS_H

#include "anthem/__config.h"

#if CXX17

# define HAS_CXX17_TYPE_TRAITS 1
# define HAS_TYPE_TRAITS 1
# define HAS_EXPERIMENTAL_TYPE_TRAITS 0

#else

# define HAS_CXX17_TYPE_TRAITS 0

# if defined(__clang__) && __clang_major__ <= 3 && __clang_minor__ <= 5

#   define HAS_TYPE_TRAITS 1
#   define HAS_EXPERIMENTAL_TYPE_TRAITS 0

# else
#   if EXPERIMENTAL_HEADERS

#     define HAS_EXPERIMENTAL_TYPE_TRAITS 1
#     define HAS_TYPE_TRAITS 0

#   else

#     define HAS_EXPERIMENTAL_TYPE_TRAITS 0
#     define HAS_TYPE_TRAITS 1

#   endif

# endif // !(defined(__clang__) && __clang_major__ <= 3 && __clang_minor__ <= 5)
#endif // CXX14

#endif // !ANTHEM_STD_TYPE_TRAITS_H
