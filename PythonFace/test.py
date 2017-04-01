# -*- coding:utf-8 -*-

import os
import sys
import termios
import pygame
from pygame.locals import *
from sys import exit

pygame.init()
# 初始化pygame对象
screen = pygame.display.set_mode((1920, 1080),FULLSCREEN)
# 设置显示的屏幕的模式和像素大小

image1_filename = 'img/1.jpg'
image2_filename = 'img/2.jpg'
image3_filename = 'img/3.jpg'
# 对于所需要的背景图命名

bgimage1 = pygame.image.load(image1_filename).convert()
bgimage2 = pygame.image.load(image2_filename).convert()
bgimage3 = pygame.image.load(image3_filename).convert()
# 将三张背景图片都加载和转化
bgimage = [bgimage1, bgimage2, bgimage3]

x1,y1=0,0



x1, y1 = 0, 0
# 给出第一张背景图左上角的坐标

while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            exit()
        if event.type == KEYDOWN:
            exit()
    # 事件捕捉使得用户退出程序

    x1 -= 2 #通过改变数值能够改变滑动的速度
    if x1 <= -1920:
        bgimage = bgimage[1:]+bgimage[:1]


        # 每当列表中的第一张图片左移动至完全消失的时候，将第一张图片加到列表的末尾
        bgimage1, bgimage2, bgimage3 = bgimage
        x1 = 0


    screen.blit(bgimage1, (x1, y1))
    screen.blit(bgimage2, (x1+1920, y1))
    screen.blit(bgimage3, (x1+1920, y1))
    # 把三张背景图依次画到屏幕上

    pygame.display.update()




    # 使得pygame对象不断刷新
