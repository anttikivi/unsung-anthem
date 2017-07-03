//===--- monad.h ------------------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file monad.h
/// \brief TODO Add short description.
/// \author Antti Kivi
/// \date 30 June 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_MONAD_H
#define ANTHEM_MONAD_H

#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <utility>

namespace anthem {

  struct sequence_tag {

  };

  struct pointer_tag {

  };

  template <class X> X category(...);

  template <class S>
  auto category(const S& s) -> decltype(std::begin(s), sequence_tag());

  template <class Ptr>
  auto category(const Ptr& p) -> decltype(*p, p == nullptr, pointer_tag());

  template <class T> struct Category {
    using type = decltype(category<T>(std::declval<T>()));
  };

  template <class R, class ... X> struct Category<R(&)(X...)> {
    using type = R(&)(X...);
  };

  template <class T> using Cat = typename Category<typename std::decay<T>::type>::type;

  template <class...> struct PartialApplication;

  template <class F, class X> struct PartialApplication<F, X> {
    F f;
    X x;

    template <class _F, class _X> constexpr PartialApplication(_F&& f, _X&& x)
        : f(std::forward<_F>(f)), x(std::forward<_X>(x)) {
    }

    /*
     * The return type of F only gets deduced based on the number of xuments
     * supplied. PartialApplication otherwise has no idea whether f takes 1 or 10 xs.
     */
    template <class ... Xs> constexpr auto
    operator()(Xs&& ...xs) -> decltype(f(x, std::declval<Xs>()...)) {
      return f(x, std::forward<Xs>(xs)...);
    }
  };

/* Recursive, variadic version. */
  template <class F, class X1, class ...Xs>
  struct PartialApplication<F, X1, Xs...> : public PartialApplication<
      PartialApplication<F, X1>,
      Xs...> {
    template <class _F, class _X1, class ..._Xs>
    constexpr PartialApplication(_F&& f, _X1&& x1, _Xs&& ...xs)
        : PartialApplication<PartialApplication<F, X1>, Xs...>(
        PartialApplication<F, X1>(std::forward<_F>(f), std::forward<_X1>(x1)),
        std::forward<_Xs>(xs)...) {
    }
  };

/*
 * Some languages implement partial application through closures, which hold
 * references to the function's arguments. But they also often use reference
 * counting. We must consider the scope of the variables we want to apply. If
 * we apply references and then return the applied function, its references
 * will dangle.
 *
 * See:
 * upward funarg problem http://en.wikipedia.org/wiki/Upward_funarg_problem
 */

/*
 * closure http://en.wikipedia.org/wiki/Closure_%28computer_science%29
 * Here, closure forwards the arguments, which may be references or rvalues--it
 * does not matter. A regular closure works for passing functions down.
 */
  template <class F, class ...X>
  constexpr PartialApplication<F, X...> closure(F&& f, X&& ...x) {
    return PartialApplication<F, X...>(std::forward<F>(f),
                                       std::forward<X>(x)...);
  }

/*
 * Thinking as closures as open (having references to variables outside of
 * itself), let's refer to a closet as closed. It contains a function and its
 * arguments (or environment).
 */
  template <class F, class ...X>
  constexpr PartialApplication<F, X...> closet(F f, X ...x) {
    return PartialApplication<F, X...>(std::move(f), std::move(x)...);
  }

  template <class F, class ...G> struct Composition;

  template <class F, class G> struct Composition<F, G> {
    F f;
    G g;

    template <class _F, class _G> constexpr Composition(_F&& f, _G&& g)
        : f(std::forward<_F>(f)), g(std::forward<_G>(g)) {
    }

    template <class X, class ...Y>
    constexpr decltype(f(g(std::declval<X>()), std::declval<Y>()...))
    operator()(X&& x, Y&& ...y) {
      return f(g(std::forward<X>(x)), std::forward<Y>(y)...);
    }

    constexpr decltype(f(g())) operator()() {
      return f(g());
    }
  };

  template <class F, class G, class ...H>
  struct Composition<F, G, H...> : Composition<F, Composition<G, H...>> {
    typedef Composition<G, H...> Comp;

    template <class _F, class _G, class ..._H>
    constexpr Composition(_F&& f, _G&& g, _H&& ...h)
        : Composition<_F, Composition<_G, _H...>>(std::forward<_F>(f),
                                                  Comp(std::forward<_G>(g),
                                                       std::forward<_H>(h)...)) {
    }
  };

  template <class F, class ...G>
  constexpr Composition<F, G...> compose(F f, G ...g) {
    return Composition<F, G...>(std::move(f), std::move(g)...);
  }

  template <class...> struct Functor;

  template <class F, class FX, class Fun=Functor<Cat<FX>>> auto
  fmap(F&& f, FX&& fx) -> decltype(Fun::fmap(std::declval<F>(),
                                             std::declval<FX>())) {
    return Fun::fmap(std::forward<F>(f), std::forward<FX>(fx));
  }

// General case: compose
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

  template <class ...> struct Monad;

  template <class F, class M, class ...N, class Mo=Monad<Cat<M>>> auto
  mbind(F&& f, M&& m, N&& ...n) -> decltype(Mo::mbind(std::declval<F>(),
                                                      std::declval<M>(),
                                                      std::declval<N>()...)) {
    return Mo::mbind(std::forward<F>(f),
                     std::forward<M>(m),
                     std::forward<N>(n)...);
  }

  template <class F, class M, class ...N, class Mo=Monad<Cat<M>>> auto
  mdo(F&& f, M&& m) -> decltype(Mo::mdo(std::declval<F>(), std::declval<M>())) {
    return Mo::mdo(std::forward<F>(f), std::forward<M>(m));
  }

// The first template argument must be explicit!
  template <class M, class X, class ...Y, class Mo = Monad<Cat<M>>> auto
  mreturn(X&& x, Y&& ...y) -> decltype(Mo::
                                       template mreturn<M>(std::declval<X>(),
                                                           std::declval<Y>()...)) {
    return Mo::template mreturn<M>(std::forward<X>(x), std::forward<Y>(y)...);
  }

  template <template <class...> class M,
                                class X,
                                class ...Y,
                                class _M = M<typename std::decay<X>::type>,
                                class Mo = Monad<Cat<_M>>> auto
  mreturn(X&& x, Y&& ...y) -> decltype(Mo::
                                       template mreturn<_M>(std::declval<X>(),
                                                            std::declval<Y>()...)) {
    return Mo::template mreturn<_M>(std::forward<X>(x), std::forward<Y>(y)...);
  }

// Also has explicit template argument.
  template <class M, class Mo = Monad<Cat<M>>>
  auto mfail() -> decltype(Mo::template mfail<M>()) {
    return Mo::template mfail<M>();
  }

  template <> struct Monad<pointer_tag> {

    template <class P> using mvalue = typename P::element_type;

    template <class F, template <class...>
              class Ptr,
              class X,
              class R = typename std::result_of<F(X)>::type>
    static R mbind(F&& f, const Ptr<X>& p) {
      return p ? std::forward<F>(f)(*p) : nullptr;
    }

    template <class F, template <class...>
              class Ptr,
              class X,
              class Y,
              class R = typename std::result_of<F(X, Y)>::type>
    static R mbind(F&& f, const Ptr<X>& p, const Ptr<Y>& q) {
      return p and q ? std::forward<F>(f)(*p, *q) : nullptr;
    }

    template <template <class...> class M, class X, class Y>
    static M<Y> mdo(const M<X>& mx, const M<Y>& my) {
      return mx ? (my ? mreturn<M<Y>>(*my) : nullptr) : nullptr;
    }

    template <class M, class X> static M mreturn(X&& x) {
      using Y = typename M::element_type;
      return M(new Y(std::forward<X>(x)));
    }

    template <class M> static M mfail() {
      return nullptr;
    }
  };

  template <> struct Monad<sequence_tag> {

    template <class S> using mvalue = typename S::value_type;

    template <class F, template <class...>
              class S,
              class X,
              class R = typename std::result_of<F(X)>::type>
    static R mbind(F&& f, const S<X>& xs) {
      R r;
      for (const X& x : xs) {
        auto ys = std::forward<F>(f)(x);
        std::move(std::begin(ys), std::end(ys), std::back_inserter(r));
      }
      return r;
    }

    template <class F, template <class...>
              class S,
              class X,
              class Y,
              class R = typename std::result_of<F(X, Y)>::type>
    static R mbind(F&& f, const S<X>& xs, const S<Y>& ys) {
      R r;
      for (const X& x : xs) {
        for (const Y& y : ys) {
          auto zs = std::forward<F>(f)(x, y);
          std::move(std::begin(zs), std::end(zs), std::back_inserter(r));
        }
      }
      return r;
    }

    template <template <class...> class S, class X, class Y>
    static S<Y> mdo(const S<X>& mx, const S<Y>& my) {
      // Note: This is not a strictly correct definition.
      // It should return my concatenated to itself for every element of mx.
      return mx.size() ? my : S<Y>{};
    }

    template <class S, class X> static S mreturn(X&& x) {
      return S{std::forward<X>(x)}; // Construct an S of one element.
    }

    template <class S> static S mfail() {
      return S{};
    }
  };


  template <class X> struct Identity {
    using value_type = typename std::decay<X>::type;
    using reference = value_type&;
    using const_reference = const value_type&;
    value_type x;

    Identity(const Identity&) = default;

    constexpr Identity(Identity&& i) : x(std::move(i.x)) {
    }

    constexpr Identity(value_type x) : x(std::move(x)) {
    }

    reference operator()() {
      return x;
    }

    constexpr const_reference operator()() {
      return x;
    }
  };

  template <class X, class D = typename std::decay<X>::type>
  Identity<D> identity(X&& x) {
    return Identity<D>(std::forward<X>(x));
  }

  template <class X> struct IO {
    using function = std::function<X()>;
    function f;

    template <class F> IO(F&& f) : f(std::forward<F>(f)) {
    }

    X operator()() const {
      return f();
    }
  };

  IO<int> rdInt = [] { return 4; };


  template <> struct IO<void> {
    using function = std::function<void()>;
    function f;

    IO(function f) : f(std::move(f)) {
    }

    void operator()() const {
      f();
    }
  };


  template <class F, class R = typename std::result_of<F()>::type>
  IO<R> io(F f) {
    return IO<R>(std::move(f));
  }

  IO<void> doNothing = io([] {});


  template <class X> struct Functor<IO<X>> {

    template <class Y> using mvalue = Y;

    template <class K, class R> struct Kompose {
      K k;
      IO<R> r;

      using Term = typename std::result_of<K(R)>::type;

      Kompose(K k, IO<R> r) : k(std::move(k)), r(std::move(r)) {
      }

      Term operator()() {
        return k(r());
      }
    };

    template <class K> struct Kompose<K, void> {
      K k;
      IO<void> r;

      using Term = typename std::result_of<K()>::type;

      Kompose(K k, IO<void> r) : k(std::move(k)), r(std::move(r)) {
      }

      Term operator()() {
        r();
        return k();
      }
    };

    template <class F, class R = typename Kompose<F, X>::Term>
    static IO<R> fmap(F f, IO<X> r) {
      return IO<R>(Kompose<F, X>(std::move(f), std::move(r)));
    }
  };

  template <class F, class G> struct Incidence {
    F a;
    G b;

    constexpr Incidence(F a, G b) : a(std::move(a)), b(std::move(b)) {
    }

    auto operator()() -> typename std::result_of<G()>::type {
      a();
      return b();
    }
  };

  template <class F, class G, class I = Incidence<F, G>>
  constexpr I incidence(F f, G g) {
    return I(std::move(f), std::move(g));
  }

  template <class F> struct DoubleCall {
    F f;

    using F2 = typename std::result_of<F()>::type;
    using result_type = typename std::result_of<F2()>::type;

    constexpr result_type operator()() {
      return f()();
    }
  };

  template <class F> constexpr DoubleCall<F> doubleCall(F f) {
    return {std::move(f)};
  }

  template <class K, class G> struct Kompose {
    K k;
    G r;

    using R    = typename std::result_of<G()>::type;
    using IO2  = typename std::result_of<K(R)>::type;
    using Term = typename std::result_of<IO2()>::type;

    constexpr Kompose(K k, G r) : k(std::move(k)), r(std::move(r)) {
    }

    template <class ...X> constexpr Term operator()(X&& ...x) {
      return k(r(std::forward<X>(x)...))();
    }
  };

  template <class K, class G> static constexpr Kompose<K, G> kompose(K k, G g) {
    return Kompose<K, G>(std::move(k), std::move(g));
  }

  template <class _> struct Monad<IO<_>> {

    template <class F> using mvalue = typename std::result_of<F()>::type;


    template <class F,
              class G,
              class R   = typename std::result_of<G()>::type,
              class _IO = typename std::result_of<F(R)>::type>
    static _IO mbind(F f, G m) {
      //return _IO (
      //    doubleCall (
      //        compose( std::move(f), std::move(m.f) )
      //    )
      //);
      return _IO(kompose(std::move(f), std::move(m.f)));
    }

    template <class F, class _IO = typename std::result_of<F()>::type>
    static _IO mbind(F f, IO<void> m) {
      return _IO(doubleCall(incidence(std::move(f), std::move(m.f))));
    }

    template <class X, class R> static IO<R> mdo(IO<X> f, IO<R> g) {
      return io(incidence(std::move(f.f), std::move(g.f)));
    }

    template <class __, class X, class D = typename std::decay<X>::type>
    static IO<D> mreturn(X&& x) {
      // We cannot use io here because identity() may return a reference.
      return IO<D>(identity(std::forward<X>(x)));
    }

    template <class __,
              class F,
              class X,
              class ...Y,
              class R = typename std::result_of<F(X, Y...)>::type>
    static IO<R> mreturn(F&& f, X&& x, Y&& ...y) {
      return io(closet(std::forward<F>(f),
                       std::forward<X>(x),
                       std::forward<Y>(y)...));
    }

    template <class _IO> static _IO mfail() {
      return _IO([] {});
    }
  };

  template <class T> IO<T> readT() {
    return io([] {
      T t;
      std::cin >> t;
      return t;
    });
  }

  constexpr struct Echo {
    static void print(const std::string& s) {
      std::cout << s;
    }

    template <class X> static std::string show(const X& x) {
      static std::ostringstream oss;
      oss.str("");
      oss << x;
      return oss.str();
    }

    template <class X, class Y, class ...Z>
    static std::string show(const X& x, const Y& y, const Z& ...z) {
      return show(x) + show(y, z...);
    }

    template <class ...X> IO<void> operator()(const X& ...x) const {
      // We don't know if x will still be around when the IO executes, so
      // convert to a string right away!
      return IO<void>(closet(print, show(x...)));
    }
  } echo{};

  IO<void> newline = IO<void>([] { std::cout << std::endl; });

  template <class X, class Y, class Z>
  IO<void> equation(const std::string& op, const X& x, const Y& y, const Z& z) {
    return echo(x, op, y, " = ", z) >> newline;
  }


  template <class M> M addM(const M& a, const M& b) {
    return mbind([&](int x) {
      return mbind([=](int y) { return mreturn<M>(x + y); }, b);
    }, a);
  }

  template <class M> M addM2(const M& a, const M& b) {
    return mbind([&](int x) {
      return fmap([=](int y) { return x + y; }, b);
    }, a);
  }

  template <class M, class F> auto operator>>=(M&& m, F&& f) -> decltype(mbind(
      std::declval<F>(),
      std::declval<M>())) {
    return mbind(std::forward<F>(f), std::forward<M>(m));
  }

  template <class M, class F> auto
  operator>>(M&& m, F&& f) -> decltype(mdo(std::declval<M>(),
                                           std::declval<F>())) {
    return mdo(std::forward<M>(m), std::forward<F>(f));
  }

  template <class F, class M> auto
  operator^(F&& f, M&& m) -> decltype(fmap(std::declval<F>(),
                                           std::declval<M>())) {
    return fmap(std::forward<F>(f), std::forward<M>(m));
  }

  template <class M> using MonadValue = typename Monad<Cat<M>>::template mvalue<
      M>;

  template <class F, template <class...> class M, class X, class Y> auto liftM(
      const F& f,
      const M<X>& a,
      const M<Y>& b) -> M<typename std::result_of<F(X, Y)>::type> {
    return a >>= [&](const X& x) {
      return b >>= [&](const Y& y) {
        return mreturn<M>(f(x, y));
      };
    };
  };

/*
 * guard<M>(b) = (return True) or mfail().
 *
 * guard prematurely halts an execution based on some bool, b. Note that:
 *      p >> q = q
 *      mfail() >> p = mfail()
 *      nullptr >> p = nullptr -- where p is a unique_ptr.
 *      {} >> v = {} -- where v is a vector.
 */
  template <template <class...> class M> M<bool> guard(bool b) {
    return b ? mreturn<M>(b) : mfail<M<bool>>();
  }

/*
 * The above version of guard creates a junk Monad. This may be costly.
 * This version is an optimal shorthand for guard(b) >> m.
 */
  template <template <class...> class M,
                                class F,
                                class R = typename std::result_of<F()>::type>
  M<R> guard(bool b, F&& f) {
    return b ? mreturn<M>(std::forward<F>(f)()) : mfail<M<R>>();
  }

  template <template <class...> class M, class X>
  M<std::pair<X, X>> uniquePairs(const M<X>& m) {
    return mbind([](int x, int y) -> M<std::pair<X, X>> {
      // This is a very Haskell-like use of guard.
      return guard<M>(x != y) >> mreturn<M>(std::make_pair(x, y));
    }, m, m);
  }

/* alias for mreturn<unique_ptr> */
  template <class X>
  auto Just(X&& x) -> decltype(mreturn<std::unique_ptr>(std::declval<X>())) {
    return mreturn<std::unique_ptr>(std::forward<X>(x));
  }

#include <cmath>

// Safe square root.
  std::unique_ptr<float> sqrt(float x) {
    // The more optimized C++-guard.
    return guard<std::unique_ptr>(x >= 0, [x] { return std::sqrt(x); });

    // Equivalently,
    return x >= 0 ? Just(std::sqrt(x)) : nullptr;
  }

// Safe quadratic root.
  std::unique_ptr<std::pair<float, float>> qroot(float a, float b, float c) {
    return fmap([=](float r /*root*/ ) {
      return std::make_pair((-b + r) / (2 * a), (-b - r) / (2 * a));
    }, sqrt(b * b - 4 * a * c));
  }

  template <class X, class Y>
  std::ostream& operator<<(std::ostream& os, const std::pair<X, Y>& p) {
    os << '(' << p.first << ',' << p.second << ')';
    return os;
  }

  template <class X>
  std::ostream& operator<<(std::ostream& os, const std::unique_ptr<X>& p) {
    if (p) {
      os << "Just " << *p;
    } else {
      os << "Nothing";
    }
    return os;
  }

  template <class X>
  std::ostream& operator<<(std::ostream& os, const std::vector<X>& v) {
    os << '[';

    for (auto it = std::begin(v); it != std::end(v); it++) {
      os << *it;
      if (std::next(it) != std::end(v)) {
        os << ',';
      }
    }

    //std::copy( v.begin(), v.end(), std::ostream_iterator<X>(os,",") );
    os << ']';
    return os;
  }

  int main() {

    std::unique_ptr<int> p(new int(5));
    auto f = [](int x) { return Just(-x); };
    std::unique_ptr<int> q = mbind(f, p);

    std::vector<int> v = {1, 2, 3}, w = {3, 4};

    auto readInt = readT<int>();

    auto program =
        equation(" + ", p, q, addM(p, q))
            >> equation(" + ", v, w, addM(v, w))

            >> echo("Unique pairs of [1,2,3]:\n\t")
            >> echo(uniquePairs(v))
            >> newline

            >> echo("Unique pairs of Just 5:\n\t")
            >> echo(uniquePairs(p))
            >> newline

            >> echo("Please enter two numbers, x and y: ")
            >> (liftM(std::plus<int>(), readInt, readInt) >>= [](int x) {
              return echo("x+y = ", x) >> newline;
            })

            >> echo("The quadratic root of (1,3,-4) = ")
            >> echo(qroot(1, 3, -4))
            >> newline
            >> echo("The quadratic root of (1,0,4) = ")
            >> echo(qroot(1, 0, 4))
            >> newline;

    program();

  }

}

#endif // !ANTHEM_MONAD_H
