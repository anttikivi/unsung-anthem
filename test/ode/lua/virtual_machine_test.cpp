/// The tests of the Lua virtual machine utilities.
/// \file
/// \author Antti Kivi
/// \date 10 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/lua/virtual_machine.h"

#include "gsl/util"

#include "ode/config.h"
#include "ode/filesystem/path.h"

#include <gtest/gtest.h>

TEST(ode_lua_make_state, values_are_got)
{
  lua_State* state = luaL_newstate();

  luaL_openlibs(state);

  const std::string filename =
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine.lua";

  const auto load_error = luaL_loadfile(state, filename.data());

  lua_pcall(state, 0, 0, 0);

  const std::string str_var = "table.str";
  const std::string int_var = "integer";
  const std::string float_var = "floating_point";
  const std::string bool_var = "boolean";
  const std::string made_up_var = "not.real";

  const auto str = ode::lua::get<std::string>(state, str_var);
  const auto integer = ode::lua::get<int>(state, int_var);
  const auto floating = ode::lua::get<float>(state, float_var);
  const auto boolean = ode::lua::get<bool>(state, bool_var);

  ASSERT_EQ(std::string{"Hello!"}, str);
  ASSERT_EQ(3, integer);
  ASSERT_EQ(7.4f, floating);
  ASSERT_EQ(true, boolean);

#if defined(GSL_UNENFORCED_ON_CONTRACT_VIOLATION) && \
    GSL_UNENFORCED_ON_CONTRACT_VIOLATION

  const auto made_up_str = ode::lua::get<std::string>(state, made_up_var);
  const auto made_up_int = ode::lua::get<int>(state, made_up_var);
  const auto made_up_float = ode::lua::get<float>(state, made_up_var);
  const auto made_up_bool = ode::lua::get<bool>(state, made_up_var);

  ASSERT_EQ(std::string{"null"}, made_up_str);
  ASSERT_EQ(0, made_up_int);
  ASSERT_EQ(0, made_up_float);
  ASSERT_EQ(0, made_up_bool);

#elif defined(GSL_THROW_ON_CONTRACT_VIOLATION) && \
    GSL_THROW_ON_CONTRACT_VIOLATION

  ASSERT_ANY_THROW(ode::lua::get<std::string>(state, made_up_var));
  ASSERT_ANY_THROW(ode::lua::get<int>(state, made_up_var));
  ASSERT_ANY_THROW(ode::lua::get<float>(state, made_up_var));
  ASSERT_ANY_THROW(ode::lua::get<bool>(state, made_up_var));

#endif // defined(GSL_THROW_ON_CONTRACT_VIOLATION) && \
    GSL_THROW_ON_CONTRACT_VIOLATION

  lua_close(state);

  state = nullptr;
}

TEST(ode_lua_call, called)
{
  lua_State* state = luaL_newstate();

  luaL_openlibs(state);

  const std::string filename =
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "virtual_machine.lua";

  const auto load_error = luaL_loadfile(state, filename.c_str());

  lua_pcall(state, 0, 0, 0);

  const std::string add_func = "add";
  const std::string pow_func = "pow";

  const auto add_ret = ode::lua::call<int>(state, add_func, 4, 6);
  const auto pow_ret = ode::lua::call<int>(state, pow_func, 2, 3);

  ASSERT_EQ(10, add_ret);
  ASSERT_EQ(8, pow_ret);

  lua_close(state);

  state = nullptr;
}
