from random import *

n = 1400
m = n
print(1, n, m)

us = list(range(n))
shuffle(us)

for i in range(n):
    print(us[i], us[(i + 1) % n])
