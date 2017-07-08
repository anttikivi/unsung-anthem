//===--- placeholders.h -*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file placeholders.h
/// \brief TODO Add short description.
/// \author Antti Kivi
/// \date 07 heinäkuu 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_INTERNAL_PLACEHOLDERS_H
#define ANTHEM_INTERNAL_PLACEHOLDERS_H

namespace anthem {
  namespace placeholders {

    struct unspec {
    };

    struct __ {
    };

    struct _a {

    };

    struct _b {

    };

    struct _c {

    };

    struct _d {

    };

    struct _e {

    };

    struct _g {

    };

    struct _h {

    };

    struct _i {

    };

    struct _j {

    };

    struct _k {

    };

    struct _l {

    };

    // monoid
    struct _m {

    };

    struct _n {

    };

    struct _o {

    };

    struct _p {

    };

    struct _q {

    };

    struct _r {

    };

    struct _s {

    };

    struct _t {

    };

    struct _u {

    };

    struct _v {

    };

    struct _w {

    };

    struct _x {

    };

    struct _y {

    };

    struct _z {

    };

    // generic function: _f<_b(_a)>  => f :: a -> b
    template <typename T> struct _f {

    };

    // container
    template <typename T> struct _C {

    };

    // functor
    template <typename T> struct _F {

    };

    // monad
    template <typename T> struct _M {

    };

    // bifunctor
    template <typename T, typename V> struct _B {

    };
  } // namespace placeholders

  constexpr auto _ = placeholders::__ {};

} // namespace anthem

#endif // !ANTHEM_INTERNAL_PLACEHOLDERS_H
