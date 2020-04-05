-- Copyright (c) 2018–2020 Antti Kivi
-- Licensed under the Effective Elegy Licence

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
