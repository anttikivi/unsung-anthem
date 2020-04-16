:: Copyright (c) 2020 Antti Kivi
:: Licensed under the Effective Elegy Licence

@echo on

setlocal enabledelayedexpansion

set /p composer_version=<%~dp0\composer-version
set composer_version_tag=v%composer_version%
set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the set-up shell script for %composer_name% %composer_version%, ^
the build script of %ode_name% and %anthem_name%

set github_url=https://github.com
set composer_repo_owner=anttikivi
set composer_repo_name=couplet-composer
set composer_repo_url=%github_url%/%composer_repo_owner%/^
%composer_repo_name%.git

set root_dir=%cd%

set script_directory_name=script
set composer_directory_base_name=composer
set composer_directory_name=%composer_directory_base_name%_%composer_version%
set composer_head_directory_name=%composer_directory_base_name%_HEAD

set script_directory=%root_dir%\%script_directory_name%

:: Install pipenv

where pipenv

if %ERRORLEVEL% neq 0 (
  echo Didn't find pipenv. Installing.
  start "pip" /w pip install pipenv
)

:: Set up the script directory

md %script_directory%

:: Clone Couplet Composer

if defined ODE_USE_DEVELOPMENT_COMPOSER (
  if %ODE_USE_DEVELOPMENT_COMPOSER%==true (
    set tmp_file=%root_dir%\tmp
    goto get_development_composer
  )
)

set composer_directory=%script_directory%\%composer_directory_name%

if not exist %composer_directory% (
  start "git clone" /w git clone %composer_repo_url% %composer_directory%
  start "git checkout" /w git -C %composer_directory% checkout ^
tags/%composer_version_tag% -b local_install_%composer_version_tag%
)

goto install_composer

:get_development_composer
echo Using development version of %composer_name%

set composer_directory=%script_directory%\%composer_head_directory_name%

if not exist %composer_directory% goto get_dev_no_dir

goto get_dev_existing_dir

:get_dev_no_dir
:: If the Composer directory doesn't exist, there is no need to check for
:: the remote HEAD SHA1.
echo The directory for %composer_name% doesn't exist and, thus, ^
%composer_name% will be cloned

start "git clone" /w git clone %composer_repo_url% %composer_directory%

start "git rev-parse" /w git -C %composer_directory% rev-parse HEAD > %tmp_file%
set /p head_sha=<%tmp_file%
del %tmp_file%

echo The SHA1 for the currently cloned HEAD of %composer_name% is %head_sha%

goto finalize_dev_setup

:get_dev_existing_dir
start "git rev-parse" /w git -C %composer_directory% rev-parse HEAD > %tmp_file%
set /p head_sha=<%tmp_file%
del %tmp_file%

start "git rev-parse" /w git -C %composer_directory% rev-parse origin/develop > %tmp_file%
set /p origin_sha=<%tmp_file%
del %tmp_file%

echo The SHA1 for the currently cloned HEAD of %composer_name% is %head_sha%

if not %head_sha%==%origin_sha% (
  echo The SHA1 for origin/develop of %composer_name% is %origin_sha% and, ^
thus, the local copy will be reset
  start "git reset" /w git -C %composer_directory% reset --hard HEAD
  start "git clean" /w git -C %composer_directory% clean -xffd
  start "git pull" /w git -C %composer_directory% pull
)

goto finalize_dev_setup

:finalize_dev_setup
echo The latest development version of %composer_name% is now set up
goto install_composer

:install_composer
start "pipenv install" /w pipenv install %composer_directory%
