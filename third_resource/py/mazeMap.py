#!/usr/bin/python
import pygame
from pygame.locals import *

import nn
the_network = nn.Network()

pygame.init()
screen = pygame.display.set_mode((640, 480), 0, 32)
pygame.display.set_caption("NN_maze")
screen.fill((255, 255, 255))

begin_pos = [240,220]

#screen settings
rc_wall=[0,0,0]
rc_space=[255,255,255]
rc_apple=[0,255,0]
rc_hero=[255,0,0]
rs = [10,10]

#map settings
mazeA=[[1,1,1,1,1,1,1,1,1,1,1,1,1,1],
       [1,3,0,0,0,0,0,0,0,0,0,0,2,1],
       [1,1,1,1,1,1,1,1,1,1,1,1,1,1]]

def screen_draw():
    global hero_pos
    rp = [begin_pos[0], begin_pos[1]]

    row_num=0
    rp[1]=begin_pos[1]
    for i in mazeA:
        rp[0] = begin_pos[0]
        col_num = 0
        for j in i:
            if j == 1:
                pygame.draw.rect(screen,rc_wall, Rect(rp,rs))
            elif j == 0:
                pygame.draw.rect(screen,rc_space, Rect(rp,rs))
            elif j ==2:
                pygame.draw.rect(screen,rc_apple, Rect(rp,rs))
            elif j ==3:
                pygame.draw.rect(screen,rc_hero, Rect(rp,rs))
                hero_pos=[row_num,col_num]
            rp[0] += 10
            col_num += 1
        rp[1] += 10
        row_num +=1

screen_draw()
pygame.display.update()

#sensor setup
#def check_wall():
#    if mazeA[hero_pos[0]][hero_pos[1]+1]==0:
#        return 1
#    else:
#        return 0
def camera_sensor():
    global face_fact
    if face_fact=="right":
        return mazeA[hero_pos[0]][hero_pos[1]+1]
    elif face_fact=="left":
        return mazeA[hero_pos[0]][hero_pos[1]-1]
    elif face_fact=="up":
        return mazeA[hero_pos[0]-1][hero_pos[1]]
    elif face_fact=="right":
        return mazeA[hero_pos[0]+1][hero_pos[1]]

def what_sensor(thing):
    if thing == 0:
        return 1
    if thing == 1:
        return 0.5
    if thing == 2:
        return 0

def move(result):
    if result==1:
        mazeA[hero_pos[0]][hero_pos[1]],\
        mazeA[hero_pos[0]][hero_pos[1]+1]=\
        mazeA[hero_pos[0]][hero_pos[1]+1],\
        mazeA[hero_pos[0]][hero_pos[1]]
        print mazeA
        return mazeA[hero_pos[0]][hero_pos[1]]

#system check
def check_crash(move_to):
    if move_to==1:
        return "crash"
    else:
        screen_draw()
        pygame.display.update()
        pygame.time.delay(500)


while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            exit()
        if event.type == KEYDOWN:
           move_to = move(the_network.run(check_wall()))
           check_crash(move_to)

