#!usr/bin/python3

import math

def rotate_matrix(p,angle):
  s,c = math.sin(angle),math.cos(angle)
  
  aux = [p[0],p[1],p[2],1]
  
  rx = [[1,0,0,0],
        [0,c,s,0],
        [0,s,c,0],
        [0,0,0,1]]

  rx[1][2] *= -1
  vector = [0,0,0,0]
  
  for i in range(0,4): 
    for j in range(0,4):
      vector[i] += aux[i] * rx[i][j]

  vector[1] = round(vector[1],3)
  vector[2] = round(vector[2],3)
  return vector

x = (-1,-1,-1)

print(rotate_matrix(x,30))