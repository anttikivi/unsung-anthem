# C++ Style Sheet for Obliging Ode and Unsung Anthem

If you’re looking to contribute C++ code to Obliging Ode and Unsung Anthem or you wish to find the coding style followed in the projects, you’re in the right place. This document contains the coding standards which you must follow when writing C++ code for the projects.

#### Table of Contents

[C++ Core Guidelines](#c-core-guidelines)

[C and C++ Standard](#c-and-c-standard)

## C++ Core Guidelines

Follow the [C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md). If this style sheet and the C++ Core Guidelines contradict, follow this style sheet.

## C and C++ Standard

C and C++ are closely related languages. They both originate in ‘Classic C’ from 1978 and have evolved in ISO committees since then. Many attempts have been made to keep them compatible, but neither is a subset of the other.

You should prefer C++ to C whenever possible.

Currently, the code should target C++17, as described in [*International Standard ISO/IEC 14882:2017(E) – Programming Language C++*](https://www.iso.org/standard/68564.html).

You can use features that will be part of the next standard, C++20, but you must always make them conditional and provide a C++17 implementation. The definition `ODE_CXX2A` is defined as `1` if the C++20 features are allowed and as `0` if they are not.
