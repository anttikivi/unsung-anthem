@rem Copyright (c) 2020 Antti Kivi
@rem Licensed under the Effective Elegy Licence

@echo off

set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows batch file launcher for %ode_name% and %anthem_name%

set current_directory=%~dp0

cd %current_directory%

echo Launching %cd%\anthem.exe

start "%anthem_name%" /w /b %cd%\anthem.exe %*
