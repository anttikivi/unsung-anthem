@rem Copyright (c) 2020 Antti Kivi
@rem Licensed under the Effective Elegy Licence

@echo off

set composer_name=Couplet Composer
set ode_name=Obliging Ode
set anthem_name=Unsung Anthem

echo Running the Windows batch file wrapper for %composer_name%, the build ^
script of %ode_name% and %anthem_name%
echo This is a wrapper for both the configuring and composing modes of ^
%composer_name%

set current_directory=%~dp0

call %current_directory%\configure %*
call %current_directory%\compose %*

echo Finished running the wrapper for both the configuration and composition ^
of %ode_name% and %anthem_name%
