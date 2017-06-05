#!/usr/bin/env python3

import pygame
from pygame import gfxdraw
pygame.gfxdraw = gfxdraw

WIDTH, HEIGHT = 600, 400
START_WIDTH, START_HEIGHT = 90, 90

pygame.init()
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Python: Baum des Pythagoras")
pygame.mouse.set_visible(1)
screen.fill((255, 255, 255))
clock = pygame.time.Clock()

class Pos():
    def __init__(self, x, y):
        self.x = x
        self.y = y

class Rect():
    # a: top left
    # b: top right
    # c: bottom right
    # d: bottom left
    def __init__(self, a, b, c, d, color=(0, 0, 0)):
        self.a = a
        self.b = b
        self.c = c
        self.d = d
        self.color = color

    def draw(self):
        pygame.draw.line(screen, self.color, [self.a.x, self.a.y], [self.b.x, self.b.y])
        pygame.draw.line(screen, self.color, [self.b.x, self.b.y], [self.c.x, self.c.y])
        pygame.draw.line(screen, self.color, [self.c.x, self.c.y], [self.d.x, self.d.y])
        pygame.draw.line(screen, self.color, [self.d.x, self.d.y], [self.a.x, self.a.y])

    def triangle(self):
        x = self.a.x + ((self.b.x - self.a.x) / 2) + ((self.a.x - self.d.x) / 2)
        y = self.a.y + ((self.b.y - self.a.y) / 2) + ((self.a.y - self.d.y) / 2)
        return Pos(x, y)

    def leftRect(self, t):
        a = Pos(self.a.x + (t.x - self.b.x), self.a.y + (t.y - self.b.y))
        b = Pos(t.x + (t.x - self.b.x), t.y + (t.y - self.b.y))
        c = t
        d = self.a
        return Rect(a, b, c, d)

    def rightRect(self, t):
        a = Pos(t.x + (t.x - self.a.x), t.y + (t.y - self.a.y))
        b = Pos(self.b.x + (t.x - self.a.x), self.b.y + (t.y - self.a.y))
        c = self.b
        d = t
        return Rect(a, b, c, d)


rect = Rect(Pos(WIDTH / 2 - START_WIDTH / 2, HEIGHT - START_HEIGHT),
            Pos(WIDTH / 2 + START_WIDTH / 2, HEIGHT - START_HEIGHT),
            Pos(WIDTH / 2 + START_WIDTH / 2, HEIGHT),
            Pos(WIDTH / 2 - START_WIDTH / 2, HEIGHT))

def draw(rect, i):
    rect.draw()
    if i >= 0:
        t = rect.triangle()
        left = rect.leftRect(t)
        right = rect.rightRect(t)

        draw(left, i-1)
        draw(right, i-1)


draw(rect, 12)

pygame.display.flip()
done = False
while not done:
    clock.tick(30)

    for event in pygame.event.get():
        if event.type == pygame.QUIT or (event.type == pygame.KEYDOWN and event.key == pygame.K_ESCAPE):
            done = True
            # print("Bye!")

