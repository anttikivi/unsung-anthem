## Preset mode

#### `-n`, `--dry-run`

Executes the build script in dry-run mode, which means that the commands which would be run are only printed to the console instead of running them.

#### `-c`, `--clean`

Erases the build directory before starting the build.

#### `--preset-file PATH`

A file from which the build script shall for the presets in preset mode.

#### `--preset NAME`

A preset in one of the specified preset files by which the command line options for the build are set.

#### `--show-presets`

Prints out the presets which can be used in the current environment.

#### `--expand-build-script-invocation`

Prints out the command which would be run according to the given preset but doesn’t run it.


## Options

### General Options

#### `-n`, `--dry-run`

Executes the build script in dry-run mode, which means that the commands which would be run are only printed to the console instead of running them.

#### `--from-preset`

This option tells the script it’s run from the preset mode. You mustn’t use this option manually!

#### `--build-subdir PATH`

The name of the directory under `$ANTHEM_BUILD_ROOT` where the build products will be placed.

#### `--install-prefix PATH`

The directory in which the final build products will be placed.

#### `-j INT`, `--jobs INT`

The number of parallel build jobs to use.

#### `--cmake PATH`

Path to the CMake executable that will be used building Unsung Anthem. If this is not set and the build script doesn’t find CMake from the `PATH` of the system, the build script downloads CMake and uses the downloaded CMake.

#### `--git PATH`

TODO

#### `--msbuild PATH`

TODO

#### `--host-cc PATH`

The absolute path to the C compiler on the host platform. The compiler is used for building Unsung Anthem and its dependencies. The default is auto-detected.

#### `--host-cxx PATH`

The absolute path to the C++ compiler on the host platform. The compiler is used for building Unsung Anthem and its dependencies. The default is auto-detected.

#### `--anthem-version MAJOR.MINOR.PATCH`

The version of Unsung Anthem. Set only if you want to use some special version number instead of the default.

#### `--darwin-deployment-version MAJOR.MINOR`

The minimum target version for deployment binaries for macOS.

#### `--cmake-extra-options OPTIONS`

Pass through extra options to the final CMake call in the form of comma separated options: '-DCMAKE_VAR1=YES,-DCMAKE_VAR2=/tmp'. This option can be called multiple times to append the list of the options to be passed.

#### `--main-tool NAME`

The toolchain name that will be used to build Unsung Anthem. The currently supported options are llvm, gcc, and msbuild. The default is llvm. TODO Windows default

#### `--main-tool-version VERSION`

The possible, specific version of the toolchain for the automatic lookup on the platform.

#### `-v`, `--verbose-build`

Print out the executed commands during the build.

### Build Target Options

#### `-h TARGET`, `--host-target TARGET`

TODO

#### `--cross-compile-hosts HOSTS`

TODO

### Project Options

#### `--llvm`

Download the pre-built LLVM and Clang binaries and use them with the included libc++ to build Unsung Anthem.

#### `--source-llvm`

Build LLVM and Clang from the source and use the built Clang to build Unsung Anthem.

#### `--libc++`

Build libc++ and use the built libc++ with Unsung Anthem. Cannot be used if `--llvm` or `--source-llvm` is enabled.

#### `--build-ninja`

TODO

#### `-t`, `--test`

Build the Unsung Anthem tests and run them thereafter.

### C++ Standard Options

These options are mutually exclusive.

#### `--c++14`

Build Unsung Anthem using C++14 standard.

#### `--c++17`

Build Unsung Anthem using C++17 standard.

#### `--c++2a`

Build Unsung Anthem using the upcoming C++ standard, currently called C++2a.

### C++ Standard Library

#### `--stdlib STDLIB`

Build Unsung Anthem using the specified C++ standard library implementation. The currently supported options are `libc++` and `--libstdc++`

### CMake Generator

#### `-e`, `--eclipse`

TODO

#### `-m`, `--make`

TODO

#### `-x`, `--xcode`

TODO

#### `--visual-studio-14`

TODO

#### `--visual-studio-15`

TODO

### Extra Actions

#### `-c`, `--clean`

Do a clean build.

#### `--gcov`

TODO

### Build Variant

#### `-d`, `--debug`

Build the debug variant of Unsung Anthem and the related projects.

#### `-r`, `--release-debuginfo`

Build the release variant of Unsung Anthem and the related projects with debug information.

#### `-R`, `--release`

Build the release variant of Unsung Anthem and the related projects.

### Build Variant in Specific Projects

#### `--debug-anthem`

Build the debug variant of Unsung Anthem.

#### `--debug-sdl`

Build the debug variant of Simple DirectMedia Player.

### Assertions

#### `--assertions`

Enable assertions in all projects which support them.

#### `--no-assertions`

Disable assertions in all projects.

### Assertions in Specific Projects.

#### `--anthem-assertions`

Enable assertions in Unsung Anthem.

#### `--libcxx-assertions`

Enable assertions in libc++ if it is built.

### Authentication

#### `--auth-token-file PATH`

Path to a file which contains an OAuth token which is used to access the GitHub GraphQL API.

#### `--auth-token TOKEN`

An OAuth token which is used to access the GitHub GraphQL API.

### Program

#### `--executable-name NAME`

TODO

#### `--lib-name NAME`

TODO

#### `--test-executable-name NAME`

TODO

### Threading Options

This group is mutually exclusive.

#### `--multithreading`

TODO

#### `--no-multithreading`

TODO

#### `--single-thread`

TODO
