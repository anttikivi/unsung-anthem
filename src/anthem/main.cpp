/// The declaration and definition of the main function of the program.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/run.h"

#include <SDL2/SDL.h>

///
/// Returns the execution status of the program with the arguments passed in.
///
/// \param argc the number of arguments passed in the execution.
/// \param argv the array containing the arguments passed in the execution.
///
/// \return The end code of the program.
///
int main(int argc, ode::argv_t argv[])
{
  const int r = anthem::run(argc, argv);
  return r;
}
