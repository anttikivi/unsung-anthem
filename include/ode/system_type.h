//===--------------------------- system_type.h ------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2018 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file system_type.h
/// \brief Declarations of the system type utilities.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEM_TYPE_H
#define ODE_SYSTEM_TYPE_H

#include <iostream>

#include "ode/__config"

namespace ode
{
  ///
  /// \brief An enumeration type, the enumerators of which represent the
  /// possible system types in Obliging Ode.
  ///
  enum class system_type : ODE_SYSTEM_TYPE_ENUM_TYPE
  {
    input
  };

  ///
  /// \brief Inserts an enumerator of type \c system_type to the
  /// \c std::ostream.
  ///
  /// \param os the stream to which the data is inserted.
  /// \param a the enumerator which is inserted.
  ///
  /// \return a reference of the \c std::ostream.
  ///
  std::ostream& operator<<(std::ostream& os, const system_type& a);

} // namespace ode

#endif // !ODE_SYSTEM_TYPE_H
