#!usr/bin/python
# encoding: utf-8

import pygame, sys, math
from time import time
from Cam import Cam

start = time() 


# some colors
BLACK = (0,0,0)
WHITE = (255,255,255)
RED = (255,0,0)

pygame.init()

def rotate2d(pos,radian):
    x,y = pos
    s,c = math.sin(radian),math.cos(radian)
    return x*c-y*s, y*c-x*s


def run():
  
  verts = (-1,-1,-1),(1,-1,-1),(1,1,-1),(-1,1,-1),(-1,-1,1),(1,-1,1),(1,1,1),(-1,1,1)
  edges = (0,1),(1,2),(2,3),(3,0),(4,5),(5,6),(6,7),(7,4),(0,4),(1,5),(2,6),(3,7)
  verts2 = (3,3,3),(5,3,3),(5,5,3),(3,5,3),(3,3,5),(5,3,5),(5,5,5),(3,5,5)
  elapsed = 0

  display_width,display_height = 1200,600
  cx, cy = display_width//2, display_height//2

  scenario = pygame.display.set_mode((display_width,display_height))
  
  # window title
  pygame.display.set_caption('3D Models')

  # game clock
  clock = pygame.time.Clock()

  cam = Cam((0,0,-5))

  # pygame.event.get()
  # pygame.mouse.get_rel()

  # radian = 0
  #  program never run more than 20 seconds
  
  while elapsed < 30:

    dt = clock.tick(30)
    key = pygame.key.get_pressed()

    # saindo quando fechamos a janela
    for event in pygame.event.get():
      if event.type == pygame.QUIT: pygame.quit(); sys.exit()
      # cam.events(event)

    scenario.fill(BLACK)

    for edge in edges:
      points = []
      for x,y,z in (verts[edge[0]],verts[edge[1]]):
        
        x-=cam.pos[0]       
        y-=cam.pos[1]
        z-=cam.pos[2]

        x,z = rotate2d((x,z),cam.rot[1])
        y,z = rotate2d((y,z),cam.rot[0])

        f = 300/(z+0.1)    
        x,y = x*f, y*f
        
        # add origem de cada vertice
        points+=[(cx+int(x), cy+int(y))]

      # line(Surface, color, start_pos, end_pos, width=1)
      # Desenhe um segmento de linha reta em uma superfície. Não há tampas de 
      # extremidade, as extremidades são ajustadas para linhas grossas.
      pygame.draw.line(scenario,WHITE,points[0],points[1],1)
      # print(points[0],points[1])
      # print(radian)
    # for edge in edges:
    #   points2 = []
    #   for x,y,z in (verts2[edge[0]],verts2[edge[1]]):
        
    #     x-=cam.pos[0]       
    #     y-=cam.pos[1]
    #     z-=cam.pos[2]

    #     f = 200/(z)   
    #     x,y = x*f, y*f        
    #     points2+=[(cx+int(x), cy+int(y))]
      
    #   pygame.draw.line(scenario,RED,points2[0],points2[1],1)
    
    pygame.display.flip()
    
    cam.update(dt,key)

    elapsed = time() - start

def main():
  run()

if __name__ == "__main__": main()