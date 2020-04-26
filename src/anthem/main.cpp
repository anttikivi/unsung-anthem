/// The declaration and definition of the main function of the program.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include <SDL2/SDL.h>

#include "anthem/run.h"

///
/// Returns the execution status of the program with the arguments passed in.
///
/// \param argc the number of arguments passed in the execution.
/// \param argv the array containing the arguments passed in the execution.
///
/// \return The end code of the program.
///
int main(int argc, char* argv[])
{
  const int r = anthem::run(argc, argv);
  return r;
}
