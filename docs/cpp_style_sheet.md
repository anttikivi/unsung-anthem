# C++ Style Sheet for Obliging Ode and Unsung Anthem

If you’re looking to contribute C++ code to Obliging Ode and Unsung Anthem or you wish to find the coding style followed in the projects, you’re in the right place. This document contains the coding standards which you must follow when writing C++ code for the projects.

#### Table of Contents

[C++ Core Guidelines](#c-core-guidelines)

[C and C++ Standard](#c-and-c-standard)

[Languages](#languages)

[Code Formatting](#code-formatting)

[Files](#files)
* [File Extensions](#file-extensions)
* [#include Guards](#include-guards)
* [`#include` Style](#include-style)
* [File Headers](#file-headers)
* [Source Code Width](#source-code-width)

[Styling](#styling)

## C++ Core Guidelines

Follow the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md). If this style sheet and the C++ Core Guidelines contradict, follow this style sheet.

## C and C++ Standard

C and C++ are closely related languages. They both originate in ‘Classic C’ from 1978 and have evolved in ISO committees since then. Many attempts have been made to keep them compatible, but neither is a subset of the other.

You should prefer C++ to C whenever possible.

Currently, the code should target C++17, as described in [*International Standard ISO/IEC 14882:2017(E) – Programming Language C++*](https://www.iso.org/standard/68564.html).

You can use features that will be part of the next standard, C++20, but you must always make them conditional and provide a C++17 implementation. The definition `ODE_CXX2A` is defined as `1` if the C++20 features are allowed and as `0` if they are not.

If you must, for some reason, use C, the C code should target C17, as described in [*International Standard ISO/IEC 9899:2018 Information technology — Programming languages — C*](https://www.iso.org/standard/74528.html).

## Languages

In all code and documentation, use English. This rule doesn’t naturally apply to translations.

In both code and documentation, prefer British English as defined in [Oxford English Dictionary](https://oed.com). To summarize, you should use British spellings and words with the exception that verbs ending in `-ize` (including words derived from them) should be spelled with the `-ize` ending instead of `-ise` ending. Also, the ‘Oxford comma’ should be used. As a rule of thumb, when you use the first word variant that comes up in its entry in Oxford English Dictionary, you’re on the right track. For example, Oxford’s [Lexico](https://lexico.com) is a good online dictionary to use when you’re unsure.

## Code Formatting

To help you follow this style sheet, the repository includes a `clang-format` rule set that can be used to automatically format the source code in the repository. To correctly run `clang-format` on all of the files, run `./util/format`. However, please note that `clang-format` can’t take every aspect of formatting into account.

## Files

### File Extensions

Each C++ header file should have the `.h` file extension. The so-called C++ source files must have `.cpp` as their file extension. Each `.cpp` file must have its own `.h` file that declares its interface.

### `#include` Guards

Use `#include` guards in all `.h` files. The format of the definition should be `<PROJECT>_<PATH>_<FILE>_H`.

You must base the path to the full in-project path of the file. For example, in Obliging Ode and Unsung Anthem, the file `include/ode/framework/scheduler.h` should have the following guard:

```cpp
#ifndef ODE_FRAMEWORK_SCHEDULER_H
#define ODE_FRAMEWORK_SCHEDULER_H

// Declarations...

#endif // !ODE_FRAMEWORK_SCHEDULER_H
```

### `#include` Style

When including header files, the `#include` directives must be sorted into groups according to the types of the included headers. The order is the following:

1. (in source files) the ‘main’ header of the source file
2. the C standard library headers
3. the C++ standard library headers
4. the guideline support library headers
5. the headers of other libraries
6. Obliging Ode headers
7. Unsung Anthem headers

Separate the groups by one empty line. Order the headers alphabetically inside each group.

Use angle brackets (`<` and `>`) in the `#include` directives for the C standard library includes, C++ standard library includes, and the includes of the headers of other libraries. For all other `#include` directives, use double quotes (`"`).

### File Headers

You should add a header to every file telling basic purpose of the file. The header should also contain standard commands for generating the [Doxygen](http://doxygen.nl) documentation. The form of the header should be like in the following example:

```cpp
/// The declaration of the type of objects that contain information about one
/// command line option.
/// \file
/// \author Antti Kivi
/// \date 19 March 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.
```

The example above is taken from the file `option.h`.

The paragraph beginning on the first line of the comment acts as the value for [Doxygen’s](http://doxygen.nl) `\brief` command so it’s an abstract of the file. Please also note that the header is a [Doxygen](http://doxygen.nl) comment which is identified by `///` instead of the regular `//`.

### Source Code Width

You must make each line of code fit within 80 colums.

## Styling
