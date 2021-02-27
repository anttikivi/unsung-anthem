@rem Copyright (c) 2021 Antti Kivi
@rem Licensed under the Effective Elegy Licence

@echo off

set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows batch file wrapper for %composer_name%, the build ^
utility of %ode_name% and %anthem_name%
echo %composer_name% will be run in configuring mode

set preset_mode_argument=preset
set configure_mode_argument=configure

set composer_executable_name=couplet-composer

@rem Set up Couplet Composer.

set current_directory=%~dp0
set current_working_directory=%cd%

call %current_directory%\util\set_up %*

@rem Change back to the directory of this script to prevent the set-up script
@rem from messing up the working directory.

cd %current_working_directory%
echo The working directory is set to %cd%

@rem Switch to the correct directory.
cd ..

echo The working directory is set to %cd%

@rem Run Couplet Composer.

set preset_mode=false

for %%g in (%*) do if /i "%%~g"=="%preset_mode_argument%" set preset_mode=true

%cd%\env\Scripts\activate

if %preset_mode%==true (
  start "%composer_name%" /w /b %composer_executable_name% %* ^
%configure_mode_argument%
) else (
  start "%composer_name%" /w /b %composer_executable_name% ^
%configure_mode_argument% %*
)

if %ERRORLEVEL% neq 0 (
  echo %composer_name% failed to run
  exit 1
)

deactivate
