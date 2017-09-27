#!/usr/bin/python
# encoding: utf-8

import math
from matrix_operations import Matrix

class Cisalhamento:

  def __init__(self,alfa):
    pass

  cyx = [ [1,0,0,0],
          [0,1,0,0],
          [0,0,1,0],
          [0,0,0,1] ]
  cyz = [ [1,0,0,0],
          [0,1,0,0],
          [0,0,1,0],
          [0,0,0,1] ]

  cxz= [ [1,0,0,0],
          [0,1,0,0],
          [0,0,1,0],
          [0,0,0,1] ]

  czx = [ [1,0,0,0],
          [0,1,0,0],
          [0,0,1,0],
          [0,0,0,1] ]
  czy = [ [1,0,0,0],
          [0,1,0,0],
          [0,0,1,0],
          [0,0,0,1] ]

  cxy = [ [1,0,0,0],
          [0,1,0,0],
          [0,0,1,0],
          [0,0,0,1] ]

















# m1 = Matrix(file = 'matriz1.txt')
# m2 = Matrix(file = 'matriz2.txt')


# o length do vetor é o numero de colunas
# a quantidade de cada elemento é o numero de linhas
# v = [[0,0,7,1]]

# m3 = Matrix(rows = 4,columns = 4)


# m1.showMatrix()
# m2.showMatrix()
# m3.generate_identity()
# m3.showMatrix()
# 

# def checkTimes(matrix1,matrix2):
#   if matrix1.get_columns() != matrix2.get_rows():
#     print('Impossível multiplicar as matrizes dadas')
#     sys.exit()
#   return

# def timesMetrix(m1,m2,scalar):
#   m3 = None
#   if scalar is not None:
#     m3 = Matrix(rows = m1.get_rows(),columns = m1.get_columns())
#     for i in range(0,m3.get_variable('columns')):
#       for j in range(0,m3.get_variable('rows')): 
#         m3.get_variable('matrix')[i][j] = m1.get_variable('matrix')[i][j] * scalar

#   else:
#     checkTimes(m1,m2)
    
#     h = m1.get_rows()
#     w = m2.get_columns()
#     y = m2.get_rows()

#     m3 = Matrix(rows = h,columns = w)
#     for i in range(0,w):
#       for j in range(0,h):
#         for k in range(0,y):
#           m3.get_variable('matrix')[i][j] += m1.get_variable('matrix')[i][k] * m2.get_variable('matrix')[k][j]

#   return m3

# def main():
#   m3 = Matrix(file='matriz1.txt')
#   # m4 = Matrix(file='matriz1.txt')
#   m5 = Matrix(matrix = v)
#   # m7 = timesMetrix(m5,None,5)
#   # m7.showMatrix()
#   t = Transformation()
#   t.set_variable('matrix1',m5)

if __name__ == "__main__": main()