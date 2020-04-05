/// The tests of the Lua stack utility functions.
/// \file
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/lua/stack.h"

#include "ode/config.h"
#include "ode/filesystem/path.h"
#include "ode/lua/script.h"

#include <gtest/gtest.h>

TEST(ode_lua_to_stack, is_set_to_stack)
{
  lua_State* l = luaL_newstate();

  const std::string filename =
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack.lua";

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  const bool is_put = ode::lua::to_stack(l, "testing.lua.stack");

  ASSERT_EQ(3, lua_gettop(l));

  lua_pop(l, 3);

  lua_close(l);
}

TEST(ode_lua_push, is_pushed_to_stack)
{
  lua_State* l = luaL_newstate();

  const std::string filename =
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "stack.lua";

  luaL_openlibs(l);

  const auto error_code = luaL_loadfile(l, filename.c_str());

  lua_pcall(l, 0, 0, 0);

  ode::lua::push(l, 3, 2.5f, std::string{"Hello, world!"}, true);

  ASSERT_EQ(4, lua_gettop(l));

  lua_pop(l, 4);

  lua_close(l);
}
