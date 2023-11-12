#!/usr/bin/env python3

import random

N = 0

def random_node():
  global N
  N = N + 1
  return random.randint(1, 1000)

def generate_random_tree():
  x = random_node()
  
  return f"{x}({generate_random_forest()})"

# A function that generates a random sequence of strings of the form "x(Y)" 
# where x is an integer and Y is another sequence of the same form
def generate_random_forest(p = 1):
  x = random_node()
  px = random.random()

  Y = ""

  pr = 1 - (p/50)

  if px < pr:
    y = random.randint(0, 10)
    py = random.random()

    if py < pr:
      for _ in range(y):
        Y += generate_random_forest(len(Y) + p)

  return f"{x}({Y})"


print(generate_random_tree())
print(f"\n{N}")


