//===--- execute.h ----------------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file execute.h
/// \brief The declaration of the main execution function of the game engine.
/// \author Antti Kivi
/// \date 29 June 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_EXECUTE_H
#define ANTHEM_EXECUTE_H

namespace anthem {

  ///
  /// \brief The main execution function of the game engine which eventually
  /// runs the program.
  ///
  /// \param argc The number of command line arguments passed to the program.
  /// \param argv An array containing the command line arguments passed to the
  /// program.
  ///
  void execute(int argc, const char* argv[]);
}

#endif // !ANTHEM_EXECUTE_H
