#!/usr/bin/python
# encoding: utf-8
# 

from matrix_operations import Matrix

class Transformation:
  
  def __init__(self,m1,m2):
    m1.__class__ = Matrix
    m2.__class__ = Matrix
    
    self.matrix1 = m1 #Matrix(matrix = m1)
    self.matrix2 = m2 # Matrix(matrix = m2)
    self.__checkTimes()

  # # checar possibilidade de multipliçãoo entre as matrizes
  def __checkTimes(self):
    if(self.matrix1.get_columns() != self.matrix2.get_rows()):
      print('Impossível multiplicar as matrizes dadas')
    return

  def timesMetrix(self):

    h = self.matrix1.get_rows()
    w = self.matrix2.get_columns()
    y = self.matrix2.get_rows()

    self.m3 = Matrix(h,w)

    for i in range(0,h):
      for j in range(0,w):
        for k in range(0,y):
          m3[i][j] += m1[i][k] * m2[k][j]

    return m3

    