from sys import argv
from math import *

n = int(argv[1])
mp = [["."] * (2 * n + 1) for i in range(2 * n + 1)]

def set_pixel_to_black(x, y):
    mp[n + x][n + y] = '#'

def draw_circle_perimeter(r):
    for x in range(-r, r + 1):
        y = round(sqrt(r ** 2 - x ** 2))
        set_pixel_to_black(x, y)
        set_pixel_to_black(x, -y)
        set_pixel_to_black(y, x)
        set_pixel_to_black(-y, x)

for r in range(n + 1):
    draw_circle_perimeter(r)

print("\n".join(map(lambda c: "".join(c), mp)))

for i in range(n + 1):
    for j in range(i, n + 1):
        if round(sqrt(i ** 2 + j ** 2)) <= r:
            if mp[i + n][j + n] == '.':
                print(i, j)
