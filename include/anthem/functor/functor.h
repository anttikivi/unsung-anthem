//===--- functor.h ----------------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file functor.h
/// \brief TODO Add short description.
/// \author Antti Kivi
/// \date 07 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_FUNCTOR_FUNCTOR_H
#define ANTHEM_FUNCTOR_FUNCTOR_H

#include <type_traits>
#include <experimental/type_traits>

#include "anthem/macro_config.h"
#include "anthem/internal/meta.h"
#include "anthem/internal/placeholders.h"

namespace anthem {

  //
  // trait for concepts
  //

  template <template <typename...> class F>
  struct is_functor : std::false_type {

  };


  // class functor
  //

  template <template <typename ...> class F> struct functor {

    template <typename A, typename Fun, typename Fa, typename = void>
    struct where {
#if !defined(DISABLE_CPP17)

      virtual auto fmap(Fun fun, Fa&& fa) -> F<std::invoke_result_t<Fun(A)>> = 0;

#elif !defined(DISABLE_CPP14)

      virtual auto fmap(Fun fun, Fa&& fa) -> F<std::result_of_t<Fun(A)>> = 0;

#else

      virtual auto fmap(Fun fun,
                        Fa&& fa) -> F<std::result_of<Fun(A)>::type> = 0;

#endif
    };
  };

  //
  // instance
  //

  template <typename F, typename ...> struct functor_instance;

  //
  // function: fmap
  //

  namespace detail {

    using namespace placeholders;

    struct fmap_ {
      using function_type = _F<_b>(_f<_b(_a)>, _F<_a>&&);

      template <typename Fun, typename Fa_>
      auto operator()(Fun f, Fa_&& xs) const {
        static_assert(meta::on_outer_type<is_functor, std::decay_t<Fa_>>::value,
                      "Type is not a functor!");

        return functor_instance<std::decay_t<Fa_>,
                                Fun,
                                Fa_>{}.fmap(std::move(f),
                                            std::forward<Fa_>(xs));
      }
    };
  } // namespace detail

  constexpr auto fmap = detail::fmap_{};

} // namespace anthem

#endif // !ANTHEM_FUNCTOR_FUNCTOR_H
