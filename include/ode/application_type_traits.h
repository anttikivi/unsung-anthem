//===--------------------- application_type_traits.h ------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file application_type_traits.h
/// \brief The declaration of the application type traits.
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_APPLICATION_TYPE_TRAITS_H
#define ODE_APPLICATION_TYPE_TRAITS_H

#include <vector>

#include "ode/systems/system_t.h"
#include "ode/systems/system_type.h"

namespace ode
{
  namespace detail
  {
    ///
    /// \struct has_make_system
    /// \brief A type which checks whether or not the given type has a function
    /// with the name ‘make_system’ which has the given signature.
    ///
    /// \tparam T the type to check.
    ///
    template <typename, typename T> struct has_make_system
    {
      static_assert(
          std::integral_constant<T, false>::value,
          "The second template parameter needs to be of a function type.");
    };

    ///
    /// \struct has_make_system
    /// \brief A type which checks whether or not the given type has a function
    /// with the name ‘make_system’ which has the given signature.
    ///
    /// \tparam C the type to check.
    /// \tparam Ret the return type of the function ‘make_system’.
    /// \tparam Args the argument types of the function ‘make_system’.
    ///
    template <typename C, typename Ret, typename... Args>
    struct has_make_system<C, Ret(Args...)>
    {
    private:
      ///
      /// \brief Checks whether or not the function ‘make_system’ exists in the
      /// given type by attempting to call it and checking whether the type of
      /// the return value is the same as the given return type.
      ///
      /// \tparam T the type to check.
      ///
      /// \return This function doesn’t have a definition.
      ///
      template <typename T> static constexpr auto check(T*)
      -> typename std::is_same<
          decltype(std::declval<T>().make_system(std::declval<Args>()...)),
          Ret>::type;

      ///
      /// \brief A specialization of the checking function for the specific
      /// case of the result of the test being equal to false.
      ///
      /// \return This function doesn’t have a definition.
      ///
      template <typename> static constexpr std::false_type check(...);

      ///
      /// \brief A type which is equal to the return type of the checking
      /// function so by getting the value from this type, the value of the can
      /// be determined.
      ///
      using type = decltype(check<C>(0));

    public:
      ///
      /// \brief The result of the check.
      ///
      static constexpr bool value = type::value;
    };

    ///
    /// \struct has_make_other_systems
    /// \brief A type which checks whether or not the given type has a function
    /// with the name ‘make_other_systems’ which has the given signature.
    ///
    /// \tparam T the type to check.
    ///
    template <typename, typename T> struct has_make_other_systems
    {
      static_assert(
          std::integral_constant<T, false>::value,
          "The second template parameter needs to be of a function type.");
    };

    ///
    /// \struct has_make_other_systems
    /// \brief A type which checks whether or not the given type has a function
    /// with the name ‘make_other_systems’ which has the given signature.
    ///
    /// \tparam C the type to check.
    /// \tparam Ret the return type of the function ‘make_other_systems’.
    /// \tparam Args the argument types of the function ‘make_other_systems’.
    ///
    template <typename C, typename Ret, typename... Args>
    struct has_make_other_systems<C, Ret(Args...)>
    {
    private:
      ///
      /// \brief Checks whether or not the function ‘make_other_systems’ exists
      /// in the given type by attempting to call it and checking whether the
      /// type of the return value is the same as the given return type.
      ///
      /// \tparam T the type to check.
      ///
      /// \return This function doesn’t have a definition.
      ///
      template <typename T> static constexpr auto check(T*)
      -> typename std::is_same<
          decltype(
              std::declval<T>().make_other_systems(std::declval<Args>()...)),
          Ret>::type;

      ///
      /// \brief A specialization of the checking function for the specific
      /// case of the result of the test being equal to false.
      ///
      /// \return This function doesn’t have a definition.
      ///
      template <typename> static constexpr std::false_type check(...);

      ///
      /// \brief A type which is equal to the return type of the checking
      /// function so by getting the value from this type, the value of the can
      /// be determined.
      ///
      using type = decltype(check<C>(0));

    public:
      ///
      /// \brief The result of the check.
      ///
      static constexpr bool value = type::value;
    };

    ///
    /// \struct has_first_scene
    /// \brief A type which checks whether or not the given type has a function
    /// with the name ‘first_scene’ which has the given signature.
    ///
    /// \tparam T the type to check.
    ///
    template <typename, typename T> struct has_first_scene
    {
      static_assert(
          std::integral_constant<T, false>::value,
          "The second template parameter needs to be of a function type.");
    };

    ///
    /// \struct has_first_scene
    /// \brief A type which checks whether or not the given type has a function
    /// with the name ‘first_scene’ which has the given signature.
    ///
    /// \tparam C the type to check.
    /// \tparam Ret the return type of the function ‘first_scene’.
    /// \tparam Args the argument types of the function ‘first_scene’.
    ///
    template <typename C, typename Ret, typename... Args>
    struct has_first_scene<C, Ret(Args...)>
    {
    private:
      ///
      /// \brief Checks whether or not the function ‘first_scene’ exists
      /// in the given type by attempting to call it and checking whether the
      /// type of the return value is the same as the given return type.
      ///
      /// \tparam T the type to check.
      ///
      /// \return This function doesn’t have a definition.
      ///
      template <typename T> static constexpr auto check(T*)
      -> typename std::is_same<
          decltype(
              std::declval<T>().first_scene(std::declval<Args>()...)),
          Ret>::type;

      ///
      /// \brief A specialization of the checking function for the specific
      /// case of the result of the test being equal to false.
      ///
      /// \return This function doesn’t have a definition.
      ///
      template <typename> static constexpr std::false_type check(...);

      ///
      /// \brief A type which is equal to the return type of the checking
      /// function so by getting the value from this type, the value of the can
      /// be determined.
      ///
      using type = decltype(check<C>(0));

    public:
      ///
      /// \brief The result of the check.
      ///
      static constexpr bool value = type::value;
    };

  } // namespace detail

  ///
  /// \struct is_application
  /// \brief A integral constant type which checks whether or not the given
  /// type is a valid application type.
  ///
  /// \tparam T the type to check.
  ///
  template <typename T> struct is_application
  : public std::bool_constant<
      detail::has_make_system<T, system_t(const system_type)>::value &&
      detail::has_make_other_systems<T, std::vector<system_t>()>::value &&
      detail::has_first_scene<T, scene_configuration_t()>::value
  >
  {

  };

  ///
  /// \brief Checks whether or not the given type is a valid application type.
  ///
  /// \tparam T the type to check.
  ///
  template <typename T>
  inline constexpr bool is_application_v = is_application<T>::value;

} // namespace ode

#endif // !ODE_APPLICATION_TYPE_TRAITS_H
