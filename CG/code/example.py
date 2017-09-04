#!usr/bin/python

import pygame, sys, math

from time import time

start = time() 
elapsed = 0

def rotate2d(pos, rad): x,y=pos; s,c = math.sin(rad), math.cos(rad); return (x*c)-(y*s), (y*c)+(x*s) 

class Cam:
  def __init__(self,pos=(0,0,0),rot=(0,0)):
    self.pos = list(pos)
    self.rot = list(rot)

  def events(self, event):
    if event.type == pygame.MOUSEMOTION:
      x,y = event.rel
      #200 is speed
      x/=5; y/=5
      self.rot[0]+=y; self.rot[1]+=x


  def update(self,dt,key):
    
    s = dt/30

    if key[pygame.K_q]: self.pos[1]+=s 
    if key[pygame.K_e]: self.pos[1]-=s

    if key[pygame.K_UP]: self.pos[2]+=s 
    if key[pygame.K_DOWN]: self.pos[2]-=s
    if key[pygame.K_LEFT]: self.pos[0]-=s
    if key[pygame.K_RIGHT]: self.pos[0]+=s

pygame.init()
w,h = 600, 600; cx,cy = w//2, h//2
screen = pygame.display.set_mode((w,h))
clock = pygame.time.Clock() 

verts = (-1,-1,-1),(1,-1,-1),(1,1,-1),(-1,1,-1),(-1,-1,1),(1,-1,1),(1,1,1),(-1,1,1)
edges = (0,1),(1,2),(2,3),(3,0),(4,5),(5,6),(6,7),(7,4),(0,4),(1,5),(2,6),(3,7)

cam = Cam((0,0,-5))

# manuseio do mouse para usar no pygame
pygame.event.get(); pygame.mouse.get_rel()
pygame.mouse.set_visible(1); pygame.event.set_grab(0)


# o programa nunca passara de 10 segundos! 

while elapsed < 10:
#while True:   
  dt = clock.tick(30)

  for event in pygame.event.get():
    if event.type == pygame.QUIT: pygame.quit(); sys.exit()
    cam.events(event)


  screen.fill((255,255,255))

  for edge in edges:
    points = []
    for x,y,z  in (verts[edge[0]],verts[edge[1]]):
      
      x-=cam.pos[0]
      y-=cam.pos[1]
      z-=cam.pos[2]
      
      # rotacionando no eixo y depois no eixo x 
      x,z = rotate2d((x,z),cam.rot[1])
      y,z = rotate2d((y,z),cam.rot[0])

      f = 200/z
      x,y = x*f, y*f
      points+=[(cx+int(x), cy+int(y))]

    pygame.draw.line(screen,(0,0,0), points[0],points[1],1)
  

  pygame.display.flip()
  key = pygame.key.get_pressed()
  cam.update(dt,key)
  elapsed = time() - start