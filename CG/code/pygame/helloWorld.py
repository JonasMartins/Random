import pygame

pygame.init()

gameDysplay = pygame.display.set_mode((800,600))

# window title
pygame.display.set_caption('A bit Racy')

# game clock
clock = pygame.time.Clock()

crashed = False

while not crashed:

  # get all events
  for event in pygame.event.get():
    if event.type == pygame.QUIT:
      crashed = True

    print(event)

  pygame.display.update()

  # frames per second
  clock.tick(20)

pygame.quit()
quit()