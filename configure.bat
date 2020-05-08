@rem Copyright (c) 2020 Antti Kivi
@rem Licensed under the Effective Elegy Licence

@echo off

set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows batch file wrapper for %composer_name%, the build ^
script of %ode_name% and %anthem_name%
echo %composer_name% will be run in configuring mode

set preset_mode_argument=preset
set configure_mode_argument=configure

set composer_executable_name=couplet-composer

@rem Set up Couplet Composer

set current_directory=%~dp0
set current_working_directory=%cd%

call %current_directory%\util\set_up %*

@rem Change back to the directory of this script to prevent the set-up script
@rem from messing up the working directory.

cd %current_working_directory%
echo The working directory is set to %cd%

@rem Switch to the correct directory.

if defined ODE_SOURCE_ROOT (
  if not "%ODE_SOURCE_ROOT%"=="" (
    cd %ODE_SOURCE_ROOT%
    goto run_composer
  )
)

cd ..
set ODE_SOURCE_ROOT=%cd%

goto run_composer

@rem Run Couplet Composer

:run_composer
echo "The working directory is set to %cd%"

set preset_mode=false

if "%~1"=="%preset_mode_argument%" set preset_mode=true

if %preset_mode%==true (
  start "%composer_name%" /w /b pipenv run %composer_executable_name% %* ^
%configure_mode_argument%
) else (
  start "%composer_name%" /w /b pipenv run %composer_executable_name% ^
%configure_mode_argument% %*
)
