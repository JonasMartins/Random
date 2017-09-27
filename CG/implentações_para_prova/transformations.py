#!/usr/bin/python
# encoding: utf-8
# 

from matrix_operations import Matrix

class Transformation:
  
  def __init__(self, **kwargs):
    self.variables = kwargs

  def set_variable(self,k,v):
    self.variables[k] = v

  def get_variable(self,k):
    return self.variables.get(k,None)
   

  # # checar possibilidade de multipliçãoo entre as matrizes
  # def __checkTimes(self):
  #   if(self.matrix1.get_columns() != self.matrix2.get_rows()):
  #     print('Impossível multiplicar as matrizes dadas')
  #   return

  # def timesMetrix(self):

  #   h = self.matrix1.get_rows()
  #   w = self.matrix2.get_columns()
  #   y = self.matrix2.get_rows()

  #   self.m3 = Matrix(h,w)

  #   for i in range(0,h):
  #     for j in range(0,w):
  #       for k in range(0,y):
  #         m3[i][j] += m1[i][k] * m2[k][j]

  #   return m3

    