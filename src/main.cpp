//===-------------------------- main.cpp ------------------------*- C++ -*-===//
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
/// \file main.cpp
/// \brief The declaration and definition of the entry function of the program.
/// \author Antti Kivi
/// \date 23 June 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "execute.h"

///
/// \brief Returns the execution status of the program with the arguments
/// passed in.
///
/// \param argc the number of arguments passed in the execution.
/// \param argv array containing the arguments passed in the execution.
///
/// \return \c 0.
///
int main(int argc, const char* argv[]) {

  anthem::execute(argc, argv);

  return 0;
}
