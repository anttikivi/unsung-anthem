## Preset mode

### `-n`, `--dry-run`

Executes the build script in dry-run mode, which means that the commands which would be run are only printed to the console instead of running them.

### `-c`, `--clean`

Erases the build directory before starting the build.

### `--preset-file PATH`

A file from which the build script shall for the presets in preset mode.

### `--preset NAME`

A preset in one of the specified preset files by which the command line options for the build are set.

### `--show-presets`

Prints out the presets which can be used in the current environment.

### `--expand-build-script-invocation`

Prints out the command which would be run according to the given preset but doesn’t run it.
