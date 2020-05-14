@rem Copyright (c) 2020 Antti Kivi
@rem Licensed under the Effective Elegy Licence

@echo off

set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows batch file wrapper for %composer_name%, the build ^
script of %ode_name% and %anthem_name%
echo %composer_name% will be run in composing mode

set preset_mode_argument=preset
set compose_mode_argument=compose

set composer_executable_name=couplet-composer

set in_tree_build_option=--in-tree-build

@rem See if the build should be done in tree.

set in_tree_build=false

for %%g in (%*) do if /i "%%~g"=="%in_tree_build_option%" set in_tree_build=true

@rem Set the current directory to the correct root while setting the directory
@rem constants.

set current_working_directory=%cd%

if /i %in_tree_build%==false cd ..

echo The working directory is set to %cd%

set build_directory_name=build
set build_directory=%cd%\%build_directory_name%

cd %current_working_directory%

echo The working directory is set to %cd%

@rem See if the directory generated by configuring mode is in place.

if not exist %build_directory% (
  echo The directory %build_directory% is missing
  goto exit_for_missing_configuration
)

@rem Set up Couplet Composer.

set current_directory=%~dp0
set current_working_directory=%cd%

call %current_directory%\util\set_up %*

@rem Change back to the directory of this script to prevent the set-up script
@rem from messing up the working directory.

cd %current_working_directory%
echo The working directory is set to %cd%

@rem Switch to the correct directory.

if /i %in_tree_build%==false cd ..

echo The working directory is set to %cd%

@rem Run Couplet Composer.

set preset_mode=false

for %%g in (%*) do if /i "%%~g"=="%preset_mode_argument%" set preset_mode=true

if %preset_mode%==true (
  start "%composer_name%" /w /b pipenv run %composer_executable_name% %* ^
%compose_mode_argument%
) else (
  start "%composer_name%" /w /b pipenv run %composer_executable_name% ^
%compose_mode_argument% %*
)

goto :eof

:exit_for_missing_configuration
echo The build directory wasn't found; please make sure to run the cofiguring ^
script before attempting to build %ode_name% and %anthem_name% 1>&2
exit 1
