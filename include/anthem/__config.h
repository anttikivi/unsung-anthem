//===-------------------------- __config.h ----------------------*- C++ -*-===//
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
/// \file __config.h
/// \brief Definition of the Unsung Anthem preprocessor macros.
/// \author Antti Kivi
/// \date 7 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_CONFIG_H
#define ANTHEM_CONFIG_H

#if defined(ANTHEM_DISABLE_CXX17)
# define DISABLE_CXX17 1
#endif

#if defined(ANTHEM_CXX17)
# define CXX2A 0
# define CXX17 1
# define CXX14 0
#elif defined(ANTHEM_CXX14)
# define CXX2A 0
# define CXX17 0
# define CXX14 1
#endif

#if CXX14
# define CXX_INLINE_VARIABLES 0
#else
# define CXX_INLINE_VARIABLES 1
#endif // !CXX14

#endif // !ANTHEM_CONFIG_H
