#!usr/bin/python
# encoding: utf-8
import pygame
import math

class Cam:
  
  """docstring for ClassName"""
  
  def __init__(self, pos=(0,0,0),rot=(0,0)):
     self.pos = list(pos)
     self.rot = list(rot)

  # rotacionando em torno do eixo x 
  def rotate_matrix(self,p,angle):
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


  def update(self,dt,key):
    
    s = dt/30

    if key[pygame.K_q]: self.pos[1]+=s 
    if key[pygame.K_e]: self.pos[1]-=s
    
    # rotation x 
    if key[pygame.K_p]:
      v = self.rotate_matrix((self.pos[0],self.pos[1],self.pos[2]),45)
      print('v: ', v)
      self.pos[0] = v[0]
      self.pos[1] = v[1]
      self.pos[2] = v[2]

    if key[pygame.K_UP]: self.pos[2]+=s
    if key[pygame.K_DOWN]: self.pos[2]-=s
    if key[pygame.K_LEFT]: self.pos[0]-=s
    if key[pygame.K_RIGHT]: self.pos[0]+=s
