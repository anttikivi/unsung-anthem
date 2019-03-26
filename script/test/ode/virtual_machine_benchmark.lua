------------------------ virtual_machine_benchmark.lua -------------------------
--
--                        Obliging Ode & Unsung Anthem
--
-- This source file is part of the Obliging Ode and Unsung Anthem open source
-- projects.
--
-- Copyright (C) 2019 Antti Kivi
-- All rights reserved
--
-------------------------------------------------------------------------------

table = {
  str = "S!",
  greeting = "Hello there!",
  int = 5,
  integer = 3,
  f = 7.4,
  float = 3.664,
  floating_point = 2.9,
  b = true,
  bool=false,
  boolean = true
}

str = "S!"
greeting = "Hello there!"
int = 5
integer = 3
f = 7.4
float = 3.664
floating_point = 2.9
b = true
boolean = true

function add(x, y)
  return x + y
end

function pow(x, y)
  return math.pow(x, y) -- x ^ y
end
