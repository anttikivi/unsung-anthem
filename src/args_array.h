//===------------------------- args_array.h ---------------------*- C++ -*-===//
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
/// \file args_array.h
/// \brief The declaration of the type of the argument array passed into the
/// main function.
/// \author Antti Kivi
/// \date 14 December 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_ARGS_ARRAY_H
#define ANTHEM_ARGS_ARRAY_H

namespace anthem
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && \
    !defined(__CYGWIN__)
  using args_array = char*;
#else
  using args_array = const char*;
#endif
} // namespace anthem

#endif // !ANTHEM_ARGS_ARRAY_H
