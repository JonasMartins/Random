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

# # retorna o inverso de um quaternio
def quaternion_i(q):
  qq = [[q[0][0],0,0,0]]
  qq[0][1] = q[0][1] * (-1) 
  qq[0][2] = q[0][2] * (-1)
  qq[0][3] = q[0][3] * (-1)
  return qq

def run_quaternion(u,q):
  x = q[0][0]; y = q[0][1]; z = q[0][2]; w = q[0][3]
  m = [
  [ (math.pow(w,2) + math.pow(x,2)) - (math.pow(y,2) - math.pow(z,2)),
    (2*x*y) - (2*w*z), (2*x*z) + (2*w*y), 0 ],
  [(2*x*y) + (2*w*z), (math.pow(w,2) - math.pow(x,2)) + (math.pow(y,2) - math.pow(z,2)),
  (2*y*z) - (2*w*x),0],
  [(2*x*z) - (2*w*y), (2*y*z) + (2*w*x), (math.pow(w,2) - math.pow(x,2)) - (math.pow(y,2) + math.pow(z,2)),0],
  [0,0,0,(math.pow(w,2) + math.pow(x,2)) + (math.pow(y,2) + math.pow(z,2))]
  ]
  return m
  # a = np.dot(u,qq)
  # return np.dot(q,a)

def main():

  
  v_trans = [90,50,0]
  v_scale = [2,2,2]


  v = np.array([[220,290,0,1]])
  vv = np.array([[-220,-290,0,1]])
 

  # m = Matrix(matrix = v)
  # m1 = Matrix(matrix = mx)

  # cisalhamento = Transformation(30,[0,0,0],[0,0,0],0).get_matrix(0)
  translacao = Transformation(0,v_trans,[0,0,0],0).get_matrix(6)
  # scala = Transformation(0,[0,0,0],v_scale,0).get_matrix(7)
  # rotacao = Transformation(0,[0,0,0],[0,0,0],270).get_matrix(9)
  # espelho = Transformation(0,[0,0,0],[0,0,0],0).get_matrix(11)

  axis = np.array([[7.776,-9.077,-7.569,0]])
  vector = np.array([[3.836],[11.37],[20.319],[1]])

  # q =  quaternion(axis,90)

  # vv = vector/la.norm(vector)

  # m = run_quaternion(vector,q)
  
  m = np.array(translacao)

  print np.dot(m,vector)
  

  

if __name__ == "__main__": main()
