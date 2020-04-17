@rem Copyright (c) 2020 Antti Kivi
@rem Licensed under the Effective Elegy Licence

echo Running the Windows batch file helper for formatting Obliging Ode and ^
Unsung Anthem

set current_directory=%~dp0

cd %current_directory%\..

echo Starting to format %current_directory%\..

:format_directory
echo Looking through %1
for %%f in (*.cpp) do call :run_clang_format %%f
for %%f in (*.h) do call :run_clang_format %%f
for %%f in (*__config) do call :run_clang_format %%f
for %%f in (*assert) do call :run_clang_format %%f
for %%f in (*util) do call :run_clang_format %%f
for %%f in (*view) do call :run_clang_format %%f
for /d %%d in (*) do (
  cd %%d
  call :format_directory %%d
  cd ..
)
goto :eof

:run_clang_format
echo Formatting: %1
start "clang-format" /w /b clang-format -i $pathname
goto :eof
