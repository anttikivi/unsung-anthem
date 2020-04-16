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
    echo Using development version of %composer_name%

    set composer_directory=%script_directory%\%composer_head_directory_name%

    :: If the Composer directory doesn't exist, there is no need to check for the
    :: remote HEAD SHA1.
    if not exist !composer_directory! (
      echo The directory for %composer_name% doesn't exist and, thus, ^
  %composer_name% will be cloned

      start "git clone" /w git clone %composer_repo_url% %composer_directory%

      for /f "tokens=* usebackq" %%f in ^
      ('git -C %composer_directory% rev-parse HEAD') do set head_sha=%%f

      echo The SHA1 for the currently cloned HEAD of %composer_name% is ^
  %head_sha%
    ) else (

      for /f "tokens=* usebackq" %%f in ^
      ('git -C %composer_directory% rev-parse HEAD') do set head_sha=%%f

      for /f "tokens=* usebackq" %%f in ^
      ('git -C %composer_directory% rev-parse origin/develop') do (
        set origin_sha=%%f
      )

      echo The SHA1 for the currently cloned HEAD of %composer_name% is ^
  %head_sha%

      if not %head_sha%==%origin_sha% (
        echo The SHA1 for origin/develop of %composer_name% is %origin_sha% and, ^
  thus, the local copy will be reset
        start "git reset" /w git -C %composer_directory% reset --hard HEAD
        start "git clean" /w git -C %composer_directory% clean -xffd
        start "git pull" /w git -C %composer_directory% pull
      )
    )

    echo The latest development version of %composer_name% is now set up
  )
) else (
  set composer_directory=%script_directory%\%composer_directory_name%

  if not exist %composer_directory% (
    start "git clone" /w git clone %composer_repo_url% %composer_directory%
    start "git checkout" /w git -C %composer_directory% checkout ^
    tags/%composer_version_tag% -b local_install_%composer_version_tag%
  )
)

:install_development_composer

start "pipenv install" /w pipenv install %composer_directory%
