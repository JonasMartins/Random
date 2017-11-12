#!usr/bin/python
# encoding: utf-8
import pygame
import math

class Cam:
  
  """docstring for ClassName"""
  
  def __init__(self, pos=(0,0,0),rot=(0,0)):
     self.pos = list(pos)
     self.rot = list(rot)
     self.x = 0
     self.y = 0

  # def events(self,event):
  #   if event.type == pygame.MOUSEMOTION:
  #     self.rot[0]+=0.0001;self.rot[1]+=0.0001;

  def update(self,dt,key):
    
    s = dt/30

    if key[pygame.K_q]: self.pos[1]+=s 
    if key[pygame.K_e]: self.pos[1]-=s
    

    if key[pygame.K_w]: self.pos[2]+=s
    if key[pygame.K_s]: self.pos[2]-=s
    if key[pygame.K_a]: self.pos[0]-=s
    if key[pygame.K_d]: self.pos[0]+=s
