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
/// \brief Implementations of some standard C++ declarations related to
/// metaprogramming and type traits which are not supported by older C++
/// standard versions or which are not part of the C++ standard but are
/// specified in technical specifications.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_TYPE_TRAITS_H
#define ANTHEM_TYPE_TRAITS_H

#include <type_traits>

namespace anthem {

  //////////////////////////////////////////////////////////////////////////////
  // 23.15.7.1 const-volatile modifications [meta.trans.cv] ////////////////////
  //////////////////////////////////////////////////////////////////////////////

  template <class T> using remove_cv_t = typename std::remove_cv<T>::type;
}

#endif // !ANTHEM_TYPE_TRAITS_H
