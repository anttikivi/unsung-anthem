@rem Copyright (c) 2021 Antti Kivi
@rem Licensed under the Effective Elegy Licence

@echo on

@rem Resolve the Couplet Composer type.

if defined DEVELOPMENT_COMPOSER (
  goto development_variable_is_defined
else (
  set "is_dev="
  goto check_local_variable
)

:development_variable_is_defined
if [%DEVELOPMENT_COMPOSER%]==[] (
  set "is_dev="
  goto check_local_variable
) else (
  goto development_variable_is_set
)

:development_variable_is_set
if %DEVELOPMENT_COMPOSER%==true (
  set is_dev=true
  goto script
) else (
  set "is_dev="
  goto check_local_variable
)

:check_local_variable
if defined LOCAL_COMPOSER (
  goto local_variable_is_defined
else (
  set "is_local="
  goto script
)

:local_variable_is_defined
if [%ODE_LOCAL_COMPOSER%]==[] (
  set "is_local="
  goto script
) else (
  goto local_variable_is_set
)

:local_variable_is_set
if %ODE_LOCAL_COMPOSER%==true (
  set is_local=true
) else (
  set "is_local="
)

goto script

:script

@rem Run the script.

set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows set-up batch file for %composer_name%, the build ^
utility of %ode_name% and %anthem_name%

set github_url=https://github.com
set composer_repo_owner=anttikivi
set composer_repo_name=couplet-composer
set composer_repo_url=%github_url%/%composer_repo_owner%/^
%composer_repo_name%.git

set current_working_directory=%cd%

@rem Switch to the correct directory.
cd ..

echo The working directory is set to %cd%

set script_directory_name=script
set composer_directory_base_name=composer
set composer_version_temporary=%composer_version:.=_%
set composer_directory_name=%composer_directory_base_name%_^
%composer_version_temporary:-=_%
set composer_head_directory_name=%composer_directory_base_name%_head
set composer_local_directory_name=%composer_directory_base_name%_local
set script_directory=%cd%\%script_directory_name%

@rem Set up the virtual environment.

if defined is_dev rmdir /s /q "%cd%\env"
if defined is_local rmdir /s /q "%cd%\env"

start "python" /w /b py -m venv env
call %cd%\env\Scripts\activate
start "python" /w /b py -m pip install --upgrade pip
call deactivate

if not defined is_dev goto install
if not defined is_local goto install

@rem Set up the script directory if it is needed.

if defined is_dev md %script_directory%
if defined is_dev echo Created the directory '%script_directory%'
if defined is_local md %script_directory%
if defined is_local echo Created the directory '%script_directory%'

@rem Clone Couplet Composer.
if defined is_dev goto get_dev
if defined is_local goto get_local

:get_dev
echo Using the development copy of %composer_name%

set composer_directory=%script_directory%\%composer_head_directory_name%
set composer_remote=origin
set composer_remote_branch=%composer_remote_branch%/develop

if not exist %composer_directory% (
  goto get_dev_no_dir
) else (
  goto get_dev_is_dir
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

:get_dev_is_dir
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
echo The latest development copy of %composer_name% is now set up
goto install

:get_local
echo Using the local development copy of %composer_name%

set composer_directory=%script_directory%\%composer_local_directory_name%
set composer_local_repo=%cd%/couplet-composer
set composer_remote=origin

if not exist %composer_directory% (
  goto get_local_no_dir
) else (
  goto get_local_is_dir
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

:get_local_is_dir
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
echo The latest local development copy of %composer_name% is now set up
goto install

:install

@rem Install the correct Couplet Composer.

call %cd%\env\Scripts\activate

if defined is_dev goto install_dir
if defined is_local goto install_dir

start "pip install" /w /b pip install %composer_directory%

goto finalize

:install_dir
start "pip install" /w /b pip install -r %current_working_directory%/requirements.txt

:finalize
deactivate
