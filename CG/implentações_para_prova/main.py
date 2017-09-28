#!/usr/bin/python
# encoding: utf-8

  
# PRODUTO VETORIAL USANDO NUMPY https://docs.scipy.org/doc/numpy-dev/user/quickstart.html
# import numpy as np
# a = np.array([1,0,0])  
# b = np.array([0,1,0])  
# print np.cross(a,b)
import sys
from transformations import Transformation
from matrix import Matrix


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

def main():

	v_trans = [-1,-1,-1]
	v_scale = [2,2,2]


	v = [[-3,12,-7,1]]

	mx = [[12,7,3,0],
				[4,5,6,0],
				[7,8,9,0],
				[0,0,0,1]]
	
	m = Matrix(matrix = v)
	m1 = Matrix(matrix = mx)
	cisalhamento = Transformation(30,[0,0,0],[0,0,0],0).get_matrix(0)
	translacao = Transformation(0,v_trans,[0,0,0],0).get_matrix(6)
	scala = Transformation(0,[0,0,0],v_scale,0).get_matrix(7)
	rotacao = Transformation(0,[0,0,0],[0,0,0],45).get_matrix(9)
	
	aux = Matrix(matrix = rotacao)

	# m.show_dimensions()
	# m1.show_dimensions()
	mfinal = timesMetrix(m,aux,None)
	# mfinal.show_dimensions()
	mfinal.showMatrix()

	# for i in range(0,len(v)):
	# 	for j in range(0,len(mx[0])):
	# 		for k in range(0,len(mx)):
	# 			print('r[{}][{}] += :{} * {}'.format(i,j,v[i][k],mx[k][j])) 

if __name__ == "__main__": main()