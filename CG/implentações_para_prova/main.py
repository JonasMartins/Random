#!/usr/bin/python
# encoding: utf-8

  
# PRODUTO VETORIAL USANDO NUMPY https://docs.scipy.org/doc/numpy-dev/user/quickstart.html

import sys
import numpy as np
import math
from matrix import Matrix
from numpy import linalg as la
from transformations import Transformation

# retorna o quartenio baseado no eixo a ser rotacionado
def quaternion(v,theta):
  # vv é meu eixo normalizado 
  vv = v/la.norm(v)
  t = theta/2
  q = np.array([[math.cos(t),
    (vv[0][0] * math.sin(t)),
    (vv[0][1] * math.sin(t)),
    (vv[0][2] * math.sin(t))]]) 
  return q

# retorna o inverso de um quaternio
def quaternion_i(q):
  qq = [[q[0][0],0,0,0]]
  qq[0][1] = q[0][1] * (-1) 
  qq[0][2] = q[0][2] * (-1)
  qq[0][3] = q[0][3] * (-1)
  return qq

def run_quaternion(u,q,q_i):
  a = np.dot(q,u)
  return np.dot(q_i,a[0][0])

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

  # cisalhamento = Transformation(30,[0,0,0],[0,0,0],0).get_matrix(0)
  # translacao = Transformation(0,v_trans,[0,0,0],0).get_matrix(6)
  # scala = Transformation(0,[0,0,0],v_scale,0).get_matrix(7)
  # rotacao = Transformation(0,[0,0,0],[0,0,0],270).get_matrix(9)
  # espelho = Transformation(0,[0,0,0],[0,0,0],0).get_matrix(11)

  axis = np.array([[1,1,1,0]])
  vector = np.array([[7],[2],[5],[0]])

  q =  quaternion(axis,240)
  qq = np.array(quaternion_i(q))
  # print q
  # print qq

  print run_quaternion(vector,q,qq)

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
