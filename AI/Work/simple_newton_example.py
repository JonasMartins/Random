#!/usr/bin/env python
'''
  find x such that y is zero using newton's method
'''

import logging
import math

def f(x):
  '''
    the formula entered will be optimized to zero using Newton's method
    ENTER YOUR FORMULA HERE
  '''
  return x * math.log(x, 2) - 1e6

def newton():
  x = 10
  step = 1e-3
  max_error = 1e-2
  max_step = 100
  y = f(x)
  while abs(y) > max_error:
    y = f(x) 
    new_y = f(x + step) 
    gradient = (new_y - y) / step
    logging.debug('x: {:.2f} y: {:.2f} gradient: {:.2f}'.format(x, y, gradient))
    x = x - y / gradient

    max_step -= 1
    if max_step == 0:
      logging.info('steps exhausted')
      break

  print('Solution: x: {:.2f} y: {:.2f}'.format(x, y))

if __name__ == '__main__':
  logging.basicConfig(format='%(asctime)s %(levelname)s %(message)s', level=logging.DEBUG)
  newton()