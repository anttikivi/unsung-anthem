@rem Copyright (c) 2020 Antti Kivi
@rem Licensed under the Effective Elegy Licence

@echo off

set /p composer_version=<%~dp0\composer-version
set composer_version_tag=v%composer_version%
set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows set-up batch file for %composer_name% ^
%composer_version%, the build script of %ode_name% and %anthem_name%

set github_url=https://github.com
set composer_repo_owner=anttikivi
set composer_repo_name=couplet-composer
set composer_repo_url=%github_url%/%composer_repo_owner%/^
%composer_repo_name%.git

set in_tree_build_option=--in-tree-build

@rem See if the build should be done in tree.

set in_tree_build=false

for %%g in (%*) do if /i "%%~g"=="%in_tree_build_option%" set in_tree_build=true

echo The value for in-tree build is set to %in_tree_build%

@rem Switch to the correct directory.

if %in_tree_build%==false cd ..

echo The working directory is set to %cd%

set script_directory_name=script
set composer_directory_base_name=composer
set composer_version_temporary=%composer_version:.=_%
set composer_directory_name=%composer_directory_base_name%_^
%composer_version_temporary:-=_%
set composer_head_directory_name=%composer_directory_base_name%_head
set composer_local_directory_name=%composer_directory_base_name%_local

setlocal enabledelayedexpansion

if %in_tree_build%==true (
  set build_directory_name=build
  set build_directory=%cd%\!build_directory_name!
  set script_directory=!build_directory!\%script_directory_name%

  md !build_directory!
  echo Created the directory '!build_directory!'
) else (
  set script_directory=%cd%\%script_directory_name%
)

setlocal disabledelayedexpansion

@rem Install pipenv.

where pipenv

if %ERRORLEVEL% neq 0 (
  echo Didn't find pipenv. Installing.
  start "pip" /w /b pip install pipenv
)

@rem Set up the script directory.

md %script_directory%
echo Created the directory '%script_directory%'

@rem Clone Couplet Composer.

if defined ODE_DEVELOPMENT_COMPOSER (
  goto development_variable_is_defined
) else (
  goto check_local_variable
)

:development_variable_is_defined
if [%ODE_DEVELOPMENT_COMPOSER%]==[] (
  goto check_local_variable
) else (
  goto development_variable_is_set
)

:development_variable_is_set
if %ODE_DEVELOPMENT_COMPOSER%==true (
  goto get_development_composer
) else (
  goto check_local_variable
)

:check_local_variable
if defined ODE_LOCAL_COMPOSER (
  goto local_variable_is_defined
else (
  goto get_composer_release
)

:local_variable_is_defined
if [%ODE_LOCAL_COMPOSER%]==[] (
  goto get_composer_release
) else (
  goto local_variable_is_set
)

:local_variable_is_set
if %ODE_LOCAL_COMPOSER%==true (
  goto get_local_composer
) else (
  goto get_composer_release
)

:get_composer_release
set composer_directory=%script_directory%\%composer_directory_name%

if not exist %composer_directory% (
  start "git clone" /w /b git clone %composer_repo_url% %composer_directory%
  start "git checkout" /w /b git -C %composer_directory% checkout ^
tags/%composer_version_tag% -b local_install_%composer_version_tag%
)

goto install_composer

:get_development_composer
echo Using development version of %composer_name%

set composer_directory=%script_directory%\%composer_head_directory_name%
set composer_remote=origin
set composer_remote_branch=%composer_remote_branch%/develop

if not exist %composer_directory% (
  goto get_dev_no_dir
) else (
  goto get_dev_existing_dir
)

:get_dev_no_dir
@rem If the Composer directory doesn't exist, there is no need to check for
@rem the remote HEAD SHA1.
echo The directory for '%composer_directory%' doesn't exist and, thus, ^
%composer_name% will be cloned

start "git clone" /w /b git clone %composer_repo_url% %composer_directory%

for /f %%i in ('git -C %composer_directory% rev-parse HEAD') do set head_sha=%%i

echo The SHA1 for the currently cloned HEAD of %composer_name% is %head_sha%

goto finalize_dev_setup

:get_dev_existing_dir
start "git fetch" /w /b git -C %composer_directory% fetch

for /f %%i in ('git -C %composer_directory% rev-parse HEAD') do set head_sha=%%i

for /f %%i in ('git -C %composer_directory% rev-parse %composer_remote_branch%') do (
  set remote_sha=%%i
)

echo The SHA1 for the currently cloned HEAD of %composer_name% is %head_sha%
echo The SHA1 for %composer_remote_branch% of %composer_name% is %remote_sha%

if not %head_sha%==%remote_sha% (
  echo The SHA1's for %composer_remote_branch% and local HEAD of ^
%composer_name% don't match and thus the local copy will be reset
  start "git reset" /w /b git -C %composer_directory% reset --hard HEAD
  start "git clean" /w /b git -C %composer_directory% clean -xffd
  start "git pull" /w /b git -C %composer_directory% pull
)

goto finalize_dev_setup

:finalize_dev_setup
echo The latest development version of %composer_name% is now set up
goto install_composer

:get_local_composer
echo Using local development version of %composer_name%

set composer_directory=%script_directory%\%composer_local_directory_name%
set composer_local_repo=%cd%/couplet-composer
set composer_remote=origin

if not exist %composer_directory% (
  goto get_local_no_dir
) else (
  goto get_local_existing_dir
)

:get_local_no_dir
@rem If the Composer directory doesn't exist, there is no need to check for
@rem the local repository HEAD SHA1.
echo The directory for '%composer_directory%' doesn't exist and, thus, ^
%composer_name% will be cloned from the local repository

start "git clone" /w /b git clone %composer_local_repo% %composer_directory%

for /f %%i in ('git -C %composer_directory% rev-parse HEAD') do set head_sha=%%i

echo The SHA1 for the currently cloned local HEAD of %composer_name% is ^
%head_sha%

goto finalize_local_setup

:get_local_existing_dir
for /f %%i in ('git -C %composer_directory% rev-parse --abbrev-ref HEAD') do (
  set current_branch=%%i
)

for /f %%i in ('git -C %composer_local_repo% rev-parse --abbrev-ref HEAD') do (
  set local_branch=%%i
)

echo The current branch in %composer_directory% is %current_branch%
echo The current branch of the remote %composer_remote% is %local_branch%

if not %current_branch%==%local_branch% (
  start "git fetch" /w /b git -C %composer_directory% fetch %composer_remote%
  start "git checkout" /w /b git -C %composer_directory% checkout -b ^
%local_branch% %composer_remote%/%local_branch%
)

start "git fetch" /w /b git -C %composer_directory% fetch %composer_remote%

for /f %%i in ('git -C %composer_directory% rev-parse HEAD') do set head_sha=%%i

for /f %%i in ('git -C %composer_directory% rev-parse %composer_remote%/%local_branch%') do (
  set remote_sha=%%i
)

echo The SHA1 for the currently cloned HEAD of %composer_name% is %head_sha%
echo The SHA1 for %composer_remote%/%local_branch% of %composer_name% is ^
%remote_sha%

if not %head_sha%==%remote_sha% (
  echo The SHA1's for %composer_remote%/%local_branch% and local HEAD of ^
%composer_name% don't match and thus the local copy will be reset
  start "git reset" /w /b git -C %composer_directory% reset --hard HEAD
  start "git clean" /w /b git -C %composer_directory% clean -xffd
  start "git pull" /w /b git -C %composer_directory% pull
)

goto finalize_local_setup

:finalize_local_setup
echo The latest local development version of %composer_name% is now set up
goto install_composer

:install_composer
start "pipenv install" /w /b pipenv install %composer_directory%
