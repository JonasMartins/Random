import pygame

pygame.init()

display_width = 800
display_height = 600

black = (0,0,0)
white = (255,255,255)
red = (255,0,0)

carImg = pygame.image.load('car_72.png')

def car(x,y):
  gameDysplay.blit(carImg, (x,y))


x = (display_width * 0.45)
y = (display_height * 0.8)

x_change = 0

gameDysplay = pygame.display.set_mode((display_width,display_height))

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

    if event.type == pygame.KEYDOWN:
      if event.key == pygame.K_LEFT:
        x_change = -15
      if event.key == pygame.K_RIGHT:
        x_change = 15

    if event.type == pygame.KEYUP:
      if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
        x_change = 0

  x += x_change
        
  gameDysplay.fill(white)
  car(x,y)
  pygame.display.update()

  # frames per second
  clock.tick(20)

pygame.quit()
quit()