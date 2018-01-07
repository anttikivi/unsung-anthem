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

#### `--cmake PATH`

Path to the CMake executable that will be used building Unsung Anthem. If this is not set and the build script doesn’t find CMake from the `PATH` of the system, the build script downloads CMake and uses the downloaded CMake.

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

#### `-v`, `--verbose-build`

Print out the executed commands during the build.

### Build Target Options

#### `-h TARGET`, `--host-target TARGET`

#### `--cross-compile-hosts HOSTS`

### Project Options

#### 
