------------------------ virtual_machine_benchmark.lua -------------------------
--
--                        Obliging Ode & Unsung Anthem
--
-- This source file is part of the Obliging Ode and Unsung Anthem open source
-- projects.
--
-- Copyright (c) 2018 Venturesome Stone
-- Licensed under GNU Affero General Public License v3.0
--
-------------------------------------------------------------------------------

table = {
  str = "S!",
  greeting = "Hello there!",
  int = 5,
  integer = 3,
  f = 7.4,
  floating_point = 2.9,
  b = true,
  boolean = true
}

str = "S!"
greeting = "Hello there!"
int = 5
integer = 3
f = 7.4
floating_point = 2.9
b = true
boolean = true

function add(x, y)
  return x + y
end

function pow(x, y)
  return math.pow(x, y) -- x ^ y
end
