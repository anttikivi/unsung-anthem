@rem Copyright (c) 2020 Antti Kivi
@rem Licensed under the Effective Elegy Licence

@echo off

set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows batch file wrapper for %composer_name%, the build ^
script of %ode_name% and %anthem_name%
echo %composer_name% will be run in configuring mode
echo The arguments passed to the script are %*

set preset_mode_argument=preset
set configure_mode_argument=configure

set composer_executable_name=couplet-composer

set in_tree_build_option=--in-tree-build

@rem See if the build should be done in tree.

set in_tree_build=false

for %%g in (%*) do if /i "%%~g"=="%in_tree_build_option%" set in_tree_build=true

@rem Set up Couplet Composer

set current_directory=%~dp0
set current_working_directory=%cd%

call %current_directory%\util\set_up %*

@rem Change back to the directory of this script to prevent the set-up script
@rem from messing up the working directory.

cd %current_working_directory%
echo The working directory is set to %cd%

@rem Switch to the correct directory.

set is_source_root_set=false

if defined ODE_SOURCE_ROOT (
  if not "%ODE_SOURCE_ROOT%"=="" (
    set is_source_root_set=true
  )
)

if "%is_source_root_set%"==false (
  if %in_tree_build%==false (
    cd ..
  )
  set ODE_SOURCE_ROOT=%cd%
) else (
  cd %ODE_SOURCE_ROOT%
)

@rem Run Couplet Composer

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
