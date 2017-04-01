from pygame import *
from math import *

screen = display.set_mode((1920,1080))
m = image.load("Beautiful.jpg")
screen.blit(m,(0,0))

mon = open("mona.py","w")
mon.write("""import pygame
from pygame.locals import *
from math import *

screen = pygame.display.set_mode((1920,1080))
""")

running = True
display.flip()
for x in range(0,1920,5):
    for y in range(0,1080,5):
        c = str(screen.get_at((x,y)))
        mon.write("pygame.draw.rect(screen,"+c+",("+str(x)+","+str(y)+",4,4))\n")
    mon.write("pygame.display.flip()\n")
    mon.write("NewImage = 'NewImage'\n")
    mon.write("pygame.image.save(screen,NewImage)\n")

mon.write("""running = True
while running:
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False
        if event.type == KEYDOWN:
            if event.key == K_q:
                exit()
quit()""")

mon.close()