#!/usr/bin/env python3

import random

def generate_random_tree():
  x = random.randint(1, 1000)
  
  return f"{x}({generate_random_forest()})"

# A function that generates a random sequence of string of the form "x(Y)"
def generate_random_forest(p = 1):
  x = random.randint(1, 1000)
  px = (0.99 / p) * 100

  Y = ""

  if px > 0.5:
    y = random.randint(0, 10)
    py = random.random()

    if (py > 0.8):
      for _ in range(y):
        Y += generate_random_forest()

  return f"{x}({Y})"


print(generate_random_tree())


