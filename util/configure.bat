:: Copyright (c) 2020 Antti Kivi
:: Licensed under the Effective Elegy Licence

@echo on

set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows batch file wrapper for %composer_name%, the build ^
script of %ode_name% and %anthem_name%
echo %composer_name% will be run in configuring mode

set preset_mode_argument=preset
set configure_mode_argument=configure

set composer_executable_name=couplet-composer

:: Set up Couplet Composer

set current_directory=%~dp0

call %current_directory%\set_up.bat %*

:: Run Couplet Composer

set preset_mode=false

if "%~1"=="%preset_mode_argument%" set preset_mode=true

if %preset_mode%==true start %composer_name% /w pipenv run %composer_executable_name% %* %configure_mode_argument% else start %composer_name% /w pipenv run %composer_executable_name% %configure_mode_argument% %*
