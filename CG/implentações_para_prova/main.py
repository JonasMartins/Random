#!/usr/bin/python
# encoding: utf-8

  
# PRODUTO VETORIAL USANDO NUMPY https://docs.scipy.org/doc/numpy-dev/user/quickstart.html

import sys
import numpy as np
from matrix import Matrix
from numpy import linalg as la
from transformations import Transformation


def normalize(matrix):
  n = la.norm(matrix)
  for i in range(0,matrix.shape[0]):
    for j in range(0,matrix.shape[1]):
      print '{0}' .format(matrix[i][j] / float(n))
  
def main():

  
  v_trans = [-1,-1,-1]
  v_scale = [2,2,2]


  v = np.array([[220,290,0,1]])
  vv = np.array([[-220,-290,0,1]])
  
  v = [[1,0,0,-220],
        [0,1,0,-290],
        [0,1,0,0],
        [0,0,0,1]]

  mx = [[-0.9164,0,-0.43664,220],
  			[0,1,0,0],
  			[-0.43664,0,0.89974,290],
  			[0,0,0,1]]


  # m = Matrix(matrix = v)
  # m1 = Matrix(matrix = mx)

  cisalhamento = Transformation(30,[0,0,0],[0,0,0],0).get_matrix(0)
  translacao = Transformation(0,v_trans,[0,0,0],0).get_matrix(6)
  scala = Transformation(0,[0,0,0],v_scale,0).get_matrix(7)
  rotacao = Transformation(0,[0,0,0],[0,0,0],270).get_matrix(9)
  espelho = Transformation(0,[0,0,0],[0,0,0],0).get_matrix(11)
  #print rotacao
  # final =  np.dot(mx,rotacao)
  # print np.dot(final,v)
  # aux = Matrix(matrix = rotacao)
  # mfinal = timesMetrix(m,aux,None)
  # mfinal.showMatrix()
  print np.dot(v,mx)

  # m = np.array(v) 
  # n = np.array(espelho)

  # # multiplicação de matrizes numpy
  # print m
  # print '----------------------------'
  # print n
  # print '----------------------------'
  
  # # mutiplicar por escalar 
  # result =  np.dot(m,10)
  
  
  # # norma de um vetor 
  # print 'result: {0} norm: {1}' .format(result,la.norm(result))
  # normalize(result)

  # normalizando na classe matrix
  # print r.get_variable('norm')
  #norma = np.array(r.get_variable('normalized'))

  #print norma


if __name__ == "__main__": main()

"""

def checkTimes(matrix1,matrix2):
  if matrix1.get_columns() != matrix2.get_rows():
    print('Impossível multiplicar as matrizes dadas')
    sys.exit()
  return

def timesMetrix(m1,m2,scalar):
  m3 = None
  if scalar is not None:
    m3 = Matrix(rows = m1.get_rows(),columns = m1.get_columns())
    for i in range(0,m3.get_variable('columns')):
      for j in range(0,m3.get_variable('rows')): 
        m3.get_variable('matrix')[i][j] = m1.get_variable('matrix')[i][j] * scalar

  else:
    checkTimes(m1,m2)
    
    h = m1.get_rows()
    w = m2.get_columns()
    y = m2.get_rows()

    m3 = Matrix(rows = h,columns = w)
    for i in range(0,h): 
      for j in range(0,w): 
        for k in range(0,y): 
          m3.get_variable('matrix')[i][j] += m1.get_variable('matrix')[i][k] * m2.get_variable('matrix')[k][j]
  return m3

  """