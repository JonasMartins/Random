''' pg_sprite_keys1.py
move a sprite rect with the arrow keys
see also ...
http://www.pygame.org/docs/ref/sprite.html
http://www.pygame.org/docs/ref/time.html
'''
import pygame as pg
pg.init()
# set screen size
width = 640
height = 480
screen = pg.display.set_mode((width, height))
pg.display.set_caption("move with arrow keys (escape key to exit)")
# color (r, g, b) tuple, values 0 to 255
white = (255, 255, 255)
background = pg.Surface(screen.get_size())
background.fill(white)
# pick an image file you have in the working folder
# or use full path
# load image of sprite
sprite = pg.image.load("SpaceShip.gif")
# get image space, rectangle ulc, lrc coordinates
sprite_rect = sprite.get_rect()
# test
print(sprite_rect)  # <rect(0, 0, 64, 64)>
# initial position of sprite, center of screen
sprite_rect.centerx = (width//2)
sprite_rect.centery = (height//2)
screen.blit(background, (0, 0))
screen.blit(sprite, sprite_rect)
pg.display.flip()
clock = pg.time.Clock()
# create the obligatory event loop
while 1:
    # limit runtime speed to 30 frames/second
    clock.tick(30)
    pg.event.pump()
    # a key has been pressed
    keyinput = pg.key.get_pressed()
    # press escape key to quit game
    if keyinput[pg.K_ESCAPE]:
        raise SystemExit
    # optional exit on window corner x click
    for event in pg.event.get():
        if event.type == pg.QUIT:
            pg.quit()
            raise SystemExit
    # check arrow keys
    # move sprite in direction of arrow by 2 pixels
    if keyinput[pg.K_LEFT]:
        sprite_rect.centerx -= 2
    elif keyinput[pg.K_RIGHT]:
        sprite_rect.centerx += 2
    elif keyinput[pg.K_UP]:
        sprite_rect.centery -= 2
    elif keyinput[pg.K_DOWN]:
        sprite_rect.centery += 2
    screen.blit(background, (0,0))
    screen.blit(sprite, sprite_rect)
    # update display
    pg.display.flip()