//===--- macro_config.h -----------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file macro_config.h
/// \brief TODO Add short description.
/// \author Antti Kivi
/// \date 07 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_MACRO_CONFIG_H
#define ANTHEM_MACRO_CONFIG_H

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

#if defined(ANTHEM_GCC)
# define DEFAULT_ASSIGNMENT delete
#else
# define DEFAULT_ASSIGNMENT default
#endif

#endif // !ANTHEM_MACRO_CONFIG_H
