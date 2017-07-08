//===--- meta.h -------------------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file meta.h
/// \brief TODO Add short description.
/// \author Antti Kivi
/// \date 07 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_INTERNAL_META_H
#define ANTHEM_INTERNAL_META_H

namespace anthem {

  namespace meta {

    ///////////////////////////////////////////////////////////////////////////////////
    //
    // apply a meta-predicate on the outer type (type constructor, e.g. functor, monad)
    // of the given type
    //

    template <template <template <typename...> class> class Trait, typename T>
    struct on_outer_type;

    template <template <template <typename...> class> class Trait,
        template <typename...> class Outer, typename... Ts>
    struct on_outer_type<Trait, Outer<Ts...>> : Trait<Outer> {

    };

  } // namespace meta

} // namespace anthem

#endif // !ANTHEM_INTERNAL_META_H
