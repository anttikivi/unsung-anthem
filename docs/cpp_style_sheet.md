# C++ Style Sheet for Obliging Ode and Unsung Anthem

If you’re looking to contribute C++ code to Obliging Ode and Unsung Anthem or you wish to find the coding style followed in the projects, you’re in the right place. This document contains the coding standards which you must follow when writing C++ code for the projects.

#### Table of Contents

[C++ Core Guidelines](#c-core-guidelines)

[C and C++ Standard](#c-and-c-standard)

[Files](#files)
* [File Extensions](#file-extensions)
* [#include Guards](#include-guards)

## C++ Core Guidelines

Follow the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md). If this style sheet and the C++ Core Guidelines contradict, follow this style sheet.

## C and C++ Standard

C and C++ are closely related languages. They both originate in ‘Classic C’ from 1978 and have evolved in ISO committees since then. Many attempts have been made to keep them compatible, but neither is a subset of the other.

You should prefer C++ to C whenever possible.

Currently, the code should target C++17, as described in [*International Standard ISO/IEC 14882:2017(E) – Programming Language C++*](https://www.iso.org/standard/68564.html).

You can use features that will be part of the next standard, C++20, but you must always make them conditional and provide a C++17 implementation. The definition `ODE_CXX2A` is defined as `1` if the C++20 features are allowed and as `0` if they are not.

If you must, for some reason, use C, the C code should target C17, as described in [*International Standard ISO/IEC 9899:2018 Information technology — Programming languages — C*](https://www.iso.org/standard/74528.html).

## Files

### File Extensions

Each C++ header file should have the `.h` file extension. The so-called C++ source files must have `.cpp` as their file extension. Each `.cpp` file must have its own `.h` file that declares its interface.

### #include Guards

Use `#include` guards in all `.h` files. The format of the definition should be `<PROJECT>_<PATH>_<FILE>_H`.

You must base the path to the full in-project path of the file. For example, in Obliging Ode and Unsung Anthem, the file `include/ode/framework/scheduler.h` should have the following guard:

```cpp
#ifndef ODE_FRAMEWORK_SCHEDULER_H
#define ODE_FRAMEWORK_SCHEDULER_H

// Declarations...

#endif // !ODE_FRAMEWORK_SCHEDULER_H
```
