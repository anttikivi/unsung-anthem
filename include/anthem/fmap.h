//===--- fmap.h -------------------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file fmap.h
/// \brief TODO Add short description.
/// \author Antti Kivi
/// \date 03 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_FMAP_H
#define ANTHEM_FMAP_H

#include <algorithm>
#include <iterator>

namespace anthem {

  namespace detail {

    struct sequence_tag {

    };

    struct pointer_tag {

    };

    template <class X> X category(...);

    template <class S>
    auto category(const S& s) -> decltype(std::begin(s), sequence_tag());

    template <class Ptr>
    auto category(const Ptr& p) -> decltype(*p, p == nullptr, pointer_tag());

    template <class T> struct category_type {
      using type = decltype(category<T>(std::declval<T>()));
    };

    template <class R, class ... X> struct category_type<R(&)(X...)> {
      using type = R(&)(X...);
    };

    template <class T> using cat = typename category_type<T>::type;

  } // namespace detail

  template <class...> struct Functor;

  template <class F, class Fx, class Fun=Functor<detail::cat<Fx>>>
  auto fmap(F&& f, Fx&& fx) -> decltype(Fun::fmap(std::declval<F>(),
                                                  std::declval<Fx>())) {
    return Fun::fmap(std::forward<F>(f), std::forward<Fx>(fx));
  }

  template <class F, class G> struct Composition {
    F f;
    G g;

    template <class X>
    auto operator()(X&& x) -> decltype(f(g(std::declval<X>()))) {
      return f(g(std::forward<X>(x)));
    }
  };

// General case: composition
  template <class Function> struct Functor<Function> {
    template <class F, class G, class C = Composition<F, G>>
    static C fmap(F f, G g) {
      C(std::move(f), std::move(g));
    }
  };

  template <> struct Functor<sequence_tag> {
    template <class F, template <class...>
              class S,
              class X,
              class R = typename std::result_of<F(X)>::type>
    static S<R> fmap(F&& f, const S<X>& s) {
      S<R> r;
      r.reserve(s.size());
      std::transform(std::begin(s),
                     std::end(s),
                     std::back_inserter(r),
                     std::forward<F>(f));
      return r;
    }
  };

  template <> struct Functor<pointer_tag> {
    template <class F, template <class...>
              class Ptr,
              class X,
              class R = typename std::result_of<F(X)>::type>
    static Ptr<R> fmap(F&& f, const Ptr<X>& p) {
      return p != nullptr ? Ptr<R>(new R(std::forward<F>(f)(*p))) : nullptr;
    }
  };

}

#endif // !ANTHEM_FMAP_H
